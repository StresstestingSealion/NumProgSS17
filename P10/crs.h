  #ifndef CRS_H
  #define CRS_H

  #include "matrix.h"

  /* Matrix typ */

  typedef struct _crsmatrix crsmatrix;

  typedef crsmatrix *pcrsmatrix; 

  struct _crsmatrix{

    unsigned int row;		/* Number of rows */
    unsigned int col;		/* Number of columns */
  
    double *Aa;			/* Non-zero entries (nze) */
    unsigned int *Ai;		/* Number of nze per row, under the condition that Ai[i] = Ai[i-1] + nze(i) */
    unsigned int *Aj;		/* Column for each entry in Aa*/
  };

  /* prototyp function*/
  typedef double (*function)(double x, void *data);

 /* ------------------------------------------------------------
 * Constructor and destructor
 * ------------------------------------------------------------ */

pcrsmatrix
new_crsmatrix( unsigned int rows, unsigned int cols);

void
del_crsmatrix(pcrsmatrix crs);


 /* ------------------------------------------------------------
 * Set up example matrix
 * ------------------------------------------------------------ */

/* 1D poisson for m inner points */
pcrsmatrix
setup_poisson(unsigned int m);

/* Set up right hand side for a given function f and save results in b */
void 
set_righthandside(int m, function f, void *data, pvector b);


 /* ------------------------------------------------------------
 * Auxiliary functions
 * ------------------------------------------------------------ */

 /* matrix vector multiplication */
void
mvm_crs(pcrsmatrix crs, pvector x, double alpha, pvector b);

void
print_crs(pcrsmatrix crs);

 /* Richardson iteration with damping parameter theta,
    defect norm tolerance eps and right hand side b, for
    lienar system of equations crs * x = b.  */
void
richardson_iteration(pcrsmatrix crs, pvector x, double theta, pvector b, double eps);
  #endif
