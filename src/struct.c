#include "ft_traceroute.h"

/*
 * This function is used to initialize the packets_stats structure
 */
void set_packets_stats() {
    traceroute.packets_stats.transmitted = 0;
    traceroute.packets_stats.received = 0;
    traceroute.packets_stats.min_rtt = DBL_MAX;
    traceroute.packets_stats.max_rtt = -DBL_MAX;
    traceroute.packets_stats.sum_rtt = 0;
    traceroute.packets_stats.sum_squared_rtt = 0;
}

void set_args_structure() {
    traceroute.args.a_flag = false;
    traceroute.args.D_flag = false;
    traceroute.args.h_flag = false;
    traceroute.args.i_flag = false;
    traceroute.args.max_hops = DEFAULT_MAX_HOPS;
    traceroute.args.nqueries = DEFAULT_NQUERIES;
    traceroute.args.w_flag = false;
    traceroute.args.W_flag = false;
    traceroute.args.timeout = 0;
    traceroute.args.deadline = 0;
    traceroute.args.interval = 1;
    traceroute.args.host = NULL;
    traceroute.args.num_packets = -1;
}