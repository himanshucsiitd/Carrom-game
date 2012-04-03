extern CIRCLE holetr,holetl,holebl,holebr;
void potgiti(CIRCLE,int,char[]);
void potnow(CIRCLE ,CIRCLE ,CIRCLE ,CIRCLE,CIRCLE, int,char[]);
float probcalc(CIRCLE git, CIRCLE holea,CIRCLE holeb,CIRCLE holec,CIRCLE holed,float hitend,float a,float b,float c ,float d );
float caldist(CIRCLE , CIRCLE );
extern CIRCLE giti[GITINO];
extern float SIZEX,SIZEY;
extern int botlevel;
void stroker(int gitino,char msg[],int side);
int isfront(CIRCLE git,int side);
float getprob(CIRCLE git,int side);
int sidetohole(int comside,char msg[]);
float mod(float x);
#define white 1
#define black 0
#define queen 3
#define WALL_DIST 1.7

