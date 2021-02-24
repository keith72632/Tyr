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

  if(argc == 4){
     
    strcpy(host, argv[1]);
    strcpy(first_port, argv[2]);
    strcpy(last_port, argv[3]);

     //convert to int
    first = atoi(first_port);
    last = atoi(last_port);

    port_scanner(host, first, last);

    exit(1);
  }else{
    system("clear");

    banner();

    while(1){
        console();        
    }


  }

  return 0;
}

