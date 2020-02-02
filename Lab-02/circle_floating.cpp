/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <iostream>
using namespace std;

static int slices = 16;
static int stacks = 16;

int Width =640, Height=480;
int a1,b1;
bool flag = false;

/* GLUT callback Handlers */

static void resize(int width, int height){
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-320, 319, -240, 239, -1, 1);
    gluOrtho2D(-Width/2, Width/2-1, -Height/2, Height/2-1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void drawPixel(int xx, int yy) {

	glPointSize(2);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2f(xx , yy);
	glEnd();
	glutSwapBuffers();
}


void draw8way(int x,int y,int a,int b)
{
    glVertex2i(x+a,y+b);
    glVertex2i(y+a,x+b);
    glVertex2i(y+a,-x+b);
    glVertex2i(x+a,-y+b);
    glVertex2i(-x+a,y+b);
    glVertex2i(-y+a,-x+b);
    glVertex2i(-y+a,x+b);
    glVertex2i(-x+a,-y+b);
    glVertex2i(y+a,x+b);
}


void draw_circle(int a,int b,int r)
{
   int d = 5-4*r;
   int x=0;
   int y=r;

   draw8way(x,y,a,b);

   while(x<y){

       if(d<0)
        {
            d+= 8*x+12;
            x++;
        }
       else
        {
            d+=8*x-8*y+20;
            x++;
            y--;
        }

       draw8way(x,y,a,b);
      }
}

int cnt=0;

void mouse(int bin, int state , int xx , int yy) {
	cnt++;
	a1 = xx -320;
	b1 = 240-yy;

	//drawPixel(a1, b1);
    if(cnt>0){
        flag=true;
    }

	printf("Taken Point: %d %d %d\n",a1,b1 ,cnt);

}


void circle_floating(int a, int b, int r)
{
    int xmin = -Width/2;
	int xmax = Width/2-1;
	int ymax = Height/2-1;
	int ymin = -Height/2;

    int cntrX1 = a1;
    int cntrY1 = b1;

	int cntrX2 = a;
	int cntrY2 = b;

    int dx1 = 2;
    int dx2 = 2;
    int dy1 = -2;
    int dy2 = -2;
    glClear(GL_COLOR_BUFFER_BIT);

    draw_circle(a,b,r);

     while(1){
        glClear(GL_COLOR_BUFFER_BIT);
        //usleep(4500);
        glBegin(GL_POINTS);
        if(cntrX1-r<xmin) dx1=dx1*(-1);
        if(cntrX1+r>xmax) dx1=dx1*(-1);
        if(cntrY1-r<ymin) dy1=dy1*(-1);
        if(cntrY1+r>ymax) dy1=dy1*(-1);
        if(cntrX2-r<xmin) dx2=dx2*(-1);
        if(cntrX2+r>xmax) dx2=dx2*(-1);
        if(cntrY2-r<ymin) dy2=dy2*(-1);
        if(cntrY2+r>ymax) dy2=dy2*(-1);


       // int z = zone(dx1,dy1);
        //color(z);

        
        cntrX1+=dx1;
        cntrY1+=dy1;
        cntrX2+=dx2;
        cntrY2+=dy2;

        draw_circle(cntrX1,cntrY1,r);
        
        glEnd();
        
        glutSwapBuffers();

     }

}


static void display(void){
   // int x = 10, y = 20;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);

    glBegin(GL_LINES);

// these 4 lines are for x-axis and y-axis
    glVertex2i(-320, 0);  
    glVertex2i(319, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 239);

    glEnd();

    glBegin(GL_POINTS);

// this is a point
    // glVertex2i(x, y+1);
    // glVertex2i(x, y);
    
    if(flag==true){
        circle_floating(a1,b1,20);
    }
    

    glEnd();
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Experiment 01");

    glutMouseFunc(mouse);

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;
}