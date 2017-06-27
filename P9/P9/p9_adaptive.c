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

double exampleFunction(double x, void *data){
	return (5 * exp(2 * x) * cos(x)) / (exp(M_PI) - 2);
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
