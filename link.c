#include<stdio.h>
#include<stdlib.h>
#define inf 999
int spath(int,int);
int cost[10][10],n;
void main()
{
int i,j,min,s,d;
printf("enter the number of nodes \n");
scanf("%d",&n);
printf("enter the cost");
for(i=1;i<=n;i++)
for(j=1;j<=n;j++)
{
scanf("%d",&cost[i][j]);
if(cost[i][j]==0 && i!=j)
{
	cost[i][j]=inf;
}
}
printf("sending hello packets \n");
for(i=1;i<=n;i++)
for(j=1;j<=n;j++)
{
	if(cost[i][j]!=0 && cost[i][j]!=inf)
	printf("\n sending hello packets from %d to %d node",i,j);
}
sleep(2);
printf("sending echo packets");
for(i=1;i<=n;i++)
for(j=1;j<=n;j++)
{
if(cost[i][j]!=0 && cost[i][j]!=inf)
printf("sending echo packets from %d to %d node \n",i,j);
}
sleep(2);
printf("constructing link state protocol");
for(i=1;i<=n;i++)
{
	printf("****%d****\n",i);
for(j=1;j<=n;j++)
{
	if(cost[i][j]!=0 && cost[i][j]!=inf)
		printf("%d-->%d\n",j,cost[i][j]);
}
}
printf("enter the source \n");
scanf("%d",&s);
for(i=1;i<=n;i++)
{
	min=spath(s,i);
	printf("min path from %d to %d =%d\n",s,i,min);
}
}
int spath(int s,int d)
{
struct path
{
int len;
enum{tentative,confirmed}label;
}state[10];

int i,u,j,num=2,min=inf;
for(i=1;i<=n;i++)
{
	state[i].label=tentative;
	state[i].len=cost[s][i];
}
state[s].label=confirmed;
while(num<=n)
{
	min=inf;
for(i=1;i<=n;i++)
{
if(state[i].label==tentative && state[i].len<min)
{
min=state[i].len;
u=i;
}
}
state[u].label=confirmed;
num++;
for(j=1;j<=n;j++)
{
if(state[u].len + cost[u][j]<state[j].len && state[j].label==tentative)
{
	state[j].len=state[u].len+cost[u][j];
}
}
}
return state[d].len;
}
