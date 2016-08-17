#ifndef _TCP_SERVER_
#define _TCP_SERVER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#ifdef WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
#endif

#include "tracker_report_syst.h"
#include "common.h"

#define CLIENT_DATA_BUFFER_LEN	256

/*void *get_in_addr(struct sockaddr *sa);
*/
void start_server();

extern char *port;

#ifdef WIN32
	extern void WSAAPI freeaddrinfo (struct addrinfo*);
	extern int WSAAPI getaddrinfo (const char*,const char*,const struct addrinfo*,
		        struct addrinfo**);
#else
	extern  void freeaddrinfo(struct addrinfo*);
	extern int getaddrinfo(const char*, const char*, const struct addrinfo*,
			struct addrinfo**);
#endif

#endif
