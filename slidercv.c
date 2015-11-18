#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define RECVBUF 20
int AdvWindow=0;
main()
{
int std, lfd, len, port, i, j, status, choice;
char str[20], str1[20], err[20],advWindow[1024] , ack_str[20];
int ack;
char frame1[20] ;
char frame[20] ;
int sendsize=5;
char *recv_str;
recv_str=malloc(50);
memset(recv_str, 0, 20);
int yes=1;
struct sockaddr_in saddr, caddr;
port=5000;
printf("Enter the port address:");
scanf("%d", &port);
std = socket(AF_INET, SOCK_STREAM, 0);
if(std<0)
perror("Error");
// lose the pesky "address already in use" error message
if (setsockopt(std, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1)
{
perror("setsockopt");
// exit(1);
}
bzero(&saddr, sizeof(saddr));
saddr.sin_family = AF_INET;
saddr.sin_addr.s_addr = htonl(INADDR_ANY);
saddr.sin_port = htons(port);
lfd = bind(std, (struct sockaddr *)&saddr, sizeof(saddr));
if(lfd)
perror("Bind Error");
listen(std, 5);
len = sizeof(&caddr);
lfd = accept(std, (struct sockaddr *)&caddr, &len);
//AdvWindow=rand(20);
len=-1;
i=0;
for(;;)
{
//media
memset(frame, 0, 20);
recv(lfd, frame, 100, 0) ;
if(strcmp(frame, "Exit") == 0)
{
printf("\nExitting!\n");
break;
}
int err=rand()%8;
int i5;
if(err < 4 )
{
memset(frame1, 0, 20);
for(i5=0;i5<err;i5++)
frame1[i5]=frame[i5];
recv_str=(char*) strcat(recv_str,frame1);
frame[err]='x';
printf("\n\nIntroduce error at frame= %dError at = %d , Error full frame recved = %s -- Retransmit ",err , i+err , frame);
i=i+ err;
ack=i;
// continue;
}
//receiver
else
{
printf("\n\nRecving frame (SUCCUSS ) = %s,Recving WINDOW: start seqno= %d - end seqno= %d",frame, i, i+ sendsize);
recv_str=(char*) strcat(recv_str,frame);
i=i+ sendsize;
ack=i;
}
printf("\n Recver : Sending ACK back to sender ack = %d ", ack);
sprintf(ack_str,"%d",ack);
send(lfd, ack_str, strlen(ack_str), 0) ;
} /*END OF FOR*/
printf("\nReceived Final str at Destination = %s \n ", recv_str);
close(std);
}
