#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <pthread.h>

#define BOTLEVEL 3
#define YES 1
#define NO 2
#define KEY_RIGHT 97
#define KEY_DOWN 115
#define KEY_UP 119
#define KEY_LEFT 100
#define KEY_CLCK 122
#define KEY_ANTICLCK 120
#define KEY_HOME 104
#define semi_side_len 2.0
#define BAR_LEN 0.6*semi_side_len
#define BAR_DIST 0.75*semi_side_len
#define WIDTH 0.05
#define KEY_GO 13
#define isclient 2
#define isserver 1
#define offline 3
#define PORTNO atoi(argv[5])
#define SERVER_IP_NAME argv[4]
#define OUT 1
#define IN 2
#define PREVIN 3
#define POT 4
#define GITINO 5
#define bottom 0
#define left 1
#define top 2
#define right 3
typedef struct
{
float r;
float g;
float b;
} colour;
typedef struct 
{
colour c;
float r;
float x;
float y;
float vx;
float vy;
int in;
} CIRCLE;
typedef struct
{
float x;
float y;
}BAR;
struct sides
{
char ip[20];
int there;
int sock;
int mepoints;
int color;
int mequeen;
int botlevel;
};
struct game
{
struct sides side[4];
float friction;
float erest;
int playercount;
int turn;
int me;
};
extern struct game gameinfo;
extern int msgrec;
extern int para[6];

void *manb(void *argv);
void *manl(void *argv);
void *manr(void *argv);
void *mant(void *argv);
void *mang_alls(void *argv);
void *mang_all(void *argv);

