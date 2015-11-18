#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main()
{
	int sockfd,pno,clen;
	struct sockaddr_in sadd,cadd;
	char buf[1024];
	clen = sizeof(cadd);
	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	printf("\n\tenter port : ");
	scanf("%d",&pno);

	sadd.sin_family = AF_INET;
	sadd.sin_addr.s_addr = htonl(INADDR_ANY);	
	sadd.sin_port = htons(pno);

	bind(sockfd,(struct sockaddr * )&sadd, sizeof(sadd) );
	
	//memset(&cadd,0,sizeof(cadd));
	bzero(&cadd,sizeof(cadd));
	bzero(buf,sizeof(buf));
	recvfrom(sockfd,buf,sizeof(buf),0,(struct sockaddr *)&cadd,&clen);
	printf("\nmessage from client : %s",buf);
	bzero(buf,sizeof(buf));
	printf("\n\nenter message to be sent : ");
	scanf("%s",buf);
	sendto(sockfd,buf,sizeof(buf),0,(struct sockaddr * )&cadd,clen);
	printf("\nserver terminating\n");
	close(sockfd);
	return 0;
}
