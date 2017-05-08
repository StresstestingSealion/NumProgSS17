/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 	Serie 3 - Block-LR-Zerlegung und Vergleich	 	 */
/* ------------------------------------------------------------- */
/*	Autoren: 				 		 */
/*	Versionsnummer:						 */
/*---------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

/* Additional libraries */
#include "basic.h"		/* basic types and time measurement */
#include "miniblas.h"		/* our simple BLAS version */
#include "matrix.h"		/* matrix functions */


/* older versions e.g. used in comparsion*/
/* ************************************************* */

/** Inplace LR-decomposition without pivot search */
void
lr_decomp(pmatrix a){

	int i, j, k;
	int n = a->rows;
	double *aa = a->a;
        int ld = a->ld;


    for (k = 0; k < n; k++) {
        for (i = k+1; i < n; i++) {
            aa[i + k*ld] = aa[i + k*ld] / aa[k + k*ld];
        }
        for (i = k+1; i < n; i++) {
            for (j = k+1; j < n; j++) {
                aa[i + ld*j] -= aa[i + k*ld] * aa[k + j*ld];
            }
        }
    }
}

/* P2 (with slightly changed name) */

static void
lr_decomp_blas(pmatrix a){

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


/* ************************************************* */


static void
block_lsolve(int n, int m, const real *L, int ldL, real *B, int ldB){

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
block_rsolve_trans(int n, int m, const real *R, int ldR, real *B, int ldB){

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
blocklr_decomp(pmatrix a, int m){

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

  int n;
  pstopwatch sw;
  pmatrix A;
  real time;
  int m;

  n = 2000;					/* matrix dimension */
  m = 100;					/* number of matrix parts */



  /* ------------------------------------------------------------
   * Block-LR decomposition
   * ------------------------------------------------------------ */
  /* ------------------------------------------------------------
   * 'only' BLAS-LR decomposition
   * ------------------------------------------------------------ */
  /* ------------------------------------------------------------
   * first version of LR decomposition
   * ------------------------------------------------------------ */

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



  /* cleaning up */
  del_stopwatch(sw);

  return EXIT_SUCCESS;
}
