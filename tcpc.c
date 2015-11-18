#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main()
{
	int sockfd,pno;
	struct sockaddr_in sadd;
	char buff[1024],host[30];
	
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	printf("\nenter host ip : ");
	scanf("%s",host);
	printf("\nenter port no : ");
	scanf("%d",&pno);
	
	sadd.sin_family = AF_INET;
	sadd.sin_addr.s_addr = inet_addr(host);
	sadd.sin_port = htons(pno);
	
	if(connect(sockfd , (struct sockaddr *)&sadd, sizeof(sadd))<0)
		exit(0);

	printf("\nenter file name : ");
	bzero(buff,sizeof(buff));
	scanf("%s",buff);
	write(sockfd,buff,strlen(buff));
	bzero(buff,sizeof(buff));

	while( read(sockfd,buff,sizeof(buff)) )
	{
		puts(buff);
		bzero(buff,sizeof(buff));
	}

	close(sockfd);
	printf("\n\n");
	return 0;
}
	
