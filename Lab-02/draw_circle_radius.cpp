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
int valid=0;

int stop=-1;
int zone,radius=10;
int old_x,old_y,x0,y0,x1,y1;
int a,b,c,d;


int R=0;

bool flag=false;
int f=0;

void mouse_func (int button, int state, int x, int y) {
  x0=x-320; 
  y0=240-y;

    // a=(rand()%3)-1;b=(rand()%3)-1;c=(rand()%3)-1;d=(rand()%3)-1;
    // if(a==0)a+=1;if(b==0)b+=1;if(c==0)c+=1;if(d==0)d+=1;a*=2;b*=2;c*=2;d*=2;

  valid = state == GLUT_DOWN;
  if(button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
    stop=1;
    printf("Mouse is unclicked\n");
    printf("Radius: %d %d %d \n",x,y,radius);

a=1;
b=1;
c=1;
d=1;
f=1;
    flag = true;
}


void motion_func (int x, int y) {
    stop=0;
  if (valid) {
    int dx = x0 - (x-320);
    int dy = y0 - (240-y);
    radius=(dx*dx)+(dy*dy);

     //if(radius>R) R = radius;
     printf("Radius: %d \n",radius);
    // radius=(int) r;   /* do something with dx and dy */
  }
  x1 = x-320;
  y1 = 240-y;

  printf("%d %d \n",x,y );
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
    
    drawCicle(x0,y0,radius);
    
}

void Circle_drawing_1()
{
    
    drawCicle(x0,y0,radius);
    drawCicle(x1,y1,radius);

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

    if(stop==0){
        Circle_drawing();
        stop=-1;
    } 

    if(flag==true and f==1) Circle_drawing_1();

    printf("%d %d\n",stop, flag);


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
    glutMouseFunc(mouse_func);
    glutMotionFunc(motion_func);
    glutMainLoop();
    return EXIT_SUCCESS;
}