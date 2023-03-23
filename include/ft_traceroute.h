#ifndef TRACEROUTE_H
#define TRACEROUTE_H

/****************************************************************************/
/*                          INCLUDES                                        */
/****************************************************************************/

#include <arpa/inet.h>
#include <errno.h>
#include <float.h>
#include <netdb.h>
#include <netinet/ip_icmp.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

/****************************************************************************/
/*                          DEFINES                                         */
/****************************************************************************/

#define PROGRAM_NAME    "ft_traceroute"
#define PROGRAM_VERSION "1.0.0"
#define PROGRAM_AUTHOR  "mabouce"

#ifdef DEBUG
#define DEBUG true
#else
#define DEBUG false
#endif

#define MAX_PACKET_SIZE     1024
#define MAX_ADDRS           16
#define DEFAULT_MAX_HOPS    30
#define MAX_QUERIES_PER_HOP 10
#define DEFAULT_NQUERIES    3
#define DEFAULT_TIMEOUT_MS  5000

/****************************************************************************/
/*                           ENUM                                           */
/****************************************************************************/

/* Error codes */
enum e_error {
    ERROR_SOCKET_OPEN = 1,
    ERROR_ARGS,
    ERROR_SOCKET_OPTION,
    ERROR_GET_HOST_BY_NAME_SOCKET_OPEN,
    ERROR_SENDTO,
    ERROR_INET_PTON,
    ERROR_RESOLVING_HOST,
    ERROR_RECVFROM,
    ERROR_SIGINT,
    NB_OF_ERROR_CODES /* Always keep last */
};

/****************************************************************************/
/*                          STRUCTS                                         */
/****************************************************************************/

typedef struct s_args {
    bool h_flag;
    bool q_flag;
    bool n_flag;
    bool W_flag;
    int timeout_ms;
    unsigned int nqueries;
    int max_hops;
    char *host;
} t_args;

typedef struct s_packet_received {
    struct sockaddr_in server_addr;
    double rtt;
    struct timeval sent_time;
    bool received;
} t_packet_received;

typedef struct s_traceroute {
    t_args args;
    struct sockaddr_in server_addr;
    t_packet_received packets_received[DEFAULT_MAX_HOPS];
    bool final_packet_received;
    int current_ttl;
    int sockfd;
} g_traceroute;

/****************************************************************************/
/*                          GLOBALS                                         */
/****************************************************************************/

extern g_traceroute traceroute;

/****************************************************************************/
/*                          FUNCTIONS DEFINITIONS                           */
/****************************************************************************/

// prints
void print_traceroute_address_infos();
void print_current_ttl_stats();
// struct
void set_packets_stats();
void set_args_structure();

// send_packages
void send_package(unsigned int packet_number);

// receive_package
void receive_package(unsigned int packet_number);

// errors
void ft_perror(const char *message);
void exit_clean(int sockfd, int status);

// args
void parse_args(int argc, char *argv[]);

// network
unsigned short ft_icmp_checksum(void *data, int len);
struct sockaddr_in *ft_gethostbyname(const char *name, int num_addrs);
double calculate_package_rtt(struct timeval *sent_time, struct timeval *end_time);
char *ft_reverse_dns_lookup(struct sockaddr *server_addr, size_t dns_name_len);

// utils
void ft_bzero(void *s, size_t n);
void *ft_memset(void *s, int c, size_t n);
void *ft_memcpy(void *dest, const void *src, size_t n);
double ft_sqrt(double num);
double ft_fab(double num, int power);
bool ft_isdigit(char c);
int ft_isnumber(const char *str);
int ft_atoi(const char *str);
int ft_strcmp(const char *s1, const char *s2);
double ft_str_to_double(const char *str);
bool ft_isdouble(const char *str);
void ft_hexdump(const void *data, size_t size);
uint16_t ft_ntohs(uint16_t n);
int ft_strlen(const char *str);

#endif
