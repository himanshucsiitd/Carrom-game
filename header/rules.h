#define white 1
#define black 0
#define queen 3
#define occupied 1
#define unoccupied -1

extern CIRCLE STRIKER;
extern CIRCLE giti[GITINO];
int gameend;
int rules(int queencover,int turn,int doturn);
void bringout(int type,int turn);
void place(CIRCLE *giti);
void donextturn();
int last(int type);
