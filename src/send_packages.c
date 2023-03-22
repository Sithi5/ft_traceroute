
#include "ft_traceroute.h"

static struct icmp create_icmp_header() {
    struct icmp icmp;

    ft_bzero(&icmp, sizeof(icmp));

    icmp.icmp_type = ICMP_ECHO;   // ICMP echo request
    icmp.icmp_code = 0;           // Always 0
    icmp.icmp_id =
        getpid() &
        0xffff;   // ID of the process, we are using our own PID here (16 bits) to keep it simple
    gettimeofday((struct timeval *) icmp.icmp_data, NULL);   // Store timestamp in icmp payload
    icmp.icmp_cksum = ft_icmp_checksum(
        (char *) &icmp, sizeof(struct icmp));   // Calculate the checksum of the ICMP header
    return icmp;
}

int send_package() {
    struct icmp icmp;

    icmp = create_icmp_header();
    int ret = sendto(traceroute.sockfd, &icmp, sizeof(icmp), 0,
                     (struct sockaddr *) &traceroute.server_addr, sizeof(traceroute.server_addr));
    return 0;
}