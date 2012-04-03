#include"../header/headers.h"
#include"../header/rules.h"




int last(int type)
{
if(type==black)
	{
	if(giti[0].in==IN && giti[2].in==IN)
		{
		return 1;
		} 
	else 
		{
		return 0;
		}
	}
else
	{
	if(giti[1].in==IN && giti[3].in==IN)
		{
		return 1;
		} 
	else 
		{
		return 0;
		}
	}

}
void donextturn()
{
do{
	gameinfo.turn=gameinfo.turn+1;
	gameinfo.turn=gameinfo.turn%4;
}
while(gameinfo.side[gameinfo.turn].there==unoccupied);
}


void result()
{
gameend=-1;

int hello=(gameinfo.me+1)%2;
if(giti[4].in==POT)
	{
	if(gameinfo.side[gameinfo.me].mequeen==YES)
		{
		printf("WIN!!");getc(stdin);
		}
	else if(gameinfo.side[hello].mequeen==YES)
		{
		printf("LOSE!!");
		getc(stdin);
		}
	}
if(gameinfo.side[gameinfo.me].mepoints==2)
	{
	printf("LOSE!!");getc(stdin);
	}
else if(gameinfo.side[hello].mequeen==2)
	{
	printf("WIN!!");getc(stdin);
	}
exit(0);
}

void place(CIRCLE *giti)
{
if(giti->in==OUT)
{
//printf("ERROR  in rules!!");
return;
}
giti->in=OUT;
giti->vx=0;
giti->vy=0;
giti->x=0;
giti->y=0;
int i=0, check=0;
for(i=0;i<GITINO;i++)
	{
	if((!circ_eq(&giti,giti[i])) && colchecker(giti))
		{
		check=1;
		break;
		}
	}
if(check==1)
	{
	giti->x=.2;
	giti->y=0;
	for(i=0;i<GITINO;i++)
		{
		if((!circ_eq(&giti,giti[i])) && colchecker(giti))
			{
			check=1;
			break;
			}
		}
	if(check==1)
		{
		giti->x=-0.2;
		giti->y=0;
		for(i=0;i<GITINO;i++)
			{
			if((!circ_eq(&giti,giti[i])) && colchecker(giti))
				{
				check=1;
				break;
				}
			}
		if(check==1)
			{
			giti->x=0;
			giti->y=0.2;
			for(i=0;i<GITINO;i++)
				{
				if((!circ_eq(&giti,giti[i])) && colchecker(giti))
					{
					check=1;
					break;
					}
				}
			if(check==1)
				{
				giti->x=0;
				giti->y=-0.2;
				for(i=0;i<GITINO;i++)
					{
					if((!circ_eq(&giti,giti[i])) && colchecker(giti))
						{
						check=1;
						break;
						}
					}
				}

			else {return;}
			}

		else {return;};
		}

	else {return;}
	}
else {return;}
}


void bringout(int type,int turn)
{
int playercolor=gameinfo.turn%2;

if(type==queen)
	{
	place(&giti[4]);
	}
else
	{
		if(playercolor==black)
			{
			if(giti[0].in==IN || giti[0].in==PREVIN)
				{
				place(&giti[0]);
				}
			else if(giti[2].in==IN || giti[2].in==PREVIN)
				{
				place(&giti[2]);
				}
			}
		else

			{
			if(giti[1].in==IN || giti[1].in==PREVIN)
				{
				place(&giti[1]);
				}
			else if(giti[3].in==IN || giti[3].in==PREVIN)
				{
				place(&giti[3]);
				}
			}


	}
}



int rules(int queencover,int turn,int doturn)		//take care if turn is mine or not and whether queen cover is true if in this turn or previous turn queen went in.
{
int playercolor=turn%2;
int whitepot=0,blackpot=0,queenpot=0,strikerpot=0,i=0;
for(;i<GITINO;i++)
	{
	if(giti[i].in==IN)
		{
		if(giti[i].c.b==1) 
			{
			whitepot++;
			}
		else if(giti[i].c.b==0)	
			{
			blackpot++;
			}
		else if(giti[i].c.b==.8)	
			{
			queenpot++;
			}

		}
	}
if(STRIKER.in==IN)
	{
	strikerpot++;
	}

//bringout function will decide which to bring out depending on gameinfo.turn%2==gameinfo.me%2 
//bringoutfunc,lastfunc,resultfunc,

if(strikerpot>0)			//queen cannit be won/lost now in any circumstance,nor can chance regained, if game ended extra placing of giti into game due to foul not counted
{
if(playercolor==white)
	{
	if(whitepot>0 && blackpot>0)
		{
		if(last(black)&& last(white))
			{
			gameinfo.side[turn].mepoints++;
			result();
			}
		else if(last(black))
			{
			result();
			}
		else if(last(white))
			{
			if(giti[4].in!=OUT)
				{
				bringout(white,turn);
				}
			else
				{
				gameinfo.side[turn].mepoints++;
				result();
				}
			}
		else
			{
			bringout(white,turn);
			}
		}
	else if(whitepot>0)
		{
		if(last(white) && giti[4].in==OUT)
			{
			gameinfo.side[turn].mepoints++;
			result();
			}
		else
			{
			bringout(white,turn);
			}
		}
	else if(blackpot>0)
		{
		if(last(black))
			{
			result();
			}
		else
			{
			bringout(white,turn);
			}
		}
	else if(queencover)
		{
		if(gameinfo.side[turn].mepoints>0 && playercolor==(gameinfo.turn%2))
			{
			gameinfo.side[turn].mepoints--;
			}
		bringout(queen,turn);
		return 0;
		}
	else
		{
		if(gameinfo.side[turn].mepoints>0 && playercolor==(gameinfo.turn%2))
			{
			gameinfo.side[turn].mepoints--;
			}
		bringout(white,turn);
		}
	if(doturn)
		{
		donextturn();
		}
	if(giti[4].in==IN || giti[4].in==PREVIN)
		{
		bringout(queen,turn);
		return 0;
		}
	}

else
	{
	if(whitepot>0 && blackpot>0)
		{
		if(last(black)&& last(white))
			{
			gameinfo.side[turn].mepoints++;
			result();
			}
		else if(last(white))
			{
			result();
			}
		else if(last(black))
			{
			if(giti[4].in!=OUT)
				{
				bringout(white,turn);
				}
			else
				{
				gameinfo.side[turn].mepoints++;
				result();
				}
			}
		else
			{
			bringout(white,turn);
			}
		}

	else if(blackpot>0)
		{
		if(last(black) && giti[4].in==OUT)
			{
			gameinfo.side[turn].mepoints++;
			result();
			}
		else
			{
			bringout(white,turn);
			}
		}
	else if(whitepot>0)
		{
		if(last(white))
			{
			result();
			}
		else
			{
			bringout(white,turn);
			}
		}
	else if(queencover)
		{
		if(gameinfo.side[turn].mepoints>0 && playercolor==(gameinfo.turn%2))
			{
			gameinfo.side[turn].mepoints--;
			}
		bringout(queen,turn);
		if(doturn)
			{
			donextturn();
			}
		return 0;
		}
	else
		{
		if(gameinfo.side[turn].mepoints>0 && playercolor==(gameinfo.turn%2))
			{
			gameinfo.side[turn].mepoints--;
			}
		bringout(white,turn);

		}
	if(doturn)
		{
		donextturn();
		}
	if(giti[4].in==IN || giti[4].in==PREVIN)
		{
		bringout(queen,turn);
		return 0;
		}

	}



}
else
{
if(playercolor==white)
	{
	if(whitepot>0 && blackpot>0)
		{
		if(last(white)&&last(black))
			{
			gameinfo.side[turn].mepoints++;
			if(queencover)
				{
				gameinfo.side[turn].mepoints=gameinfo.side[turn].mepoints+3;
				giti[4].in=POT;
				gameinfo.side[turn].mequeen=YES;
				}
			result();
			}		
		else if(last(white))
			{
			gameinfo.side[turn].mepoints++;
			if(queencover)
				{
				gameinfo.side[turn].mepoints=gameinfo.side[turn].mepoints+3;
				giti[4].in=POT;
				gameinfo.side[turn].mequeen=YES;
				}
			result();
			}
		else if(last(black))
			{
			if(queencover)
				{
				giti[4].in=POT;
				}
			result();
			}
		else
			{
			gameinfo.side[turn].mepoints++;
			if(doturn)
				{
				donextturn();
				}
			if(queencover)
				{
				gameinfo.side[turn].mepoints=gameinfo.side[turn].mepoints+3;
				giti[4].in=POT;
				gameinfo.side[turn].mequeen=YES;
				}
			}
		}
	else if(whitepot>0)
		{
		if(last(white))
			{
			gameinfo.side[turn].mepoints++;
			if(queencover)
				{
				gameinfo.side[turn].mepoints=gameinfo.side[turn].mepoints+3;
				giti[4].in=POT;
				gameinfo.side[turn].mequeen=YES;
				}
			result();
			}
		else
			{
			gameinfo.side[turn].mepoints++;
			if(queencover)
				{
				gameinfo.side[turn].mepoints=gameinfo.side[turn].mepoints+3;
				giti[4].in=POT;
				gameinfo.side[turn].mequeen=YES;
				}
			}
		}
	else if(blackpot>0)
		{
		if(last(black))
			{
			if(queencover)
				{
				giti[4].in=POT;
				}
			result();
			}
		else
			{
			if(queencover)
				{
				giti[4].in=POT;
				}
			if(doturn)
				{
				donextturn();
				}
			}
		}
	else if(giti[4].in==IN)
		{
		return 1;
		}		
	else
		{
		if(queencover)
			{
			bringout(queen,turn);
			}
		if(doturn)
			{
			donextturn();
			}
		return 0;
		}
	}
else
	{
	if(whitepot>0 && blackpot>0)
		{
		if(last(white)&&last(black))
			{
			gameinfo.side[turn].mepoints++;
			if(queencover)
				{
				gameinfo.side[turn].mepoints=gameinfo.side[turn].mepoints+3;
				giti[4].in=POT;
				gameinfo.side[turn].mequeen=YES;
				}
			result();
			}		
		else if(last(black))
			{
			gameinfo.side[turn].mepoints++;
			if(queencover)
				{
				gameinfo.side[turn].mepoints=gameinfo.side[turn].mepoints+3;
				giti[4].in=POT;
				gameinfo.side[turn].mequeen=YES;
				}
			result();
			}
		else if(last(white))
			{
			if(queencover)
				{
				giti[4].in=POT;
				}
			result();
			}
		else
			{
			gameinfo.side[turn].mepoints++;
			if(doturn)donextturn();
			if(queencover)
				{
				gameinfo.side[turn].mepoints=gameinfo.side[turn].mepoints+3;
				giti[4].in=POT;
				gameinfo.side[turn].mequeen=YES;
				}
			}
		}
	else if(blackpot>0)
		{

		if(last(black))
			{
			gameinfo.side[turn].mepoints++;
			if(queencover)
				{
				gameinfo.side[turn].mepoints=gameinfo.side[turn].mepoints+3;
				giti[4].in=POT;
				gameinfo.side[turn].mequeen=YES;
				}
			result();
			}
		else
			{
			gameinfo.side[turn].mepoints++;
			if(queencover)
				{
				gameinfo.side[turn].mepoints=gameinfo.side[turn].mepoints+3;
				giti[4].in=POT;
				gameinfo.side[turn].mequeen=YES;
				}
			}
		}
	else if(whitepot>0)
		{

		if(last(white))
			{
			if(queencover)
				{
				giti[4].in=POT;
				}
			result();
			}
		else
			{
			if(queencover)
			{
			giti[4].in=POT;
			}
			if(doturn)
				{
				donextturn();
				}
			}
		}
	else if(giti[4].in==IN)
		{
		return 1;
		}		
	else
		{
		if(queencover)
			{
			bringout(queen,turn);
			}
		if(doturn)donextturn();
		return 0;
		}


	}
}

}
