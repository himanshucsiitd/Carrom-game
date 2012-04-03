#include"../header/headers.h"
#include"../header/man.h"

void *manl(void *argv)
{
int side=atoi((char*)argv);int nororw;
char buffer[256];
	while(gameinfo.side[side].there!=unoccupied)
		{while(msgrec==1);				
			nororw=recv(gameinfo.side[side].sock,buffer,256,0);
			decrypt(buffer,para);
			msgrec=1;
		}


}

void *manr(void *argv)
{
int side=atoi((char*)argv);int nororw;
char buffer[256];
	while(gameinfo.side[side].there!=unoccupied)
		{while(msgrec==1);
			nororw=recv(gameinfo.side[side].sock,buffer,256,0);
			decrypt(buffer,para);
			msgrec=1;

		}


}


void *mant(void *argv)
{
int side=atoi((char*)argv);int nororw;
char buffer[256];
	while(gameinfo.side[side].there!=unoccupied)
		{while(msgrec==1);
			nororw=recv(gameinfo.side[side].sock,buffer,256,0);
			decrypt(buffer,para);
			msgrec=1;

		}


}


void *manb(void *argv)
{
int side=atoi((char*)argv);int nororw;
char buffer[256];
printf("misery!\n");
	while(gameinfo.side[side].there!=unoccupied)
		{while(msgrec==1);
			
			nororw=recv(gameinfo.side[side].sock,buffer,256,0);
			decrypt(buffer,para);
			msgrec=1;

		}



}

