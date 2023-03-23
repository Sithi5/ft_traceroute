#include "ft_traceroute.h"

void usage() {
    printf("Usage\n"
           "  %s [options] <destination>\n\n"
           "Options:\n"
           "  <destination>      dns name or ip address\n"
           "  -q <nqueries>      set the number of probes per each hop\n"
           "  -m <max_ttl>       set the max number of hops\n"
           "  -n                 no dns name resolution\n"
           "  -V                 print version and exit\n"
           "  -W <timeout>       number of ms to wait for response. By default %d\n",
           PROGRAM_NAME, DEFAULT_TIMEOUT_MS);
    exit(1);
}

void parse_args(int argc, char *argv[]) {
    if (argc < 2) {
        usage();
    }
    for (int i = 1; i < argc; i++) {
        if (ft_strcmp(argv[i], "-h") == 0) {
            usage();
        } else if (ft_strcmp(argv[i], "-V") == 0) {
            printf("%s by %s %s\n", PROGRAM_NAME, PROGRAM_AUTHOR, PROGRAM_VERSION);
            exit(ERROR_ARGS);
        } else if (ft_strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
            if (i + 1 < argc && ft_isnumber(argv[i + 1])) {
                traceroute.args.max_hops = ft_atoi(argv[i + 1]);
                i++;
            } else {
                fprintf(stderr, "%s: invalid argument: '%s'\n", PROGRAM_NAME, argv[i + 1]);
                exit(ERROR_ARGS);
            }
        } else if (ft_strcmp(argv[i], "-n") == 0) {
            traceroute.args.n_flag = true;
        } else if (ft_strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            if (i + 1 < argc && ft_isnumber(argv[i + 1])) {
                traceroute.args.nqueries = ft_atoi(argv[i + 1]);
                if (traceroute.args.nqueries < 1 ||
                    traceroute.args.nqueries > MAX_QUERIES_PER_HOP) {
                    fprintf(stderr, "no more than 10 probes per hop");
                    exit(ERROR_ARGS);
                }
                i++;
            } else {
                fprintf(stderr, "%s: invalid argument: '%s'\n", PROGRAM_NAME, argv[i + 1]);
                exit(ERROR_ARGS);
            }
        } else if (ft_strcmp(argv[i], "-W") == 0 && i + 1 < argc) {
            if (i + 1 < argc && ft_isnumber(argv[i + 1])) {
                traceroute.args.W_flag = true;
                traceroute.args.timeout_ms = ft_atoi(argv[i + 1]);
                i++;
            } else {
                fprintf(stderr, "%s: invalid argument: '%s'\n", PROGRAM_NAME, argv[i + 1]);
                exit(ERROR_ARGS);
            }
        } else if (argv[i][0] == '-') {
            fprintf(stderr, "%s: Invalid option -- `%s`\n", PROGRAM_NAME, argv[i]);
            usage();
        } else if (traceroute.args.host == NULL) {
            traceroute.args.host = argv[i];
        } else {
            fprintf(stderr, "%s: Invalid option -- `%s`\n", PROGRAM_NAME, argv[i]);
            usage();
        }
    }
    if (traceroute.args.host == NULL) {
        usage();
        exit(ERROR_ARGS);
    }
}