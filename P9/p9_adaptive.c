/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 		Serie 9 - Adaptive Quadratur 		 	 */
/* ------------------------------------------------------------- */
/*	Autoren: 		 				 */
/*	Versionsnummer:						 */
/*---------------------------------------------------------------*/


  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include <assert.h>

  #include "quadrature.h"

  #ifndef M_PI
  /* Copied from math.h  */
  #define M_PI		3.14159265358979323846
  #endif

pquadrature quad_m, quad_t;

double data[2];

/* ------------------------------------------------------------
* Example function
*-------------------------------------------------------------*/

<<<<<<< HEAD
double exampleFunction(double x, void *data){
	return (5 * exp(2 * x) * cos(x)) / (exp(M_PI) - 2);
=======
double exampleFunction(double x, void *data) {
    return (5 * exp(2 * x) * cos(x)) / (exp(M_PI) - 2);
}


/* ------------------------------------------------------------
* GLUT functions
*-------------------------------------------------------------*/

static void reshape(int width, int height) {

    glLoadIdentity();
    if (width > height) {
        glScaled((double) height / width, 1.0, 1.0);
    } else {
        glScaled(1.0, (double) width / height, 1.0);
    }

}


static void draw_coordinates() {

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(-1.0, 0.0);
    glVertex2d(1.0, 0.0);
    glVertex2d(0.0, 1.0);
    glVertex2d(0.0, -1.0);
    glEnd();

}


static void draw_example_func(color c) {

    glColor3fv(c);
    glBegin(GL_LINE_STRIP);
    for (double x = 0.0; x <= x_max; x += 0.01) {
        glVertex2d(x / 2, exampleFunction(x, data));
    }
    glEnd();

}


static void draw_quadrature(color c) {

    double x1, x2;
    double a = x_min;
    double b = x_max;

    glColor3fv(c);
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.8, 0.0);

    for (int i = 0; i < interpolationPoints; i++) {

        x1 = a + (b - a) / interpolationPoints * i;
        x2 = a + (b - a) / interpolationPoints * (i + 1);

        glVertex2d(x1 / 2, 0);

        if (quad->m == 0) {
            glVertex2d(x1 / 2, exampleFunction((x1 + x2) / 2, data));
            glVertex2d(x2 / 2, exampleFunction((x1 + x2) / 2, data));
        } else {
            glVertex2d(x1 / 2, exampleFunction(x1, data));
            glVertex2d(x2 / 2, exampleFunction(x2, data));
        }
        glVertex2d(x2 / 2, 0);
    }
    glEnd();

}

void print_sum() {
    double sum = eval_composite_quadrature(quad, x_min, x_max, interpolationPoints, &exampleFunction, data);
    printf("Integrated area: %f\n", sum);
}

static void display() {

    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    draw_coordinates();
    draw_example_func(COLOR_RED);
    draw_quadrature(COLOR_GREEN);

    glFlush();

}

/* Controls: 
	q: add one interpolation point
	a: remove one interpolation point
	1: toggle midpoint rule
	2: toggle trapezoid rule
*/
static void
<<<<<<< HEAD
key(unsigned char key, int x, int y){

	(void) x;
	(void) y;
	
	switch (key){
	  case '1':		quad = setup_midpointrule();
				glutPostRedisplay();
				break;
	  case '2':		quad = setup_trapezoidalrule();
				glutPostRedisplay();
				break;
	  case 27 :
				exit (EXIT_SUCCESS);
				break;
	  default :
				break;	 		
	  }
=======
key(unsigned char key, int x, int y) {

    (void) x;
    (void) y;

    switch (key) {
        case 'a':
            interpolationPoints -= 1;
            glutPostRedisplay();
            break;
        case 'q':
            interpolationPoints += 1;
            glutPostRedisplay();
            break;
        case '1':
            quad = setup_midpointrule();
            glutPostRedisplay();
            break;
        case '2':
            quad = setup_trapezoidalrule();
            glutPostRedisplay();
            break;
        case 27 :
            exit(EXIT_SUCCESS);
            break;
        default :
            break;
    }
    print_sum();
>>>>>>> master
>>>>>>> master
}

int main(int argc, char** argv){
	double sum = 0.0;
	double precisision = 0.00001;
	int steps = 0;

	data[0] = 0.0;
	data[1] = 1.0;

	quad_m = setup_midpointrule();
	quad_t = setup_trapezoidalrule();

	sum = eval_composite_quadrature(quad_m, quad_t, 0, M_PI/2, precisision, &exampleFunction, data, &steps);
	printf("Integrated Value: %f, steps: %d\n", sum, steps);
	return 0;

}
