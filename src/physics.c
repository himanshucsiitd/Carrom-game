#include"../header/headers.h"
#include"../header/physics.h"
int hasstop()		//striker and giti arraay
	{			//corrected this
	int i, check;
	check = 0;
	for(i= 0; i<GITINO; i++)
		{
		if((giti[i].in==PREVIN || giti[i].in==IN ||(giti[i].vx<0.005 && giti[i].vy<.005 && giti[i].vx> -0.005 && giti[i].vy> -0.005)) && (STRIKER.in==IN ||(STRIKER.vx<0.005 && STRIKER.vy<.005 && STRIKER.vx> -0.005 && STRIKER.vy > -.005)))check++;
		}
	if(check == GITINO) return 1;
	return 0;
	}

int circ_eq(CIRCLE a, CIRCLE b)
{
if (a.x==b.x && a.y==b.y && a.r==b.r)
{
return 1;
}
return 0;
}

void col(CIRCLE *a,CIRCLE *b)
	{			//giti and striker array
int massratio;
if(a->r==b->r)
	{
	massratio=1;
	}
else if(a->r>b->r)
	{
	massratio=MASSRATIO;
	}
else
	{
	return(col(b,a));
	}
	float v1x,v1y,v2x,v2y;


		if(a->x==b->x)
		{
		float temp=(a->vy*(massratio-gameinfo.erest)+2*b->vy)/(massratio+1);
		float temp2=temp+gameinfo.erest*a->vy-b->vy;
		a->vy=temp;
		b->vy=temp2;
		return;
		}
/*
	float tantheta=(a->y-b->y)/(a->x-b->x);
	float cossq=1/(1+tantheta*tantheta);
	float sinsq=1-cossq;
	float sin2hal= tantheta*cossq;

	v2x=a->vx*cossq+(a->vy-b->vy)*sin2hal+b->vx*sinsq;			//split into individual operations without mass into consideration
	v2y=(a->vx-b->vx)*sin2hal+a->vy*sinsq+b->vy*cossq;
	v1x=b->vx*cossq+(b->vy-a->vy)*sin2hal+a->vx*sinsq;			
	v1y=(b->vx-a->vx)*sin2hal+b->vy*sinsq+a->vy*cossq;
*/

	float tantheta=(a->y-b->y)/(a->x-b->x);
	float cossq=1/(1+tantheta*tantheta);
	float sinsq=1-cossq;
	float sin2hal= tantheta*cossq;
	float delx=a->vx-b->vx;
	float dely=a->vy-b->vy;

	v1x=massratio*a->vx+b->vx*cossq+a->vx*sinsq-sin2hal*dely-gameinfo.erest*(delx*cossq+dely*sin2hal);
	v1y=massratio*a->vy+b->vy*sinsq+a->vy*cossq-sin2hal*delx-gameinfo.erest*(delx*sin2hal+dely*sinsq);
	v2x=b->vx+massratio*(b->vx*sinsq+a->vx*cossq)+massratio*(dely*sin2hal)+massratio*gameinfo.erest*(delx*cossq+dely*sin2hal);
	v2y=b->vy+massratio*(b->vy*cossq+a->vy*sinsq)+massratio*(delx)*sin2hal+massratio*gameinfo.erest*(delx*sin2hal+dely*sinsq);
	a->vx=v1x/(massratio+1);
	a->vy=v1y/(massratio+1);
	b->vx=v2x/(massratio+1);
	b->vy=v2y/(massratio+1);
	int i =0;
	for(i=0; i<GITINO; i++)
	{
	if(!(circ_eq(*a, giti[i]))&& !(circ_eq(*b, giti[i])))
	{
//		printf("and here\n");
	}
	}
	if(!(circ_eq(*a, STRIKER))&& !(circ_eq(*b, STRIKER)))
	{
		if(STRIKER.in != IN) checkcol(*a, STRIKER);
		if(STRIKER.in != IN) checkcol(*b, STRIKER);
	}
	}
int checkpot(CIRCLE a,CIRCLE b)
	{
	float xdif=a.x-b.x;
	float ydif=a.y-b.y;
	xdif*=xdif;
	ydif*=ydif;
	float res=xdif+ydif;
	float rad=b.r;
	rad*=rad;
	if(res<=rad+0.001)
		{
			return 1;
		}
	return 0;
	}
void ispot(CIRCLE *git)
	{
//HOLES INFO
/*CIRCLE holetr = {0.2, 0.2, 0.2, 0.1,1.6, 1.6, 0.0, 0.0};			//radius kept zero, 
CIRCLE holetl = {0.2, 0.2, 0.2, 0.1,-1.6, 1.6, 0.0, 0.0};
CIRCLE holebr = {0.2, 0.2, 0.2, 0.1,1.6, -1.6, 0.0, 0.0};
CIRCLE holebl = {0.2, 0.2, 0.2, 0.1,-1.6, -1.6, 0.0, 0.0};
*/

	if(checkpot(*git,holetl))
		{
		git->in=IN;
		printf("POT1\n");
		}
	if(checkpot(*git,holetr))
		{
		git->in=IN;
		printf("POT2\n");
		}
	if(checkpot(*git,holebl))
		{
		git->in=IN;
		printf("POT3\n");
		}
	if(checkpot(*git,holebr))
		{
		git->in=IN;
		printf("POT4\n");
		}

	}

int checkcol(CIRCLE a,CIRCLE b)
{
	if(colchecker(a,b))
		{
		col(&a, &b);
		return 1;
		}
	return 0;
	}

int colchecker(CIRCLE a, CIRCLE b)
{
	float xdif=a.x-b.x;
	float ydif=a.y-b.y;
	float vxdif = a.vx - b.vx;
	float vydif = a.vy - b.vy;
	float res=xdif*xdif+ydif*ydif;
	float vres=vxdif*vxdif+vydif*vydif;
	float sinx = ydif/(sqrt(res));
	float cosx = xdif/(sqrt(res));
	float sinvx = vydif/(sqrt(vres));
	float cosvx = vxdif/(sqrt(vres));
	float check = cosvx*cosx+sinvx*sinx;
	float rad=a.r+b.r;
	rad*=rad;
if(res+.001<=rad)
	if(check<0)
		{
		return 1;
		}
	return 0;
	}





