#include<stdio.h>

int a[100],b[100],i,j,len,k,count=0;

//generate polynomial :g(x)=x^16+x^12+x^5+1

int gp[]={1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1};
int flag;
int main()
{
	
	void div();
	
	system("clear");
	
	printf("\n enter the length of data frame: ( 4 )  ");
	scanf("%d",&len);
	
	printf("\n enter the message:  ( 1 0 1 1 ) ");
	for(i=0;i<len;i++)
		scanf("%d",&a[i]);
	
	//append r(16) degree zero to msg bits
	for(i=0;i<16;i++)
		a[len++]=0;
	
	for(i=0;i<len;i++)
		b[i]=a[i];
	
	k=len-16;
	div();
	
	for(i=0;i<len;i++)
	     b[i]=b[i]^a[i];
	printf("\n data to be transmitted:");
	for(i=0;i<len;i++)
	printf("%2d",b[i]);
	

	printf("\nwhether you wish to introduce error(1) or not(0) : ");	
	scanf("%d",&flag);
	if(flag==0)
	{	for(i=0;i<len;i++)
		   a[i]=b[i];
	}
	else
	{	for(i=0;i<len;i++)
		{	a[i]=b[i]^(rand()%2);
		}
	}	

	printf("recived message is=");
	for(i=0;i<len;i++)
	printf("%2d ",a[i]);



	div();
	for(i=0;i<len;i++)
	{
	  if(a[i]!=0)
	  {
	   printf("\n error  in recieved data");
	   goto END;
	  }
        }
   	printf(" \n data recieved in error free");
END: printf("\n remender is:");
	for(i=(len-16);i<len;i++)
	printf("%2d",a[i]);
	printf("\n");
}

void div()
{
	for(i=0;i<k;i++)
	{
	 if(a[i]==gp[0])
 	  {
	  for(j=i;j<17+i;j++)
		a[j]=a[j]^gp[count++];
 	  }
 	count=0;
 	}
}
