#include "ft_traceroute.h"

g_traceroute traceroute;

void int_handler(int signo) {
    exit_clean(traceroute.sockfd, ERROR_SIGINT);
    (void) signo;
}

void create_socket() {
    struct timeval timeout;

    traceroute.sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (traceroute.sockfd < 0) {
        fprintf(stderr, "%s: socket: %s\n", PROGRAM_NAME, strerror(errno));
        exit(ERROR_SOCKET_OPEN);
    }
}

void resolve_server_addr() {
    int status;
    struct sockaddr_in *server_addrs;

    traceroute.server_addr.sin_family = AF_INET;   // IPv4
    traceroute.server_addr.sin_port = 0;           // Use default port
    status = inet_pton(AF_INET, traceroute.args.host, &traceroute.server_addr.sin_addr);
    if (status == 0) {   // Input is not an IPv4 address, try resolving as a domain name
        if (!(server_addrs = ft_gethostbyname(traceroute.args.host, 1))) {
            fprintf(stderr, "%s: cannot resolve %s: Unknow host\n", PROGRAM_NAME,
                    traceroute.args.host);
            exit_clean(traceroute.sockfd, ERROR_RESOLVING_HOST);
        }
        traceroute.server_addr.sin_addr = server_addrs[0].sin_addr;   // Use first address
    } else if (status < 0) {
        fprintf(stderr, "%s: inet_pton: %s\n", PROGRAM_NAME, strerror(errno));
        exit_clean(traceroute.sockfd, ERROR_INET_PTON);
    }
}

int main(int argc, char *argv[]) {
    set_args_structure();
    parse_args(argc, argv);
    create_socket();
    signal(SIGINT, int_handler);
    resolve_server_addr();
    print_traceroute_address_infos();
    traceroute.final_packet_received = false;
    for (traceroute.current_ttl = 1; traceroute.current_ttl < traceroute.args.max_hops;
         traceroute.current_ttl++) {
        // Set TTL
        if (setsockopt(traceroute.sockfd, IPPROTO_IP, IP_TTL, &traceroute.current_ttl,
                       sizeof(int)) < 0) {
            fprintf(stderr, "%s: setsockopt: %s\n", PROGRAM_NAME, strerror(errno));
            exit_clean(traceroute.sockfd, ERROR_SOCKET_OPTION);
        }
        // Reset packets received
        for (unsigned int i = 0; i < traceroute.args.nqueries; i++) {
            ft_bzero(&traceroute.packets_received, sizeof(t_packet_received));
        }
        // Send and receive packets for current TTL nqueries times and fill packets_received
        for (unsigned int packet_number = 0; packet_number < traceroute.args.nqueries;
             packet_number++) {
            send_package(packet_number);
            receive_package(packet_number);
        }
        print_current_ttl_stats();
        if (traceroute.final_packet_received) {
            break;
        }
    }
    close(traceroute.sockfd);
    return 0;
}