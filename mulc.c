#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>

int main()
{
	int sfd,pno=2200,r=1;
	struct sockaddr_in lol;
	struct ip_mreq gp;
	char buf[1024];

	sfd = socket(AF_INET,SOCK_DGRAM,0);
	setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,(char *)&r,sizeof(r));
	//printf("\nenter port no : ");
	//scanf("%d",&pno);
	lol.sin_addr.s_addr = htonl(INADDR_ANY);;
	lol.sin_family = AF_INET;
	lol.sin_port = htons(pno);
	if(bind(sfd,(struct sockaddr *)&lol,sizeof(lol))<0)
	{
		printf("\nerror");
		exit(0);
	}
	gp.imr_multiaddr.s_addr = inet_addr("228.8.8.8");
	gp.imr_interface.s_addr = htonl(INADDR_ANY);

	if(setsockopt(sfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char *)&gp,sizeof(gp))<0)
	{
		printf("\nerror2 ");
		exit(0);
	}
	if(read(sfd,buf,sizeof(buf))<0)
	{
		printf("\nerror");
		exit(0);
	}
	printf("\nmsg : %s\n",buf);
	close(sfd);
	return 0;
}
