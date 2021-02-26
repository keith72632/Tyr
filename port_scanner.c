#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <unistd.h>
#include "colors.h"

void port_scanner(char *hostname, int first, int last)
{
	int sock, err, total;
	int counter = 0;
	struct sockaddr_in server_addr;
	//initialize server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(hostname);


  //start scan
    for(int i = first; i <= last; i++){
    	total = last - first;
    	server_addr.sin_port = htons(i);
    	sock = socket(AF_INET, SOCK_STREAM, 0);

        if(sock < 0){
    	    perror("\n[x]Socket");
     	    exit(1);
        }
        //connect using this sock and socket address
        err = connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

        //not connected
        if(err < 0){
            fflush(stdout);
         }
        //connected
        else {
            system("clear");
            printf("%s[+]%sScanning ports %d - %d\n", KGRN, KWHT, first, last);
            printf("%s*****************************************************************%s\n", KCYN, KWHT);
            printf("%s[+]%sPORT: %-5d open\n", KGRN, KWHT, i);
            printf("%s*****************************************************************%s\n", KCYN, KWHT);
            counter++;

            if(i == 21 && err == 0){
            printf("%s[+]%sftp open on port 21\n", KGRN, KWHT);
            }

            if(i == 8080 && err == 0){
            printf("%s[+]%sHttp open on port 8080\n", KGRN, KWHT);
            }
        }
        close(sock);
    }
    printf("%s[+]%s%d out of %d ports are open\n\n", KGRN, KWHT, counter, total);

    fflush(stdout);
}
