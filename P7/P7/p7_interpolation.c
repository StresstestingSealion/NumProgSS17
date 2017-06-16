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
#include <GL/freeglut.h>
#include "interpolation.h"

#ifndef M_PI
/* Copied from math.h  */
#define M_PI		3.14159265358979323846
#endif

// some colors :)
typedef float color[3];
color COLOR_RED = {1.0, 0.0, 0.0};
color COLOR_GREEN = {0.0, 1.0, 0.0};
color COLOR_BLUE = {0.0, 0.0, 1.0};
color COLOR_BLACK = {0.0, 0.0, 0.0};
color COLOR_WHITE = {1.0, 1.0, 1.0};


/* ------------------------------------------------------------
* Global variable
*-------------------------------------------------------------*/

int w1, w2, w3;
pinterpolation equidistant, chebyshev;
double data[1] = {1.0};
int m = 10;
int resolution = 500;
int end_transition = 0;

double min_x = -10.0;
double max_x = 10.0;

double example_function_1(double x, void *data) {
    double lambda = ((double *) data)[0];
    return lambda * exp(-0.5 * x * x);
}

double example_function_2(double x, void *data) {
    (void) data;
    return 1 / (1 + x * x);
}

function func = example_function_1;

/* ------------------------------------------------------------
* GLUT functions
*-------------------------------------------------------------*/

static void
reshape(int width, int height) {

    glLoadIdentity();
    if (width > height) {
        glScalef((GLfloat) height / width, 1.0, 1.0);
    } else {
        glScalef(1.0, (GLfloat) width / height, 1.0);
    }

}

/**
 * print coordinate system
 */
static void print_coordinates() {

    glColor3d(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2d(-1.0, 0.0);
    glVertex2d(1.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2d(0.0, 1.0);
    glVertex2d(0.0, -1.0);
    glEnd();

}

/**
 * print given interpolation
 * @param n number of interpolations to print
 * @param interpolations array containing pointer to interpolations
 */
static void print_interpolation(pinterpolation inter, int res, color c) {

    glBegin(GL_LINE_STRIP);
    glColor3fv(c);
    for (int i = 0; i < res; i++) {
        double x = -1 + 2.0 / res * i;
        double y = eval_interpolation_polynomial(inter, min_x + (max_x - min_x) / resolution * i);
        glVertex2d(x, y);
    }
    glEnd();

}

/**
 * display given interpolation with equidistant points
 */
static void display_equidistant() {

    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, width, height);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    print_coordinates();
    print_interpolation(equidistant, resolution, COLOR_RED);

    glEnd();
    glFlush();

}

/**
 * display given interpolation with chebyshev points
 */
static void display_chebychev() {

    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, width, height);

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINE_STRIP);

    print_coordinates();
    print_interpolation(chebyshev, resolution, COLOR_GREEN);

    glEnd();
    glFlush();

}

/**
 * display both equidistant and chebyshev interpolation
 */
static void display_combined() {

    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, width, height);

    int mAequidistant = equidistant->m;
    int mChebychev = chebyshev->m;

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1.0, 1.0, 1.0, 1.0);

    print_coordinates();
    print_interpolation(equidistant, resolution, COLOR_RED);
    print_interpolation(chebyshev, resolution, COLOR_GREEN);

    glBegin(GL_LINES);
    glColor3fv(COLOR_RED);
    for (int i = 0; i < mAequidistant + 1; i++) {
        glVertex2d(2 / (max_x - min_x) * equidistant->xi[i], -0.06);
        glVertex2d(2 / (max_x - min_x) * equidistant->xi[i], 0.06);
    }
    glColor3fv(COLOR_GREEN);
    for (int i = 0; i < mChebychev + 1; i++) {
        glVertex2d(2 / (max_x - min_x) * chebyshev->xi[i], -0.06);
        glVertex2d(2 / (max_x - min_x) * chebyshev->xi[i], 0.06);
    }
    glEnd();
    glFlush();

}

void interpolate() {

    setup_aequidistant_interpolationpoints(equidistant, min_x, max_x);
    eval_interpolated_values(equidistant, func, data);
    newton_divided_differences(equidistant);

    setup_chebyshev_interpolationpoints(chebyshev, min_x, max_x);
    eval_interpolated_values(chebyshev, func, data);
    newton_divided_differences(chebyshev);

}

void refreshView() {

    glutSetWindow(w1);
    glutPostRedisplay();

    glutSetWindow(w2);
    glutPostRedisplay();

    glutSetWindow(w3);
    glutPostRedisplay();

}

void transition(int val) {

    if (!val || end_transition) return;

    int m = chebyshev->m;
    double *xEqui = equidistant->xi;
    double *xCheb = chebyshev->xi;

    int done = 0;
    for (int j = 0; j < m + 1; j++) {
        double distance = fabs(xCheb[j] - xEqui[j]);
        if (distance > 0.01) {
            if (xCheb[j] > xEqui[j]) {
                xCheb[j] -= 0.01;
            } else if (xCheb[j] < xEqui[j]) {
                xCheb[j] += 0.01;
            }
        } else done++;
        if (done >= m+1) val = 1 - val;
    }
    eval_interpolated_values(chebyshev, func, data);
    newton_divided_differences(chebyshev);
    display_combined();

    glutTimerFunc(5, transition, val);

}

/**
*	Use:
 *	- 1: switch to example function 1
 *	- 2: switch to example function 2
 *	- r: reset to standard values
 *	- w: increase lambda by 0.05
 *	- s: decrease lambda by 0.05
 *	- q: increase m by 1
 *	- a: decrease m by 1
 *	- space: transition from chebyshev to equidistant
 *	- escape: exit application
*/
static void
key(unsigned char key, int x, int y) {
    (void) x;
    (void) y;

    switch (key) {

        case '1':
            func = example_function_1;
            data[0] = 1.0;
            interpolate();
            refreshView();
            printf("switched to example function 1.\n");
            break;
        case '2':
            func = example_function_2;
            interpolate();
            refreshView();
            printf("switched to example function 2.\n");
        case 'r':
            data[0] = 1.0;
            del_interpolation(equidistant);
            del_interpolation(chebyshev);
            equidistant = new_interpolation(m);
            chebyshev = new_interpolation(m);
            interpolate();
            end_transition = 1;
            refreshView();
            break;
        case 'w':
            data[0] += 0.05;
            interpolate();
            refreshView();
            printf("increased lambda by 0.05 and is now %f.\n", data[0]);
            break;
        case 's':
            data[0] -= 0.05;
            interpolate();
            refreshView();
            printf("decreased lambda by 0.05 and is now %f.\n", data[0]);
            break;
        case 'q':
            m += 1;
            del_interpolation(equidistant);
            del_interpolation(chebyshev);
            equidistant = new_interpolation(m);
            chebyshev = new_interpolation(m);
            interpolate();
            refreshView();
            printf("increased m by 1 and is now %d.\n", m);
            break;
        case 'a':
            m = m <= 0 ? 0 : m - 1;
            del_interpolation(equidistant);
            del_interpolation(chebyshev);
            equidistant = new_interpolation(m);
            chebyshev = new_interpolation(m);
            interpolate();
            refreshView();
            printf("decreased m by 1 and is now %d.\n", m);
            break;
        case 32:
            end_transition = 0;
            transition(1);
            break;
        case 27:
            exit(0);
        default :
            break;
    }
}

int main(int argc, char **argv) {

    equidistant = new_interpolation(m);
    chebyshev = new_interpolation(m);
    interpolate();

    glutInit(&argc, argv);

    w1 = glutCreateWindow("Equidistant");
    glutPositionWindow(150, 100);
    glutReshapeWindow(resolution, resolution);
    glutDisplayFunc(display_equidistant);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);

    w2 = glutCreateWindow("Chebyshev");
    glutPositionWindow(1250, 100);
    glutReshapeWindow(resolution, resolution);
    glutDisplayFunc(display_chebychev);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);

    w3 = glutCreateWindow("Comparision");
    glutPositionWindow(700, 100);
    glutReshapeWindow(resolution, resolution);
    glutDisplayFunc(display_combined);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);

    glutMainLoop();

    del_interpolation(equidistant);
    del_interpolation(chebyshev);

    return 0;
}
