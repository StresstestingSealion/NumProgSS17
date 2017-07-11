/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 		Serie 10 - Schwachbesetzte Matrizen 		 */
/* ------------------------------------------------------------- */
/*	Autoren: 				 		 */
/*	Versionsnummer:						 */
/*---------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include "crs.h"
#include "miniblas.h"
#include "matrix.h"


/* ------------------------------------------------------------
* Constructor and destructor
* ------------------------------------------------------------ */

pcrsmatrix
new_crsmatrix(unsigned int rows, unsigned int cols) {

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
del_crsmatrix(pcrsmatrix crs) {


    if (crs->Aa) {
        free(crs->Aa);
    }
    if (crs->Ai) {
        free(crs->Ai);
    }
    if (crs->Aj) {
        //   free(crs->Aj);
    }

    free(crs);
}

/* ------------------------------------------------------------
* Set up example matrix and right hand side
* ------------------------------------------------------------ */

pcrsmatrix
setup_poisson(unsigned int m) {

    double h_2 = 1.0 / ((m + 1) * (m + 1));
    int nze = 3 * (m - 2) + 4;

    pcrsmatrix crs = new_crsmatrix(m,m);
    crs->Aa = (double *) malloc(nze * sizeof(double));
    crs->Aj = (unsigned int *) malloc(nze * sizeof(unsigned int));
    crs->Ai = (unsigned int *) malloc((m + 1) * sizeof(unsigned int));

    switch(m) {
        case 1:
            crs->Aa[0] = 2 * h_2;
            crs->Aj[0] = 1;
            crs->Ai[0] = 0;
            crs->Ai[1] = 1;
            break;
        case 2:
            crs->Aa[0] = 2 * h_2;
            crs->Aa[1] = -1 * h_2;
            crs->Aa[2] = -1 * h_2;
            crs->Aa[3] = 2 * h_2;
            crs->Aj[0] = 0;
            crs->Aj[1] = 1;
            crs->Aj[2] = 0;
            crs->Aj[3] = 1;
            crs->Ai[0] = 0;
            crs->Ai[1] = 2;
            crs->Ai[2] = 4;
            break;
        default:

            // Aa
            for (int i = 0; i < nze; i++) {
                if(i % 3) {
                    crs->Aa[i] = -1;
                } else {
                    crs->Aa[i] = 2;
                }
            }

            // Ai
            crs->Ai[0] = 0;
            for (int i = 1; i < m + 1; i++) {
                if (i == 1 || i == m) {
                    crs->Ai[i] = crs->Ai[i - 1] + 2;
                } else {
                    crs->Ai[i] = crs->Ai[i - 1] + 3;
                }
            }

            // Aj
            for (int i = 0; i < nze; i++) {
                if (i % 3 == 1)
                    crs->Aj[i] = (unsigned int) (i / 3 + i % 3);
                else
                    crs->Aj[i] = (unsigned int) (i / 3);
            }

            break;
    }

    print_crs(crs);
    return crs;
}


void
set_righthandside(int m, function f, void *data, pvector b) {

    double h = 1.0 / (m + 1);
    for (int i = 0; i < b->rows; i++) {
        b->x[i] = f((i + 1) * h, data);

    }

}


/* ------------------------------------------------------------
* Auxiliary functions
* ------------------------------------------------------------ */

void
print_crs(pcrsmatrix crs) {

    unsigned int nnze = crs->Ai[crs->row];
    unsigned int i;


    if (nnze > 1) {
        printf("Non-zero entries\n");
        printf("(%f,  ", crs->Aa[0]);
        for (i = 1; i < nnze - 1; i++) {
            printf("%f,  ", crs->Aa[i]);
        }
        printf("%f)\n", crs->Aa[nnze - 1]);
        printf("\n");
        printf("Entries per row\n(%d", crs->Ai[0]);
        for (i = 1; i <= crs->row; i++) {
            printf(", %d", crs->Ai[i]);
        }
        printf(")\n");
        printf("\n");
        printf("Column for entries\n");
        printf("(%d, ", crs->Aj[0]);
        for (i = 1; i < nnze - 1; i++) {
            printf("%d, ", crs->Aj[i]);
        }
        printf("%d)\n", crs->Aj[nnze - 1]);
        printf("\n");

    } else {
        printf("Matrix\n");
        printf("(%f ) \n", crs->Aa[0]);
    }


}


void
mvm_crs(pcrsmatrix A, pvector x, double alpha, pvector b) {

    unsigned int nze;           // number of nze in current row
    unsigned int current = 0;   // pointer to current element in Aa


    for (int i = 0; i < A->row; i++) {
        nze = A->Ai[i+1] - A->Ai[i];
        b->x[i] = 0;
        while (nze--) {
            b->x[i] += alpha * A->Aa[current] * x->x[A->Aj[current]];
            current++;
        }
    }
}


void
richardson_iteration(pcrsmatrix A, pvector x, double theta, pvector b, double eps) {

    int n = x->rows;
    pvector p = new_zero_vector(n);


    mvm_crs(A, x, 1, p);                    // p = A * x
    axpy(n, -1, p->x, 1, b->x, 1);          // b = b - Ax

    while (nrm2(n, b->x, 1) > eps) {

        mvm_crs(A, b, 1, p);                  // a = A * b
        axpy(n, theta, b->x, 1, x->x, 1);       // x = x + theta * b
        axpy(n, -theta, p->x, 1, b->x, 1);      // b = b - theta * a
    }

/*
    pvector err_vec = new_zero_vector(x->rows);
    double err;

    mvm_crs(A, x, 1, err_vec);
    axpy(err_vec->rows, -1, b->x, 1, err_vec->x, 1);
    err = nrm2(err_vec->rows, err_vec->x, 1);

    while (eps < err) {
        *//*for(int j = 0; j < x->rows; j++)
            printf("x[%d]=%f\n", j, x->x[j]);*//*
        mvm_crs(A, x, -theta, x);
        axpy(x->rows, theta, b->x, 1, x->x, 1);
        //Calculate error
        err_vec = new_zero_vector(x->rows);
        mvm_crs(A, x, 1, err_vec);
        axpy(err_vec->rows, -1, b->x, 1, err_vec->x, 1);
        err = nrm2(err_vec->rows, err_vec->x, 1);
        //i++;
    }*/


}

