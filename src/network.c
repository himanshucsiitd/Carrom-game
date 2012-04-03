#include"../header/headers.h"
#include"../header/network.h"
void startserver(int port,int inf[])
{
char buffer[256];

int cliaddlen,acceptsyscall;
static int socketsyscall=0;
static struct sockaddr_in serv_addr;
struct sockaddr_in cli_addr;
//printf("tryingto connect");

//server side
if(socketsyscall==0)
	{
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port= htons(port);		//htons converts to network byte order
	serv_addr.sin_addr.s_addr=INADDR_ANY;  			//dummy constant automaticaly gets  address of machine on which its running
	//client side
	bzero((char *) &cli_addr, sizeof(cli_addr));
	//cli_addr.sin_family=AF_INET;
	//cli_addr.sin_port= htons(atoi(argvp[1]));
	//cli_addr.sin_addr=//??

	socketsyscall=socket(AF_INET,SOCK_STREAM,0);
	bind(socketsyscall,(struct sockaddr *)&serv_addr,sizeof(serv_addr));			//tricky 
	}

listen(socketsyscall,2);				//2 can be changed to 5
cliaddlen=sizeof(cli_addr);printf("Waiting for clients!%d\n",port);
acceptsyscall=accept(socketsyscall,(struct sockaddr *)&cli_addr, &cliaddlen);printf("found someone!\n");
bzero(buffer,256);
inf[0]=acceptsyscall;
inf[1]=cli_addr.sin_addr.s_addr;
}

void error(const char *msg)
	{
	    perror(msg);
	    exit(0);
	}

int startclient(char *ipaddr,int port)
{
char buffer[256];
    int  portno,sockfd;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    portno = port;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd <= 0) //done equal to 0 also
        {
	error("ERROR opening socket");
	}
    server = gethostbyname(ipaddr);
    if (server == NULL) 
	{
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
	}
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,
    server->h_length);
    serv_addr.sin_port = htons(portno);
    printf("connect coming up\n");
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        {
	printf("tried conetin with %s ",ipaddr);
	error("ERROR connecting");
	printf("hell");
	}
    bzero(buffer,256);
    bzero(buffer,256);
    return sockfd;
}

