BEGIN{
#include<stdio.h>
count=0
}
{
if($1=="c") {
printf("The [ %s ] Packet occured collision at the node:[ %s ]\n",$5,$3);
count++;
}
}
END{
printf("\n***************************************\n");
printf("\nThe Total Packet Collision %d", count);
printf("\n***************************************\n");
}

