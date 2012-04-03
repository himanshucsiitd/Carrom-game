extern int flag;
#define strikerposition 1
#define posfixed 2
#define power 3
#define angle 4
#define anglefixed 5
int getcord(char *feed,int type,int,int );
void managebot(int);
void *manbot1(void *input);
void *manbot2(void *input);
void *manbot3(void *input);
extern CIRCLE giti[GITINO];
extern CIRCLE STRIKER;
extern int gameend;
