#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include "colors.h"

void prompt(char *ipAddr, int *port);

void server(int argc, char **argv)
{
	char ipAddr[16]; 
	int sock, new_sock, port;
	int *ptr = &port;
	char *lines = "**********************************************************************************************";
	struct sockaddr_in server_addr;

	prompt(ipAddr, ptr);

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if(sock < 0){
		printf("%sError Creating Socket%s\n", KRED, KWHT);
	}

	system("clear");

	printf("%s[+]%sSocket creating successful\n", KGRN, KWHT);

	memset(&server_addr, '\0', sizeof(server_addr));
	server_addr.sin_addr.s_addr = inet_addr(ipAddr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);

	if(bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
		printf("%sSocket Bind Unsuccessful%s\n",KRED, KWHT);
	}

	printf("%s[+]%sBind successful!\n", KGRN, KWHT);

	printf("%s\n", lines);
	printf("Listenting on port: %d\n", port);
	printf("%s\n", lines);

	listen(sock, 3);

	while(1){
		struct sockaddr_in client;
		int client_len = sizeof(client);

		new_sock = accept(sock, (struct sockaddr *)&client, (socklen_t *)&client_len);
		if(new_sock < 0){
			printf("%sSocket accept unsuccessful%s\n", KRED, KWHT);
			exit(1);
		}

		printf("%s[+]%sSocket accept successful!\n", KGRN, KWHT);

		if(send(new_sock, "Hello", 6, 0) < 0)
			printf("%sMessage send failed%s\n", KRED, KWHT);
		printf("%s[+]%sMessage to %s sent successfully\n%s\n\n", KGRN, KWHT, inet_ntoa(client.sin_addr), lines);
	}

}

void prompt(char *ipAddr, int *port)
{
	printf("Enter Ip Address of server or write local\n>");
	scanf("%s", ipAddr);
	if(strcmp(ipAddr, "local") == 0)
		ipAddr = "127.0.0.1";
	printf("Enter port you wish to run server on\n>");
	scanf("%d", port);
}