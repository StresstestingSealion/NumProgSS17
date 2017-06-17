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

double euler = 2.71828182845904523536;

int window;

/* ------------------------------------------------------------
* Example function
*-------------------------------------------------------------*/

double example_function(double x) {
	x = ((pow(5 * euler, 2 * x)) * cos(x)) / (pow(euler, M_PI) -2);
	return x;
}

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

static void
key(unsigned char key, int x, int y) {
    (void) x;
    (void) y;

    switch (key) {

        case '1':
            printf("did nothing at all.\n");
            break;
		}
}

int main(int argc, char **argv) {

		glutInit(&argc, argv);

		window = glutCreateWindow("Bullshit");
		glutPositionWindow(150, 100);
		glutReshapeWindow(500	, 500);
		glutReshapeFunc(reshape);
		glutKeyboardFunc(key);

		glutMainLoop();


		return 0;
}
