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
#include <stdio.h>

static int slices = 16;
static int stacks = 16;

int click=0;
bool check=true;
int zone;
int x0,y0,x1,y1;
int a,b,c,d;



void mouse(int button , int state , int mousex, int mousey){
	int x, y;
    a=(rand()%3)-1;b=(rand()%3)-1;c=(rand()%3)-1;d=(rand()%3)-1;
    if(a==0)a+=1;if(b==0)b+=1;if(c==0)c+=1;if(d==0)d+=1;a*=2;b*=2;c*=2;d*=2;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		check=true;
		x=mousex-320;
		y=240-mousey;

		if(click==0){
			x0=x;
			y0=y;
			click=1;
		}
		else if(click ==1 ){
			x1=x;
			y1=y;
			click=2;
		}
		else{
			x0=x;
			y0=y;
			click =0;
		}
        printf("%d %d %d %d\n",x0,y0,x1,y1);
	}
	else if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
		glClearColor(1,1,1,0);
		glClear(GL_COLOR_BUFFER_BIT);
		check=false;
	}
	glutPostRedisplay();
}


static void resize(int width, int height){
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 319, -240, 239, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void draw8way(int c_x,int c_y,int x, int y){
    glVertex2i(c_x+x,c_y+y);
    glVertex2i(c_x-x,c_y+y);

    glVertex2i(c_x+y,c_y+x);
    glVertex2i(c_x+y,c_y-x);

    glVertex2i(c_x-y,c_y+x);
    glVertex2i(c_x-y,c_y-x);
    
    glVertex2i(c_x+x,c_y-y);
    glVertex2i(c_x-x,c_y-y);

}

void drawCicle(int c_x, int c_y, int r)
{
    int x=0,y=r;
    int d= 5-4*r;

    draw8way(c_x,c_y,x,y);

    while(x<y)
    {

        if(d<0)//dE
        {
            d+=(8*x+12);
            x++;
        }
        else//dSE
        {
            d+=(8*x-8*y+20);
            x++;
            y--;
        }
        draw8way(c_x,c_y,x,y);
    }

}

int get_dis(int xo,int yo, int xt, int yt){
    int ddd= ((xt-xo)*(xt-x0))+((yt-yo)*(yt-yo));
    return ddd;
}

void Circle_drawing()
{
    
    drawCicle(x0,y0,40);
    drawCicle(x1,y1,40);
    x0+=a;y0+=b;x1+=c;y1+=d;
    if(x0<-280 or x0>280)a*=-1;
    if(y0<-200 or y0>200)b*=-1;
    if(x1<-280 or x1>280)c*=-1;
    if(y1<-200 or y1>200)d*=-1;
    int dis=get_dis(x0,y0,x1,y1);
    if(dis<=6400){
        int e =a,f=b;
        a=c,b=d,c=e,d=f;
    }
}

static void display(void){
    int x = 10, y = 20;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    // glBegin(GL_LINES);
    // glVertex2i(-320, 0);
    // glVertex2i(319, 0);
    // glVertex2i(0, -240);
    // glVertex2i(0, 239);
    // glEnd();
    glBegin(GL_POINTS);
    if(click==2) Circle_drawing();


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

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutMainLoop();
    return EXIT_SUCCESS;
}