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

static int slices = 16;
static int stacks = 16;

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


	void drawPixel(int x, int y){
		glVertex2i(x,y);
	}

	void drawLine_0(int x0,int y0,int x1,int y1){
		int dx = x1-x0;
		int dy = y1-y0;
		int x = x0;
		int y = y0;
		int d = 2*dy-dx;
		int dE = 2*dy;
		int dNE = 2*(dy-dx);
	
		drawPixel(x,y);

		while(x<x1){
			if(d<0){
				x++;
				d+=dE;
			}
			else {
				x++;
				y++;
				d+=dNE;
			}
			drawPixel(x,y);
		}
	}

	void drawLine_1(int x0,int y0,int x1,int y1){
		int dx = x1-x0;
		int dy = y1-y0;
		int x = x0;
		int y = y0;
		int d = 2*dy-dx;
		int dE = 2*dy;
		int dNE = 2*(dy-dx);
	
		drawPixel(x,y);

		while(x<x1){
			if(d<0){
				x++;
				d+=dE;
			}
			else {
				x++;
				y++;
				d+=dNE;
			}
			drawPixel(x,y);
		}
	}

	void drawLine_2(int x0,int y0,int x1,int y1){
		int dx = x1-x0;
		int dy = y1-y0;
		int x = x0;
		int y = y0;
		int d = -(2*dx+dy);
		int dN = -2*dx;
		int dWN = -2*(dx+dy);
	
		drawPixel(x,y);

		while(y<y1){
			if(d<0){
				y++;
				d+=dN;
			}
			else {
				x--;
				y++;
				d+=dWN;
			}
			drawPixel(x,y);
		}
	}

	void drawLine_3(int x0,int y0,int x1,int y1){
		int dx = x1-x0;
		int dy = y1-y0;
		int x = x0;
		int y = y0;
		int d = -dx+2*dy;
		int dW = -2*dy;
		int dWN = -2*(dx+dy);
	
		drawPixel(x,y);

		while(x>x1){
			if(d<0){
				x--;
				y++;
				d+=dWN;
			}
			else {
				x--;
				d+=dW;
			}
			drawPixel(x,y);
		}
	}

	void drawLine_4(int x0,int y0,int x1,int y1){
		int dx = x1-x0;
		int dy = y1-y0;
		int x = x0;
		int y = y0;

		int d = dx-2*dy;
		int dW = -2*dy;
		int dSW = 2*(dx-dy);
	
		drawPixel(x,y);

		while(x>x1){
			if(d<0){
				x--;
				y--;
				d+=dSW;
			}
			else {
				x--;
				d+=dW;
			}
			drawPixel(x,y);
		}
	}

	void drawLine_5(int x0,int y0,int x1,int y1){
		int dx = x1-x0;
		int dy = y1-y0;
		int x = x0;
		int y = y0;

		int d = 2*dx - dy;
		int dS = 2*dx;
		int dSW = 2*(dx-dy);
	
		drawPixel(x,y);

		while(y>y1){
			if(d<0){
				y--;
				d+=dS;
			}
			else {
				x--;
				y--;
				d+=dSW;
			}
			drawPixel(x,y);
		}
	}


	void drawLine_6(int x0,int y0,int x1,int y1){
		int dx = x1-x0;
		int dy = y1-y0;
		int x = x0;
		int y = y0;

		int d = 2*dx + dy;
		int dS = 2*dx;
		int dSE = 2*(dx+dy);
	
		drawPixel(x,y);

		while(y>y1){
			if(d<0){
				x++;
				y--;
				d+=dSE;
			}
			else {
				y--;
				d+=dS;
			}
			drawPixel(x,y);
		}
	}

	void drawLine_7(int x0,int y0,int x1,int y1){
		int dx = x1-x0;
		int dy = y1-y0;
		int x = x0;
		int y = y0;

		int d = 2*dy + dx;
		int dE = 2*dy;
		int dSE = 2*(dx+dy);
	
		drawPixel(x,y);

		while(x<x1){
			if(d<0){
				x++;
				d+=dE;
			}
			else {
				x++;
				y--;
				d+=dSE;
			}
			drawPixel(x,y);
		}
	}

	void zoneFind(int x0,int y0,int x1,int y1){
		int dx = x1-x0;
		int dy = y1-y0;
		
		if(dx>0 and dy>=0){
			if(dx>dy) return drawLine_0(x0,y0,x1,y1);
			else return drawLine_1(x0,y0,x1,y1);
		}
		if(dx<=0 and dy>0){
			if(abs(dx)>abs(dy)) return drawLine_3(x0,y0,x1,y1);
			else return drawLine_2(x0,y0,x1,y1);
		}
		if(dx<0 and dy<=0){
			if(abs(dx)>abs(dy)) return drawLine_4(x0,y0,x1,y1);
			else return drawLine_5(x0,y0,x1,y1);
		}
		if(dx>=0 and dy<0){
			if(abs(dx)>abs(dy)) return drawLine_7(x0,y0,x1,y1);
			else return drawLine_6(x0,y0,x1,y1);
		}
}



static void display(void){
    int x = 10, y = 20;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    glBegin(GL_LINES);

//we can edit code from here.
    glVertex2i(-320, 0);
    glVertex2i(319, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 239);

	
	zoneFind(int x0,int y0,int x1,int y1);
		

//we can edit code till here.
    glEnd();
    glBegin(GL_POINTS);
    glVertex2i(x, y+1);
    glVertex2i(x, y);
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

    glutMainLoop();

    return EXIT_SUCCESS;
}
