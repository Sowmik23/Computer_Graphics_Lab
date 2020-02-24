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
#include<math.h>

static int slices = 16;
static int stacks = 16;

int flag1 = 0,flag2=0, flag3=0;
int x00,y00,x11=-500,y11=400,radius=40;
int addx1=1,addy1=1,addx2=-1,addy2=-1;
int mass1=1,mass2=1;

int Wi=640, He=480;
int cntrY;


void draw_britto(int a,int b,int r);
void draw8way(int x,int y,int a,int b);
void draw4way(int x,int y,int cntrX, int cntrY);
void draw_upobritto(int a,int b,int cntrX, int cntrY);


void myInit (void){
    glClearColor(0.0, 0.0, 0.0,1.0);
}



/* GLUT callback Handlers */

static void resize(int width, int height){
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 319, -240, 239, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void draw_britto(int a,int b,int r)
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


void func(int a,int b,int r)
{
    int xmax=Wi-1;
    int ymax=He-1;

    int xmin=-Wi/2;
    int ymin=-He/2;

    int cntrX=a;
    cntrY = b;
     

    int t=1;

       while(1){
       glClear(GL_COLOR_BUFFER_BIT);

       draw_britto(cntrX,cntrY,r);


       while(cntrY-r>ymin)
      {

          glClear(GL_COLOR_BUFFER_BIT);

          glBegin(GL_POINTS);
          // if(cntrY>100) t=2;
          // else if(cntrY>0) t=2;
          // else if(cntrY>-90) t=3;
          // else if(cntrY>-120) t=4;
          // else if(cntrY>-175) t=6;
          // else if(cntrY>-250) t=8;
      
          if(cntrY>150) t=1;
          else if(cntrY>100) t=2;
          else if(cntrY>50) t=3;
          else if(cntrY>0) t=4;
          else if(cntrY>-50) t=5;
          else if(cntrY>-100) t=6;
          else if(cntrY>-150) t=7;
          else if(cntrY>-200) t=8;
          else if(cntrY>-250) t=9;
          
          else t=10;

          cntrY-=t;

          if(cntrY>=b-5){
            int c =0;
            while(1){
              c++;
              if(c==999) break;
            }

          }

          draw_britto(cntrX,cntrY,r);


         glEnd();

         glutSwapBuffers();
      }


        int A=r;
        int B=r;
        for(int i=0;i<5;i++)
        {
          glClear(GL_COLOR_BUFFER_BIT);

          glBegin(GL_POINTS);


          A+=3;
          B=sqrt(abs(2*r*r-A*A));

          draw_upobritto(A,B,cntrX,cntrY);
          glEnd();

         glutSwapBuffers();
        }

        for(int i=0;i<5;i++)
        {
          glClear(GL_COLOR_BUFFER_BIT);

          glBegin(GL_POINTS);

          //cntrY--;
          A-=3;
         // B+=3;
          B=sqrt(abs(2*r*r-A*A));
          draw_upobritto(A,B,cntrX,cntrY);
          glEnd();

         glutSwapBuffers();

        }
   
      while(cntrY<=200){
          glClear(GL_COLOR_BUFFER_BIT);

          if(cntrY>150) t=1;
          else if(cntrY>100) t=2;
          else if(cntrY>50) t=3;
          else if(cntrY>0) t=4;
          else if(cntrY>-50) t=5;
          else if(cntrY>-100) t=6;
          else if(cntrY>-150) t=7;
          else if(cntrY>-200) t=8;
          else if(cntrY>-250) t=9;
      
          else t=10;

          cntrY+=t;
          glBegin(GL_POINTS);

          draw_britto(cntrX,cntrY,r);

          glEnd();

         glutSwapBuffers();
    }
  }  
}

void draw_upobritto(int a,int b, int cntrX,int cntrY)
{
   float d = a*a -b*b*(a-.25);
   int x=a,y=0;
   draw4way(x,y,cntrX,cntrY);
   
   while(b*b*(x-.5)>a*a*(y+1)){

       if(d<0){
           d+=a*a*(2*y+3);
           y++;
        }    
        else{
            d+=a*a*(2*y+3)-b*b*(2*x-2);
            x--;
            y++;
        }

        draw4way(x,y,cntrX,cntrY);
    }

    while(x>-5)
    {
        if(d<0){

        d+=b*b*(3-2*x)+a*a*(2*y+2);
            x--;
            y++;

        }
        else{
        
            d+=b*b*(3-2*x);
            x--;
        }

        draw4way(x,y,cntrX,cntrY);
    }
}


void draw4way(int x,int y,int cntrX, int cntrY){

    glVertex2i(x+cntrX,y+cntrY);
    glVertex2i(-x+cntrX,y+cntrY);
    glVertex2i(x+cntrX,-y+cntrY);
    glVertex2i(-x+cntrX,-y+cntrY);

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


int calculateHypotenous(int dx,int dy){
    return sqrt((dx*dx + dy*dy));
}

void mouse(int button, int state, int mousex, int mousey)
{

    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        int mx = mousex;
        int my = mousey;
        printf("click %d %d %d\n",flag1,flag2,flag3);

        //printf(" c1 %d %d\n",mx-320,-my+240);
        glutPostRedisplay();

        if (flag3==1){
            flag1=0;
            flag2=0;
            flag3=0;
            x11=x00;
            y11=y00;
        }

        if(flag1==0){
            flag1=1;
            x00 = mx-320;
            y00 = -my+240;
            x11=x00;
            y11=y00;
            printf("%d %d\n",x11,y11);
        }
        else{
            //flag1=0;
            flag3 = 1;
            x11 = mx-320;
            y11 = -my+240;
            addx1 = (x11 - x00);
            addy1 = (y11 - y00);
            int d = calculateHypotenous(addx1,addy1);
            addx1 = 2*(addx1)/d;
            addy1 = 2*(addy1)/d;
            printf("%d %d\n",x11,y11);
        }
    }
}

void myMouseMove( int mousex, int mousey)
{
    int mx = mousex;
    int my = mousey;
    if(flag3 ==0){
        flag2 = 1;
        x11 = mx-320;
        y11 = -my+240;
    //printf("%d %d\n",tempX,tempY);
    }

    glutPostRedisplay();
}


void drawCircle1(int a,int b,int r){
    int x=0,y=r, d=5-4*r;
    draw8way(x,y,a,b);
    while(x<y){
        if(d<0){
            x++;
            d+= 8*x + 12;
        }
        else{
            x++,y--;
            d+= 8*x - 8*y + 20;
        }
        draw8way(x,y,a,b);
    }
}

bool collisionDetected(int x0,int y0,int x1,int y1){
    return ((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0) < 4*radius*radius);
}
int calculateRadius(int x0,int y0,int x1,int y1){
    return sqrt((x1-x0)*(x1-x0) + (y1-y0)*(y1-y0));
}


static void display(void){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);


    // glVertex2i(-320, 0);
    // glVertex2i(319, 0);
    // glVertex2i(0, -240);
    // glVertex2i(0, 239);
    glEnd();
    glBegin(GL_POINTS);
    //printf("1\n");

    if(flag1==1 && flag3==0){
            if (flag2==0){
                drawCircle1(x00,y00,0);
                // func(x00, y00, 0);
                printf("yeah11111\n");
            }
            else{
            drawCircle1(x00,y00,radius);
                // func(x00, y00, radius);
                printf("yeah2222\n");
            }
        //printf("2\n");
        if(flag2 ==1){
            radius = calculateRadius(x00,y00,x11,y11);
          //  printf("3\n");
            printf("yeah333333\n");
        }
       
    }
    else if(flag1==1 && flag3 ==1){
        drawCircle1(x00,y00,radius);
        func(x00,y00, radius);

        printf("yeah4444\n");
        

        x00+=addx1, y00+=addy1;
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

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glutMouseFunc(mouse);
    glutPassiveMotionFunc( myMouseMove);
    glutMainLoop();



    return EXIT_SUCCESS;
}