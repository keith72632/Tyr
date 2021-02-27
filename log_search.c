#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "colors.h"

#define FILE_NAME "Files/log.txt"

void log_search(void)
{
	FILE *fp;

	fp = fopen(FILE_NAME, "r");
	char c;

	if(fp == NULL)
		printf("%sCould not open file. Does it exist in your current directory?%s\n", KRED, KWHT);

	printf("Opening of log file is successful!\n");
	c = fgetc(fp);

	while(c != EOF){
		if(c == '*' || c == '#'){
			printf("%s%c", KCYN, c);
			c = fgetc(fp);
		}
		printf("%s%c", KWHT, c);
		c = fgetc(fp);
	}
	fclose(fp);
}