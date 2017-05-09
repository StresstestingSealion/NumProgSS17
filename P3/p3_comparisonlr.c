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
#include "basic.h"        /* basic types and time measurement */
#include "miniblas.h"        /* our simple BLAS version */
#include "matrix.h"        /* matrix functions */


/* older versions e.g. used in comparsion*/
/* ************************************************* */

/** Inplace LR-decomposition without pivot search */
void
lr_decomp(pmatrix a) {

    int i, j, k;
    int n = a->rows;
    double *aa = a->a;
    int ld = a->ld;


    for (k = 0; k < n; k++) {
        for (i = k + 1; i < n; i++) {
            aa[i + k * ld] = aa[i + k * ld] / aa[k + k * ld];
        }
        for (i = k + 1; i < n; i++) {
            for (j = k + 1; j < n; j++) {
                aa[i + ld * j] -= aa[i + k * ld] * aa[k + j * ld];
            }
        }
    }
}

/* P2 (with slightly changed name) */
static void
lr_decomp_blas(pmatrix a) {

    int k;
    int n = a->rows;
    int ldA = a->ld;
    double *A = a->a;

    for (k = 0; k < n; k++) {
        scal(n - k - 1, 1.0 / A[k + k * ldA], A + (k + 1) + k * ldA, 1);
        ger(n - k - 1, n - k - 1, -1.0,
            A + (k + 1) + k * ldA, 1, A + k + (k + 1) * ldA, ldA,
            A + (k + 1) + (k + 1) * ldA, ldA);
    }
}


/* ************************************************* */


static void
block_lsolve(int n, int m, const real *L, int ldL, real *B, int ldB) {

    int k;
    for (k = 0; k < n; k++) {
        ger(n - k - 1, m, -1.0, L + (k + 1) + k * ldL, 1, B + k, ldB, B + (k + 1), ldB);
    }

}

static void
block_rsolve_trans(int n, int m, const real *R, int ldR, real *B, int ldB) {

    int k;
    for (k = 0; k < n; k++) {
        scal(m, 1.0 / R[k + k * ldR], B + k * ldB, 1);
        ger(m, n - k - 1, -1.0, B + k + ldB, 1, R + k + (k + 1) * ldR, ldR, B + (k + 1) * ldB, ldB);
    }

}

static void
blocklr_decomp(pmatrix A, int m) {

    int i, j, k;
    int n = A->rows;
    int ldA = A->ld;
    int oi, oj, ok, ni, nj, nk;
    real *a = A->a;

    for (k = 0; k < m; k++) {
        ok = n * k / m;
        nk = n * (k + 1) / m - ok;
        //	lrdecomp(a+ok+ok+ldA, ldA);

        for (j = k + 1; j < m; j++) {
            oj = n * j / m;
            nj = n * (j + 1) / m - oj;

            block_lsolve(nk, nj, a + ok + ok * ldA, ldA, a + ok + oj * ldA, ldA);
            block_rsolve_trans(nk, nj, a + ok + ok * ldA, ldA, a + oj + ok * ldA, ldA);
        }
        for (j = k + 1; j < m; j++) {
            oj = n * j / m;
            nj = n * (j + 1) / m - oj;
            for (i = k + 1; i < m; i++) {
                oi = n * i / m;
                ni = n * (i + 1) / m - oi;
                gemm(false, false, ni, nj, nk, -1.0, a + oi + ok * ldA, ldA, a + ok + oj * ldA, ldA, 1.0,
                     a + oi + oj * ldA, ldA);
            }
        }
    }
}


/* ============================================================
 * Main program
 * ============================================================ */

int
main(void) {

    int n;
    pstopwatch sw = new_stopwatch();
    real time = 0;
    int m;

    n = 2000;                    /* matrix dimension */
    m = 50;                    /* number of matrix parts */

    pmatrix A = new_diaghilbert_matrix(n);

    /* ------------------------------------------------------------
     * Block-LR decomposition
     * ------------------------------------------------------------ */
    start_stopwatch(sw);
    blocklr_decomp(A,m);
    time = stop_stopwatch(sw);
    printf("Block: %f\n", time);

    /* ------------------------------------------------------------
     * 'only' BLAS-LR decomposition
     * ------------------------------------------------------------ */
    start_stopwatch(sw);
    lr_decomp_blas(A);
    time = stop_stopwatch(sw);
    printf("BLAS: %f\n", time);

    /* ------------------------------------------------------------
     * first version of LR decomposition
     * ------------------------------------------------------------ */
    start_stopwatch(sw);
    lr_decomp(A);
    time = stop_stopwatch(sw);
    printf("manual: %f\n", time);


    /* cleaning up */
    del_stopwatch(sw);

    return EXIT_SUCCESS;
}
