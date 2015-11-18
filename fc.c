#include<string.h>
#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define MAXLINE 4096

int main(){
int readfd,writefd;
ssize_t len;
char buf[MAXLINE];

writefd=open(FIFO1,O_WRONLY,0);  
readfd=open(FIFO2,O_RDONLY,0); 

printf("Enter the file name:");
scanf("%s",buf);
len=strlen(buf);
printf("\nWritting file name %s into FIFO1\n",buf);

write(writefd,buf,len);  

printf("\nReading from the FIFO2\nContents of file %s\n",buf);

while(read(readfd,buf,MAXLINE)>0)
printf("%s\n",buf);

close(readfd);
close(writefd);
unlink(FIFO1);
unlink(FIFO2);
return 0;
}


