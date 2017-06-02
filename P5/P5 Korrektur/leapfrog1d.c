/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 	Serie 5 - Simulation Loesung der Wellengleichung 	 */
/* ------------------------------------------------------------- */
/*	Autoren: Christina Boerst				 */
/*	Versionsnummer:	1					 */
/*---------------------------------------------------------------*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
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
    double d = u_old->d;


    if (left) {
        left_boundary_gridfunc1d(u_new, t);
    } else {
        right_boundary_gridfunc1d(u_new, t);
    }

    for (int i = 1; i < d - 1; i++) {
        ux_new[i] = ux_old[i] + 2 * delta * vx_old[i];
        vx_new[i] = vx_old[i] + 2*delta * c*c / (2 *h*2*h) *
                                (ux_old[i - 1] - 2 * ux_old[i] + ux_old[i + 1]);
    }
}