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

const int WIDTH  = 960;
const int HEIGHT = 640;

const int center_x = 480;
const int center_y = 320;

const int min_x = -480;
const int max_x = 479;

const int min_y = -320;
const int max_y = 319;

/* GLUT callback Handlers */

static void resize(int width, int height){
	const float ar = (float) width / (float) height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-WIDTH / 2, WIDTH / 2 - 1, -HEIGHT / 2, HEIGHT / 2 - 1, -1, 1);
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

void draw8way (int x, int y, int a, int b) {
	glVertex2i(x + a, y + b);
	glVertex2i(y + a, x + b);
	glVertex2i(-x + a, y + b);
	glVertex2i(-y + a, x + b);
	glVertex2i(-x + a, -y + b);
	glVertex2i(-y + a, -x + b);
	glVertex2i(x + a, -y + b);
	glVertex2i(y + a, -x + b);
}

void drawCircle (int a, int b, int r) {
	int x = 0, y = r;
	int d = 5 - 4 * r;
	while (x <= y) {
		draw8way(x, y, a, b);
		if (d < 0) {
			d += 8 * x + 12;
			++x;
		}
		else {
			d += 8 * x - 8 * y + 20;
			++x, --y;
		}
	}
}

int call, anoCall;
int sx, sy, ex, ey;
int dx, dy;
int radius;

int sign (int x) {
	return (x < 0) ? 0 : 1;
}

void myMouse (int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON and state == GLUT_DOWN) {
		++call;
		if (call == 1) {
			sx = x - center_x, sy = y - center_y;
			sy *= -1;

			ex = sx, ey = sy;
		}
		else if (anoCall == 0 and call > 1) {
			ex = x - center_x, ey = y - center_y;
			ey *= -1;
		}
	}
	if (button == GLUT_LEFT_BUTTON and state == GLUT_UP) {
		++anoCall;
		ex = x - center_x, ey = y - center_y;
		ey *= -1;
		dx = ex - sx, dy = ey - sy;
		radius = (int) sqrt(dx * dx + dy * dy);

		double minVal = 1e15;
		int nowX, nowY;
		for (int nx = -10; nx <= 10; nx++) {
			for (int ny = -10; ny <= 10; ny++) {
				if (nx == 0 and ny == 0) {
					continue;
				}
				if (abs(nx * dy - ny * dx) < minVal and sign(nx) == sign(dx) and sign(dy) == sign(ny)) {
					minVal = abs(nx * dy - ny * dx);
					nowX = nx, nowY = ny;
				}
			}
		}
		dx = nowX, dy = nowY;

		//while (abs(dx) > 10) {
			//dx /= 10;
		//}
		//while (abs(dy) > 10) {
			//dy /= 10;
		//}

		int g = __gcd(abs(dx), abs(dy));
		if (g != 0) {
			dx /= g, dy /= g;
		}
	}
	printf("%d %d\n", x, y);
}

void nowMouse (int x, int y) {
	if (anoCall == 0) {
		ex = x - center_x, ey = y - center_y;
		ey *= -1;

		radius = (int) sqrt((ex - sx) * (ex - sx) + (ey - sy) * (ey - sy));
	}
}

void checkBoundaries (int a, int b, int *p, int *q) {
	if ((b + radius > max_y) or (b - radius < min_y)) {
		(*q) *= -1;
	}
	else if ((a + radius > max_x) or (a - radius < min_x)) {
		(*p) *= -1;
	}
}

static void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3d(1,1,1);

	glBegin(GL_POINTS);
	glColor3d(0, 204, 0);

	glutMouseFunc(myMouse);
	glutMotionFunc(nowMouse);
	if (call > 0) {
		drawCircle(sx, sy, radius);
	}

	if (anoCall > 0) {
		sx += dx, sy += dy;
		checkBoundaries(sx, sy, &dx, &dy);
	}

	//printf("call = %d\n", anoCall);

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
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(10,10);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutCreateWindow("Experiment 01");

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutIdleFunc(idle);

	srand(time(0));
	glutMainLoop();

	return EXIT_SUCCESS;
}