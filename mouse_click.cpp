#include <GL/glut.h>
#include <GL/gl.h>
#include<iostream>
using namespace std;

int a,b,c,d;

bool flag = false;


void drawPixel1(int x, int y){
		glVertex2i(x,y);
	}


void drawPixel(int xx, int yy) {

	glPointSize(2);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);


	glVertex2f(xx , yy);

	//zoneFind(0,0,x,y);


	glEnd();
	glutSwapBuffers();
	//glFlush();
}


	void drawLine_0(int x0,int y0,int x1,int y1){
		printf("Zone 0\n");
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
		printf("Zone 1\n");
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
		printf("Zone 2\n");
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
		printf("Zone 3\n");
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
		printf("Zone 4\n");
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
		printf("Zone 5\n");
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
		printf("Zone 6\n");
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
		printf("Zone 7\n");
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



	int findZone(int i0,int j0,int i1,int j1){


		int x1=i1,y1=j1,x0=i0,y0=j0;

		//printf("inner zoneFind: %d %d %d %d\n",x0,y0,x1,y1 );

		int dx=x1-x0;
		int dy=y1-y0;		

		if(dx>0 and dy>=0){
			if(dx>dy) return 0;
			else return 1;
		}
		if(dx<=0 and dy>0){
			if(abs(dx)>abs(dy)) return 3;
			else return 2;
		}
		if(dx<0 and dy<=0){
			if(abs(dx)>abs(dy)) return 4;
			else return 5;
		}
		if(dx>=0 and dy<0){
			if(abs(dx)>abs(dy)) return 7;
			else return 6;
		}
}





int cnt = 0;
void mouse(int bin, int state , int xx , int yy) {
	cnt=cnt%4;
	printf("%d\n",cnt);
	int a1,b1;
	
	a1 = xx -320;
	b1 = 240-yy;
	drawPixel(a1, b1);
	printf("Taken Point: %d %d\n",a1,b1 );

	if(cnt==0){
		a = a1;
		b = b1;
	}
	else if(cnt==3){
		c = a1;
		d = b1;
	}
	printf("aboltabol\n");
	

/*	if(bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {

		a1 = xx -320;
		b1 = 240-yy;
		printf("2nd: %d %d\n\n\n\n",a1,b1 );
	
	}*/

	if(cnt==3){
		printf("%d %d %d %d\n",a,b,c,d);
		int zone = findZone(a,b,c,d);
		printf("Zone no: %d\n\n\n",zone);

		if(zone==0) drawLine_0(a, b, c, d);
		else if(zone==1) drawLine_1(a, b, c, d);
		else if(zone==2) drawLine_2(a, b, c, d);
		else if(zone==3) drawLine_3(a, b, c, d);
		else if(zone==4) drawLine_4(a, b, c, d);
		else if(zone==5) drawLine_5(a, b, c, d);
		else if(zone==6) drawLine_6(a, b, c, d);
		else if(zone==7) drawLine_7(a, b, c, d);
	}
	cnt++;
}


void init (int width, int height)
{
	/* select clearing (background) color */
	//glClearColor (1.0, 1.0, 1.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);


	const float ar = (float) width / (float) height;

	glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-320, 319, -240, 239, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

	
void display (void){
	// glClear(GL_COLOR_BUFFER_BIT);
	// //glColor3f(1.0,1.0,1.0);
	// glFlush();




	int x = 10, y = 20;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,1,1);
    
    glBegin(GL_LINES);

//we can edit code from here.
    glVertex2i(-320, 0);
    glVertex2i(319, 0);
    glVertex2i(0, -240);
    glVertex2i(0, 239);

    //zoneFind(-2,4,-45,34);


	glFlush();


//we can edit code till here.
    glEnd();
    glBegin(GL_POINTS);
    glVertex2i(x, y+1);
    glVertex2i(x, y);
    glEnd();
    glutSwapBuffers();

}



/*Main*/

int main (int argc,char** argv){
	// glutInit(&argc,argv);
	// glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	// glutInitWindowSize(640,480);
	// Set the posotion of window
	// glutInitWindowPosition(10,10);
	// glutCreateWindow("My Vindow");
	// glutDisplayFunc(display);

	glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Experiment 01");

   //glutReshapeFunc(resize);

    glutMouseFunc(mouse);
	glutReshapeFunc(init);

    glutDisplayFunc(display);
    //glutKeyboardFunc(key);
    //glutIdleFunc(idle);

    glutMainLoop();

    return EXIT_SUCCESS;

	

}
