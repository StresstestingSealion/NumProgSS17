/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 	Serie 4 - Eigenwertbestimmung (Inverse Iteration) 	 */
/* ------------------------------------------------------------- */
/*	Autoren:				 		 */
/*	Versionsnummer:						 */
/*---------------------------------------------------------------*/

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "miniblas.h"
#include <time.h>


/* ------------------------------------------------------------
 * LR decomposition and solve
 * ------------------------------------------------------------ */
static void
tridiag_lrdecomp(ptridiag a) {

    /*
     * Tridiagnonalmatrix mit "Informatik-Variablen"
     *
     * d0 u0 00 00
     * l0 d1 u1 00
     * 00 l1 d2 u2
     * 00 00 l2 d3
     *
     * wird zerlegt in zwei Matritzen
     *
     * 01 00 00 00    b0 c0 00 00
     * a0 01 00 00    00 b1 c1 00
     * 00 a1 01 00    00 00 b2 c2
     * 00 00 a2 01    00 00 00 b3
     *
     */

    double *d = a->d;
    double *l = a->l;
    double *u = a->u;
    int n = a->rows;
    int i;

    for (i = 1; i < n-1; i++) {
        l[i-1] /= d[i-1];
        d[i] -= l[i-1] * u[i-1];
    }

    l[n-2] /= d[n-2];
    d[n-1] -= l[n-2] * u[n-2];

}

static void
tridiag_lrsolve(const ptridiag a, pvector b) {

    double *d = a->d;
    double *l = a->l;
    double *u = a->u;
    double *bb = b->x;
    int n = a->rows;
    int i,j;

    // lowersolve
    for (i = 1; i < n; i++) {
        bb[i] -= l[i-1] * bb[i-1];
    }

    // uppersolve
    bb[n-1] /= d[n-1];
    for (j = n-1; j-- > 0; ) {
        bb[j] = (bb[j] - u[j] * bb[j+1]) / d[j];
    }

}


/* ------------------------------------------------------------
 * inverse iteration
 * ------------------------------------------------------------ */

/* Note:
   'steps' is used to determine the maximum number
   of steps, which should be used to the iteration step.
   'eigenvalue' will be overwritten by the computed
    eigenvalue.
   'res' is used to determine the error, measured in the
    euclidean norm.
   */

static void
inverse_iteration(ptridiag a, pvector x, int steps, double *eigenvalue, double *res){

    int i,j;
    double lambda = 0, norm;
    int n = a->rows;
    double *xx = x->x;

    // save original vector
    pvector x0 = new_zero_vector(n);
    for (i = 0; i < n; i++) {
        x0->x[i] = xx[i];
    }

    pvector y = new_zero_vector(n);
    double *yx = y->x;

    // calculate y = Ax
    yx[0] = (a->d[0] * xx[0] + a->u[0] * xx[1]);
    for (i = 1; i < n-1; i++) {
        yx[i] = a->l[i-1] * xx[i-1] + a->d[i] * xx[i] + a->u[i] * xx[i+1];
    }
    yx[n-1] = a->d[n-1] * xx[n-1] + a->l[n-2] * xx[n-2];

    // calculate lambda
    lambda = dot(n, xx, 1, yx, 1) / dot(n, xx, 1, xx, 1);

    for (i = 0; i < steps; i++) {

        norm = nrm2(n, x->x, 1);
        scal(n, 1 / norm, yx, 1);

        for (j = 0; j < n; j++) {
            xx[j] = yx[j];
        }

        // calculate y = Ax
        yx[0] = (a->d[0] * xx[0] + a->u[0] * xx[1]);
        for (i = 1; i < n-1; i++) {
            yx[i] = a->l[i-1] * xx[i-1] + a->d[i] * xx[i] + a->u[i] * xx[i+1];
        }
        yx[n-1] = a->d[n-1] * xx[n-1] + a->l[n-2] * xx[n-2];

        // calculate lambda
        lambda = dot(n, xx, 1, yx, 1) / dot(n, xx, 1, xx, 1);

    }

    *eigenvalue = lambda;
    *res = norm2_diff_vector(x0, x);

    // cleanup
    del_vector(y);
    del_vector(x0);


}

 /* Note:
   'shift' describs the parameter mu, used to compute (A - mu * I).
   */

static void
inverse_iteration_withshift(ptridiag a, pvector x, double shift, int steps, double *eigenvalue, double *res){

     int i;
     double lambda, norm;
     int n = a->rows;
     double *xx = x->x;

     // save original vector
     pvector x0 = new_zero_vector(n);
     for (i = 0; i < n; i++) {
         x0->x[i] = xx[i];
     }

     pvector y = new_zero_vector(n);
     double *yx = y->x;

     // save  A - shift * ID and decomp
     ptridiag B = new_tridiag(n);
     for(i = 0; i < n-1; i++) {
         B->d[i] = a->d[i] - shift;
         B->u[i] = a->u[i];
         B->l[i] = a->l[i];
     }
     B->d[n-1] = a->d[n-1] - shift;
     tridiag_lrdecomp(B);

     // calculate y = Ax
     yx[0] = (a->d[0] * xx[0] + a->u[0] * xx[1]);
     for (i = 1; i < n-1; i++) {
         yx[i] = a->l[i-1] * xx[i-1] + a->d[i] * xx[i] + a->u[i] * xx[i+1];
     }
     yx[n-1] = a->d[n-1] * xx[n-1] + a->l[n-2] * xx[n-2];

     // calculate lambda
     lambda = dot(n, xx, 1, yx, 1) / dot(n, xx, 1, xx, 1);

     for (i = 0; i < steps; i++) {

         norm = nrm2(n, x->x, 1);
         tridiag_lrsolve(B, x);
         scal(n, 1 / norm, x->x, 1);

         // calculate y = Ax
         yx[0] = (a->d[0] * xx[0] + a->u[0] * xx[1]);
         for (i = 1; i < n-1; i++) {
             yx[i] = a->l[i-1] * xx[i-1] + a->d[i] * xx[i] + a->u[i] * xx[i+1];
         }
         yx[n-1] = a->d[n-1] * xx[n-1] + a->l[n-2] * xx[n-2];

         // calculate lambda
         lambda = dot(n, xx, 1, yx, 1) / dot(n, xx, 1, xx, 1);

     }

     *eigenvalue = lambda;
     *res = norm2_diff_vector(x0, x);

     // cleanup
     del_tridiag(B);
     del_vector(y);
     del_vector(x0);

}

 /* Note:
   In this case 'shift' is only the start parameter mu.
   */

static void
rayleigh_iteration(ptridiag a, pvector x, double shift, int steps, double *eigenvalue, double *res){

     int i;
     double lambda = 0, norm;
     int n = a->rows;
     double *xx = x->x;
     double rayleigh;

     // save original vector
     pvector x0 = new_zero_vector(n);
     for (i = 0; i < n; i++) {
         x0->x[i] = xx[i];
     }

     pvector y = new_zero_vector(n);
     double *yx = y->x;

     ptridiag B = new_tridiag(n);

     // calculate y = Ax
     yx[0] = (a->d[0] * xx[0] + a->u[0] * xx[1]);
     for (i = 1; i < n-1; i++) {
         yx[i] = a->l[i-1] * xx[i-1] + a->d[i] * xx[i] + a->u[i] * xx[i+1];
     }
     yx[n-1] = a->d[n-1] * xx[n-1] + a->l[n-2] * xx[n-2];

     // calculate lambda
     lambda = dot(n, xx, 1, yx, 1) / dot(n, xx, 1, xx, 1);

     for (i = 0; i < steps; i++) {

         if (i == 0) {
             rayleigh = shift;
         } else {
             rayleigh = lambda;
         }

         // restore A - shift * ID and decomp
         for(i = 0; i < n; i++) {
             B->d[i] = a->d[i] - rayleigh;
         }
         B->u = a->u;
         B->l = a->l;
         tridiag_lrdecomp(B);

         norm = nrm2(n, x->x, 1);
         tridiag_lrsolve(B, x);
         scal(n, 1 / norm, x->x, 1);

         // calculate y = Ax
         yx[0] = (a->d[0] * xx[0] + a->u[0] * xx[1]);
         for (i = 1; i < n-1; i++) {
             yx[i] = a->l[i-1] * xx[i-1] + a->d[i] * xx[i] + a->u[i] * xx[i+1];
         }
         yx[n-1] = a->d[n-1] * xx[n-1] + a->l[n-2] * xx[n-2];

         // calculate lambda
         lambda = dot(n, xx, 1, yx, 1) / dot(n, xx, 1, xx, 1);

     }

     *eigenvalue = lambda;
     *res = norm2_diff_vector(x0, x);

     // cleanup
     del_tridiag(B);
     del_vector(y);
     del_vector(x0);

}

/* ============================================================
 * Main program
 * ============================================================ */

int
main(void){

  tridiag *a;
  vector *x;
  double norm, lambda, mu;
  int n;
  time_t t;

  n = 1000;

  time(&t);
  srand((unsigned int) t);

  a = new_threepointstencil(n);
  x = new_vector(n);
  random_vector(x);

  /* ------------------------------------------------------------
   * Inverse iteration
   * ------------------------------------------------------------ */

  printf("Inverse iteration\n");
  lambda = 0.0;
  norm = 0.0;
  inverse_iteration(a, x, 10, &lambda, &norm);

  printf("  Eigenvalue %g\n"
	 "  Residual norm %e\n",
	 lambda, norm);

 /* ------------------------------------------------------------
   * Inverse iteration with shift
   * ------------------------------------------------------------ */
  random_vector(x);

  printf("Inverse iteration with shift\n");
  lambda = 0.0;
  norm = 0.0;
  mu = 7.0;
  inverse_iteration_withshift(a, x, mu, 10, &lambda, &norm);

  printf("  Eigenvalue %g\n"
	 "  Residual norm %e\n",
	 lambda, norm);

  /* ------------------------------------------------------------
   * Rayleigh iteration
   * ------------------------------------------------------------ */

  printf("Rayleigh iteration\n");

  random_vector(x);
  lambda = 0.0;
  norm = 0.0;
  mu = 7.0;
  rayleigh_iteration(a, x, mu, 10, &lambda, &norm);

  printf("  Eigenvalue %g\n"
	 "  Residual norm %e\n",
	 lambda, norm);

  del_vector(x);
  del_tridiag(a);


  return EXIT_SUCCESS;
}
