#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main()
{
	int sfd,pno=2200;
	struct sockaddr_in gadd;
	struct in_addr lol;
	char msg[] = "hello pple";

	sfd = socket(AF_INET,SOCK_DGRAM,0);
	//printf("\nenter port : ");
	//scanf("%d",&pno);
	gadd.sin_family = AF_INET;
	gadd.sin_port = htons(pno);
	gadd.sin_addr.s_addr = inet_addr("228.8.8.8");
	
	lol.s_addr = htonl(INADDR_ANY);
	setsockopt(sfd,IPPROTO_IP,IP_MULTICAST_IF,(char *)&lol,sizeof(lol));
	sendto(sfd,msg,strlen(msg),0,(struct sockaddr *)&gadd,sizeof(gadd));
	printf("\nterminating\n");
	close(sfd);
	return 0;
}
	
