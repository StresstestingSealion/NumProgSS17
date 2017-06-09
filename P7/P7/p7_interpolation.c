/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 	Serie 7 - Approximation von Funktionen (Interpolation) 	 */
/* ------------------------------------------------------------- */
/*	Autoren: Christina Boerst				 */
/*	Versionsnummer:	1					 */
/*---------------------------------------------------------------*/

		
  #include <stdio.h>		
  #include <stdlib.h> 
  #include <math.h>
  #include <assert.h>
  #include <GL/freeglut.h>
  #include <GL/glut.h>
  
  #include "interpolation.h"
  
  #ifndef M_PI
/* Copied from math.h  */
#define M_PI		3.14159265358979323846
#endif	

  
/* ------------------------------------------------------------
* Global variable
*-------------------------------------------------------------*/

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

  
/* ------------------------------------------------------------
* Example function
*-------------------------------------------------------------*/

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

/* ------------------------------------------------------------
* GLUT functions
*-------------------------------------------------------------*/

/* If necessary use the pictures as orientation,
   but feel free to create something different =)*/


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
