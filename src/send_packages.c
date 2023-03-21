
#include "ft_ping.h"

static struct icmp create_icmp_header(int sequence) {
    struct icmp icmp;

    ft_bzero(&icmp, sizeof(icmp));

    icmp.icmp_type = ICMP_ECHO;   // ICMP echo request
    icmp.icmp_code = 0;           // Always 0
    icmp.icmp_id =
        getpid() &
        0xffff;   // ID of the process, we are using our own PID here (16 bits) to keep it simple
    icmp.icmp_seq = sequence;                                // Sequence number
    gettimeofday((struct timeval *) icmp.icmp_data, NULL);   // Store timestamp in icmp payload
    icmp.icmp_cksum = ft_icmp_checksum(
        (char *) &icmp, sizeof(struct icmp));   // Calculate the checksum of the ICMP header
    return icmp;
}

int send_ping(int sequence) {
    struct icmp icmp;

    icmp = create_icmp_header(sequence);
    int ret = sendto(ping.sockfd, &icmp, sizeof(icmp), 0, (struct sockaddr *) &ping.server_addr,
                     sizeof(ping.server_addr));
    if (ret < 0) {
        fprintf(stderr, "%s: sendto: %s\n", PROGRAM_NAME, strerror(errno));
    } else {
        ping.packets_stats.transmitted++;
    }
    return 0;
}