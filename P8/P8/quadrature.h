
  #ifndef QUADRATURE_H
  #define QUADRATURE_H
  
  #include "basic.h"

  /* prototyp function*/
  typedef double (*function)(double x, void *data);

  typedef struct _quadrature quadrature;

  typedef quadrature *pquadrature;
  
 
  struct _quadrature {
    int m;				/* quadrature order */

    double *xq;			/* quadrature points */
    double *w;			/* quadrature weights */
  };

  
 /* ------------------------------------------------------------
 * Constructor and destructor
 * ------------------------------------------------------------ */

pquadrature
new_quadrature(int m);

void
del_quadrature(pquadrature quad);

 /* ------------------------------------------------------------
 * Set up midpoint rule and trapezoidal rule
 * ------------------------------------------------------------ */

/* Allocate memory and set up quadrature weights and points on [-1,1] */

pquadrature
setup_midpointrule(void);

pquadrature
setup_trapezoidalrule(void);

/* Map quadrature points given on [-1,1] onto [a,b]*/

void
map_quadrature_points(pquadrature quad, double a, double b, double *x);


 /* ------------------------------------------------------------
 * Compute quadrature formulas  composite 
 * ------------------------------------------------------------ */

/* Compute integral of f on [a,b] with given quadrature formula */ 
 
double
eval_quadrature(pquadrature quad, double a, double b, function f, void *data);

/* Compute integral of f on [a,b] with given composite quadrature formula 
   using n even subintervalls of [a,b] */ 

double
eval_composite_quadrature(pquadrature quad, double a, double b, int n, function f, void *data);

  #endif
