#include "ft_traceroute.h"

void set_args_structure() {
    traceroute.args.h_flag = false;
    traceroute.args.max_hops = DEFAULT_MAX_HOPS;
    traceroute.args.first_hop = DEFAULT_FIRST_HOP;
    traceroute.args.nqueries = DEFAULT_NQUERIES;
    traceroute.args.w_flag = false;
    traceroute.args.n_flag = false;
    traceroute.args.timeout = DEFAULT_TIMEOUT;
    traceroute.args.sendwait = DEFAULT_SENDWAIT;
    traceroute.args.host = NULL;
}