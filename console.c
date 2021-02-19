#include <stdio.h>
#include <stdlib.h>
#include "port_scanner.h"

void banner(void);

void console(char *pHost, int *first, int *last){
    system("clear");

    banner();

    printf("Enter IP address\n>");
    scanf("%s", pHost);
    printf("Enter PORT number you wish to begin scanning at\n>");
    scanf("%d", first);
    printf("Enter PORT number you wish to end scanning at\n>");
    scanf("%d", last);
}
