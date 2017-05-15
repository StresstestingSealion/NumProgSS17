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
 lowersolve_matrix(int unit, const pmatrix a, pvector b){ //copied from P2

   int k;
   int n = a->rows;
   double *L = a->a;
   int ldL = a->ld;
   double *bb = b->x;

   if(unit != 0){
     for(k=0; k<n; k++)
       axpy(n-k-1, -bb[k], L+(k+1)+k*ldL, 1, bb+(k+1), 1);
   }
   else{
     for(k=0; k<=n; k++)
       axpy(n-k-1, -bb[k], L+(k+1)+k*ldL, 1, bb+(k+1), 1);
   }
 }


 static void
 uppersolve_matrix(int unit, const pmatrix a, pvector b){ //copied from P2

   int k;
   int n = a->rows;
   int ldR = a->ld;
   double *R = a->a;
   double *bb = b->x;

   if(unit != 0){
     for(k=n; k-->0; ) {
       bb[k] /= R[k+k*ldR];
       axpy(k, -bb[k], R+k*ldR, 1, bb, 1);
     }
   }
   else{
     for(k=n; k-->0; ) {
       bb[k] /= R[k+k*ldR];
       axpy(k, -bb[k], R+k*ldR, 1, bb, 1);
     }
   }
 }
 static void convert_to_pmatrix(pmatrix p, ptridiag a){

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

 static void convert_to_ptridiag(pmatrix p, ptridiag a){
   int k;
   double *A = p->a;
   int ldA = p->ld;

   for(k=0; k<a->rows-1; k++){
     A[(k+1)*ldA]=a->l[k];
     A[k+k*ldA]=a->d[k];
     A[k+(k+1)*ldA]=a->u[k];
   }
     k= a->rows-1;
     A[k+k*ldA]=a->d[k];
 }

static void
tridiag_lrdecomp(ptridiag a){

int k;
int rows = a->rows;
pmatrix p = new_zero_matrix(rows, rows);

double *A = p->a;
int ldA = p->ld;
int n = p->cols;

//copy values of a into p so we can use our previous lr functions
convert_to_pmatrix(p, a);

for(k=0; k<n; k++){ //decompose matrix
  scal(n-k-1, 1.0 / A[k+k*ldA], A+(k+1)*ldA, 1);
  ger (n-k-1, n-k-1, -1.0,
      A+(k+1)+k*ldA, 1, A+k+(k+1)*ldA, ldA, A+(k+1)+(k+1)*ldA, ldA);
}

//revert solution into a ptridiag matrix

convert_to_ptridiag(p, a);

}

static void
tridiag_lrsolve(const ptridiag a, pvector b){

pmatrix p = new_zero_matrix(a->rows, a->rows); //use p to hold a's values so we can use our previous solve functions

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

lowersolve_matrix(true, p, b);
uppersolve_matrix(false, p, b);
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

//inverse_iteration_withshift(a, x, 0.0, steps, *eigenvalue, *res);

}

 /* Note:
   'shift' describs the parameter mu, used to compute (A - mu * I).
   */

static void
inverse_iteration_withshift(ptridiag a, pvector x, double shift, int steps, double *eigenvalue, double *res){

ptridiag y = new_tridiag(a->rows);
y = a;
mvm_tridiag(0, 0.0, y, x, x);

tridiag_lrdecomp(a);
tridiag_lrsolve(a, x);
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
