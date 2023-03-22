
#include "ft_traceroute.h"

static int recv_ping_msg(struct msghdr *msg) {
    int received_size = recvmsg(traceroute.sockfd, msg, 0);
    if (received_size < 0) {
        return -1;
    }
    return received_size;
}

static int process_received_package(int received_size, struct msghdr *msg) {
    struct icmp icmp;
    struct ip *ip_header = (struct ip *) msg->msg_iov->iov_base;
    int ip_header_length = ip_header->ip_hl << 2;

    ft_bzero(&icmp, sizeof(struct icmp));
    ft_memcpy(&icmp, (char *) ip_header + ip_header_length, sizeof(struct icmp));

    if ((icmp.icmp_type == ICMP_ECHOREPLY && icmp.icmp_id == (getpid() & 0xffff)) ||
        icmp.icmp_type == ICMP_TIMXCEED) {
        printf("Received ICMP type %d\n", icmp.icmp_type);
        if (icmp.icmp_type == ICMP_TIMXCEED)
            return 0;
        return 1;
    } else {
        return -1;
    }
}

int receive_package() {
    char buffer[IP_MAXPACKET];
    struct iovec iov;
    struct msghdr msg;
    int received_size;
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

    if ((received_size = recv_ping_msg(&msg)) >= 0) {
        return process_received_package(received_size, &msg);
    }
    return -2;
}