/*
	Little Smalltalk, version 3
	Main Driver
	written By Tim Budd, September 1988
	Oregon State University
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "env.h"
#include "memory.h"
#include "names.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

int initial = 0;		/* not making initial image */

extern int objectCount();
boolean execute(object aProcess, int maxsteps);

int main(int argc, char **argv)
{
    FILE *fp;
    object firstProcess;
    char *p, buffer[500];

    initMemoryManager();

    strcpy(buffer, "systemImage");
    p = buffer;

    if (argc != 1)
	p = argv[1];

    fp = fopen(p, "r");
    if (fp == NULL) {
       strcpy(buffer, TOSTRING(PREFIX));
       strcat(buffer, "/lib/yalsf/systemImage");
	fp = fopen(p, "r");
	if (fp == NULL) {
		sysError("cannot open image", p);
		exit(1);
	}
    }
    imageRead(fp);
    initCommonSymbols();

    firstProcess = globalSymbol("systemProcess");
    if (firstProcess == nilobj) {
	sysError("no initial process", "in image");
	exit(1);
	return 1;
    }

    printf("Little Smalltalk, Version 3.1\n");
    printf("Written by Tim Budd, Oregon State University\n");
    printf("Updated for modern systems by Charles Childers\n");

    while (execute(firstProcess, 15000));

/* exit and return - belt and suspenders, but it keeps lint happy */
    exit(0);
    return 0;
}
