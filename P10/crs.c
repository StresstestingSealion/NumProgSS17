/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 		Serie 10 - Schwachbesetzte Matrizen 		 */
/* ------------------------------------------------------------- */
/*	Autoren: 				 		 */
/*	Versionsnummer:						 */
/*---------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "crs.h"
#include "miniblas.h"


 /* ------------------------------------------------------------
 * Constructor and destructor
 * ------------------------------------------------------------ */

pcrsmatrix
new_crsmatrix( unsigned int rows, unsigned int cols){

  pcrsmatrix crs;
  
  crs = (pcrsmatrix) calloc(1, sizeof(crsmatrix));
  crs->row = rows;
  crs->col = cols;
  
  crs->Aa = NULL;
  crs->Ai = NULL;
  crs->Aj = NULL;

  return crs;
}

void
del_crsmatrix(pcrsmatrix crs){


  if(crs->Aa){
    free(crs->Aa);
  }
  if(crs->Ai){
    free(crs->Ai);
  }
  if(crs->Aj){
 //   free(crs->Aj);
  }
  
  free(crs);
}

 /* ------------------------------------------------------------
 * Set up example matrix and right hand side
 * ------------------------------------------------------------ */

pcrsmatrix
setup_poisson(unsigned int m){
 
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


void 
set_righthandside(int m, function f, void *data, pvector b){

  double h = 1.0/(m+1);
  unsigned int i;

  for(i = 0; i < b->rows; i++){
    b->x[i] = f((i+1)*h, data);

  }

}


 /* ------------------------------------------------------------
 * Auxiliary functions
 * ------------------------------------------------------------ */

void
print_crs(pcrsmatrix crs){

  unsigned int nnze = crs->Ai[crs->row];
  unsigned int i;


  if(nnze >1){
    printf("Non-zero entries\n");
    printf("(%f,  ", crs->Aa[0]);
    for(i = 1; i < nnze-1; i++){
      printf("%f,  ", crs->Aa[i]);
    }
    printf("%f)\n", crs->Aa[nnze-1]);
    printf("\n");
    printf("Entries per row\n(%d", crs->Ai[0]);
    for(i = 1; i <= crs->row; i++){
      printf(", %d", crs->Ai[i]);
    }
    printf(")\n");
    printf("Column for entries\n");
    printf("(%d, ", crs->Aj[0]);
    for(i = 1; i < nnze-1; i++){
      printf("%d, ", crs->Aj[i]);
    }
    printf("%d)\n", crs->Aj[nnze-1]);

  }
  else{
    printf("Matrix\n");
    printf("(%f ) \n", crs->Aa[0]);
  }


}


void
mvm_crs(pcrsmatrix crs, pvector x, double alpha, pvector b){

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

void
richardson_iteration(pcrsmatrix crs, pvector x, double theta, pvector b, double eps){

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

