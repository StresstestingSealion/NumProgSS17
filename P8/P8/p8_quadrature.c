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

  /* ---------------------------------------------- */
  /*                                                */
  /* T T T T T     O O       D D           O O      */
  /*     T        O   O      D   D        O   O     */
  /*     T       O     O     D     D     O     O    */
  /*     T       O     O     D     D     O     O    */
  /*     T        O   O      D   D        O   O     */
  /*     T         O O       D D           O O      */
  /*                                                */
  /* ---------------------------------------------- */
