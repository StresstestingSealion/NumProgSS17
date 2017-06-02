/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 	Serie 5 - Simulation Loesung der Wellengleichung 	 */
/* ------------------------------------------------------------- */
/*	Autoren: Christina Boerst				 */
/*	Versionsnummer:	1					 */
/*---------------------------------------------------------------*/

#include "gridfunc1d.h"
#include "leapfrog1d.h"


/* Note:
    - 't' time value
    - 'delta' increment for the leapfrog method
    - 'data' used for c and the knowledge if a
       wave on the boundary should start at the left
       interval edge or the right .
*/

void
step_leapfrog1d_wave(pcgridfunc1d u_old, pcgridfunc1d v_old,
                     pgridfunc1d u_new, pgridfunc1d v_new,
                     double t, double delta, void *data) {

    double *ux_new = u_new->x;
    double *ux_old = u_old->x;

    double *vx_new = v_new->x;
    double *vx_old = v_old->x;

    double c = ((double *) data)[0];
    double left = ((double *) data)[1];
    double h = u_old->g->h;
    int d = u_old->d;

	for (int i = 1; i<d)
		ux_new[i] = ux_old[i]+2*delta*vx_old[i];

    if (left) {
        left_boundary_gridfunc1d(u_new, t);
	ux_new[d-1] = 0.0;
    } else {
        right_boundary_gridfunc1d(u_new, t);
	ux_new[0]=0.0;
    }

    for (int i = 1; i < d - 1; i++) {
        ux_new[i] = ux_old[i] + 2 * delta * vx_old[i];
        vx_new[i] = vx_old[i] + 2*delta * c*c / (h*h) *
                                (ux_new[i - 1] - 2 * ux_new[i] + ux_new[i + 1]);
				//calculate ux_new[i+1] in additional loop
    }
}
