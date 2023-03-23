
#include "ft_traceroute.h"

static struct icmp create_icmp_header(unsigned int packet_number) {
    struct icmp icmp;
    struct timeval sent_time;
    ft_bzero(&icmp, sizeof(icmp));

    gettimeofday((struct timeval *) &sent_time, NULL);
    icmp.icmp_type = ICMP_ECHO;   // ICMP echo request
    icmp.icmp_code = 0;           // Always 0
    icmp.icmp_id =
        getpid() &
        0xffff;   // ID of the process, we are using our own PID here (16 bits) to keep it simple
    icmp.icmp_seq = packet_number;   // Sequence number of the packet
    ft_memcpy(&icmp.icmp_data, &sent_time,
              sizeof(struct timeval));   // Store timestamp in icmp payload
    icmp.icmp_cksum = ft_icmp_checksum(
        (char *) &icmp, sizeof(struct icmp));   // Calculate the checksum of the ICMP header
    traceroute.packets_received[packet_number].sent_time = sent_time;
    return icmp;
}

void send_package(unsigned int packet_number) {
    struct icmp icmp;

    icmp = create_icmp_header(packet_number);
    if (sendto(traceroute.sockfd, &icmp, sizeof(icmp), 0,
               (struct sockaddr *) &traceroute.server_addr, sizeof(traceroute.server_addr)) < 0) {
        // We don't want to exit the program if we can't send a packet
        DEBUG ? fprintf(stderr, "%s: sendto: %s\n", PROGRAM_NAME, strerror(errno)) : 0;
    }
}