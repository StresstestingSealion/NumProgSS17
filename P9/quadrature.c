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
new_quadrature(int m) {

    pquadrature quad;

    quad = (pquadrature) calloc(1, sizeof(quadrature));
    quad->xq = (double *) calloc(m + 1, sizeof(double));
    quad->w = (double *) calloc(m + 1, sizeof(double));
    quad->m = m;

    return quad;
}

void
del_quadrature(pquadrature quad) {

    free(quad->xq);
    free(quad->w);
    free(quad);

}

pquadrature
setup_midpointrule(void) {

<<<<<<< HEAD
	pquadrature midpoint = new_quadrature(0);

	midpoint->xq[0] = 0;
	midpoint->w[0] = 2;

	return midpoint;
=======
    pquadrature midpoint = new_quadrature(0);

    midpoint->xq[0] = 0;
    midpoint->w[0] = 2;

    return midpoint;
>>>>>>> master
}

pquadrature
setup_trapezoidalrule(void) {

<<<<<<< HEAD
	pquadrature trapezoid = new_quadrature(1);

	trapezoid->xq[0] = -1;
	trapezoid->xq[1] = 1;
	trapezoid->w[0] = 1;
	trapezoid->w[1] = 1;

	return trapezoid;
=======
    pquadrature trapezoid = new_quadrature(1);

    trapezoid->xq[0] = -1;
    trapezoid->xq[1] = 1;
    trapezoid->w[0] = 1;
    trapezoid->w[1] = 1;

    return trapezoid;
>>>>>>> master
}

void
map_quadrature_points(pquadrature quad, double a, double b, double *x) {

    int i;
    int m = quad->m;

<<<<<<< HEAD
for(i = 0; i <= m; i++){
	x[i] = (b + a) / 2 + (((b - a) / 2) * quad->xq[i]);
	}
=======
    for (i = 0; i <= m; i++) {
        x[i] = (b + a) / 2 + (b - a) / 2 * quad->xq[i];
    }
>>>>>>> master
}

double
eval_quadrature(pquadrature quad, double a, double b, function f, void *data) {

<<<<<<< HEAD
	double sum = 0.0;
	int m = quad->m;
	int i;
	double* x = malloc((m+1) * sizeof(double));
	map_quadrature_points(quad, a, b, x);

	for(i = 0; i <= m; i++){
		sum += quad->w[i] * f(x[i], data);
		}

	free(x);

	sum *= ((b - a) / 2);
	return sum;
}


bool is_accurate_enough(pquadrature midpointquad, pquadrature trapezoidquad, int recs, double a, double b, function f, void *data){

double midpointarea = eval_quadrature(midpointquad, a, b, f, *data);
double trapezoidarea = eval_quadrature(trapezoidquad, a, b, f, *data);

	if (recs < 20 && ((midpointarea - trapezoidarea) / trapezoidarea) >= epsilon){
		
	}
=======
    double sum = 0.0;
    int m = quad->m;
    int i;
    double *x = malloc((m + 1) * sizeof(double));
    map_quadrature_points(quad, a, b, x);

    for (i = 0; i <= m; i++) {
        sum += quad->w[i] * f(x[i], data);
    }

    free(x);

    sum *= ((b - a) / 2);
    return sum;
>>>>>>> master
}

double
eval_composite_quadrature(pquadrature quad, double a, double b, int n, function f, void *data) {

<<<<<<< HEAD
	int i;
	double sum = 0.0;
	double distance = (b - a) / n;

	for(i = 0; i < n; i++){
		sum += eval_quadrature(quad, a + distance * i, a + distance * (i + 1), f, data);
		}

	return sum;
=======
    int i;
    double sum = 0.0;
    double distance = (b - a) / n;

    for (i = 0; i < n; i++) {
        sum += eval_quadrature(quad, a + distance * i, a + distance * (i + 1), f, data);
    }

    return sum;
>>>>>>> master
}
