#define MASSRATIO 2
#define HOLE_RAD 0.075*semi_side_len
#define floatZERO 0.0

extern CIRCLE STRIKER;
extern CIRCLE giti[GITINO];
extern CIRCLE holetl,holetr,holebl,holebr;
int hasstop();
int circ_eq(CIRCLE a, CIRCLE b);
void col(CIRCLE *a,CIRCLE *b);
int checkpot(CIRCLE a,CIRCLE b);
void ispot(CIRCLE *git);
int checkcol(CIRCLE a,CIRCLE b);
int colchecker(CIRCLE a, CIRCLE b);
