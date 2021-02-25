#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include "colors.h"


int server(int argc, char **argv)
{
	int sock, new_sock;
	struct sockaddr_in server_addr;

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0){
		printf("%sError Creating Socket%s\n", KRED, KWHT);
	}
	printf("Socket creating successful\n");

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		printf("%sSocket Bind Unsuccessful%s\n",KRED, KWHT);
	}

	return 0;
}