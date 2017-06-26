/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 	Serie 8 - Approximation von Integralen (Quadratur) 	 */
/* ------------------------------------------------------------- */
/*	Autoren: 						 */
/*	Versionsnummer:						 */
/*---------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <GL/freeglut.h>
#include <GL/glut.h>

#include "quadrature.h"

#ifndef M_PI
/* Copied from math.h  */
#define M_PI		3.14159265358979323846
#endif


/* ------------------------------------------------------------
* Global variable
*-------------------------------------------------------------*/


int window;
int window_size_x = 500;
int window_size_y = 500;
int interpolationPoints = 1;

pquadrature quad;

double data[2];
double x_max = M_PI / 2;
double precisision = 0.000001;

/* ------------------------------------------------------------
* Example function
*-------------------------------------------------------------*/


double exampleFunction(double x, void *data) {
    return (5 * exp(2 * x) * cos(x)) / (exp(M_PI) - 2);
}

/* ------------------------------------------------------------
* GLUT functions
*-------------------------------------------------------------*/

static void reshape(int width, int height) {

    glViewport(0, 0, width, height);
    glLoadIdentity();

    if (width > height) {
        glScalef((double) height / width, 1.0, 1.0);
    } else {
        glScalef(1.0, (double) width / height, 1.0);
    }
}

static void createCoordinateSystem() {

    glColor3d(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-1.0, 0.0);
    glVertex2f(1.0, 0.0);

    glVertex2f(0.0, 1.0);
    glVertex2f(0.0, -1.0);

    for (int i = 0; i <= 10; i++) {

        glVertex2f(1.0 / 10 * i, -0.05);
        glVertex2f(1.0 / 10 * i, 0.05);
        glVertex2f(-1.0 / 10 * i, -0.05);
        glVertex2f(-1.0 / 10 * i, 0.05);
        glVertex2f(-0.05, 1.0 / 10 * i);
        glVertex2f(0.05, 1.0 / 10 * i);
        glVertex2f(-0.05, -1.0 / 10 * i);
        glVertex2f(0.05, -1.0 / 10 * i);
    }

    glEnd();

}

static void display() {

    double x, x1, x2, sum;
    int i;
    double a = 0;
    double b = M_PI / 2;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    coordinates();

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glPointSize(2.0);
    glBegin(GL_LINE_STRIP);

    for (x = 0.0; x <= M_PI / 2; x += precisision) {
        glColor3f(0.8, 0.0, 0.0);
        glVertex2f(x / 2, exampleFunction(x, data));
    }

    glEnd();
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0, 0.8, 0.0);

    for (i = 0; i < interpolationPoints; i++) {
        x1 = a + (b - a) / interpolationPoints * i;
        x2 = a + (b - a) / interpolationPoints * (i + 1);
        glVertex2f(x1 / 2, 0);

        if (quad->m == 0) {
            glVertex2f(x1 / 2, exampleFunction((x1 + x2) / 2, data));
            glVertex2f(x2 / 2, exampleFunction((x1 + x2) / 2, data));
        } else {
            glVertex2f(x1 / 2, exampleFunction(x1, data));
            glVertex2f(x2 / 2, exampleFunction(x2, data));
        }
        glVertex2f(x2 / 2, 0);
    }
    glEnd();

    sum = eval_composite_quadrature(quad, 0, M_PI / 2, interpolationPoints, &exampleFunction, data);
    printf("Integrated area: %f\n", sum);

    glFlush();

}

/* Controls: 
	q: add one interpolation point
	a: remove one interpolation point
	1: toggle midpoint rule
	2: toggle trapezoid rule
*/
static void
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
}

int main(int argc, char **argv) {

    data[0] = 0.0;
    data[1] = 1.0;

    quad = setup_midpointrule();

    glutInit(&argc, argv);

    window = glutCreateWindow("Quadrature");
    glutPositionWindow(150, 150);
    glutReshapeWindow(window_size_x, window_size_y);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);

    glutMainLoop();
    return 0;
}
