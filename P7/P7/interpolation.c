/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 	Serie 7 - Approximation von Funktionen Interpolation  	 */
/* ------------------------------------------------------------- */
/*	Autoren: 						 */
/*	Versionsnummer:						 */
/*---------------------------------------------------------------*/

  #include <stdlib.h>
  #include <assert.h>		
  #include <math.h>
  #include "interpolation.h"

#ifndef M_PI
/* Copied from math.h  */
#define M_PI		3.14159265358979323846
#endif		
  
 /* ------------------------------------------------------------
 * Constructor and destructor
 * ------------------------------------------------------------ */

pinterpolation
new_interpolation(int m){

  int i;
  pinterpolation inter;

  inter = (pinterpolation) calloc(1, sizeof(interpolation));
  inter->xi = (double *) calloc(m+1, sizeof(double));
  inter->f = (double *) calloc(m+1, sizeof(double));
  inter->d = (double *) calloc(m+1, sizeof(double));
  inter->m = m;
  
  for(i = 0; i < m+1; i++){
    inter->d[i] = 0.0;
  }

  return inter;
}

void
del_interpolation(pinterpolation inter){

  free(inter->xi);
  free(inter->f);
  free(inter->d);
  free(inter);

}

/* Chebyshev points [a,b] */

void
setup_chebyshev_interpolationpoints(pinterpolation inter, double a, double b){

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

void 
setup_aequidistant_interpolationpoints(pinterpolation inter, double a, double b){

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

void
eval_interpolated_values(pinterpolation inter, function f, void *data){
	
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

/* Evaluate Newton divided differences */

void
newton_divided_differences(pinterpolation inter){

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

/* Horner schema */

double
eval_interpolation_polynomial(const pinterpolation inter, double x){

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
