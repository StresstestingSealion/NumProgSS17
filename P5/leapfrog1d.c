/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 	Serie 5 - Simulation Loesung der Wellengleichung 	 */
/* ------------------------------------------------------------- */
/*	Autoren: Christina Boerst				 */
/*	Versionsnummer:	1					 */
/*---------------------------------------------------------------*/

  #include <assert.h>		
  #include "gridfunc1d.h"
  #include "leapfrog1d.h"		
  

/* Note:
    -'t' time value
    - 'delta' increment for the leapfrog method
    - 'data' used for m, c and the knowledge if a 
       wave on the boundary should start at the left
       interval edge or the right .
*/

  void
  step_leapfrog1d_wave(pcgridfunc1d u_old, pcgridfunc1d v_old,
  pgridfunc1d u_new, pgridfunc1d v_new, double t, double delta, void* data){
	  
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
