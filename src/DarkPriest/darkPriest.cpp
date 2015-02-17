#include <iostream>
#include <unistd.h>
#include "darkPriest.h"

darkPriest::darkPriest()
{

	host_info.ai_family = AF_UNSPEC;
	host_info.ai_socktype = SOCK_STREAM;

}

int darkPriest::initialize()
{
	memset(&host_info, 0, sizeof(host_info));

	status = getaddrinfo("10.24.81.50","9999", &host_info, &host_info_list);
	if(status != 0)
	return -1;

	socket_one = socket(host_info_list->ai_family, host_info_list->ai_socktype, host_info_list->ai_protocol);

	if(socket_one == -1)
	return -1;

	return 0;
}

int darkPriest::connecter()
{
	do{
	sleep(.1);
	status = connect(socket_one, host_info_list->ai_addr, host_info_list->ai_addrlen);
	} while(status == -1);
	std::cout << status << std::endl;

	if(status == -1)
	return -1;

	return 0;
}

int darkPriest::send_data()
{

	bytes_sent = send(socket_one, &dataStruct, sizeof(info), 0);

	if(bytes_sent == -1)
	return -1;

	return 0;
}

int darkPriest::revieve_data()
{
    bytes_recieved = 0;
    int temp;
    len = sizeof(info);
    while(bytes_recieved < len){
        temp = recv(socket_one, &dataStruct + bytes_recieved , len - bytes_recieved , 0);

        if(temp == 0)
        return 1;

        if(temp == -1)
        return -1;

        bytes_recieved += temp;
    }
	return 0;
}

int darkPriest::shut_down()
{
	freeaddrinfo(host_info_list);

	close(socket_one);

	return 0;
}
