#include"../header/headers.h"
#include"../header/aibot1.h"
#define striker_rad 0.15
//int botlevel=1;

void fillxy(CIRCLE giti,CIRCLE potin,float *xco,float *yco)
{
float x1,x2,x3,y1,y2,y3,costh,sinth,tanth,cotth;
CIRCLE he1,he2;
tanth=(potin.y-giti.y)/(potin.x-giti.x);
//costh=1/sqrt(1+tanth*tanth);
//sinth=tanth*sinth;
cotth=1/tanth;
sinth=1/(sqrt(1+cotth*cotth));
costh=cotth*sinth;
he1.x=striker_rad*costh+giti.x;
he1.y=striker_rad*sinth+giti.y;
he2.x=-1*striker_rad*costh+giti.x;
he2.y=-1*striker_rad*sinth+giti.y;

x2=caldist(he1,potin);
x3=caldist(he2,potin);
if(x2<x3)
	{
	*xco=he2.x;
	*yco=he2.y;
}
else
	{
	*xco=he1.x;
	*yco=he1.y;

	}

}

void stroker(int gitino,char msg[],int side)
{
int flaghelp;
int xcor,ycor;
float xco,yco;
float help1,help2;
float x1,x2,x3,y1,y2,y3,factor,temp,temp2;
int whichhole=0;

if(isfront(giti[gitino],side))
	{
	if(gameinfo.side[gameinfo.turn].botlevel==1)
		{
		xco=giti[gitino].x;
		yco=giti[gitino].y;
		}
else
	{
	switch(side)
		{
		case bottom: 
			{
			temp=caldist(giti[gitino],holetl);
			temp2=caldist(giti[gitino],holetr);
			if(temp<temp2)
				{
				fillxy(giti[gitino],holetl,&xco,&yco);
				}
			else
				{
				fillxy(giti[gitino],holetr,&xco,&yco);
				}
			break;
			}
		case left:   
			{
			temp=caldist(giti[gitino],holebr);
			temp2=caldist(giti[gitino],holetr);
			if(temp<temp2)
				{
				fillxy(giti[gitino],holebr,&xco,&yco);
				}
			else
				{
				fillxy(giti[gitino],holetr,&xco,&yco);
				}
			break;
			}
		case top: 
			{
			temp=caldist(giti[gitino],holebl);
			temp2=caldist(giti[gitino],holebr);
			if(temp<temp2)
				{
				fillxy(giti[gitino],holebl,&xco,&yco);
				}
			else
				{
				fillxy(giti[gitino],holebr,&xco,&yco);
				}
			break;
			}
		case right:   
			{
			temp=caldist(giti[gitino],holebl);
			temp2=caldist(giti[gitino],holetl);
			if(temp<temp2)
				{
				fillxy(giti[gitino],holebl,&xco,&yco);
				}
			else
				{
				fillxy(giti[gitino],holetl,&xco,&yco);
				}
			break;
			}

		}

	}

	}
else
{
if(gameinfo.side[gameinfo.turn].botlevel<=2)
{
x2=giti[gitino].x;
y2=giti[gitino].y;
}
else
{
flaghelp=1;
fillxy(giti[gitino],holetl,&x2,&y2);
}
switch(side)
	{
	case bottom: 
		{
		temp=caldist(giti[gitino],holebl);
		temp2=caldist(giti[gitino],holebr);
		if(temp<temp2)
			{
			if(flaghelp==1)fillxy(giti[gitino],holebl,&x2,&y2);
			whichhole=-1;
			}
		else
			{
			if(flaghelp==1)fillxy(giti[gitino],holebr,&x2,&y2);
			whichhole=1;
			}
		x1=whichhole*.8*BAR_DIST;
		y1=-BAR_DIST;
		y3=WALL_DIST;
		yco=y3;
		factor=(y2-y3)/(y1-y3);
		xco=(factor*x1+x2)/(factor+1);
		break;
		}
	case left:   
		{
		temp=caldist(giti[gitino],holebl);
		temp2=caldist(giti[gitino],holetl);
		if(temp<temp2)
			{
			if(flaghelp==1)fillxy(giti[gitino],holebl,&x2,&y2);
			whichhole=-1;
			}
		else
			{
			if(flaghelp==1)fillxy(giti[gitino],holetl,&x2,&y2);
			whichhole=1;
			}
		y1=whichhole*.8*BAR_DIST;
		x1=-BAR_DIST;
		x3=WALL_DIST;
		xco=x3;
		factor=(x2-x3)/(x1-x3);
		yco=(factor*y1+y2)/(factor+1);
		break;
		}
	case top: 
		{
		temp=caldist(giti[gitino],holetl);
		temp2=caldist(giti[gitino],holetr);
		if(temp<temp2)
			{
			if(flaghelp==1)fillxy(giti[gitino],holetl,&x2,&y2);
			whichhole=-1;
			}
		else
			{
			if(flaghelp==1)fillxy(giti[gitino],holetr,&x2,&y2);
			whichhole=1;
			}
		x1=whichhole*.8*BAR_DIST;
		y1=BAR_DIST;
		y3=-WALL_DIST;
		yco=y3;
		factor=(y2-y3)/(y1-y3);
		xco=(factor*x1+x2)/(factor+1);
		break;
		}
	case right:   
		{
		temp=caldist(giti[gitino],holebr);
		temp2=caldist(giti[gitino],holetr);
		if(temp<temp2)
			{
			if(flaghelp==1)fillxy(giti[gitino],holebr,&x2,&y2);
			whichhole=-1;
			}
		else
			{
			if(flaghelp==1)fillxy(giti[gitino],holetr,&x2,&y2);
			whichhole=1;
			}
		y1=whichhole*.8*BAR_DIST;
		x1=BAR_DIST;
		x3=-WALL_DIST;
		xco=x3;
		factor=(x2-x3)/(x1-x3);
		yco=(factor*y1+y2)/(factor+1);
		break;
		}

	}



}
xcor=xco*128+SIZEX/2;

ycor=-1*(yco*128)+SIZEY/2;
sprintf(msg,"2/0/0/0/%d/%d/",xcor,ycor);

}

int isfront(CIRCLE git,int side)
{
float temp;
switch(side)
	{
	case bottom: {temp=git.y;break;}
	case left: {temp=git.x;break;}
	case top: {temp=-git.y;break;}
	case right: {temp=-git.x;break;}


	}
if(temp>(-1*BAR_DIST+.05))
{
return 1;
}
else {return 0;}
}

float caldist(CIRCLE a, CIRCLE b)
{
return(sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)));
}

float probcalc(CIRCLE git, CIRCLE holea,CIRCLE holeb,CIRCLE holec,CIRCLE holed,float hitend,float a,float b,float c ,float d )
{
CIRCLE dummy,dummy2;
dummy.x=a;
dummy.y=b;
dummy2.x=c;
dummy2.y=d;
float dist1,dist2,mindist,sidedist,heightdist,strikedist1,strikedist2,minstrikedist,backdist1,backdist2,minbackdist;
if(hitend>-BAR_DIST)
	{
	dist1=caldist(holea,git);
	dist2=caldist(holeb,git);
	if(dist1<dist2)
		{
		mindist=dist1;
		}
	else
		{
		mindist=dist2;
		}
	strikedist1=caldist(dummy,git);
	strikedist2=caldist(dummy2,git);
	if(strikedist1<strikedist2)
		{
		minstrikedist=strikedist1;
		}
	else
		{
		minstrikedist=strikedist2;
		}
	return (1/(.5*mindist+.5*minstrikedist));
	}
else 
	{
	if(gameinfo.side[gameinfo.turn].botlevel<=2)
		{
		return 0;
		}
	backdist1=caldist(holec,git);
	backdist2=caldist(holed,git);
	if(backdist1<backdist2)
		{
		minbackdist=backdist1;
		}
	else
		{
		minbackdist=backdist2;
		}

	return 1/(1+minbackdist);

	}
}


float getprob(CIRCLE git,int side)
	{
	float chance;
	switch(side)
		{
		case bottom: {chance=probcalc(git,holetl,holetr,holebl,holebr,git.y,-BAR_DIST*.6,-BAR_DIST,BAR_DIST*.6,-BAR_DIST);break;}
		case left: {chance=probcalc(git,holebr,holetr,holetl,holebl,git.x,-BAR_DIST,BAR_DIST*.6,-BAR_DIST,-BAR_DIST*.6);break;}
		case top: {chance=probcalc(git,holebl,holebr,holetl,holetr,-git.y,-BAR_DIST*.6,BAR_DIST,BAR_DIST*.6,BAR_DIST);break;}
		case right: {chance=probcalc(git,holetl,holebl,holetr,holebr,-git.x,BAR_DIST,BAR_DIST*.6,BAR_DIST,-BAR_DIST*.6);break;}

		}
	return chance;
	}


int sidetohole(int comside,char msg[])
{
float prob1,prob2,prob3;
switch(gameinfo.side[comside].mepoints)
{
case 0:	
	{
	prob1=getprob(giti[4],comside);
	if(comside%2==white)
		{
		prob2=getprob(giti[1],comside);
		prob3=getprob(giti[3],comside);
		}
	else
		{
		prob2=getprob(giti[0],comside);
		prob3=getprob(giti[2],comside);
		}
	if(giti[4].in!=OUT)
		{
		prob1=0;
		}
	if(prob1>=prob2)
		{
		if(prob1>=prob3)
			{
			potgiti(giti[4],comside,msg);
			return 4;
			}
		else
			{
			if(comside%2==white)
				{
				potgiti(giti[3],comside,msg);
				return 3;
				}
			else
				{
				potgiti(giti[2],comside,msg);
				return 2;
				}
			}
		}
	else if(prob2>=prob3)
		{
		if(comside%2==white)
			{
			potgiti(giti[1],comside,msg);
			return 1;
			}
		else
			{
			potgiti(giti[0],comside,msg);
			return 0;
			}
		}
	else
		{
		if(comside%2==white)
			{
			potgiti(giti[3],comside,msg);
			return 3;
			}
		else
			{
			potgiti(giti[2],comside,msg);
			return 2;
			}
		}

	break;
	}

case 1:	
	{
	if(giti[4].in!=OUT)
		{
		if(comside%2==white)
			{
			if(giti[1].in==OUT)
				{
				potgiti(giti[1],comside,msg);
				return 1;
				}
			else
				{
				potgiti(giti[3],comside,msg);
				return 3;
				}
			}
		else
			{
			if(giti[0].in==OUT)
				{
				potgiti(giti[1],comside,msg);
				return 1;
				}
			else
				{
				potgiti(giti[2],comside,msg);
				return 2;
				}
			}
		}
	else
		{
		potgiti(giti[4],comside,msg);
		return 4;
		}
	break;
	}
case 4: 
	{
	if(comside%2==white)
		{
		if(giti[1].in==OUT)
			{
			potgiti(giti[1],comside,msg);
			return 1;
			}
		else
			{
			potgiti(giti[3],comside,msg);
			return 3;
			}
		}
	else
		{
		if(giti[0].in==OUT)
			{
			potgiti(giti[1],comside,msg);
			return  1;
			}
		else
			{
			potgiti(giti[2],comside,msg);
			return 2;
			}
		}
	break;
	}


}

}


void potgiti(CIRCLE git,int side,char msg[])
{
switch(side)
	{
	case bottom: {potnow(git,holetl,holetr,holebl,holebr,side,msg);break;}		//negativefirst
	case left: {potnow(git,holebr,holetr,holebl,holetl,side,msg);break;}
	case top: {potnow(git,holebl,holebr,holetl,holetr,side,msg);break;}
	case right: {potnow(git,holetl,holebl,holebr,holetr,side,msg);break;}

	}

}

float mod(float x)
	{

	if(x<0)
		{
		return(-x);
		}
	else 
		{
		return x;
		}
	}

void potnow(CIRCLE pot,CIRCLE closea,CIRCLE closeb,CIRCLE fara,CIRCLE farb, int side,char msg[])
{
float coefe=1;
float strikerx[4];
float strikery[4];
float temp,temp2,take;
float xco,yco;
int xcor,ycor;
float help;
if(isfront(pot,side)  || gameinfo.side[gameinfo.turn].botlevel<2)
	{
	temp=(pot.y-closea.y)/(pot.x-closea.x);
	temp2=(pot.y-closeb.y)/(pot.x-closeb.x);
	if(side%2==0)
		{
		if(mod(pot.x-closeb.x)>mod(pot.x-closea.x))
			{
			take=temp;
			}
		else
			{
			take=temp2;
			}
		}
	else
		{
		if(mod(pot.y-closeb.y)>mod(pot.y-closea.y))
			{
			take=temp;
			}
		else
			{
			take=temp2;
			}
		}
	strikerx[0]=pot.x+(-BAR_DIST-pot.y)/take;
	strikerx[1]=-BAR_DIST;
	strikerx[2]=pot.x+(BAR_DIST-pot.y)/take;
	strikerx[3]=BAR_DIST;
	strikery[0]=-BAR_DIST;
	strikery[1]=pot.y+(-BAR_DIST-pot.x)*take;
	strikery[2]=BAR_DIST;
	strikery[3]=pot.y+(BAR_DIST-pot.x)*take;
	//char msg[30];
	xco=strikerx[side];
	yco=strikery[side];

	}
else
	{
	float x1,x2,x3,y1,y2,y3,factor;
	int whichhole=0;
	x2=pot.x;
	y2=pot.y;
	temp=caldist(pot,fara);
	temp2=caldist(pot,farb);
	if(temp<temp2)
		{
		whichhole=-1;
		}
	else
		{
		whichhole=1;
		}
	switch(side)
		{
		case bottom: {x1=whichhole*.7*BAR_DIST;y1=-BAR_DIST;break;}
		case left:   {y1=whichhole*.7*BAR_DIST;x1=-BAR_DIST;break;}
		case top: {x1=whichhole*.7*BAR_DIST;y1=BAR_DIST;break;}
		case right:   {y1=whichhole*.7*BAR_DIST;x1=BAR_DIST;break;}

		}
	xco=x1;
	yco=y1;
	}
xcor=xco*128+SIZEX/2;

ycor=-1*(yco*128)+SIZEY/2;


sprintf(msg,"2/0/0/0/%d/%d/",xcor,ycor);
}
