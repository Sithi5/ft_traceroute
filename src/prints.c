#include "ft_traceroute.h"

void print_traceroute_address_infos() {
    char ip_address[INET_ADDRSTRLEN];

    inet_ntop(AF_INET, &(traceroute.server_addr.sin_addr), ip_address, INET_ADDRSTRLEN);

    printf("traceroute to %s (%s), %i hops max, %lu byte packets\n", traceroute.args.host,
           ip_address, traceroute.args.max_hops, sizeof(struct icmp));
}
