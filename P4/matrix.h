
#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
  int rows;
  int cols;
  int ld;

  double *a;
} matrix;

typedef matrix *pmatrix;

typedef struct {
  int rows;

  double *x;
} vector;

typedef vector *pvector;

/* 			tridiagonal matrix						*/

typedef struct {
  int rows;			/* Matrix dimension */

  double *d;			/* Diagonal elements */
  double *l;			/* Subdiagonal elements */
  double *u;			/* Superdiagonal elements */
} tridiag;

typedef tridiag *ptridiag;

/* ------------------------------------------------------------
 * Constructors and destructors
 * ------------------------------------------------------------ */

pmatrix
new_matrix(int rows, int cols);

pmatrix
new_zero_matrix(int rows, int cols);

pmatrix
new_identity_matrix(int rows);

void
del_matrix(pmatrix a);

pvector
new_vector(int rows);

pvector
new_zero_vector(int rows);

void
del_vector(pvector x);

pmatrix
init_sub_matrix(pmatrix asub, pmatrix a, int rows, int roff, int cols, int coff);


/* 			tridiagonal matrix						*/

ptridiag 
new_tridiag(int rows);

void
del_tridiag(ptridiag a);

/* ------------------------------------------------------------
 * Example matrix
 * ------------------------------------------------------------ */

pmatrix
new_diaghilbert_matrix(int rows);

pmatrix
new_hilbert_matrix(int rows);

ptridiag
new_threepointstencil(int rows);

/* ------------------------------------------------------------
 * Simple utility functions
 * ------------------------------------------------------------ */

void
clear_matrix(pmatrix x);

void
clear_vector(pvector x);

void
print_matrix(pmatrix a);

void
random_vector(pvector x);

double
normmax_vector(pvector x);

double
normmax_diff_vector(pvector x, pvector y);

double
norm2_diff_vector(const pvector x, const pvector y);


/* 			tridiagonal matrix						*/

void
copy_tridiag(const ptridiag a, ptridiag b);

ptridiag
clone_tridiag(const ptridiag a);

void
mvm_tridiag(int trans, double alpha, const ptridiag a,
	    const pvector x, pvector y);

#endif
