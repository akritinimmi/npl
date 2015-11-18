#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main()
{
	int sfd,pno,clen;
	struct sockaddr_in saddr,cadd;
	char buf[1024],host[30];

	printf("\nenter port no : ");
	scanf("%d",&pno);
	printf("\nenter host : ");
	scanf("%s",host);
	sfd = socket(AF_INET,SOCK_DGRAM,0);
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = inet_addr(host);
	saddr.sin_port = htons(pno);
	clen = sizeof(cadd);
	//bind(sfd,(struct sockaddr *)&saddr,sizeof(saddr));
	bzero(buf,sizeof(buf));
	printf("\nenter msg : ");
	scanf("%s",buf);
	sendto(sfd,buf,strlen(buf),0,(struct sockaddr *)&saddr,sizeof(saddr));
	bzero(buf,sizeof(buf));
	recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr *)&cadd,&clen);
	printf("\nmessage from server : %s",buf);
	close(sfd);
	printf("\nbye\n");
	return 0;
}
