#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>
#include "port_scanner.h"
#include "console.h"
#include "packet_sniffer.h"
#include "server.h"

void banner(void);
extern char global_ip[15];
extern int global_start_port;
extern int global_finish_port;

char host[16] = {0};
int first, last;

int main(int argc, char **argv)
{

  char first_port[6] = {0};
  char last_port[6] = {0};

  if(argc == 5 && strcmp(argv[1], "scan") == 0){
     
    strcpy(host, argv[2]);
    strcpy(first_port, argv[3]);
    strcpy(last_port, argv[4]);

     //convert to int
    first = atoi(first_port);
    last = atoi(last_port);

    port_scanner(host, first, last);

    exit(1);
  }else if(argc == 2 && strcmp(argv[1], "sniff")==0){
    sniff();
  }else if(argc == 2 && strcmp(argv[1], "server") == 0){
    server();
  } else {
    system("clear");

    banner();

    while(1){
        console();        
    }


  }

  return 0;
}

