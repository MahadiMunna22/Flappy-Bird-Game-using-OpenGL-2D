#include<windows.h>
#include<mmsystem.h>
#include <GL/glut.h>
#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#define PI 3.1416
#include<string>
#include<iostream>
using namespace std;

static int tx,ty = 0.0;
float house_position = 0;
float land_position = 0;
float cloud_Position = 0;
int pillar_Position = 0;
int pillarsX[] = {100, 300, 200, 100};
int pillarsY[] = {-100, 300, 70, 200};
int Count = 0;
int PillarSpeed = 5;
int birdSpeed = 15;
int score = 0;
bool CollisionDetected = false;
bool GameRestart = false;
void RestartGame();
double keyCounter = 0;
bool lock = false;

void init(void)
{
	glClearColor (0.16,0.68, 0.94, 0);
}

void drawText(const char *text, int length, int x, int y)
{
    glMatrixMode(GL_PROJECTION);
    double *matrix = new double[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrix);
    glLoadIdentity();
    glOrtho(0,800,0,800,-5,5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPushMatrix();
    glLoadIdentity();
    glRasterPos2i(x, y);
    for(int i = 0; i<length; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, (int)text[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixd(matrix);
    glMatrixMode(GL_MODELVIEW);
}
void circle(float radius_x, float radius_y)
{
	int i=0;
	float angle = 0.0;
	glBegin(GL_POLYGON);
    for(i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f (cos(angle) * radius_x, sin(angle) * radius_y);
    }
	glEnd();
}
void sun(int x, int y, float radius_x, float radius_y)
{
    glPushMatrix();             //Green Circle
	glTranslatef(x,y,0);
    glColor3f(0.93, 0.78, 0.18);
	circle(radius_x, radius_y);
	glPopMatrix();
}

void house(float x, float y)
{
    glPushMatrix();
	glTranslatef(x + house_position,y,0);
	//roof
    glColor3f(0.86, 0.21, 0.17);
    glBegin(GL_POLYGON);
        glVertex2f (x, y);
        glVertex2f (x+480, y);
        glVertex2f (x+380, y+100);
        glVertex2f (x+100, y+100);
    glEnd();
    //2nd floor
    glColor3f(0.93, 0.84, 0.68);
    glBegin(GL_POLYGON);
        glVertex2f (x+170, y+150);
        glVertex2f (x+170, y+80);
        glVertex2f (x+310, y+80);
        glVertex2f (x+310, y+150);
        glVertex2f (x+330, y+150);
        glVertex2f (x+240, y+240);
        glVertex2f (x+150, y+150);
    glEnd();
    //roof_2
    glColor3f(0.86, 0.21, 0.17);
    glBegin(GL_POLYGON);
        glVertex2f (x+240, y+240);
        glVertex2f (x+340, y+140);
        glVertex2f (x+360, y+140);
        glVertex2f (x+240, y+260);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex2f (x+120, y+140);
        glVertex2f (x+140, y+140);
        glVertex2f (x+240, y+240);
        glVertex2f (x+240, y+260);
    glEnd();

    //roof 2 shadow
    glColor3f(0.82, 0.72, 0.57);
    glBegin(GL_POLYGON);
        glVertex2f (x+240, y+220);
        glVertex2f (x+340, y+140);
        glVertex2f (x+240, y+240);
        glVertex2f (x+140, y+140);
    glEnd();

    //1st floor room
    glColor3f(0.93, 0.84, 0.68);
    glBegin(GL_POLYGON);
        glVertex2f (x+50, y);
        glVertex2f (x+50, y-200);
        glVertex2f (x+430, y-200);
        glVertex2f (x+430, y);
    glEnd();
    //1st floor room shadow
    glColor3f(0.82, 0.72, 0.57);
    glBegin(GL_POLYGON);
        glVertex2f (x+50, y);
        glVertex2f (x+50, y-20);
        glVertex2f (x+430, y-20);
        glVertex2f (x+430, y);
    glEnd();
    //  gate

    glBegin(GL_POLYGON);
        glColor3f(0.2, 0.2, 0.1);
        glVertex2f (x+270, y-200);
        glVertex2f (x+370, y-200);
        glColor3f(0.73, 0.64, 0.35);
        glVertex2f (x+370, y-50);
        glVertex2f (x+270, y-50);
    glEnd();
    //  window
    glBegin(GL_POLYGON);
        glColor3f(0, 0, .2);
        glVertex2f (x+110, y-150);
        glVertex2f (x+210, y-150);

        glColor3f(0.058, 0.6, 0.85);
        glVertex2f (x+210, y-50);
        glVertex2f (x+110, y-50);
    glEnd();

    glColor3f(0.058, 0.6, 0.85);
	glTranslatef(x+240,y+150,0);
	circle(30, 30);

    glBegin(GL_POLYGON);
        glColor3f(0, 0, .2);
        glVertex2f (x+80, y-30);
        glVertex2f (x+20, y-30);
        glColor3f(0.058, 0.6, 0.85);
        glVertex2f (x+20, y+10);
        glVertex2f (x+80, y+10);

    glEnd();

    glPopMatrix();
}
void cloud(int x, int y)
{
    glPushMatrix();

    glColor3f(1,1,1);
    glTranslatef(x + cloud_Position,y,0);
    glBegin(GL_POLYGON);
        glVertex2f (x, y);
        glVertex2f (x+100, y);
        glVertex2f (x+100, y+100);
        glVertex2f (x, y+100);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f (x-150, y);
        glVertex2f (x+250, y);
        glVertex2f (x+250, y+30);
        glVertex2f (x-150, y+30);
    glEnd();

    glTranslatef(x-150,y+15,0);
    circle(15,15);

    glTranslatef(x+500,y-80,0);
    circle(15,15);

    glTranslatef(x-170,y-35,0);
    circle(35,35);

    glTranslatef(x+175,y-40,0);
    circle(60,60);

    glTranslatef(x+165,y-130,0);
    circle(30,30);

    glPopMatrix();
}

void bird(int x, int y)
{
    glPushMatrix();

    glTranslatef(x+200,y+ty,0);
    x = x + 755;
    y = y - 66;
//  Leap Start

    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f (x+20, y);
        glVertex2f (x+40, y-10);
        glVertex2f (x+40, y+15);
        glVertex2f (x+32, y+38);
        glVertex2f (x+20, y+47);
        glVertex2f (x+10, y+52);
        glVertex2f (x, y+55);
        glVertex2f (x-5, y+54);
        glVertex2f (x+5, y);
    glEnd();
    glColor3f(0,0,0);
    glLineWidth(4.5f);
    glBegin(GL_LINE_STRIP);
        glVertex2f (x+5, y);
        glVertex2f (x+20, y);
        glVertex2f (x+40, y-10);
        glVertex2f (x+40, y+15);
        glVertex2f (x+32, y+38);
        glVertex2f (x+20, y+47);
        glVertex2f (x+10, y+52);
        glVertex2f (x, y+55);
        glVertex2f (x-5, y+54);
    glEnd();

    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2f (x-5, y-20);
        glVertex2f (x+5, y-25);
        glVertex2f (x+20, y-23);
        glVertex2f (x+15, y-35);
        glVertex2f (x+5, y-40);
        glVertex2f (x-10, y-45);
        glVertex2f (x-25, y-43);
    glEnd();
    glColor3f(0,0,0);
    glLineWidth(4.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f (x-5, y-20);
        glVertex2f (x+5, y-25);
        glVertex2f (x+20, y-23);
        glVertex2f (x+15, y-35);
        glVertex2f (x+5, y-40);
        glVertex2f (x-10, y-45);
        glVertex2f (x-25, y-43);
    glEnd();
//  Leap End

//  Head Crown Start//
    glColor3f(0,0,0);
    glLineWidth(5.0f);
    glBegin(GL_LINE_STRIP);
        glVertex2f (x, y+55);
        glVertex2f (x-5, y+80);
        glVertex2f (x-15, y+100);
        glVertex2f (x-25, y+110);
        glVertex2f (x-25, y+90);
        glVertex2f (x-40, y+95);
        glVertex2f (x-55, y+95);
    glEnd();
// Head Crown End //

    x = x - 755;
    y = y + 66;

// Body Start//
    glColor3f(0,0,0);
    circle(70,70);

    glColor3f(0.3,0.5,1);
    circle(65,65);
// Body End //

//  Eye Start
    glColor3f(0,0,0);
    glTranslatef(x+735,y-45,0);
    circle(25,30);

    glColor3f(1,1,1);
    circle(20,25);

    glColor3f(0,0,0);
    glTranslatef(x+710,y-50,0);
    circle(10,12);

    glColor3f(1,1,1);
    glTranslatef(x+695,y-45,0);
    circle(6,7);
//  Eye End

//  Wing Start
    x = x + 700;
    y = y - 150;
   // glRotatef(180, 1, 0, 0);
    glRotatef(280, 0, 0, 1);
    glTranslatef(x,y,0);
    int i=0;
	float angle = 0.0;
    glColor3f(0,0,0);
	glBegin(GL_POLYGON);
        for(i = 0; i < 100; i++)
        {
            angle = 1.2 * PI * i / 100;
            glVertex2f (cos(angle) * 40, sin(angle) * 60);
        }
    glEnd();

    angle = 0.0;
    glColor3f(0.3,0.5,1);
    glBegin(GL_POLYGON);
        for(i = 0; i < 100; i++)
        {
            angle = 1.18 * PI * i / 100;
            glVertex2f (cos(angle) * 35, sin(angle) * 55);
        }
	glEnd();
//  Wing End

    glPopMatrix();
}

void tree(int x, int y)
{
    glPushMatrix();             //Green Circle
	glTranslatef(x - 150 + land_position,y + 100,0);

	int i=0;
	float angle = 0.0;
    glRotatef(275, 0, 0, 1);
	glBegin(GL_POLYGON);
    for(i = 0; i < 100; i++)
    {
        if(i == 0)
            glColor3f(0,1,0);
        else
            glColor3f(0,0.4,0);
        angle = 2 * PI * i / 100;
        glVertex2f (cos(angle) * 100, sin(angle) * 100);
    }
    glEnd();

    glRotatef(-275, 0, 0, 1);
	x = x + 240;
	y = y - 130;

	glBegin(GL_POLYGON);
        glColor3f(.8, 0.4, 0);
        glVertex2f (x, y);
        glVertex2f (x+30, y);
        //glColor3f(0.4, 0, 0);
        glVertex2f (x+30, y-330);
        glVertex2f (x, y-330);
    glEnd();

    glRotatef(-50, 0,0,1);
    x = x + 55 ;
    y = y + 30;
    glBegin(GL_POLYGON);
        glColor3f(.8, 0.4, 0);
        glVertex2f (x, y);
        glVertex2f (x+20, y);
        glVertex2f (x+20, y-50);
        glVertex2f (x, y-50);
    glEnd();

    glRotatef(100, 0,0,1);
    x = x-105 ;
    y = y-5;
    glBegin(GL_POLYGON);
        glColor3f(.8, 0.4, 0);
        glVertex2f (x, y);
        glVertex2f (x+20, y);
        glVertex2f (x+20, y-50);
        glVertex2f (x, y-50);
    glEnd();

	glPopMatrix();
}

void forest(int x, int y)
{
    glPushMatrix();
	glTranslatef(x + land_position, y,0);

    for(int i = 0; i<100; i++)
    {
        glColor3f(0, 0.1, 0);
        glBegin(GL_POLYGON);
            glVertex2f(x,y);
            glVertex2f(x+180,y);
            glColor3f(0, 1, 0);
            glVertex2f(x+90,y+300);
        glEnd();
        x += 160;
    }

	glPopMatrix();
}

void land()
{
    glPushMatrix();

    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
    glVertex2d(-1000, -200);
    glVertex2d(-1000, -800);
    glVertex2d(1000, -800);
    glVertex2d(1000, -200);
    glEnd();

    glColor3f(0,1,0);
    glTranslatef(land_position-400 ,-400,0);
    circle(300,300);

    glPopMatrix();
}

void pillar(int x, int y)
{
    glPushMatrix();

    //Bottom Circle
    glColor3f(1,.2,.8);
    glTranslatef(x+pillarsX[Count]+ pillar_Position, (y - 500) + pillarsY[Count],0);
    int i=0;
	float angle = 0.0;
	glBegin(GL_POLYGON);
    for(i = 0; i < 100; i++)
    {
        if(i == 0)
        {
            glColor3f(.5,0,0);
        }
        else if(i == 50)
        {
            glColor3f(1,0,1);
        }
        angle = 2 * PI * i / 100;
        glVertex2f (cos(angle) * 50, sin(angle) * 20);
    }
	glEnd();

    //Pillar Body
    glTranslatef(x-250,y+200,0);
    glBegin(GL_POLYGON);
        glColor3f(1,0,1);
        glVertex2d(x, y);
        glColor3f(.5,0,0);
        glVertex2d(x+100, y);
        glColor3f(.5,0,0);
        glVertex2d(x+100, y-500);
        glColor3f(1,0,1);
        glVertex2d(x, y-500);
    glEnd();

    //Top Circle
    glColor3f(1,.2,.8);
    glTranslatef(x+50,y,0);
    circle(50,20);

    glPopMatrix();
}

void gameOverScreen()
{
    glPushMatrix();

    glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
        glVertex2f (-310,-210);
        glVertex2f (310, -210);
        glVertex2f (310, 210);
        glVertex2f (-310, 210);
    glEnd();
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
        glVertex2f (-300,-200);
        glVertex2f (300, -200);
        glVertex2f (300, 200);
        glVertex2f (-300, 200);
    glEnd();

    glColor3f(1, 0, 0);
    string text;
    text = "GAME OVER";
    drawText(text.data(), text.size(), 360, 440);

    glColor3f(0, 0, 1);
    text = "Score: " + to_string(score);
    drawText(text.data(), text.size(), 370, 360);

    glColor3f(0, .5, 0);
    text = "Press 'R' to restart the Game!!" ;
    drawText(text.data(), text.size(), 320, 300);

	glPopMatrix();
}

void showScore(int score)
{
    glColor3f(0,0,0);
    string text;
    text = "Score: " + to_string(score);
    drawText(text.data(), text.size(), 650,750);
}

void OnMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        ty += birdSpeed;
        keyCounter = 0;
        lock = true;
        glutPostRedisplay();
    }
}

void spe_key(int key, int x, int y)
{
	switch (key) {

		case GLUT_KEY_UP:
				ty += birdSpeed;
				keyCounter = 0;
				lock = true;
				glutPostRedisplay();
				break;
        case GLUT_KEY_DOWN:
				ty -= birdSpeed;
				glutPostRedisplay();
				break;
	  default:
			break;
	}
}

void keyboard_key(unsigned char key, int x, int y)
{
	switch (key) {

		case 'r':
                GameRestart = true;
				RestartGame();
				tx +=5;
				glutPostRedisplay();
				break;
		case ' ':
				ty += birdSpeed;
				keyCounter = 0;
				lock = true;
				glutPostRedisplay();
				break;
	  default:
			break;
	}
}


static void resize(int, int);

static void display(void);

void timer(int);

int main(int argc, char *argv[])
{
        glutInit(&argc, argv);
        glutInitWindowSize (1400, 700);
        glutInitWindowPosition (0, 0);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

        glutCreateWindow("Window 1");

        glutReshapeFunc(resize);
        glutDisplayFunc(display);
        glutSpecialFunc(spe_key);
        glutKeyboardFunc(keyboard_key);
        glutMouseFunc(OnMouseClick);
        glutTimerFunc(0, timer, 0);
        init();
        //PlaySound("music.wav", NULL, SND_LOOP|SND_ASYNC);
        glutMainLoop();

}

static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-780,780,-400,400);
    glMatrixMode(GL_MODELVIEW);
}


int state = -1;
int gameOverCounter = 0;

void display(void)
{
    if(keyCounter > .8 && lock == true && CollisionDetected == false)
    {
        sndPlaySound("2.wav", SND_ASYNC);
        lock = false;
    }
    keyCounter = keyCounter + 0.08;

    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    sun(30, 80, 300, 300);
    cloud(-100, 80);
    forest(-2000 , -90);
    forest(-2040 , -100);
    land();
    tree(-250, 120);
    house(-50,-10);
    bird(-700,50);
    pillar(100,150);
    showScore(score);

    if(CollisionDetected)
    {
        gameOverScreen();

        if(gameOverCounter == 0)
        {
            sndPlaySound("game_over.wav", SND_ASYNC);
            gameOverCounter+=2;
        }
    }

	glutSwapBuffers();

}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);

    if(!GameRestart)
    {
        if(ty > -380)
            ty-=2;

        if(house_position>-1200)
            house_position -= 5;
        else
            house_position = 1200;

        if(land_position>-800)
            land_position -= 5;
        else
            land_position = 1600;

        if(cloud_Position< 1200)
            cloud_Position += 1;
        else
            cloud_Position = -1000;
    }

    if(pillar_Position> -1300)
    {
        pillar_Position -= PillarSpeed;
    //***************** Collision Detection *****************//
        int birdStartX = -410;
        int birdEndX = -600;
        int birdStartY = ty + 140 ;
        int birdEndY = ty ;
        int pillarStartX = pillar_Position+ 50 + pillarsX[Count];
        int pillarStartY = 160 + pillarsY[Count];
        int pillarEndX = pillar_Position +50+ pillarsX[Count] + 100;
        int pillarEndY = 150 + pillarsY[Count] - 500;

        if(birdStartY > 400)
        {
            birdSpeed = 0;
        }
        else if(birdEndY < -380)
        {
            CollisionDetected = true;
            birdSpeed = 0;
        }
        else{
            birdSpeed = 15;
        }

        if((birdStartX > pillarStartX && birdEndX < pillarEndX && birdEndY < pillarStartY && birdStartY > pillarEndY) || birdEndY < -420 )
        {
            CollisionDetected = true;
            printf("Collision Detected\n");
            PillarSpeed = 0;
        }
        else
        {
            printf("Bird -> %d %d Pillar Start-> %d %d End-> %d %d PillarSpeed -> %d\n",birdStartX ,birdStartY ,pillarStartX ,pillarStartY ,pillarEndX ,pillarEndY, PillarSpeed) ;
        }
    }
    else
    {
        pillar_Position = 700;
        Count++;
        score += 10;
        if(Count == sizeof(pillarsX)/4)
            Count = 0;
    }
}
void RestartGame()
{
    tx = 0;
    ty = 0;
    house_position = 0;
    land_position = 0;
    cloud_Position = 0;
    pillar_Position = 0;
    Count = 0;
    PillarSpeed = 5;
    birdSpeed = 15;
    score = 0;
    CollisionDetected = false;
    GameRestart = false;
    gameOverCounter = 0;
}

