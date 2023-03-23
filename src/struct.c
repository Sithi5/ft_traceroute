#include "ft_traceroute.h"

void set_args_structure() {
    traceroute.args.h_flag = false;
    traceroute.args.max_hops = DEFAULT_MAX_HOPS;
    traceroute.args.nqueries = DEFAULT_NQUERIES;
    traceroute.args.W_flag = false;
    traceroute.args.n_flag = false;
    traceroute.args.timeout_ms = DEFAULT_TIMEOUT_MS;
    traceroute.args.host = NULL;
}