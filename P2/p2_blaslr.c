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


static void
lowersolve_matrix(int unit, const pmatrix a, pvector b){

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


static void
uppersolve_matrix(int unit, const pmatrix a, pvector b){

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


static pmatrix
invert(const pmatrix a){

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

  pmatrix a, inva;
  pvector b, x, xrev;
  double err, err_abs, norm_x;
  int rows;
  int i;
  
  rows = 12;
  
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
