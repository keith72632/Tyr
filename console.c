#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "port_scanner.h"

#define LEN 10

void console(char *pHost, int *first, int *last){

	char *request = (char*)malloc(LEN);

	printf("Welcome to Tyr. Enter command or type help for options\n");
	label:
		printf(">");
		scanf("%s", request);

	if(strcmp(request, "scan") == 0){
		printf("Enter IP address\n>");
    	scanf("%s", pHost);
    	printf("Enter PORT number you wish to begin scanning at\n>");
    	scanf("%d", first);
    	printf("Enter PORT number you wish to end scanning at\n>");
    	scanf("%d", last);
    	goto label;
	} else if(strcmp(request, "sniff") == 0) {
		printf("Packet sniffer coming soon\n");
		goto label;
	} else if(strcmp(request, "help") == 0){
		printf("-scan:\n\tPerform network scan. When prompted, enter ip address and range of ports you wish to scan\n");
		printf("-sniff:\n\tPacket sniffer\n");
		printf("-quit:\n\tgive up\n");	
		printf("\n#############################################################################################\n");
		goto label;
	} else if(strcmp(request, "quit") == 0){
		exit(1);
	}


}
