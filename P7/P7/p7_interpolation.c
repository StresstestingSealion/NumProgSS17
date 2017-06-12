/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 	Serie 7 - Approximation von Funktionen (Interpolation) 	 */
/* ------------------------------------------------------------- */
/*	Autoren: Christina Boerst				 */
/*	Versionsnummer:	1					 */
/*---------------------------------------------------------------*/


  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include <assert.h>
  #include <GL/freeglut.h>
  #include <GL/glut.h>

  #include "interpolation.h"

  #ifndef M_PI
/* Copied from math.h  */
#define M_PI		3.14159265358979323846
#endif


/* ------------------------------------------------------------
* Global variable
*-------------------------------------------------------------*/

int window_1, window_2, window_3;
pinterpolation aequidistant, chebychev;
double data[2];
int m = 10;
int resolution = 500;

double min_x = -10.0;
double max_x = 10.0;

int window_width = 500;
int window_height = 500;

double exampleFunction(double x, void *data){
	if (((double *) data)[0] == 0.0){
		double lambda = ((double *) data)[1];
		return lambda * exp(- 0.5 * x * x);
	}
	return 1 / (1 + x * x);
}

/* ------------------------------------------------------------
* GLUT functions
*-------------------------------------------------------------*/

/* If necessary use the pictures as orientation,
   but feel free to create something different =)*/

static void
reshape(int width, int height){
	glViewport(0, 0, width, height);

	glLoadIdentity();

    	if(width > height)
	{
       		glScalef((double) height/width, 1.0, 1.0);
    	}
    	else
	{
       		glScalef(1.0, (double) width/height, 1.0);
    	}
}


static void aequidistantView(){
	int i;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,0.0);
	glPointSize(2.0);
	glBegin(GL_POINTS);

	for(i = 0; i < 500; i++){
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(-1 + 2.0/500 * i, eval_interpolation_polynomial(aequidistant, min_x + (max_x - min_x)/resolution * i));
	}

	glEnd();

    	glFlush();

}

static void chebychevView(){
	int i;
	glClearColor(0.0,0.0,0.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	for(i = 0; i < resolution; i++){
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(-1 + 2.0/resolution * i, eval_interpolation_polynomial(chebychev, min_x + (max_x - min_x)/resolution * i));
	}
	glEnd();

    	glFlush();
}

static void combinedView(){
	int i;
	int mAequidistant = aequidistant->m;
	int mChebychev = chebychev->m;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0,0.0,0.0,0.0);
	glPointSize(2.0);
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	for(i = 0; i < resolution; i++){
		glVertex2f(-1 + 2.0/resolution * i, eval_interpolation_polynomial(aequidistant, min_x + (max_x - min_x)/resolution * i));
	}

	glEnd();
	glBegin(GL_LINES);
	for(i = 0; i < mAequidistant + 1; i++){
		glVertex2f(2/(max_x - min_x) * aequidistant->xi[i], -0.06);
		glVertex2f(2/(max_x - min_x) * aequidistant->xi[i], 0.06);
	}

	glEnd();
	glBegin(GL_POINTS);
	glColor3f(0.0, 1.0, 0.0);
	for(i = 0; i < resolution; i++){
		glVertex2f(-1 + 2.0/resolution * i, eval_interpolation_polynomial(chebychev, min_x + (max_x - min_x)/resolution * i));
	}

	glEnd();
	glBegin(GL_LINES);
	for(i = 0; i < mChebychev + 1; i++){
		glVertex2f(2/(max_x - min_x) * chebychev->xi[i], -0.06);
		glVertex2f(2/(max_x - min_x) * chebychev->xi[i], 0.06);
	}

	glEnd();
  glFlush();
}

void interpolate(){
	setup_aequidistant_interpolationpoints(aequidistant, min_x, max_x);
	eval_interpolated_values(aequidistant, &exampleFunction, data);
	newton_divided_differences(aequidistant);

	setup_chebyshev_interpolationpoints(chebychev, min_x, max_x);
	eval_interpolated_values(chebychev, &exampleFunction, data);
	newton_divided_differences(chebychev);
}

void refreshView(){
	glutSetWindow(window_1);
	glutPostRedisplay();
	glutSetWindow(window_2);
	glutPostRedisplay();
	glutSetWindow(window_3);
	glutPostRedisplay();
}
/*
*	Use:
*	e: use exponential function
*	p: use 1/polynom function
*	h: increases lambda (if mode is exponential)
*	l: decreases lambda (if mode is exponential)
*	m: increases the shown interval.
*	n: decreases the shown interval.
*	a: remove one interpolaration point.
*	d: add one interpolaration point.
*/
static void
key(unsigned char key, int x, int y){
  	(void) x;
	(void) y;

	switch (key){
	  case '1':
				data[0] = 0.0;
				interpolate();
				refreshView();
				break;
	  case '2':
				data[0] = 1.0;
				interpolate();
				refreshView();
				break;
	  case '3':		if(data[0]==0.0){
					data[1] += 0.05;
					interpolate();
					refreshView();
				}
				break;
	  case '4':		if(data[0]==0.0){
					data[1] -= 0.05;
					interpolate();
					refreshView();
				}
				break;
	  case '5':		m -= 1;
		if(m > 0){
				aequidistant = new_interpolation(m);
				chebychev = new_interpolation(m);
				interpolate();
				refreshView();
			}
				break;
	  case '6':		m += 1;
				aequidistant = new_interpolation(m);
				chebychev = new_interpolation(m);
				interpolate();
				refreshView();
				break;
	  default :
				break;
	  }
}

int main(int argc, char** argv)
{
	data[0] = 0.0;
	data[1] = 1.0;

	aequidistant = new_interpolation(m);
	chebychev = new_interpolation(m);
	interpolate();

	glutInit(&argc, argv);

	window_1 = glutCreateWindow ("Aequidistant interpolation points");
	glutPositionWindow(150, 100);
	glutReshapeWindow(window_width, window_height);
	glutDisplayFunc(aequidistantView);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	window_2 = glutCreateWindow ("Chebychev interpolation points");
	glutDisplayFunc(chebychevView);
	glutReshapeWindow(window_width, window_height);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	window_3 = glutCreateWindow ("Comparision Chebychev vs. Aequidistant points");
	glutDisplayFunc(combinedView);
	glutReshapeWindow(window_width, window_height);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);

	glutMainLoop();
   return 0;
}
