#include"../header/mainhead.h"
#include"../header/mainhead1.h"

void initgameinfo()		//gameinfo
{

int i;
for(i=0;i<4;i++)
{

gameinfo.side[i].there=unoccupied;
gameinfo.side[i].sock=0;
bzero(gameinfo.side[i].ip,20);
strcpy(gameinfo.side[i].ip,"no");
}
gameinfo.friction=0;
gameinfo.erest=0;
gameinfo.playercount=0;
gameinfo.turn=0;
gameinfo.me=0;


}

void Init_var()		//giti, striker, player
{
	STRIKER.in = OUT;
	STRIKER.x = floatZERO;
	STRIKER.y = -BAR_DIST;
	STRIKER.r = striker_rad;
	STRIKER.c.r = 0.3;
	STRIKER.c.g = 0.3;
	STRIKER.c.b = 0.4;
	PLAYER[0].x = floatZERO;
	PLAYER[0].y = -BAR_DIST;
	PLAYER[1].y = floatZERO;
	PLAYER[1].x = -BAR_DIST;
	PLAYER[2].x = floatZERO;
	PLAYER[2].y = BAR_DIST;
	PLAYER[3].y = floatZERO;
	PLAYER[3].x = BAR_DIST;
	giti[0].x = -.2;
	giti[1].x =  .2;
//	giti[1].y = -1.5;
//	giti[4].x= 1.6;
	giti[2].y = .2;
	giti[3].y = -.2;
int i=0;
for(i = 0; i<GITINO; i++)
{
	giti[i].c.r = (float)(i%2);
	giti[i].c.g = (float)(i%2);
	giti[i].c.b = (float)(i%2);
	giti[i].r = giti_rad;
	giti[i].in = OUT;
}
giti[4].c.r = 1.0;
giti[4].c.g = 0.8;
giti[4].c.b = 0.8;

}

void handleKeypress(unsigned char key, //The key that was pressed			//gameinfo user msgrec v camera(x,y.z)
					int x, int y) {    //The current mouse coordinates
	switch(key)
	{
		case KEY_DOWN:
			{
				camerax+=1.0f;
				if (camerax > 88) {
					 camerax = 88;
					}
				glutPostRedisplay();
				break;
			}
		case KEY_UP:
			{
				camerax-=1.0f;
				if (camerax < -88) {
					 camerax = -88;
					}
				glutPostRedisplay();
				break;
			}
		case KEY_LEFT:
			{
				cameray+=1.0f;
				if (cameray > 88) {
					 cameray = 88;
					}
				glutPostRedisplay();
				break;
			}
		case KEY_RIGHT:
			{
				cameray-=1.0f;
				if (cameray < -88) {
					 cameray = -88;
					}
				glutPostRedisplay();
				break;
			}
		case KEY_CLCK:
			{
				cameraz+=1.0f;
				if (cameraz > 360) {
					 cameraz -= 360;
					}
				glutPostRedisplay();
				break;
			}
		case KEY_ANTICLCK:
			{
				cameraz-=1.0f;
				if (cameraz < -360) {
					 cameraz += 360;
					}
				glutPostRedisplay();
				break;
			}
		case KEY_HOME:
			{
				camerax = floatZERO;
				cameray = floatZERO;
				cameraz = 0*gameinfo.me*(90);
				glutPostRedisplay();
				break;
			}
		case KEY_GO:
			{
				
				v = v+1;
				if(v>vmax) v = vmin;
				powlevel=v;
				if(msgrec!=1 &&(gameinfo.playercount>1))createmsg(1,0,0,13,x,y);else{msgrec=0;}
				glutPostRedisplay();
				break;
			}
		
		case 27: //Escape key
			{
				if(user==isclient){createmsg(4,gameinfo.me,0,0,0,0);close(gameinfo.side[gameinfo.me].sock);}
				if(user==isserver)
					{
//					close(socketsyscall);
					createmsg(4,gameinfo.me,0,0,0,0);
					close(gameinfo.side[gameinfo.me].sock);
					createmsg(1,0,0,27,x,y);
					}
				exit(0);
			}
	}
}

void initRendering() {		//none
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	Init_var();
}
void handleResize(int w, int h) {			//sizex sizey
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(60.0, (double)w / (double)h, 1.0, 200);
	SIZEX = w;
	SIZEY = h;
}

void createCircle (float rad, float center_x, float center_y, float width) {
    glBegin(GL_TRIANGLES);
	float i = 0;
	float a, b, c =0;
	a = rad - width;
	if(width >= rad) a = 0;
    for (i = 0; i < iteration; i++)
    {
	b = a * cos(i/factor);
	c = a * sin(i/factor);
	glVertex3f(b + center_x, c + center_y, floatZERO);
	b = rad * cos(i/factor + offset);
	c = rad * sin(i/factor + offset);
	glVertex3f(b + center_x, c + center_y ,floatZERO);
	b = rad * cos(i/factor - offset);
	c = rad * sin(i/factor - offset);
	glVertex3f(b + center_x, c + center_y, floatZERO);
    }
    glEnd();
}

void moveCircle (float r, float* h, float* k, float width, float* vx, float* vy, float red, float green, float blue)	//gameinfo
	{
		float i = 0;
		float b, c, d,e;

		*h = *h + 0.010*(*vx);
		*k = *k + 0.010*(*vy);
	float comp=sqrt((*vx)*(*vx)+(*vy)*(*vy));
	if(comp!=0 && gameinfo.friction <=comp)
	{
	*vx=*vx-gameinfo.friction*(*vx/comp);
	*vy=*vy-gameinfo.friction*(*vy/comp);
	}
	else if(gameinfo.friction>comp)
	{				
	*vx=0;
	*vy=0;
	}

		if(*h>=(semi_side_len-r))
		{
			*vx = -((*vx)*gameinfo.erest);
			*h = (semi_side_len-r);	
		}
		else if(*h<=-(semi_side_len-r))
		{
			*vx = -((*vx)*gameinfo.erest);
			*h = -(semi_side_len-r);	
		}
		if(*k>=(semi_side_len-r))
		{
			*vy = -((*vy)*gameinfo.erest);
			*k = (semi_side_len-r);
		}
		else if(*k<=-(semi_side_len-r))
		{
			*vy = -((*vy)*gameinfo.erest);
			*k = -(semi_side_len-r);
		}
	glPushMatrix();
		glColor3f(red, green, blue);
		createCircle(r, *h, *k, width);
		glTranslatef(floatZERO, floatZERO, WIDTH);
		createCircle(r, *h, *k, width);

		for (i = 0; i < 16; i++)
		{
		d = r * cos(i*3.14/8 + 0.2);
		e = r * sin(i*3.14/8 + 0.2);
		b = r * cos(i*3.15/8 - 0.2);
		c = r * sin(i*3.15/8 - 0.2);
	glBegin(GL_QUADS);
		glVertex3f(b + *h, c + *k, -WIDTH);
		glVertex3f(b + *h, c + *k, floatZERO);
		glVertex3f(d + *h, e + *k, floatZERO);
		glVertex3f(d + *h, e + *k, -WIDTH);
	glEnd();
	glPopMatrix();
		}
	}


void printd(CIRCLE a)
	{
	//printf("x=%lf y=%lf vx=%lf vy=%lf\n",a.x,a.y,a.vx,a.vy);
	}
void handleMotion(int x, int y1);
void handleMouse(int,int,int, int);

void drawCarrom()
{
	glBegin(GL_QUADS);

	glColor3f(1.0, 0.7, 0.2);
	glVertex3f(-semi_side_len, semi_side_len, floatZERO);
	glVertex3f(semi_side_len, semi_side_len, floatZERO);
	glVertex3f(semi_side_len, -semi_side_len, floatZERO);
	glVertex3f(-semi_side_len, -semi_side_len, floatZERO);


glColor3f(floatZERO, floatZERO, floatZERO);
	glVertex3f(-(semi_side_len + edge_width), semi_side_len, height);
	glVertex3f((semi_side_len + edge_width), semi_side_len, height);
	glVertex3f((semi_side_len + edge_width), (semi_side_len + edge_width), height);
	glVertex3f(-(semi_side_len + edge_width), (semi_side_len + edge_width), height);

	glVertex3f(-(semi_side_len + edge_width), (semi_side_len + edge_width), height);
	glVertex3f((semi_side_len + edge_width), (semi_side_len + edge_width), height);
	glVertex3f((semi_side_len + edge_width), (semi_side_len + edge_width), -height);
	glVertex3f(-(semi_side_len + edge_width), (semi_side_len + edge_width), -height);

	glVertex3f(-(semi_side_len + edge_width), semi_side_len, height);
	glVertex3f((semi_side_len + edge_width), semi_side_len, height);
	glVertex3f((semi_side_len + edge_width), semi_side_len, -height);
	glVertex3f(-(semi_side_len + edge_width), semi_side_len, -height);

	glVertex3f(-(semi_side_len + edge_width), semi_side_len, -height);
	glVertex3f((semi_side_len + edge_width), semi_side_len, -height);
	glVertex3f((semi_side_len + edge_width), (semi_side_len + edge_width), -height);
	glVertex3f(-(semi_side_len + edge_width), (semi_side_len + edge_width), -height);
//

	glVertex3f(-(semi_side_len + edge_width), -semi_side_len, height);
	glVertex3f((semi_side_len + edge_width), -semi_side_len, height);
	glVertex3f((semi_side_len + edge_width), -(semi_side_len + edge_width), height);
	glVertex3f(-(semi_side_len + edge_width), -(semi_side_len + edge_width), height);

	glVertex3f(-(semi_side_len + edge_width), -(semi_side_len + edge_width), height);
	glVertex3f((semi_side_len + edge_width), -(semi_side_len + edge_width), height);
	glVertex3f((semi_side_len + edge_width), -(semi_side_len + edge_width), -height);
	glVertex3f(-(semi_side_len + edge_width), -(semi_side_len + edge_width), -height);

	glVertex3f(-(semi_side_len + edge_width), -semi_side_len, height);
	glVertex3f((semi_side_len + edge_width), -semi_side_len, height);
	glVertex3f((semi_side_len + edge_width), -semi_side_len, -height);
	glVertex3f(-(semi_side_len + edge_width), -semi_side_len, -height);

	glVertex3f(-(semi_side_len + edge_width), -semi_side_len, -height);
	glVertex3f((semi_side_len + edge_width), -semi_side_len, -height);
	glVertex3f((semi_side_len + edge_width), -(semi_side_len + edge_width), -height);
	glVertex3f(-(semi_side_len + edge_width), -(semi_side_len + edge_width), -height);
//
	glVertex3f(-semi_side_len, (semi_side_len + edge_width), height);
	glVertex3f(-semi_side_len, -(semi_side_len + edge_width), height);
	glVertex3f(-(semi_side_len + edge_width), -(semi_side_len + edge_width), height);
	glVertex3f(-(semi_side_len + edge_width), (semi_side_len + edge_width), height);

	glVertex3f(-(semi_side_len + edge_width), (semi_side_len + edge_width), height);
	glVertex3f(-(semi_side_len + edge_width), -(semi_side_len + edge_width), height);
	glVertex3f(-(semi_side_len + edge_width), -(semi_side_len + edge_width), -height);
	glVertex3f(-(semi_side_len + edge_width), (semi_side_len + edge_width), -height);

	glVertex3f(-semi_side_len, (semi_side_len + edge_width), height);
	glVertex3f(-semi_side_len, -(semi_side_len + edge_width), height);
	glVertex3f(-semi_side_len, -(semi_side_len + edge_width), -height);
	glVertex3f(-semi_side_len, (semi_side_len + edge_width), -height);

	glVertex3f(-semi_side_len, (semi_side_len + edge_width), -height);
	glVertex3f(-semi_side_len, -(semi_side_len + edge_width), -height);
	glVertex3f(-(semi_side_len + edge_width), -(semi_side_len + edge_width), -height);
	glVertex3f(-(semi_side_len + edge_width), (semi_side_len + edge_width), -height);
//
	glVertex3f(semi_side_len, (semi_side_len + edge_width), height);
	glVertex3f(semi_side_len, -(semi_side_len + edge_width), height);
	glVertex3f((semi_side_len + edge_width), -(semi_side_len + edge_width), height);
	glVertex3f((semi_side_len + edge_width), (semi_side_len + edge_width), height);

	glVertex3f(semi_side_len, (semi_side_len + edge_width), height);
	glVertex3f(semi_side_len, -(semi_side_len + edge_width), height);
	glVertex3f((semi_side_len + edge_width), -(semi_side_len + edge_width), -height);
	glVertex3f((semi_side_len + edge_width), (semi_side_len + edge_width), -height);

	glVertex3f(semi_side_len, (semi_side_len + edge_width), height);
	glVertex3f(semi_side_len, -(semi_side_len + edge_width), height);
	glVertex3f((semi_side_len + edge_width), -(semi_side_len + edge_width), -height);
	glVertex3f((semi_side_len + edge_width), (semi_side_len + edge_width), -height);

	glVertex3f(semi_side_len, (semi_side_len + edge_width), -height);
	glVertex3f(semi_side_len, -(semi_side_len + edge_width), -height);
	glVertex3f((semi_side_len + edge_width), -(semi_side_len + edge_width), -height);
	glVertex3f((semi_side_len + edge_width), (semi_side_len + edge_width), -height);

	glEnd(); 

	glTranslatef(floatZERO, floatZERO, raise);
	glBegin(GL_LINES);
	glColor3f(floatZERO, floatZERO, floatZERO);

	glVertex3f((BAR_DIST+SEMI_BAR_WIDTH), BAR_LEN, floatZERO);
	glVertex3f((BAR_DIST+SEMI_BAR_WIDTH), -BAR_LEN, floatZERO);
	glVertex3f((BAR_DIST-SEMI_BAR_WIDTH), BAR_LEN, floatZERO);
	glVertex3f((BAR_DIST-SEMI_BAR_WIDTH), -BAR_LEN, floatZERO);

	glVertex3f(-(BAR_DIST+SEMI_BAR_WIDTH), BAR_LEN, floatZERO);
	glVertex3f(-(BAR_DIST+SEMI_BAR_WIDTH), -BAR_LEN, floatZERO);
	glVertex3f(-(BAR_DIST-SEMI_BAR_WIDTH), BAR_LEN, floatZERO);
	glVertex3f(-(BAR_DIST-SEMI_BAR_WIDTH), -BAR_LEN, floatZERO);

	glVertex3f(BAR_LEN, -(BAR_DIST+SEMI_BAR_WIDTH), floatZERO);
	glVertex3f(-BAR_LEN, -(BAR_DIST+SEMI_BAR_WIDTH), floatZERO);
	glVertex3f(BAR_LEN, -(BAR_DIST-SEMI_BAR_WIDTH), floatZERO);
	glVertex3f(-BAR_LEN, -(BAR_DIST-SEMI_BAR_WIDTH), floatZERO);

	glVertex3f(BAR_LEN, (BAR_DIST+SEMI_BAR_WIDTH), floatZERO);
	glVertex3f(-BAR_LEN, (BAR_DIST+SEMI_BAR_WIDTH), floatZERO);
	glVertex3f(BAR_LEN, (BAR_DIST-SEMI_BAR_WIDTH), floatZERO);
	glVertex3f(-BAR_LEN, (BAR_DIST-SEMI_BAR_WIDTH), floatZERO);

	glEnd();
//Making the arrows
	glBegin(GL_LINES);
	
	glVertex3f(ARROW_OUT, ARROW_OUT, floatZERO);
	glVertex3f(ARROW_IN, ARROW_IN, floatZERO);

	glVertex3f(-ARROW_OUT, ARROW_OUT, floatZERO);
	glVertex3f(-ARROW_IN, ARROW_IN, floatZERO);

	glVertex3f(-ARROW_OUT, -ARROW_OUT, floatZERO);
	glVertex3f(-ARROW_IN, -ARROW_IN, floatZERO);
	
	glVertex3f(ARROW_OUT, -ARROW_OUT, floatZERO);
	glVertex3f(ARROW_IN, -ARROW_IN, floatZERO);

	glEnd();
	createCircle(ARROW_RAD, (ARROW_RAD/ROOT2 + ARROW_IN), (ARROW_RAD/ROOT2 + ARROW_IN), ring_width);
	createCircle(ARROW_RAD, -(ARROW_RAD/ROOT2 + ARROW_IN), (ARROW_RAD/ROOT2 + ARROW_IN), ring_width);
	createCircle(ARROW_RAD, -(ARROW_RAD/ROOT2 + ARROW_IN), -(ARROW_RAD/ROOT2 + ARROW_IN), ring_width);
	createCircle(ARROW_RAD, (ARROW_RAD/ROOT2 + ARROW_IN), -(ARROW_RAD/ROOT2 + ARROW_IN), ring_width);
//Making center
	createCircle(MAIN_RAD, floatZERO, floatZERO, ARROW_RAD/2);
	glPushMatrix();
	glColor3f(0.5, floatZERO, floatZERO);
	createCircle(ARROW_RAD/2, floatZERO, floatZERO, ARROW_RAD/2);
	glPopMatrix();
//Making the remaining circular parts
	createCircle(BAR_RING_RAD, -BAR_LEN, BAR_DIST, BAR_RING_WIDTH);
	createCircle(BAR_RING_RAD, BAR_LEN, BAR_DIST, BAR_RING_WIDTH);
	createCircle(BAR_RING_RAD, BAR_DIST, BAR_LEN, BAR_RING_WIDTH);
	createCircle(BAR_RING_RAD, BAR_DIST, -BAR_LEN, BAR_RING_WIDTH);
	createCircle(BAR_RING_RAD, BAR_LEN, -BAR_DIST, BAR_RING_WIDTH);
	createCircle(BAR_RING_RAD, -BAR_LEN, -BAR_DIST, BAR_RING_WIDTH);
	createCircle(BAR_RING_RAD, -BAR_DIST, -BAR_LEN, BAR_RING_WIDTH);
	createCircle(BAR_RING_RAD, -BAR_DIST, BAR_LEN, BAR_RING_WIDTH);

	glColor3f(1.0, floatZERO, floatZERO);
	createCircle(BAR_DISC_RAD, -BAR_LEN, BAR_DIST, BAR_DISC_RAD);
	createCircle(BAR_DISC_RAD, BAR_LEN, BAR_DIST, BAR_DISC_RAD);
	createCircle(BAR_DISC_RAD, BAR_DIST, BAR_LEN, BAR_DISC_RAD);
	createCircle(BAR_DISC_RAD, BAR_DIST, -BAR_LEN, BAR_DISC_RAD);
	createCircle(BAR_DISC_RAD, BAR_LEN, -BAR_DIST, BAR_DISC_RAD);
	createCircle(BAR_DISC_RAD, -BAR_LEN, -BAR_DIST, BAR_DISC_RAD);
	createCircle(BAR_DISC_RAD, -BAR_DIST, -BAR_LEN, BAR_DISC_RAD);
	createCircle(BAR_DISC_RAD, -BAR_DIST, BAR_LEN, BAR_DISC_RAD);

	glColor3f(0.3, 0.2, floatZERO);
	createCircle(HOLE_RAD, (semi_side_len - HOLE_RAD), (semi_side_len - HOLE_RAD), HOLE_RAD);
	createCircle(HOLE_RAD, -(semi_side_len - HOLE_RAD), (semi_side_len - HOLE_RAD), HOLE_RAD);
	createCircle(HOLE_RAD, -(semi_side_len - HOLE_RAD), -(semi_side_len - HOLE_RAD), HOLE_RAD);
	createCircle(HOLE_RAD, (semi_side_len - HOLE_RAD), -(semi_side_len - HOLE_RAD), HOLE_RAD);

	glEnd();
}

void drawScene() {			//v flag gameinfo striker giti boardside msgrec para
	int i;
	int j = 0;
	float b,c,d,e=0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	glTranslatef(floatZERO, floatZERO, -5.0);

	glRotatef(camerax, 1.0f, floatZERO, floatZERO);
	glRotatef(cameray, floatZERO, 1.0f, floatZERO);
	glRotatef(cameraz, floatZERO, floatZERO, 1.0f);

	drawCarrom();

	glBegin(GL_QUADS);

	glColor3f(0.2, 0.2, 0.2);
	glVertex3f((semi_side_len + 4*offset), -(semi_side_len /2), floatZERO);
	glVertex3f((semi_side_len + 4*offset), (semi_side_len /2), floatZERO);
	glVertex3f((semi_side_len + 3*offset), (semi_side_len /2), floatZERO);
	glVertex3f((semi_side_len + 3*offset), -(semi_side_len /2), floatZERO);
	//glEnd();
	glColor3f(0.1, 0.9, 0.2);
float boxes;
if(gameinfo.turn==gameinfo.me){boxes=v-1;}
else {boxes=4.01;}
for(i=0; i< boxes; i++)
{
	//glBegin(GL_QUADS);
	b = -(semi_side_len/2 -offset + raise) +(float)i*offset;
	c = -(semi_side_len/2 - raise) +(float)i*offset;

	glVertex3f((semi_side_len + 3*offset) + raise, b, 0.01f);
	glVertex3f((semi_side_len + 3*offset) + raise, c, 0.01f);
	glVertex3f((semi_side_len + 4*offset) - raise, c, 0.01f);
	glVertex3f((semi_side_len + 4*offset) - raise, b, 0.01f);
	//glEnd();
}

if(flag!=2)
{
	
	glPushMatrix();
	glTranslatef(floatZERO, floatZERO, 0.02);	
	glColor3f(0.3, 0.3, 0.4);
	createCircle(striker_rad, STRIKER.x, STRIKER.y, striker_rad);
	glTranslatef(floatZERO, floatZERO, WIDTH);
	createCircle(striker_rad, STRIKER.x, STRIKER.y, striker_rad);
	glBegin(GL_QUADS);
	//glColor3f(0.1, 0.1, 0.1);
    for (i = 0; i < 16; i++)
    {
	d = striker_rad * cos(i*3.14/8 + 0.2);
	e = striker_rad * sin(i*3.14/8 + 0.2);
	b = striker_rad * cos(i*3.15/8 - 0.2);
	c = striker_rad * sin(i*3.15/8 - 0.2);

	glVertex3f(b + STRIKER.x, c + STRIKER.y, -WIDTH);
	glVertex3f(b + STRIKER.x, c + STRIKER.y, floatZERO);
	glVertex3f(d + STRIKER.x, e + STRIKER.y, floatZERO);
	glVertex3f(d + STRIKER.x, e + STRIKER.y, -WIDTH);
    }
    glEnd();
	glPopMatrix();
}
int strokelevel;
int botlevel=BOTLEVEL;
float strokex=STROKE.x-STRIKER.x,strokey=STROKE.y-STRIKER.y;
float strokelen=sqrt(strokex*strokex+strokey*strokey);
if(flag==1 && gameinfo.turn==gameinfo.me)
{
	glBegin(GL_LINE_STRIP);
	glVertex3f(STRIKER.x, STRIKER.y, floatZERO);

if(strokelen>(3/botlevel) && 0){strokex=(3/botlevel)*strokex/strokelen;strokey=(3/botlevel)*strokey/strokelen;}else{strokex=STROKE.x;strokey=STROKE.y;}
	glVertex3f(strokex, strokey, floatZERO);
	glEnd();
}	//showAngle(STRIKER.x, STRIKER.y);
	

glColor3f(0.6, 0.3, 0.1);
//createCircle(giti.r,giti.x,giti.y,.21);
for(i=0; i<GITINO; i++)
	{
	if(giti[i].in==OUT && STRIKER.in==OUT)
		{//printf("here%d\n",i);
		//moveCircle(giti[i].r, &giti[i].x, &giti[i].y, 0.21f, &giti[i].vx, &giti[i].vy, giti[i].c.r, giti[i].c.g, giti[i].c.b);
		float one=STRIKER.vx+giti[i].vx,two=STRIKER.vy+giti[i].vy;
		if(checkcol(STRIKER,giti[i]))
			{
			col(&STRIKER,&giti[i]);
			}
//printd(STRIKER);
//printd(giti[i]);
		for(j = 0; j < GITINO; j++)
			{
				if((checkcol(giti[j], giti[i]))&& (j<i) && giti[j].in==OUT) {col(&giti[j],&giti[i]);/*printf("colbetwemn giti\n");*/}
				if(checkcol(giti[j], STRIKER)&& j!=i && giti[j].in==OUT) {col(&giti[j],&STRIKER);/*printf("colSTRIKER\n");*/}
			}

			//if(one-(STRIKER.vx+giti[i].vx)>.01)printf("x dont match");
			//if(two -(STRIKER.vy+giti[i].vy)>.01)printf("y dont match");
			//printf("\n\n");
		}
	else if(giti[i].in==OUT)
		{
		for(j = 0; j < GITINO; j++)
			{
				if(checkcol(giti[j], giti[i])&& j<i && giti[j].in==OUT) col(&giti[j],&giti[i]);
			//	if(checkcol(&giti[j], &STRIKER)&& j!=i) col(&giti[j],&STRIKER);
			}
		}
	}
for(j = 0; j < GITINO; j++)
	{
	if(giti[j].in==OUT)
		{
		moveCircle(giti[j].r, &giti[j].x, &giti[j].y, 0.21f, &giti[j].vx, &giti[j].vy, giti[j].c.r, giti[j].c.g, giti[j].c.b);
		ispot(&giti[j]);
		}
	}
if (flag == 2)
	{
		glColor3f(0.3, 0.3, 0.4);
		if(STRIKER.in!=IN)
		{
		moveCircle(striker_rad, &STRIKER.x, &STRIKER.y, striker_rad, &STRIKER.vx, &STRIKER.vy, STRIKER.c.r, STRIKER.c.g, STRIKER.c.b);
		ispot(&STRIKER);
		}
	}
glutPostRedisplay();
glutSwapBuffers();
static int checker=0;
if(msgrec==1)
	{
	if(para[0]==1)handleKeypress(13, para[4], para[5]);			
	if(para[0]==2)handleMouse(para[1],para[2],para[4],para[5]);
	if(para[0]==3){handleMotion(para[4], para[5]);}
	if(para[0]==4){gameinfo.playercount--;gameinfo.side[para[1]].there=unoccupied;if(gameinfo.turn==para[1])flag=2;msgrec=0;}			//rest parameters of side left as it is
	if(para[0]==5){checker++;msgrec=0;}
	}
if(hasstop() && flag==2)
{
static int queencover=0;int temp;
int finhelp,once=0;
for(j=0;j<4;j++)
{if(gameinfo.side[j].there==bot /*&& gameinfo.turn!=j*/){
if(gameinfo.turn==j && once==0)
	{
	finhelp=1;once=1;
	}
else
	{
	finhelp=0;
	}
temp=rules(queencover,j,finhelp);}
}


if(once==0)
	{
	finhelp=1;once=1;
	}
else
	{
	finhelp=0;
	}
queencover=rules(queencover,gameinfo.me,finhelp);
	flag=0;
	STROKE.x=0;
	STROKE.y=0;
	STRIKER.in=OUT;
	STRIKER.vx=0;
	STRIKER.vy=0;
for(j=0;j<GITINO;j++)
{
if(giti[j].in==IN){giti[j].in=PREVIN;
}
}
	v=5.01;
	switch(gameinfo.turn)
	{
	case bottom:	{STRIKER.x = floatZERO;
		STRIKER.y = -BAR_DIST;break;}
	case top:	{STRIKER.x = floatZERO;
		STRIKER.y = BAR_DIST;break;}
	case left:	{STRIKER.y = floatZERO;
		STRIKER.x = -BAR_DIST;break;}
	case right:	{STRIKER.y = floatZERO;
		STRIKER.x = BAR_DIST;break;}
	}
int actplayer=0;
for(j=0;j<4;j++){if(gameinfo.side[j].there==occupied)actplayer++;}
createmsg(5,0,0,0,0,0);
while(checker!=(actplayer-1)){if(msgrec==1){if(para[0]==5){checker++;msgrec=0;}
}usleep(5000);}
checker=0;	
	}
}

void handleMouse(int button, int state, int x, int y)	//msgrec flag gameinfo stroke striker v
	{
//add that send msg if bot on this comp n playin its turn
	if(gameinfo.turn==gameinfo.me || msgrec==1)
		{
		if(state == GLUT_DOWN)
			{
			if(msgrec!=1 && (gameinfo.playercount>1))		
				{
				createmsg(2,button,state,0,x,y);
				}
			else
				{
				msgrec=0;
				}
			}

		//send msg
		float rslt;
		if(state == GLUT_DOWN)
			{
				if(flag==0)
				{
					flag = 1;
					glutPostRedisplay();		//added
//from here new
	switch(gameinfo.turn){
	case bottom:{		
	  		if((x - SIZEX/2)/128 > BAR_LEN) STRIKER.x = BAR_LEN;
			else if ((x - SIZEX/2)/128 <-BAR_LEN) STRIKER.x = -BAR_LEN;
			else STRIKER.x = (x - SIZEX/2)/128;
			STRIKER.y = -BAR_DIST;
	break;		
	}
	case top:{		
	  		if((x - SIZEX/2)/128 > BAR_LEN) STRIKER.x = BAR_LEN;
			else if ((x - SIZEX/2)/128 <-BAR_LEN) STRIKER.x = -BAR_LEN;
			else STRIKER.x = (x - SIZEX/2)/128;
			STRIKER.y = BAR_DIST;

	break;
		}
	case left:{		
	  		if(-(y - SIZEY/2)/128 > BAR_LEN) STRIKER.y = BAR_LEN;
			else if (-(y - SIZEY/2)/128 <-BAR_LEN) STRIKER.y = -BAR_LEN;
			else STRIKER.y = -(y - SIZEY/2)/128;
			STRIKER.x = -BAR_DIST;

	break;
		}
	case right:{		
	  		if(-(y - SIZEY/2)/128 > BAR_LEN) STRIKER.y = BAR_LEN;
			else if (-(y - SIZEY/2)/128 <-BAR_LEN) STRIKER.y = -BAR_LEN;
			else STRIKER.y = -(y - SIZEY/2)/128;
			STRIKER.x = BAR_DIST;

	break;
		}
	}
			STROKE.x = STRIKER.x;
			STROKE.y = STRIKER.y;
//till here

				}
				else if(flag==1)
				{

//from here


	switch(gameinfo.turn)
	{
	case bottom:	{
				STROKE.x = (x - SIZEX/2)/128;
				STROKE.y = -(y - SIZEY/2)/128;
				if(STROKE.y <= -1.35) STROKE.y = -1.35;
				break;
			}
	case top:	{
				STROKE.x = (x - SIZEX/2)/128;
				STROKE.y = -(y - SIZEY/2)/128;
				if(STROKE.y >= 1.35) STROKE.y = 1.35;
				break;
			}
	case left:	{
				STROKE.x = (x - SIZEX/2)/128;
				STROKE.y = -(y - SIZEY/2)/128;
				if(STROKE.x <= -1.35) STROKE.x = -1.35;
				break;
			}
	case right:	{
				STROKE.x = (x - SIZEX/2)/128;
				STROKE.y = -(y - SIZEY/2)/128;
				if(STROKE.x >= 1.35) STROKE.x = 1.35;
				break;
			}
	}

float xlen = STRIKER.x - STROKE.x;
float ylen = STRIKER.y - STROKE.y;
float dist = sqrt(xlen*xlen + ylen*ylen);
if(dist !=0)
{
STROKE.x = STRIKER.x - xlen*dir_len/dist;
STROKE.y = STRIKER.y - ylen*dir_len/dist;
}



//till here




					flag =2;
					STRIKER.vx = STROKE.x - STRIKER.x;
					STRIKER.vy = STROKE.y - STRIKER.y;
					rslt = sqrt(STRIKER.vx*STRIKER.vx + STRIKER.vy*STRIKER.vy);
					STRIKER.vx = v* STRIKER.vx/rslt;
					STRIKER.vy = v* STRIKER.vy/rslt;
					glutPostRedisplay();
//					update(0);
				}
			}
		}
	}
void handleMotion(int x, int y1)		
{
if(gameinfo.turn==gameinfo.me || msgrec==1)
{
	if(msgrec!=1 &&(gameinfo.playercount>1))
		{
		createmsg(3,0,0,0,x,y1);
		}
	else
		{
		msgrec=0;
		}

	//send msg
if(flag == 0)
{
	switch(gameinfo.turn){
	case bottom:{		
	  		if((x - SIZEX/2)/128 > BAR_LEN) STRIKER.x = BAR_LEN;
			else if ((x - SIZEX/2)/128 <-BAR_LEN) STRIKER.x = -BAR_LEN;
			else STRIKER.x = (x - SIZEX/2)/128;
			STRIKER.y = -BAR_DIST;
	break;		
	}
	case top:{		
	  		if((x - SIZEX/2)/128 > BAR_LEN) STRIKER.x = BAR_LEN;
			else if ((x - SIZEX/2)/128 <-BAR_LEN) STRIKER.x = -BAR_LEN;
			else STRIKER.x = (x - SIZEX/2)/128;
			STRIKER.y = BAR_DIST;

	break;
		}
	case left:{		
	  		if(-(y1 - SIZEY/2)/128 > BAR_LEN) STRIKER.y = BAR_LEN;
			else if (-(y1 - SIZEY/2)/128 <-BAR_LEN) STRIKER.y = -BAR_LEN;
			else STRIKER.y = -(y1 - SIZEY/2)/128;
			STRIKER.x = -BAR_DIST;

	break;
		}
	case right:{		
	  		if(-(y1 - SIZEY/2)/128 > BAR_LEN) STRIKER.y = BAR_LEN;
			else if (-(y1 - SIZEY/2)/128 <-BAR_LEN) STRIKER.y = -BAR_LEN;
			else STRIKER.y = -(y1 - SIZEY/2)/128;
			STRIKER.x = BAR_DIST;

	break;
		}
	}
			STROKE.x = STRIKER.x;
			STROKE.y = STRIKER.y;
}
else if(flag == 1)
{
	switch(gameinfo.turn)
	{
	case bottom:	{
				STROKE.x = (x - SIZEX/2)/128;
				STROKE.y = -(y1 - SIZEY/2)/128;
				if(STROKE.y <= -1.35) STROKE.y = -1.35;
				break;
			}
	case top:	{
				STROKE.x = (x - SIZEX/2)/128;
				STROKE.y = -(y1 - SIZEY/2)/128;
				if(STROKE.y >= 1.35) STROKE.y = 1.35;
				break;
			}
	case left:	{
				STROKE.x = (x - SIZEX/2)/128;
				STROKE.y = -(y1 - SIZEY/2)/128;
				if(STROKE.x <= -1.35) STROKE.x = -1.35;
				break;
			}
	case right:	{
				STROKE.x = (x - SIZEX/2)/128;
				STROKE.y = -(y1 - SIZEY/2)/128;
				if(STROKE.x >= 1.35) STROKE.x = 1.35;
				break;
			}
	}
}
float xlen = STRIKER.x - STROKE.x;
float ylen = STRIKER.y - STROKE.y;
float dist = sqrt(xlen*xlen + ylen*ylen);
if(dist !=0)
{
STROKE.x = STRIKER.x - xlen*dir_len/dist;
STROKE.y = STRIKER.y - ylen*dir_len/dist;
}
glutPostRedisplay();

}
}



void *manbot1(void *input);
void *manbot2(void *input);
void *manbot3(void *input);

int main(int argc, char** argv) {
	//Initialize GLUT
/*char jads[20];
gethostname(jads,20);
printf("sada=%s\n",jads);
*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(SIZEX, SIZEY); //Set the window SIZEX
	//Create the window
	glutCreateWindow("Making of Carrom server");
	initRendering(); //Initialize rendering
	//Set handler functions for drawing, keypresses, and window reSIZEs
	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);
	glutKeyboardFunc(handleKeypress);
	glutPassiveMotionFunc(handleMotion);
	user=MODE;
	int flevel=FRICTION;
	int portnof;	int side;
	char *serveripf;
//	gameinfo=(struct game *)malloc(sizeof(struct game));
	char tem_p[10];
	initgameinfo();
	gameinfo.friction=.005*flevel;
	gameinfo.erest=EREST;
	if(user==offline)
		{
		side=bottom;
		gameinfo.me=bottom;
		gameinfo.side[side].color=side%2;
		gameinfo.side[side].mepoints=0;
		gameinfo.side[side].mequeen=NO;

		gameinfo.turn=bottom;
		gameinfo.playercount=1;
		gameinfo.side[side].there=occupied;
		gethostname(gameinfo.side[side].ip,20);
		gameinfo.side[side].sock=-1;

		}
	if(user==isclient)
		{
		char data[100];
		printf("Enter the server address..\n");
		scanf("%s",serveripf);

		strcpy(data,serveripf);
		strcat(data,"/");
		printf("Enter the portno..\n");
		scanf("%d",&portnof);

		sprintf(tem_p,"%d",portnof);
		strcat(data,tem_p);
		strcat(data,"/");
		printf("Enter your desired side..\n");
		scanf("%d",&side);

		sprintf(tem_p,"%d",side);
		strcat(data,tem_p);
		pthread_t controlmanager,mangs;
		pthread_create(&mangs,NULL,mang_alls,data);

		}
	if(user==isserver)
		{
		side=bottom;
		gameinfo.playercount=1;
//		clientno++;
//		startserver(PORTNO);
		gameinfo.turn=bottom;
		gameinfo.me=side;
		gameinfo.side[side].color=side%2;
		gameinfo.side[side].mepoints=0;
gameinfo.side[side].mequeen=NO;

		gameinfo.side[side].there=occupied;
		gethostname(gameinfo.side[side].ip,20);
		gameinfo.erest=EREST;
		gameinfo.friction=.005*flevel;
		pthread_t controlmanager,mang;
		printf("Enter the portno..\n");
		scanf("%d",&portnof);

		sprintf(tem_p,"%d",portnof);
		pthread_create(&mang,NULL,mang_all,tem_p);

		}
	if(user==isclient)
		{
/*Not required as default values already assigned*/
//		flevel=getfrictioncoef();
//		requestdata();		
//		if(part[1]>=4){printf("Server Full!\nExiting....");exit(0);}
//		friction=.005*part[0];
		}
	if(MODE==offline)
	{
	int bots;
	printf("Enter the number of bots..\n");
	scanf("%d",&bots);
	pthread_t bot1,bot2,bot3;
	int botside;
	int botloop=0;
	for(botloop=0;botloop<bots;botloop++)
		{
		printf("Enter the botside for bot %d..\n",botloop+1);
		scanf("%d",&botside);
		char herehelp[30];
		sprintf(herehelp,"%d",botside);
		switch(botloop+1){

			case 1: {pthread_create(&bot1,NULL,manbot1,herehelp);break;}
			case 2: {pthread_create(&bot2,NULL,manbot2,herehelp);break;}
			case 3: {pthread_create(&bot3,NULL,manbot3,herehelp);break;}

			}

		gameinfo.side[botside].there=bot;
		gameinfo.side[botside].mepoints=0;
		gameinfo.side[botside].mequeen=NO;
		gameinfo.playercount++;
		gethostname(gameinfo.side[botside].ip,20);
		gameinfo.side[botside].sock=-1;
		printf("Enter the botlevel..\n");
		scanf("%d",&gameinfo.side[botside].botlevel);

		}

	int i,j;
		for(i=0;i<4;i++){
		gameinfo.side[i].color=0;
		}
	}
	glutMouseFunc(handleMouse);		//moved out
	pthread_t new,controlmanager;
//	pthread_czeate(&controlmanager,NULL,manager,"foo");
//	pthread_create(&new,NULL,check4msg,"foo");
	glutMainLoop(); //Start the main loop.  glutMainLoop doesn't return.
	return 0; //This line is never reached
}

