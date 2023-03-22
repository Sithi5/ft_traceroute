
#include "ft_traceroute.h"

static int recv_ping_msg(struct msghdr *msg) {
    int received_size = recvmsg(traceroute.sockfd, msg, 0);
    if (received_size < 0) {
        return -1;
    }
    return received_size;
}

static void process_received_package(struct msghdr *msg, unsigned int packet_number) {
    struct icmp icmp;
    struct sockaddr_in server_addr;
    struct ip *ip_header = (struct ip *) msg->msg_iov->iov_base;
    int ip_header_length = ip_header->ip_hl << 2;

    // Extract the server address from the IP header
    server_addr.sin_addr = ip_header->ip_src;

    ft_bzero(&icmp, sizeof(struct icmp));
    ft_memcpy(&icmp, (char *) ip_header + ip_header_length, sizeof(struct icmp));

    if (icmp.icmp_type == ICMP_ECHOREPLY) {
        traceroute.packets_received[packet_number].received = true;
        traceroute.final_packet_received = true;
    } else if (icmp.icmp_type == ICMP_TIMXCEED) {
        traceroute.packets_received[packet_number].received = true;
        traceroute.packets_received[packet_number].server_addr = server_addr;
    }
}

void receive_package(unsigned int packet_number) {
    char buffer[IP_MAXPACKET];
    struct iovec iov;
    struct msghdr msg;
    struct sockaddr_in sockaddr_copy;

    ft_bzero(&msg, sizeof(struct msghdr));

    // Copy the server address to sockaddr_copy because recvmsg() will overwrite the address
    sockaddr_copy = traceroute.server_addr;
    iov.iov_base = buffer;
    iov.iov_len = sizeof(buffer);
    msg.msg_name = &sockaddr_copy;
    msg.msg_namelen = sizeof(struct sockaddr_in);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = buffer;
    msg.msg_controllen = IP_MAXPACKET;
    msg.msg_flags = 0;

    if ((recv_ping_msg(&msg)) >= 0) {
        process_received_package(&msg, packet_number);
    } else {
        DEBUG ? fprintf(stderr, "%s: recvmsg: %s\n", PROGRAM_NAME, strerror(errno)) : 0;
    }
}