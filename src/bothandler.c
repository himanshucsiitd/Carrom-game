#include"../header/headers.h"
#include"../header/bothandler.h"

void *manbot1(void *input)		
	{
	int botside=atoi((char *)input);
	managebot(botside);
	}
//have to send msg to all so add create msg if bot in handling functions

void *manbot2(void *input)		
	{
	int botside=atoi((char *)input);
	managebot(botside);
	}
void *manbot3(void *input)		
	{
	int botside=atoi((char *)input);
	managebot(botside);
	}




void managebot(int botside)
{
char aibuf[256];
int hello,dummy,pow;
while(gameend!=-1)		//better condition till game ends
	{

	while(flag!=0)
		{
		sleep(1);
		}
	while(gameinfo.turn!=botside)
		{
		sleep(1);
		}
	sleep(2);
	dummy=getcord(aibuf,strikerposition,botside,hello);
	decrypt(aibuf,para);
	msgrec=1;		

	while(msgrec!=0);
	hello=getcord(aibuf,posfixed,botside,hello);
	decrypt(aibuf,para);
	msgrec=1;

	while(msgrec!=0);
	dummy=getcord(aibuf,angle,botside,hello);
	decrypt(aibuf,para);
	msgrec=1;
	while(msgrec!=0);
	if(!isfront(giti[hello],botside))
		{
		pow=3;
		}
	float distpow=caldist(STRIKER,giti[hello]);
	if(distpow>1.5)
		{
		pow=(int)((distpow-1.5)*7)%4;
		}
	while(pow>0)
	{

	while(msgrec!=0);
	dummy=getcord(aibuf,power,botside,hello);
	decrypt(aibuf,para);
	pow--;
	msgrec=1;
	}
	
	while(msgrec!=0);
	hello=getcord(aibuf,anglefixed,botside,hello);
	decrypt(aibuf,para);
	msgrec=1;
	while(msgrec!=0);			


	}
}

int getcord(char *feed,int type,int myside,int potgitino)
{

switch(type)
{
//int type,int button,int state,int power,int x, int y
case power: {sprintf(feed,"1/0/0/13/100/100");break;}
case angle: {sprintf(feed,"3/0/0/0/500/100");break;}
//case angle: {sprintf(feed,"3/0/0/0/500/300/");break;}
//case strikerposition: {sprintf(feed,"3/0/0/0/500/300/");break;}
case strikerposition: {sprintf(feed,"3/0/0/0/400/200/");break;}
case posfixed: {return sidetohole(myside,feed);break;}
case anglefixed: {stroker(potgitino,feed,myside);break;}

}
}
