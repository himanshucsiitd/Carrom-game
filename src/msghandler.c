#include"../header/headers.h"
#include"../header/msghandler.h"

void decrypt(char *buffer,int info[])		
	{
	char *part;
	part=strtok(buffer,"/");
	int i=0;
	while(part!=NULL)
		{if(i>5)break;
		info[i]=atoi(part);
		part=strtok(NULL,"/");
		i++;
		}
buffer[0]='\0';	
	}
void decryptstring(char *buffer,char *info[20])		
	{
	char *part;
	part=strtok(buffer,"/");
	int i=0;					
	while(part!=NULL)
		{
		info[i]=(char *)malloc(20*(sizeof(char)));
		strcpy(info[i],part);
		part=strtok(NULL,"/");
		i++;
		}
//return info;	
	}

void createmsg(int type,int button,int state,int power,int x, int y)		//gameinfo
{
/*createmsg(0,0,0,0,0,0);
createmsg(1,0,0,13,x,y);
createmsg(2,button,state,0,x,y);
createmsg(3,0,0,0,x,y);
*/

char buffer[256];
char temp[11];
sprintf(temp,"%d",type);
strcpy(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%d",button);
strcat(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%d",state);
strcat(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%d",power);
strcat(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%d",x);
strcat(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%d",y);
strcat(buffer,temp);
strcat(buffer,"/");
int i;
int nrorwch;
for(i=0;i<4;i++)
{
if(i!=gameinfo.me && gameinfo.side[i].there==occupied)
	{
	nrorwch=send(gameinfo.side[i].sock,buffer,strlen(buffer),0);
	}
/*printf("msg is %s\n",buffer);*/

}
}

