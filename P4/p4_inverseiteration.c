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

    for (i = 1; i < n - 1; i++) {
        l[i - 1] /= d[i - 1];
        d[i] -= l[i - 1] * u[i - 1];
    }

    l[n - 2] /= d[n - 2];
    d[n - 1] -= l[n - 2] * u[n - 2];

}

static void
tridiag_lrsolve(const ptridiag a, pvector b) {

    double *d = a->d;
    double *l = a->l;
    double *u = a->u;
    double *bb = b->x;
    int n = a->rows;
    int i, j;

    // lowersolve
    for (i = 1; i < n; i++) {
        bb[i] -= l[i - 1] * bb[i - 1];
    }

    // uppersolve
    bb[n - 1] /= d[n - 1];
    for (j = n - 1; j-- > 0;) {
        bb[j] = (bb[j] - u[j] * bb[j + 1]) / d[j];
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
inverse_iteration(ptridiag a, pvector x, int steps, double *eigenvalue, double *res) {

    int i;
    double norm;
    int n = a->rows;
    double *xx = x->x;

    ptridiag lr = clone_tridiag(a);
    tridiag_lrdecomp(lr);

    pvector y = new_zero_vector(n);
    double *yx = y->x;

    for (i = 0; i < steps; i++) {

        tridiag_lrsolve(lr, x);
        norm = nrm2(n, x->x, 1);
        scal(n, 1 / norm, xx, 1);

    }

    // y = Ax
    clear_vector(y);
    mvm_tridiag(0, 1, a, x, y);

    *eigenvalue = dot(n, xx, 1, yx, 1) / dot(n, xx, 1, xx, 1);
    axpy(n, -*eigenvalue, xx, 1, yx, 1);
    *res = nrm2(n, yx, 1);

    // cleanup
    del_tridiag(lr);
    del_vector(y);

}

/* Note:
  'shift' describs the parameter mu, used to compute (A - mu * I).
  */

static void
inverse_iteration_withshift(ptridiag a, pvector x, double shift, int steps, double *eigenvalue, double *res) {

    int i;
    double norm;
    int n = a->rows;
    double *xx = x->x;

    ptridiag lr = clone_tridiag(a);
    for (i = 0; i < n; i++) {
        lr->d[i] -= shift;
    }
    tridiag_lrdecomp(lr);

    pvector y = new_zero_vector(n);
    double *yx = y->x;


    for (i = 0; i < steps; i++) {

        tridiag_lrsolve(lr, x);
        norm = nrm2(n, x->x, 1);
        scal(n, 1 / norm, xx, 1);

    }

    // y = Ax
    clear_vector(y);
    mvm_tridiag(0, 1, a, x, y);

    *eigenvalue = dot(n, xx, 1, yx, 1) / dot(n, xx, 1, xx, 1);
    axpy(n, -*eigenvalue, xx, 1, yx, 1);
    *res = nrm2(n, yx, 1);

    // cleanup
    del_tridiag(lr);
    del_vector(y);

}

/* Note:
  In this case 'shift' is only the start parameter mu.
  */

static void
rayleigh_iteration(ptridiag a, pvector x, double shift, int steps, double *eigenvalue, double *res) {

    int i;
    double norm, lambda;
    int n = a->rows;
    double *xx = x->x;

    ptridiag lr = clone_tridiag(a);
    for (i = 0; i < n; i++) {
        lr->d[i] -= shift;
    }
    tridiag_lrdecomp(lr);

    pvector y = new_zero_vector(n);
    double *yx = y->x;


    for (i = 0; i < steps; i++) {

        tridiag_lrsolve(lr, x);
        norm = nrm2(n, x->x, 1);
        scal(n, 1 / norm, xx, 1);

        // y = Ax
        clear_vector(y);
        mvm_tridiag(0, 1, a, x, y);


        lambda = dot(n, xx, 1, yx, 1) / dot(n, xx, 1, xx, 1);
        copy_tridiag(a, lr);
        for (i = 0; i < n; i++) {
            lr->d[i] -= lambda;
        }
        tridiag_lrdecomp(lr);

    }


    *eigenvalue = dot(n, xx, 1, yx, 1) / dot(n, xx, 1, xx, 1);
    axpy(n, -*eigenvalue, xx, 1, yx, 1);
    *res = nrm2(n, yx, 1);

    // cleanup
    del_tridiag(lr);
    del_vector(y);

}

/* ============================================================
 * Main program
 * ============================================================ */

int
main(void) {

    tridiag *a;
    vector *x;
    double norm, lambda, mu;
    int n;
    time_t t;

    n = 100;

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
