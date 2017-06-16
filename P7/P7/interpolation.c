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
#include <stdio.h>

#ifndef M_PI
/* Copied from math.h  */
#define M_PI		3.14159265358979323846
#endif

/* ------------------------------------------------------------
* Constructor and destructor
* ------------------------------------------------------------ */

pinterpolation
new_interpolation(int m) {

    pinterpolation inter;
    inter = (pinterpolation) calloc(1, sizeof(interpolation));
    inter->xi = (double *) calloc((size_t) (m + 1), sizeof(double));
    inter->f = (double *) calloc((size_t) (m + 1), sizeof(double));
    inter->d = (double *) calloc((size_t) (m + 1), sizeof(double));
    inter->m = m;
    return inter;

}

void
del_interpolation(pinterpolation inter) {

    free(inter->xi);
    free(inter->f);
    free(inter->d);
    free(inter);

}

/* Chebyshev points [a,b] */
void
setup_chebyshev_interpolationpoints(pinterpolation inter, double a, double b) {

    int m = inter->m;
    double *x = inter->xi;
    for (int i = 0; i < m + 1; i++) {
        x[i] = a + (b - a) / 2 * (cos((2 * i + 1) / (2.0 * (m + 1)) * M_PI) + 1);
    }

}

void
setup_aequidistant_interpolationpoints(pinterpolation inter, double a, double b) {

    int m = inter->m;
    for (int i = 0; i < m + 1; i++) {
        inter->xi[i] = a + (b - a) / m * i;
    }

}

void
eval_interpolated_values(pinterpolation inter, function f, void *data) {

    int m = inter->m;
    for (int i = 0; i < m + 1; i++) {
        inter->f[i] = f(inter->xi[i], data);
    }

}

/* Evaluate Newton divided differences */
void
newton_divided_differences(pinterpolation inter) {

    int m = inter->m;
    double *t = (double *) malloc((m + 1) * sizeof(double));
    for (int i = 0; i < m + 1; i++) {
        t[i] = inter->f[i];
        for (int j = i - 1; j >= 0; j--) {
            t[j] = (t[j + 1] - t[j]) / (inter->xi[i] - inter->xi[j]);
        }
        inter->d[i] = t[0];
    }

}

/* Horner schema */
double
eval_interpolation_polynomial(const pinterpolation inter, double x) {

    double p;
    int m = inter->m;
    p = inter->d[m];

    for (int l = 1; l < m + 1; l++) {
        p = inter->d[m - l] + (x - inter->xi[m - l]) * p;

    }
    return p;

}
