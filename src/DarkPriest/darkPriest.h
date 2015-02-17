#ifndef DARK_PRIEST_H
#define DARK_PRIEST_H

#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <cstring>


struct info{
	uint32_t angle;
	uint32_t x;
	uint32_t y;
};

class darkPriest
{
public:
    struct info dataStruct;
	darkPriest(void);
	int status;
	int socket_one;
	int len;
	char *msg;
	char incoming_data_buffer[1000];
	ssize_t bytes_sent;
	ssize_t bytes_recieved;

	struct addrinfo host_info;
	struct addrinfo *host_info_list;

	int initialize();

	int connecter();

	int send_data();

	int revieve_data();

	int shut_down();

};
#endif
