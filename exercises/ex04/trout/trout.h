#ifndef TROUT_H
#define TROUT_H "trout.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <netinet/in_systm.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/un.h>
#include <stdarg.h>
#include <stdint.h>
#include <syslog.h>
#include <unistd.h>

#define BUFSIZE 1500

typedef struct rec {                /* outgoing UDP data */
  unsigned short seq;          /* sequence number */
} Rec;

typedef struct timeval Timeval;
typedef struct sockaddr Sockaddr;

/* the following are a few definitions from Stevens' unp.h */

typedef	void Sigfunc(int);        /* for signal handlers */

#define max(a,b) ((a) > (b) ? (a) : (b))

/* variables we might want to configure */
extern int max_ttl;
extern int nprobes;

extern Sockaddr *sasend;    /* socket addresses for various purposes */
extern Sockaddr *sarecv;
extern Sockaddr *salast;
extern Sockaddr *sabind;

extern socklen_t salen;                    /* length of a socket address */
extern int datalen;         /* length of the data in a datagram */

extern unsigned short sport;                      /* source UDP port # */
extern unsigned short dport;        /* destination port -- hopefully unused */
                                    /* 668 = the neighbor of the beast */

int process_ip (struct ip *ip, int len);
int recv_dgram ();
void sub_tv (Timeval *plus, Timeval *minus, Timeval *res);
double time_to_double (Timeval *time);
void print_report ();
void send_dgram (int ttl);
int send_probes (int ttl);
void loop_ttl();

#endif
