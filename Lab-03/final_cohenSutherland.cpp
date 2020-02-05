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

#include <bits/stdc++.h>
using namespace std;

static int slices = 16;
static int stacks = 16;

int Wi=640, He=480;

bool colored = false;
int boundary = 150;

int Xmin = -boundary;
int Xmax = boundary;
int Ymin = -boundary;
int Ymax = boundary;


const int LEFT      = 1;
const int RIGHT     = 2;
const int BOTTOM    = 4;
const int TOP       = 8;

int x0click,y0click,x1click,y1click;

int call;
int x_0, x_1, y_0, y_1;

int flag1=0,flag2=0;

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

int findZone (int x0, int y0, int x1, int y1) {
	int dx = x1 - x0, dy = y1 - y0;
	if (dx >= 0 and dy >= 0) {
		if (dx >= dy) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else if (dx < 0 and dy >= 0) {
		if (-dx >= dy) {
			return 3;
		}
		else {
			return 2;
		}
	}
	else if (dx < 0 and dy < 0) {
		if (-dx >= -dy) {
			return 4;
		}
		else {
			return 5;
		}
	}
	else {
		if (dx >= -dy) {
			return 7;
		}
		else {
			return 6;
		}
	}
}

void drawPixel (int x, int y, int zone) {
	switch (zone) {
		case 0:
			// glColor3d(0, 102, 0);
			glVertex2i(x, y);
			break;
		case 1:
			// glColor3d(0, 102, 102);
			glVertex2i(y, x);
			break;
		case 2:
			// glColor3d(51, 0, 102);
			glVertex2i(-y, x);
			break;
		case 3:
			// glColor3d(255, 255, 0);
			glVertex2i(-x, y);
			break;
		case 4:
			// glColor3d(204, 0, 0);
			glVertex2i(-x, -y);
			break;
		case 5:
			// glColor3d(255, 153, 255);
			glVertex2i(-y, -x);
			break;
		case 6:
			// glColor3d(255, 255, 255);
			glVertex2i(y, -x);
			break;
		case 7:
			// glColor3d(102, 0, 51);
			glVertex2i(x, -y);
			break;
	}
}

void drawLine0 (int x0, int y0, int x1, int y1, int zone) {
	int dx = x1 - x0, dy = y1 - y0;
	int x = x0, y = y0, d = 2 * dy - dx;
	int de = 2 * dy, dne = 2 * (dy - dx);
	while (x <= x1) {
		drawPixel (x, y, zone);
		if (d < 0) {
			++x;
			d += de;
		}
		else {
			++x, ++y;
			d += dne;
		}
	}
}

void drawLine (int x0, int y0, int x1, int y1) {
	int zone = findZone(x0, y0, x1, y1);
	//printf("zone = %d\n", zone);
	switch (zone) {
		case 0:
			drawLine0(x0, y0, x1, y1, zone);
			break;
		case 1:
			drawLine0(y0, x0, y1, x1, zone);
			break;
		case 2:
			drawLine0(y0, -x0, y1, -x1, zone);
			break;
		case 3:
			drawLine0(-x0, y0, -x1, y1, zone);
			break;
		case 4:
			drawLine0(-x0, -y0, -x1, -y1, zone);
			break;
		case 5:
			drawLine0(-y0, -x0, -y1, -x1, zone);
			break;
		case 6:
			drawLine0(-y0, x0, -y1, x1, zone);
			break;
		case 7:
			drawLine0(x0, -y0, x1, -y1, zone);
			break;
	}
}


int makeCode(double x,double y)
{
    int code = 0;
    
    if(y>Ymax)
        code |= TOP;
    else if(y<Ymin)
        code |= BOTTOM;

    if(x>Xmax)
        code |= RIGHT;
    else if(x<Xmin)
        code |= LEFT;

    return code;
}


void cohen_Sutherland(double x0,double y0,double x1,double y1)
{
    // glPointSize(3);
    // glColor3f(1.0,1.0,1.0);
    // glBegin(GL_POINTS);
    // glVertex2i(x0,y0);
    // glVertex2i(x1,y1);
    // glEnd();
    // glPointSize(1); 


    glBegin(GL_POINTS);

    
    int code0,code1,code;
    double x,y;

    double x0_ = x0;
    double x1_ = x1;
    double y0_ = y0;
    double y1_ = y1;

    code0 = makeCode(x0,y0);
    code1 = makeCode(x1,y1);
    int ff=0;
    int f0=0;
    while(true)
    {
        ff++;

        if ((code0 == 0) && (code1 == 0)) //fully accepted
        {
        	
        	if(ff==1){
        		if(f0!=0) printf("Fully Accepted\n");
        		f0++;
        	}
        
            // glEnd();
            // glPointSize(4);
            // glColor3f(1.0,1.0,1.0);
            // glBegin(GL_POINTS);
            // glVertex2i(x0,y0);
            // glVertex2i(x1,y1);
            // glEnd();
            // glPointSize(1); 
            // glBegin(GL_POINTS);

            // glColor3f(1.0,1.0,0.0);///Yellow
            x_0=x0;y_0=y0;x_1=x1,y_1=y1;
            drawLine(x0,y0,x1,y1);            
            break;
            //exit();
        }
        else if (code0 & code1)//fully rejected
        {
        	if(ff==1) printf("Fully Rejected\n");
            // glColor3f(1.0, 0.0, 0.0);///Red
            // drawLine(x0,y0,x1,y1);
            break;
            //exit();
        }
        else //partial
        {
        	if(ff==1) printf("Partial Accepted\n");
            int code; 
            double x, y; 

            if (code0) 
                code = code0; 
            else
                code = code1; 
  
            if (code & TOP) 
            { 
                
                x = x0 + (x1 - x0) * (Ymax - y0) / (y1 - y0); 
                y = Ymax; 
            } 
            else if (code & BOTTOM) 
            { 
                x = x0 + (x1 - x0) * (Ymin - y0) / (y1 - y0); 
                y = Ymin; 
            } 
            else if (code & RIGHT) 
            { 
                y = y0 + (y1 - y0) * (Xmax - x0) / (x1 - x0); 
                x = Xmax; 
            } 
            else if (code & LEFT) 
            { 
                y = y0 + (y1 - y0) * (Xmin - x0) / (x1 - x0); 
                x = Xmin; 
            } 



            if(code == code0)
            {
                // glColor3f(0.5, 0.5, 0.5);
                // drawLine(x0,y0,x,y);
                x0 = x;
                y0 = y;
                code0 = makeCode(x0,y0);
            }
            else
            {
                // glColor3f(0.5, 0.5, 0.5);
                // drawLine(x1,y1,x,y);
                x1 = x;
                y1 = y;
                code1 = makeCode(x1,y1);   
            }
  
        
        }//partial
    
    }//while loop
    glEnd();
    //if(flag1==1) printf("Fully Accepted\n");
  //  else if(flag2==1) printf("Partial Accepted\n");
    //else printf("Fully Rejected\n");

}//end of function


void myMouse (int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON and state == GLUT_UP) {
		if (call % 2 == 0) {
			x0click=x_0 = x - 320, y_0 = y - 240;
			y_0 *= -1;
			y0click=y_0;
		}
		else if (call % 2 == 1) {
			x1click=x_1 = x - 320, y_1 = y - 240;
			y_1 *= -1;
			y1click=y_1;
		}
		printf("%d %d\n", x, y);
		if (call % 2 == 1) {
			printf("zone = %d\n", findZone(x_0, y_0, x_1, y_1));
		}
		++call;
	}
}

static void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1,1,1);
	glBegin(GL_LINES);
	// glVertex2i(-320, 0);
	// glVertex2i(319, 0);
	// glVertex2i(0, -240);
	// glVertex2i(0, 239);


    glColor3f(1.0,1.0,1.0);
    // glVertex2i(-320,0);
    // glVertex2i(319,0);
    // glVertex2i(0,239);
    // glVertex2i(0,-240);

    glVertex2i(boundary,He/2-1);
    glVertex2i(boundary,-He/2);

    glVertex2i(Wi/2-1,-boundary);
    glVertex2i(-Wi/2,-boundary);

    glVertex2i(-boundary,He/2-1);
    glVertex2i(-boundary,-He/2);    

    glVertex2i(Wi/2-1,boundary);
    glVertex2i(-Wi/2,boundary);
	glEnd();
	glPointSize(5.0);
	glBegin(GL_POINTS);

	if (call % 2 == 0 and call) {
		glColor4f(1.0f, 1.0f, 0.0f, 0.0f);  //yellow point color
		glVertex2i(x_0, y_0);
		glVertex2i(x_1, y_1);
		glColor4f(1.0f, 0.5f, 0.0f, 0.0f);//orange/brown
		glVertex2i(x0click,y0click);  
		glVertex2i(x1click,y1click);
	}

	glEnd();
	glPointSize(1.0);
	glBegin(GL_POINTS);

	if (call % 2 == 0) {
		glColor3f(1,0,0);
		drawLine(x0click,y0click,x1click,y1click);
		glColor3f(1,1,1);
		cohen_Sutherland(x_0, y_0, x_1, y_1);
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

	glutMouseFunc(myMouse);
	glutIdleFunc(idle);

	glutMainLoop();

	return EXIT_SUCCESS;
}
