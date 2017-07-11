/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/*   	Serie 10 - Schwachbesetzte Matrizen (Richardson)	 */
/* ------------------------------------------------------------- */
/*	Autoren: 		 				 */
/*	Versionsnummer:						 */
/*---------------------------------------------------------------*/

  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>
  #include "crs.h"

  #ifndef M_PI
/* Copied from math.h  */
#define M_PI		3.14159265358979323846
#endif

static double
sinus(double x, void *data){

  double *dat = (double *) data;
  double fx;
  double mu = dat[0];

  fx = sin(M_PI * mu * x);
  return fx;
}

int
main(void){

  pcrsmatrix crs;
  unsigned int m;
  pvector x, b;
  unsigned int i;
  double data[1];
  double theta, h, lambda;

  m = 5;				
  data[0] = 1.0;
  // theta = 0.000001;
  h = 1.0/(m+1);

<<<<<<< Updated upstream
  theta = 2 / (4.0/h/h * sinus(h *0.5, data) * sinus(h *0.5, data));
 
  printf("Solve poisson equation with Richardson iteration\n");
  printf("-----------------------------------------\n");
=======
  printf("Apply Richardson Iteration:\n");
>>>>>>> Stashed changes

  crs = setup_poisson(m);
  b = new_zero_vector(m);
  x = new_zero_vector(m);
  set_righthandside(m, sinus, data, b);

  printf("Right side \n");
    for(i = 0; i < m; i++){
    printf("%f\n", b->x[i]);
  }

<<<<<<< Updated upstream
  /* solve with Richardson iteration */
=======
>>>>>>> Stashed changes
  richardson_iteration(crs, x, theta, b, 1.e-7);
  printf("Solution\n");
  	lambda = sinus(h *0.5, data);
    lambda *= lambda;
 	lambda *= 4.0/h/h;
  for(i = 0; i < m ; i++){
    printf("Richardson: %f \t accurate: %f \t difference: %e \n", x->x[i],  b->x[i]/ lambda, fabs(x->x[i] - b->x[i]/ lambda));
  }

  del_crsmatrix(crs);
  del_vector(x);
  del_vector(b);

  return EXIT_SUCCESS;
}
