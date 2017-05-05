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

/* P1 */
static void
lr_decomp(pmatrix a){
	
  /* -------------------------------------------*/ 
  /*                                            */
  /*    C C      O O      P P P     Y     Y  	*/
  /*   C        O   O     P    P     Y   Y 	*/
  /*  C        O     O    P    P       Y        */ 
  /*  C        O     O    P P P        Y        */ 
  /*   C        O   O     P            Y       	*/
  /*    C C      O O      P            Y       	*/
  /*                                            */ 
  /* -------------------------------------------*/ 
	
}

/* P2 (with slightly changed name) */

static void
lr_decomp_blas(pmatrix a){

  /* -------------------------------------------*/ 
  /*                                            */
  /*    C C      O O      P P P     Y     Y  	*/
  /*   C        O   O     P    P     Y   Y 	*/
  /*  C        O     O    P    P       Y        */ 
  /*  C        O     O    P P P        Y        */ 
  /*   C        O   O     P            Y       	*/
  /*    C C      O O      P            Y       	*/
  /*                                            */ 
  /* -------------------------------------------*/ 

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
