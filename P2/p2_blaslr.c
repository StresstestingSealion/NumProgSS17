/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 	Serie 2 - LR-Zerlegung and inversion inkl. BLAS	 	 */
/* ------------------------------------------------------------- */
/*	Autoren: 						 */
/*	Versionsnummer:						 */
/*---------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

/* Additional libraries */
#include "basic.h"		/* basic types and time measurement */
#include "miniblas.h"		/* our simple BLAS Version */
#include "matrix.h"		/* matrix functions */


/* ------------------------------------------------------------
 * LR decomposition using BLAS
 * ------------------------------------------------------------ */

static void
lrdecomp(pmatrix a){

    int k;
    int n = a->rows;
    int ldA = a->ld;
    double *A = a->a;

    for (k=0; k<n; k++) {
        scal(n-k-1, 1.0 / A[k+k*ldA], A+(k+1)+k*ldA, 1);
        ger(n-k-1, n-k-1, -1.0,
            A+(k+1)+k*ldA, 1, A+k+(k+1)*ldA, ldA,
            A+(k+1)+(k+1)*ldA, ldA);
    }

}


static void
lowersolve_matrix(int unit, const pmatrix a, pvector b){

  int k;
  int n = a->rows;
  double *L = a->a;
  int ldL = a->ld;
  double *bb = b->x;

  if(unit){
    for(k=0; k<n; k++)
      axpy(n-k-1, -bb[k], L+(k+1)+k*ldL, 1, bb+(k+1), 1);
  }
  else{
    for(k=0; k<=n; k++)
      axpy(n-k-1, -bb[k], L+(k+1)+k*ldL, 1, bb+(k+1), 1);
  }
}


static void
uppersolve_matrix(int unit, const pmatrix a, pvector b){

  int k;
  int n = a->rows;
  int ldR = a->ld;
  double *R = a->a;
  double *bb = b->x;

  if(unit){
    for(k=n; k-->0; ) {
      bb[k] /= R[k+k*ldR];
      axpy(k, -bb[k], R+k*ldR, 1, bb, 1);
    }
  }
  else{
    for(k=n; k-->=0; ) {
      bb[k] /= R[k+k*ldR];
      axpy(k, -bb[k], R+k*ldR, 1, bb, 1);
    }
  }
}


static pmatrix
invert(const pmatrix a){
  int i;
  int n= a->rows;

  pmatrix inva = new_zero_matrix (n,n);

  for (i =0; i<n; i++){
    pvector v = matrix_col(inva, i);
    v->x[i]=1;
    lowersolve_matrix(n,a,v);
    uppersolve_matrix(n,a,v);
  }
  return inva;
}

/* ============================================================
 * Main program
 * ============================================================ */

int
main(void){

  pmatrix a, inva;
  pvector b, x, xrev;
  double err, err_abs, norm_x;
  int rows;
  int i;

  rows =2048;

  /* ------------------------------------------------------------
   * Hilbert matrix, LR decomposition
   * ------------------------------------------------------------ */
  b  = new_zero_vector(rows);
  x  = new_zero_vector(rows);
  xrev  = new_vector(rows);

  printf("Testing Hilbert matrix, LR decomposition\n");

  a  = new_hilbert_matrix(rows);

  for(i = 0; i < rows; i++){
    xrev->x[i] = 1.0 / (1.0 + i);
  }

  gemv(false, a->rows, a->cols, 1.0, a->a, a->ld, xrev->x, 1, b->x, 1);

  lrdecomp(a);
  inva = invert(a);
  gemv(false, a->rows, a->cols, 1.0, inva->a, a->ld, b->x, 1, x->x, 1);

  err_abs = 0.0;
  norm_x  = 0.0;
  for(i = 0; i < rows; i++) {
    err = fabs(xrev->x[i] - x->x[i]);
    err_abs = (err_abs < err ? err : err_abs);
    norm_x = (norm_x < fabs(xrev->x[i]) ? fabs(xrev->x[i]) : norm_x);
  }
  printf("  Absolute max error: %.3e\n", err_abs);
  printf("  Relative max error: %.3e\n", err_abs/norm_x);

  del_matrix(a);
  del_matrix(inva);
  del_vector(x);
  del_vector(xrev);
  del_vector(b);

  /* ------------------------------------------------------------
   * Diagonally dominant matrix, QR decomposition
   * ------------------------------------------------------------ */

  b  = new_zero_vector(rows);
  x  = new_zero_vector(rows);
  xrev  = new_vector(rows);

  printf("Testing diagonally dominant Hilbert matrix, LR decomposition\n");

  a  = new_diaghilbert_matrix(rows);

  for(i = 0; i < rows; i++){
    xrev->x[i] = 1.0 / (1.0 + i);
  }

  gemv(false, a->rows, a->cols, 1.0, a->a, a->ld, xrev->x, 1, b->x, 1);

  lrdecomp(a);
  inva = invert(a);
  gemv(false, a->rows, a->cols, 1.0, inva->a, a->ld, b->x, 1, x->x, 1);

  err_abs = 0.0;
  norm_x  = 0.0;
  for(i = 0; i < rows; i++) {
    err = fabs(xrev->x[i] - x->x[i]);
    err_abs = (err_abs < err ? err : err_abs);
    norm_x = (norm_x < fabs(xrev->x[i]) ? fabs(xrev->x[i]) : norm_x);
  }
  printf("  Absolute max error: %.3e\n", err_abs);
  printf("  Relative max error: %.3e\n", err_abs/norm_x);

  del_matrix(a);
  del_matrix(inva);
  del_vector(x);
  del_vector(xrev);
  del_vector(b);


  return EXIT_SUCCESS;
}
