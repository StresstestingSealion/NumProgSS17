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
tridiag_lrdecomp(ptridiag a){

int k;
int rows = a->rows;
pmatrix p = new_zero_matrix(rows, rows);


double *A = p->a;
int ldA = p->ld;
int n = p->cols;

convert_to_pmatrix(p, a);

for(k=0; k<n; k++){
  scal(n-k-1, 1.0 / A[k+k*ldA], A+(k+1)+*ldA, 1);
  ger (n-k-1, n-k-1, -1.0, A+(k+1)+k*ldA, 1, A+k+(k+1)*ldA)
}

convert_to_ptridiag(p, a);
del_matrix(p);

}

static void
tridiag_lrsolve(const ptridiag a, pvector b){

pmatrix p = new_zero_matrix(a->rows, a->rows);
convert_to_pmatrix(p, a);
lowersolve_matrix(true, p, b);
uppersolve_matrix(false, p, b);
del_matrix(p);

}

static void convert_to_pmatrix(pmatrixp, ptridiag a){

int k;
double *A = p->a;
int ldA = p->ld;

for(k=0; k<a->rows-1; k++){
  A[(k+1)+k*ldA]= a->l[k];
  A[k + k*ldA]=a->d[k];
  A[k+(k+1)*ldA]=a->u[k];
}
  k= a->rows-1;
  A[k+k*ldA]=a->d[k];
}

static void convert_to_ptridiag(pmatrix p, ptrdiag a){
  int k;
  double *A = p->a;
  int ldA = p->ld;

  for(k=0; k<a->rows-1; k++){
    A[(k+1)+*ldA]=a->l[k];
    A[k+k*ldA]=a->d[k];
    A[k+(k+1)*ldA]=a->u[k];
  }
    k= a->rows-1;
    A[k+k*ldA]=a->d[k];
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

tridiag_lrdecomp(a);


}

 /* Note:
   'shift' describs the parameter mu, used to compute (A - mu * I).
   */

static void
inverse_iteration_withshift(ptridiag a, pvector x, double shift, int steps, double *eigenvalue, double *res){

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

 /* Note:
   In this case 'shift' is only the start parameter mu.
   */

static void
rayleigh_iteration(ptridiag a, pvector x, double shift, int steps, double *eigenvalue, double *res){

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
