#include<stdio.h>	//For standard things
#include<stdlib.h>	//malloc
#include<string.h>	//memset
#include<netinet/ip_icmp.h>	//Provides declarations for icmp header
#include<netinet/tcp.h>	//Provides declarations for tcp header
#include<netinet/ip.h>	//Provides declarations for ip header
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include "colors.h"

#define BUFF_SIZE 65536

void ProcessTCPPacket(unsigned char *buffer, int size);
void print_ip_header_tcp(unsigned char* Buffer, int size);
void print_tcp_packet_tcp(unsigned char* Buffer, int Size);
void PrintTcpData (unsigned char* data , int Size);


int sock_raw_tcp;
FILE *logfile_tcp;
int _tcp=0;
struct sockaddr_in tcp_source, tcp_dest;

int sniff_tcp(void)
{
	int saddr_size, data_size;
	struct sockaddr saddr;
	//struct in_addr in;

	unsigned char *buffer = (unsigned char*)malloc(BUFF_SIZE);

	logfile_tcp = fopen("tcp_log.txt", "w");
	if(logfile_tcp == NULL) printf("Unable to create file\n");

	printf("starting...\n");

	//This creates raw socket that will sniff. Raw sockets are "connectionless" and only associate socket with address
	sock_raw_tcp = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if(sock_raw_tcp < 0){
		printf("%sSocket Error. Try sudo%s\n", KRED, KWHT);
		return 1;
	}
    system("clear");
	printf("[+]TCP Socket success!\n*Must kill process with ctrl-c and reopen Tyr because I suck.\n*Check log.txt in current directory\n");
	while(1){
		saddr_size = sizeof(saddr);
		//The recvfrom() function shall receive a message from a connection-mode or connectionless-mode socket. It is normally used 
		//with connectionless-mode sockets because it permits the application to retrieve the source address of received data.
		data_size = recvfrom(sock_raw_tcp, buffer, BUFF_SIZE, 0, &saddr, (socklen_t*)&saddr_size);
		if(data_size < 0){
			printf("%sRecvfrom error, failed to get packet%s\n", KRED, KWHT);
			return 1;
		}
		//Process packet
        ProcessTCPPacket(buffer, data_size);
	}
	close(sock_raw_tcp);
	printf("Finished\n");
	return 0;
}

void ProcessTCPPacket(unsigned char *buffer, int size)
{
	//Get the IP header part of this packet
	struct iphdr *iph = (struct iphdr*)buffer;
	if(iph->protocol == 6){
		++_tcp;
		print_tcp_packet_tcp(buffer, size);
		printf("TCP : %d\r",_tcp);
	}
	
}

void print_ip_header_tcp(unsigned char* Buffer, int size)
{
	//unsigned short iphdrlen;

	struct iphdr *iph = (struct iphdr *)Buffer;
	//iphdrlen = iph->ihl*4;

	memset(&tcp_source, 0, sizeof(tcp_source));
	tcp_source.sin_addr.s_addr = iph->saddr;

	memset(&tcp_dest, 0, sizeof(tcp_dest));
	tcp_dest.sin_addr.s_addr = iph->daddr;

	fprintf(logfile_tcp, "\n");
	fprintf(logfile_tcp, "IP Header\n");
	fprintf(logfile_tcp, "    |-IP Version         :%d\n", (unsigned int)iph->version);
	fprintf(logfile_tcp, "    |-IP Header Length   :%d DWORDS of %d Bytes\n", (unsigned int)iph->ihl,((unsigned int)(iph->ihl))*4);
	fprintf(logfile_tcp, "    |-Type of Service    :%d\n", (unsigned int)iph->tos);
	fprintf(logfile_tcp, "    |-IP Total Length    :%d Bytes(Size of Packet)\n", ntohs(iph->tot_len));
	fprintf(logfile_tcp, "    |-Identification     :%d\n", ntohs(iph->id));
	fprintf(logfile_tcp, "    |-TTL                :%d\n", (unsigned int)iph->ttl);
	fprintf(logfile_tcp, "    |-Protocol           :%d\n", (unsigned int)iph->protocol);
	fprintf(logfile_tcp, "    |-Checksum           :%d\n", ntohs(iph->check));
	fprintf(logfile_tcp, "    |-Source IP          :%s\n", inet_ntoa(tcp_source.sin_addr));
	fprintf(logfile_tcp, "    |-Destination IP     :%s\n", inet_ntoa(tcp_dest.sin_addr));
}

void print_tcp_packet_tcp(unsigned char* Buffer, int Size)
{
	unsigned short iphdrlen;
	
	struct iphdr *iph = (struct iphdr *)Buffer;
	iphdrlen = iph->ihl*4;
	
	struct tcphdr *tcph=(struct tcphdr*)(Buffer + iphdrlen);
			
	fprintf(logfile_tcp,"\n\n***********************TCP Packet*************************\n");	
		
	print_ip_header_tcp(Buffer,Size);
		
	fprintf(logfile_tcp,"\n");
	fprintf(logfile_tcp,"TCP Header\n");
	fprintf(logfile_tcp,"   |-Source Port      : %u\n",ntohs(tcph->source));
	fprintf(logfile_tcp,"   |-Destination Port : %u\n",ntohs(tcph->dest));
	fprintf(logfile_tcp,"   |-Sequence Number    : %u\n",ntohl(tcph->seq));
	fprintf(logfile_tcp,"   |-Acknowledge Number : %u\n",ntohl(tcph->ack_seq));
	fprintf(logfile_tcp,"   |-Header Length      : %d DWORDS or %d BYTES\n" ,(unsigned int)tcph->doff,(unsigned int)tcph->doff*4);
	//fprintf(logfile,"   |-CWR Flag : %d\n",(unsigned int)tcph->cwr);
	//fprintf(logfile,"   |-ECN Flag : %d\n",(unsigned int)tcph->ece);
	fprintf(logfile_tcp,"   |-Urgent Flag          : %d\n",(unsigned int)tcph->urg);
	fprintf(logfile_tcp,"   |-Acknowledgement Flag : %d\n",(unsigned int)tcph->ack);
	fprintf(logfile_tcp,"   |-Push Flag            : %d\n",(unsigned int)tcph->psh);
	fprintf(logfile_tcp,"   |-Reset Flag           : %d\n",(unsigned int)tcph->rst);
	fprintf(logfile_tcp,"   |-Synchronise Flag     : %d\n",(unsigned int)tcph->syn);
	fprintf(logfile_tcp,"   |-Finish Flag          : %d\n",(unsigned int)tcph->fin);
	fprintf(logfile_tcp,"   |-Window         : %d\n",ntohs(tcph->window));
	fprintf(logfile_tcp,"   |-Checksum       : %d\n",ntohs(tcph->check));
	fprintf(logfile_tcp,"   |-Urgent Pointer : %d\n",tcph->urg_ptr);
	fprintf(logfile_tcp,"\n");
	fprintf(logfile_tcp,"                        DATA Dump                         ");
	fprintf(logfile_tcp,"\n");
		
	fprintf(logfile_tcp,"IP Header\n");
	PrintTcpData(Buffer,iphdrlen);
		
	fprintf(logfile_tcp,"TCP Header\n");
	PrintTcpData(Buffer+iphdrlen,tcph->doff*4);
		
	fprintf(logfile_tcp,"Data Payload\n");	
	PrintTcpData(Buffer + iphdrlen + tcph->doff*4 , (Size - tcph->doff*4-iph->ihl*4) );
						
	fprintf(logfile_tcp,"\n###########################################################");
}

void PrintTcpData (unsigned char* data , int Size)
{
	int i, j;
	
	for(i=0 ; i < Size ; i++)
	{
		if( i!=0 && i%16==0)   //if one line of hex printing is complete...
		{
			fprintf(logfile_tcp,"         ");
			for(j=i-16 ; j<i ; j++)
			{
				if(data[j]>=32 && data[j]<=128)
					fprintf(logfile_tcp,"%c",(unsigned char)data[j]); //if its a number or alphabet
				
				else fprintf(logfile_tcp,"."); //otherwise print a dot
			}
			fprintf(logfile_tcp,"\n");
		} 
		
		if(i%16==0) fprintf(logfile_tcp,"   ");
			fprintf(logfile_tcp," %02X",(unsigned int)data[i]);
				
		if( i==Size-1)  //print the last spaces
		{
			for(j=0;j<15-i%16;j++) fprintf(logfile_tcp,"   "); //extra spaces
			
			fprintf(logfile_tcp,"         ");
			
			for(j=i-i%16 ; j<=i ; j++)
			{
				if(data[j]>=32 && data[j]<=128) fprintf(logfile_tcp,"%c",(unsigned char)data[j]);
				else fprintf(logfile_tcp,".");
			}
			fprintf(logfile_tcp,"\n");
		}
	}
}
