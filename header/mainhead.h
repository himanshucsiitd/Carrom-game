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


void *mang_alls(void *argv);
void *mang_all(void *argv);

#define BOTLEVEL 2
#define YES 1
#define NO 2
#define occupied 1
#define unoccupied -1
#define bot 2	
			//add occupied or bot on network
#define KEY_RIGHT 97
#define KEY_DOWN 115
#define KEY_UP 119
#define KEY_LEFT 100
#define KEY_CLCK 122
#define KEY_ANTICLCK 120
#define KEY_HOME 104
#define KEY_GO 13

#define isclient 2
#define isserver 1
#define offline 3
#define PORTNO atoi(argv[2])
#define SERVER_IP_NAME argv[1]

#define OUT 1
#define IN 2
#define PREVIN 3
#define POT 4
#define GITINO 5
#define bottom 0
#define left 1
#define top 2
#define right 3
#define dir_len 1

#define iteration 3150
#define factor 100.0
#define offset 0.2
#define ROOT2 1.414
#define raise 0.02
#define arc_null 0.0
#define arc_quarter 0.05
#define arc_3quarter 0.35
#define arc_full 0.6
#define arc_half 0.3
#define ring_width 0.01
#define semi_side_len 2.0
#define BAR_LEN 0.6*semi_side_len
#define BAR_DIST 0.75*semi_side_len
#define height semi_side_len * 0.1
#define edge_width semi_side_len * 0.1
#define MAIN_RAD 0.2*semi_side_len
#define SEMI_BAR_WIDTH 0.05*semi_side_len
#define BAR_RING_RAD  0.05*semi_side_len
#define BAR_RING_WIDTH 0.0075*semi_side_len
#define BAR_DISC_RAD 0.04*semi_side_len
#define HOLE_RAD 0.075*semi_side_len
#define ARROW_RAD 0.125*semi_side_len
#define ARROW_IN 0.3*semi_side_len
#define ARROW_OUT 0.75*semi_side_len
#define WIDTH 0.05
#define floatZERO 0.0
#define giti_rad 0.1
#define striker_rad 0.15
#define vmax 11
#define vmin 1

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
int color;				//have to initialise it EVERYWHERE
int mepoints;
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

struct game gameinfo;
//float e = 1.0;  commented
float v = 5.01;
int powlevel=0;
float camerax = -40.0;
float cameray = floatZERO;
float cameraz = floatZERO;
int flag = 0;
int pieces = 9;
BAR PLAYER[4];
int msgrec=0;
int para[6];
int user=0;
int botlevel;
CIRCLE STRIKER;
CIRCLE giti[GITINO];
CIRCLE holetr = {0.2, 0.2, 0.2, 0.1,(semi_side_len-HOLE_RAD), (semi_side_len-HOLE_RAD), floatZERO, floatZERO};			//radius kept zero
CIRCLE holetl = {0.2, 0.2, 0.2, 0.1,-(semi_side_len-HOLE_RAD), (semi_side_len-HOLE_RAD), floatZERO, floatZERO};
CIRCLE holebr = {0.2, 0.2, 0.2, 0.1,(semi_side_len-HOLE_RAD), -(semi_side_len-HOLE_RAD), floatZERO, floatZERO};
CIRCLE holebl = {0.2, 0.2, 0.2, 0.1,-(semi_side_len-HOLE_RAD), -(semi_side_len-HOLE_RAD), floatZERO, floatZERO};
BAR STROKE = {floatZERO, floatZERO};
float SIZEX = 900.0;
float SIZEY = 600.0;
//char buffer[256];		// size type fixed

void createmsg(int ,int ,int ,int ,int , int );

//void ispot(CIRCLE *);

int hasstop()	;
void col(CIRCLE *,CIRCLE *);

int checkpot(CIRCLE ,CIRCLE );

void ispot(CIRCLE *);

int checkcol(CIRCLE ,CIRCLE);




