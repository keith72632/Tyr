#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "port_scanner.h"
#include "packet_sniffer.h"
#include "colors.h"
#include "console.h"
#include "ping.h"
#include "log_search.h"

#define LEN 10
char global_ip[15];
int global_start_port = 0;
int global_finish_port = 0;

extern int first;
extern int last;
extern char host[16];

void console(){

	char *request = (char*)malloc(LEN);
	char confirm;

	printf("Welcome to Tyr. Enter command or type help for options\n");
	label:
		printf("%sTyr>%s", KCYN, KWHT);
		scanf("%s", request);

	if(strcmp(request, "scan") == 0){
		printf("Enter IP address\n>");
    	scanf("%s", host);
    	printf("Enter PORT number you wish to begin scanning at\n>");
    	scanf("%d", &first);
    	printf("Enter PORT number you wish to end scanning at\n>");
    	scanf("%d", &last);
    	port_scanner(host, first, last);
    	
	} else if(strcmp(request, "sniff") == 0) {
		sniff();
		goto label;
	} else if(strcmp(request, "help") == 0){
		printf("-scan:\n\tPerform network scan. When prompted, enter ip address and range of ports you wish to scan\n");
		printf("-sniff:\n\tPacket sniffer\n");
		printf("-init:\n\tPrompted to initialize a global ip, starting port and finishing port\n");
		printf("-showinfo:\n\tShow global varaibles\n");
		printf("-longsearch:\n\tThis will print the data from packet sniffer int the terminal. Heads up, it could be alot.\n");
		printf("-quit:\n\tgive up\n");	
		printf("\n#############################################################################################\n");
		goto label;
	} else if(strcmp(request, "init") == 0){
		printf("Enter target ip address:\n");
		scanf("%s", global_ip);
		printf("Enter starting port:\n");
		scanf("%d", &global_start_port);
		printf("Enter finishing port:\n");
		scanf("%d", &global_finish_port);
		printf("ip: %s\nstart: %d\nend: %d\n", global_ip, global_start_port, global_finish_port);
		goto label;
	} else if(strcmp(request, "showinfo")==0){
		printf("ip: %s\nstart: %d\nend: %d\n", global_ip, global_start_port, global_finish_port);
		goto label;
	}else if(strcmp(request, "ping")==0){
		ping();
		goto label;
	}else if(strcmp(request, "logsearch")==0){
		log_search();
		goto label;
	}else if(strcmp(request, "quit") == 0){
		printf("Are you sure you want to quit?[y/n]\n");
		scanf("%c", &confirm);
		if((confirm = getchar()) == 'y'){
			exit(1);
		}else{
			goto label;
		}
	}
}

