#include "ft_traceroute.h"

void print_traceroute_address_infos() {
    char ip_address[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &(traceroute.server_addr.sin_addr), ip_address, INET_ADDRSTRLEN);

    printf("traceroute to %s (%s), %i hops max, %lu byte packets\n", traceroute.args.host,
           ip_address, traceroute.args.max_hops, sizeof(struct icmp));
}

void print_statistics() {
    double avg_rtt = traceroute.packets_stats.sum_rtt / traceroute.packets_stats.received;
    double variance =
        (traceroute.packets_stats.sum_squared_rtt / traceroute.packets_stats.received) -
        (avg_rtt * avg_rtt);
    double stddev_rtt = ft_sqrt(variance);

    printf("--- %s ping statistics ---\n", traceroute.args.host);

    printf("%d packets transmitted, %d packets received, %.1f%% packet loss\n",
           traceroute.packets_stats.transmitted, traceroute.packets_stats.received,
           (1.0 - traceroute.packets_stats.received / traceroute.packets_stats.transmitted) *
               100.0);
    if (traceroute.packets_stats.received > 0) {
        printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
               traceroute.packets_stats.min_rtt, avg_rtt, traceroute.packets_stats.max_rtt,
               stddev_rtt);
    }
}

void display_received_package_infos(struct ip *ip_header, int sequence) {
    char src_ip_address[INET_ADDRSTRLEN];
    char dst_ip_address[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &ip_header->ip_src, src_ip_address, INET_ADDRSTRLEN);
    inet_ntop(AF_INET, &traceroute.server_addr.sin_addr.s_addr, dst_ip_address, INET_ADDRSTRLEN);
    printf("IP Hdr Dump:\n ");
    ft_hexdump(ip_header, sizeof(struct ip));
    printf("Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src\tDst\tData\n");
    printf("%2d ", ip_header->ip_v);                             // Vr
    printf("%2d ", ip_header->ip_hl);                            // HL
    printf("%02x ", ip_header->ip_tos);                          // TOS
    printf("%04x ", ft_ntohs(ip_header->ip_len));                // Len
    printf("%04x  ", ft_ntohs(ip_header->ip_id));                // ID
    printf("%2d ", (ft_ntohs(ip_header->ip_off) >> 13) & 0x7);   // Flg
    printf("%04x ", ft_ntohs(ip_header->ip_off) & 0x1FFF);       // off
    printf("%3d ", ip_header->ip_ttl);                           // TTL
    printf("%02d ", ip_header->ip_p);                            // Pro
    printf("%04x ", ft_ntohs(ip_header->ip_sum));                // cks
    printf("%s  ", src_ip_address);                              // Src
    printf("%s ", dst_ip_address);                               // Dst
    printf("\n");
    printf("ICMP: type %d, code %d, size %ld, id 0x%x, seq 0x%x\n", ICMP_ECHO, ICMP_ECHOREPLY,
           sizeof(struct icmp), getpid() & 0xffff, sequence);
}