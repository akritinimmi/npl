#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int sockfd,newsockfd,pno;
	struct sockaddr_in servadd;
	FILE *fp;
	char buff[1024];

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	printf("\n\nenter port : ");
	scanf("%d",&pno);

	servadd.sin_family = AF_INET;
	servadd.sin_addr.s_addr = htonl(INADDR_ANY);
	servadd.sin_port = htons(pno);

	if(bind(sockfd,(struct sockaddr *)&servadd,sizeof(servadd))<0)
	{
		printf("\n\terror");
		exit(0);
	}

	listen(sockfd,5);
	newsockfd = accept(sockfd,NULL,NULL);
	close(sockfd);
	bzero(buff,sizeof(buff));
	read(newsockfd,buff,1024);
	printf("\nrequested file : %s",buff);
	fp = fopen(buff,"r");
	if(!fp)
	{
		printf("\n\nwrong name");
		bzero(buff,sizeof(buff));
		strcpy(buff,"wrong name");
		write(newsockfd,buff,strlen(buff));
		close(newsockfd);
		exit(0);
	}
	while(!feof(fp))
	{
		bzero(buff,sizeof(buff));	
		fgets(buff,1024,fp);
		write(newsockfd,buff,strlen(buff));
		puts(buff);
	}
	printf("\nserver bye");
	close(newsockfd);
	close(fp);
	return 0;
}
