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
	pcrsmatrix crs = new_crsmatrix(m, m);
	double h_2 = 1.0 / ((m + 1) * (m + 1));
	int nze = 3 * (m - 2) + 4;
	int i;
	crs->Aa = (double*) malloc(nze * sizeof(double));
	crs->Aj = (unsigned int*) malloc(nze * sizeof(unsigned int));
	crs->Ai = (unsigned int*) malloc((m + 1) * sizeof(unsigned int));

	for(i = 0; i < nze; i++){
		if(i % 3 == 0)
			crs->Aa[i] = 2 * h_2;
		else
			crs->Aa[i] = -1 * h_2;
	}

	for(i = 0; i < nze; i++){
		if(i % 3 == 1)
			crs->Aj[i] = i / 3 + i % 3;
		else
			crs->Aj[i] = i / 3;
	}

	crs->Ai[0] = 0;
	for(i = 1; i < m + 1; i++){
		if(i == 1 || i == m)
			crs->Ai[i] = crs->Ai[i - 1] + 2;
		else
			crs->Ai[i] = crs->Ai[i - 1] + 3;
	}
	print_crs(crs);
	return crs;
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
	int curr = crs->Ai[0];
	double j;
	for(int i = 0; i < crs->row; i++){
		j = crs->Ai[i + 1] - crs->Ai[i];
		while(j-- > 0){
			b->x[i] += alpha * crs->Aa[curr] * x->x[curr];
			curr++;	
		}
	}
 
}

void
richardson_iteration(pcrsmatrix crs, pvector x, double theta, pvector b, double eps){
	pvector err_vec;
	double err;
	//int i = 0;
	err_vec = new_zero_vector(x->rows);
	mvm_crs(crs, x, 1, err_vec);
	axpy(err_vec->rows, -1, b->x, 1, err_vec->x, 1);
	err = nrm2(err_vec->rows, err_vec->x, 1);
	while(eps < err){
		//printf("Error: %f\n", err);
		/*for(int j = 0; j < x->rows; j++)
			printf("x[%d]=%f\n", j, x->x[j]);*/
		mvm_crs(crs, x, -theta, x);
		axpy(x->rows, theta, b->x, 1, x->x, 1);
		//Calculate error
		err_vec = new_zero_vector(x->rows);
		mvm_crs(crs, x, 1, err_vec);
		axpy(err_vec->rows, -1, b->x, 1, err_vec->x, 1);
		err = nrm2(err_vec->rows, err_vec->x, 1);
		//i++;
	}
  
}

