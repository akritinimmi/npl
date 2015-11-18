BEGIN{
#include<stdio.h>
ftppack=0
telpack=0
ftptime=0
teltime=0
}
{
if($1=="r"&&$3=="2"&&$4=="3")
{
ftppack=ftppack+$6;
ftptime=$2;
}
if($1=="r"&&$3=="4"&&$4=="5")
{
telpack=telpack+$6;
teltime=$2;
}
}
END{
printf("Throughput of Ftp:%fMbps",(ftppack/ftptime)*(8/1000000));
printf("Throughput of tel:%fMbps",(telpack/teltime)*(8/1000000));
}


