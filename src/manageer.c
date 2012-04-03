#include"../header/headers.h"
#include"../header/manageer.h"
int checkpos(char *buffer,int *vicside,char *ipaddress)
	{
	char *info[20];
	decryptstring(buffer,info);
	*vicside=atoi(info[0]);
	strcpy(ipaddress,info[2]);
	if(gameinfo.side[atoi(info[0])].there==occupied)
		{
		return -1;
		}
	else if(atoi(info[1])==0)
		{
		return 1;
		}
	else return 2;
	}

void sendgameinfo(char *buffer)
{
char temp[11];
sprintf(temp,"%d",gameinfo.side[bottom].there);
strcpy(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%d",gameinfo.side[left].there);
strcat(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%d",gameinfo.side[top].there);
strcat(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%d",gameinfo.side[right].there);
strcat(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%s",gameinfo.side[bottom].ip);
strcat(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%s",gameinfo.side[left].ip);
strcat(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%s",gameinfo.side[top].ip);
strcat(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%s",gameinfo.side[right].ip);
strcat(buffer,temp);
strcat(buffer,"/");

sprintf(temp,"%d",gameinfo.playercount);
strcat(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%f",gameinfo.friction/.005);
strcat(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%f",gameinfo.erest/.001);
strcat(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%d",gameinfo.turn);
strcat(buffer,temp);
strcat(buffer,"/");
sprintf(temp,"%d",gameinfo.me);
strcat(buffer,temp);
strcat(buffer,"/");		//extra added
}



void *mang_all(void *portno)
{
int port=atoi((char *)portno);
int syscall,noworr,valid,side;int netinfo[2];
char *ipaddress=(char *)malloc(20*(sizeof(char)));;
pthread_t man_left,man_top,man_right,man_bottom;
char buffer[256];
while(1)		//better condition??
	{
	bzero(buffer,256);
	printf("WAITING!\n");
	startserver(port,netinfo);
	noworr=recv(netinfo[0],buffer,256,0);//client wrote its position relative to this comp and whether it has game info and machine name
	valid=checkpos(buffer,&side,ipaddress);
	//extract side from buffer
	printf("neti==%d\n",netinfo[0]);
	if(valid==-1)
		{
		sprintf(buffer,"0");
		noworr=send(netinfo[0],buffer,strlen(buffer),0);
		}
	else if(valid==1)
		{
		//for new client connecting to this as server
		sendgameinfo(buffer);
		noworr=send(netinfo[0],buffer,strlen(buffer),0);		//check for buffer overflow
		//updategameinfo(side,syscall);			//playercount
		gameinfo.side[side].sock=netinfo[0];
		gameinfo.side[side].there=occupied;
		strcpy(gameinfo.side[side].ip,ipaddress);
		gameinfo.playercount++;

		printf("side===%d\n",side);
		switch(side)
			{
			case left: {pthread_create(&man_left,NULL,manl,"1");break;}
			case right: {pthread_create(&man_right,NULL,manr,"3");break;}
			case top: {pthread_create(&man_top,NULL,mant,"2");break;}
			case bottom: {pthread_create(&man_bottom,NULL,manb,"0");break;}

			}
		}
	else if(valid==2)
		{
		// for client is already connected to some comp. thus having game info
		gameinfo.side[side].sock=netinfo[0];
		gameinfo.side[side].there=occupied;
		strcpy(gameinfo.side[side].ip,ipaddress);

		gameinfo.playercount++;

		switch(side)
			{
			case left: {pthread_create(&man_left,NULL,manl,"1");break;}
			case right: {pthread_create(&man_right,NULL,manr,"3");break;}
			case top: {pthread_create(&man_top,NULL,mant,"2");break;}
			case bottom: {pthread_create(&man_bottom,NULL,manb,"0");break;}
			}
		}
	}
}



void *mang_alls(void *argv)
{

//side is passed as absolute frame
char *serverip,*parameter;
parameter=(char*)argv;
serverip=strtok(parameter,"/");

int portno=atoi(strtok(NULL,"/"));

int side=atoi(strtok(NULL,"/")),sockfd,k,noworr,socketid;
char buffer[256];
char *info[20];
for(k=0;k<20;k++)
	{
	info[k]=(char *)malloc(20*(sizeof(char)));
	}

sockfd=startclient(serverip,portno);
char help[20];
gethostname(help,20);
sprintf(buffer,"%d/0/",side);
strcat(buffer,help);				
noworr=send(sockfd,buffer,strlen(buffer),0);
noworr=recv(sockfd,buffer,256,0);
pthread_t man_left,man_right,man_bottom,man_top,mang;
//tokenize buffer
decryptstring(buffer,info);
gameinfo.me=side;
gameinfo.side[side].mepoints=0;
gameinfo.side[side].mequeen=NO;


int i,j=0;
//updatemygameinfo;
gameinfo.playercount=atoi(info[8])+1;			//make sure abotut this that not added twice
gameinfo.friction=atof(info[9])*0.005;
gameinfo.erest=atof(info[10])*0.001;

gameinfo.turn=atoi(info[11]);
for(i=0;i<4;i++)
	{
	gameinfo.side[i].there=atoi(info[i]);
	strcpy(gameinfo.side[i].ip,info[i+4]);
	}





//figure out positions of others fromgame info, 
for(i=0;i<4;i++)
{
if(i==side)
	{
	printf("side==%d\n",side);
	gameinfo.side[side].there=occupied;
	gethostname(gameinfo.side[side].ip,20);
	continue;
	}		//add for server too
if(atoi(info[i])==occupied)
	{
	if(i!=atoi(info[12]))
		{
		socketid=startclient(info[4+i],portno);gethostname(help,20);
		sprintf(buffer,"%d/1/",side);
		strcat(buffer,help);				//why 1 -it implies already hve info??
		noworr=send(socketid,buffer,strlen(buffer),0);
		}
	else
		{
		socketid=sockfd;
		}
	gameinfo.side[i].sock=socketid;
	switch(i)
		{
		case left: {pthread_create(&man_left,NULL,manl,"1");break;}
		case right: {pthread_create(&man_right,NULL,manr,"3");break;}
		case top: {pthread_create(&man_top,NULL,mant,"2");break;}
		case bottom: {pthread_create(&man_bottom,NULL,manb,"0");break;}

		}
	}

}
char tem_ps[10];printf("exiting with portno=%d\n",portno);
sprintf(tem_ps,"%d",portno);
pthread_create(&mang,NULL,mang_all,tem_ps);			

getc(stdin);



}

