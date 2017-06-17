/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 	Serie 8 - Approximation von Integralen Quadratur  	 */
/* ------------------------------------------------------------- */
/*	Autoren: 				 */
/*	Versionsnummer:						 */
/*---------------------------------------------------------------*/

  #include <stdlib.h>
  #include <assert.h>
  #include <math.h>
  #include "quadrature.h"

#ifndef M_PI
/* Copied from math.h  */
#define M_PI		3.14159265358979323846
#endif

#define EPS 1.0e-10
 /* ------------------------------------------------------------
 * Constructor and destructor
 * ------------------------------------------------------------ */

pquadrature
new_quadrature(int m){

  pquadrature quad;

  quad = (pquadrature) calloc(1, sizeof(quadrature));
  quad->xq = (double *) calloc(m+1, sizeof(double));
  quad->w = (double *) calloc(m+1, sizeof(double));
  quad->m = m;

  return quad;
}

void
del_quadrature(pquadrature quad){

  free(quad->xq);
  free(quad->w);
  free(quad);

}

pquadrature
setup_midpointrule(void){

pquadrature midpoint = new_quadrature(2);
return midpoint;
}

pquadrature
setup_trapezoidalrule(void){

pquadrature trapezoid = new_quadrature(1);
return trapezoid;
}

void
map_quadrature_points(pquadrature quad, double a, double b, double *x){

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

}

double
eval_quadrature(pquadrature quad, double a, double b, function f, void *data){

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

}

double
eval_composite_quadrature(pquadrature quad, double a, double b, int n, function f, void *data){

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

}
