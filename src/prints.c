#include "ft_traceroute.h"

void print_traceroute_address_infos() {
    char ip_address[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &(traceroute.server_addr.sin_addr), ip_address, INET_ADDRSTRLEN);

    printf("traceroute to %s (%s), %i hops max, %lu byte packets\n", traceroute.args.host,
           ip_address, traceroute.args.max_hops, sizeof(struct icmp));
}

void print_current_ttl_stats() {
    char buffer[1024];
    unsigned int len = 0;
    bool server_addr_added = false;
    unsigned int count_failed_packets = 0;
    char *dns_name;

    len += snprintf(buffer + len, sizeof(buffer) - len, "%2i  ", traceroute.current_ttl);

    for (unsigned int i = 0; i < traceroute.args.nqueries; i++) {
        if (traceroute.packets_received[i].received) {
            if (!server_addr_added) {
                server_addr_added = true;
                dns_name = ft_reverse_dns_lookup(
                    (struct sockaddr *) &traceroute.packets_received[i].server_addr, NI_MAXHOST);
                len += snprintf(buffer + len, sizeof(buffer) - len, "%s ", dns_name);
                len += snprintf(buffer + len, sizeof(buffer) - len, "(%s) ",
                                inet_ntoa(traceroute.packets_received[i].server_addr.sin_addr));
            }
            len += snprintf(buffer + len, sizeof(buffer) - len, "%.3lf ms ",
                            traceroute.packets_received[i].rtt);
        } else {
            count_failed_packets++;
        }
    }

    while (count_failed_packets--) {
        len += snprintf(buffer + len, sizeof(buffer) - len, "*    ");
    }
    len += snprintf(buffer + len, sizeof(buffer) - len, "\n");
    write(STDOUT_FILENO, buffer, len);
}