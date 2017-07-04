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
	pquadrature quad = new_quadrature(0);

	quad->xq[0] = 0;
	quad->w[0] = 2;

	return quad;
}

pquadrature
setup_trapezoidalrule(void){
	pquadrature quad = new_quadrature(1);

	quad->xq[0] = -1;
	quad->xq[1] = 1;

	quad->w[0] = 1;
	quad->w[1] = 1;

	return quad;
}

void
map_quadrature_points(pquadrature quad, double a, double b, double *x){
	int i;
	int m = quad->m;

	for(i = 0; i <= m; i++)
		x[i] = (b + a) / 2 + (b - a) / 2 * quad->xq[i];
}

double calculate_relative_error(double midpointquad, double trapezoidquad){
	if (midpointquad == 0.0)
		return 0.0;
	if(midpointquad < trapezoidquad){
		return (trapezoidquad - midpointquad) / midpointquad;
  }
	else{
		return (midpointquad - trapezoidquad) / midpointquad;
  }
}



double
eval_quadrature(pquadrature quad, double a, double b, function f, void *data){
	double sum = 0.0;
	int m = quad->m;
	int i;

	double* x = malloc((m + 1) * sizeof(double));

	map_quadrature_points(quad, a, b, x);

	for(i = 0; i <= m; i++){
		sum += quad->w[i] * f(x[i], data);
  }

	sum *= (b - a) / 2;
	free(x);
	return sum;
}

double
eval_composite_quadrature(pquadrature midpointquad, pquadrature trapezoidquad, double a, double b, double epsilon, function f, void *data, int *steps){
	double sum = 0.0;

	double m = 0.0;
	double t = 0.0;

		m = eval_quadrature(midpointquad, a, b, f, data);
		t = eval_quadrature(trapezoidquad, a, b, f, data);
		if(ABS(t-m) <= epsilon * ABS(m)){
			sum += eval_composite_quadrature(midpointquad, trapezoidquad, a, b - (b - a) / 2, epsilon, f, data, steps);
			sum += eval_composite_quadrature(midpointquad, trapezoidquad, a + (b - a) / 2, b, epsilon, f, data, steps);
		}
		else{
			sum += (m + t) / 2;
    }

		(*steps)++;

		return sum;
}
