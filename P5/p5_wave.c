/*---------------------------------------------------------------*/
/*		     Numerische Programmierung  	 	 */
/* 	Serie 5 - Simulation Loesung der Wellengleichung 	 */
/* ------------------------------------------------------------- */
/*	Autoren: 						 */
/*	Versionsnummer:						 */
/*---------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <GL/freeglut.h>
#include <GL/glut.h>

#include "gridfunc1d.h"
#include "leapfrog1d.h"

/* ------------------------------------------------------------
* Global variable
*-------------------------------------------------------------*/

/* Some nice ideas for global values, but feel free to change them */

/*	Wave equation and grid		*/
pgridfunc1d u[2], v[2];
pstopwatch sw;
unsigned int current = 0;        /* switch between grid functions */
double data[2];                /* data 'c' and left or right wave */
double t = 1.25;            /* time used to create a start wave */
double delta;                /* incremenet */
unsigned int step;            /* to find a good relation between increment size (therefore accuracy)
 					   update rate for glut. */


/* reshape function (simple 2D without frills!) */
static void
reshape_wave(int width, int height) {

    /*Setzt den Anwendungsbereich der vom
    Fenster tatsaechlich genutzt wird*/
    glViewport(0, 0, width, height);

    /*Identitaetsmatrix laden, um Veraenderungen
    in ihr zu speichern und mit der
    Veraenderung weiter zu arbeiten*/
    glLoadIdentity();

    /*Skalierung des Inhalts, wenn die
    Fenstergroeße waehrend der Anwendung
    vom User geaendert wird*/
    if (width > height) {
        glScalef((GLfloat) height / width, 1.0, 1.0);
    } else {
        glScalef(1.0, (GLfloat) width / height, 1.0);
    }

}


/* and now... the content =)
   draw the string and the deflections, maybe with some nice colors
   and think about scaling !*/

static void
display_wave() {


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    /* Hintergrundfarbe */
    glClearColor(1.0, 1.0, 1.0, 1.0);

    // Koordinaten-System
    glColor3d(0.0,0.0,0.0);
    glBegin(GL_LINES);
    glVertex2f(-1.0,0.0);
    glVertex2f(1.0,0.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex2f(0.0, 1.0);
    glVertex2f(0.0, -1.0);
    glEnd();

    // u
    glBegin(GL_LINE_STRIP);
    glColor3d(1.0,0.0,0.0);
    for (unsigned int j = 0; j < u[current]->d; j++) {
        double n = u[current]->d-2;
        double x = -1.0 + 2.0/n * (j+1);
        double y = u[current]->x[j] * 0.2;
        glVertex2d(x, y);
    }
    glEnd();

    glFlush();

}

/* start new waves, leave and so on.... there are a lot of possibilities 
   Think about a way to change the start point for a new wave (left or right) 
   and how to reset the simulation */
static void
key_wave(unsigned char key, int x, int y) {

    (void) x;
    (void) y;

    /*
     * Beschreibung, welche Folgen das
     * Druecken einer Taste hat.
     * - 'esc' fuehrt zum Beenden (Fenster wird geschlossen)
     * */
    switch (key) {
        case 27 :
            exit(EXIT_SUCCESS);
        case 'a' :
            data[1] = 1.0;
            t = 0.0;
            break;
        case 'd' :
            data[1] = 0.0;
            t = 0.0;
            break;
        case 'r' :
            zero_gridfunc1d(u[current]);
            zero_gridfunc1d(u[1 - current]);
            zero_gridfunc1d(v[current]);
            zero_gridfunc1d(v[1 - current]);
            t = 1.25;
        default :
            break;
    }

}


/* it's necessary to compute new values and redisplay them after a while....*/
static void
timer_wave(int val) {

    int steps = 20000;
    delta = 0.05 / steps;

    int old = current;
    int new = current % 1;

    for (int i = 0; i <= steps; i++) {
        t += delta;
        step_leapfrog1d_wave(u[old], v[old], u[new], v[new], t, delta, data);
    }

    current = current % 1;

    /*sorgt dafuer, dass die display wieder aufgerufen
    wird und damit die Veraenderungen gezeichnet*/
    glutPostRedisplay();

    /*Die Finktion ruft sich selbst wieder auf,
    damit die Bewegung erneut durchgefuehrt werden
    kann!!*/
    glutTimerFunc(step, timer_wave, val + 1);

}


/* last but not least the main function
  don't forget to set 'c' and the number
  of points 'n' */
int
main(int argc, char **argv) {

    double c = 0.2;
    data[0] = c;

    unsigned int n = 300;
    pgrid1d grid = new_grid1d(n);

    u[0] = new_gridfunc1d(grid);
    u[1] = new_gridfunc1d(grid);
    zero_gridfunc1d(u[0]);
    zero_gridfunc1d(u[1]);

    v[0] = new_gridfunc1d(grid);
    v[1] = new_gridfunc1d(grid);
    zero_gridfunc1d(v[0]);
    zero_gridfunc1d(v[1]);

/****************************************
Grundsaetzliches Erstellen eines Fensters
****************************************/

    /*Initialisieren von Glut, moegliche Daten
    werden an Freeglut uebergeben*/
    glutInit(&argc, argv);

    /*Erstellen eines Fensters*/
    glutCreateWindow("Hello Wave Equation!");

    /*Position des Fensters in Pixeln von der
    obenen linken Ecke des Bildschirms ausgehend*/
    glutPositionWindow(150, 100);

    /*Groeße des Fensters in Pixeln*/
    glutReshapeWindow(800, 800);

/*****************************************
Freeglut Callback-Funktionen fuer den
				Inhalt
******************************************/

    /*Zum Erstellen des Hintergrunds, einrichten
    der Perspektive */
    glutReshapeFunc(reshape_wave);

    /*Zum Erstellen des Fensterinhalts, was soll
    dargestellt werden?*/
    glutDisplayFunc(display_wave);


    /*Zur Umsetzung von vorher festgelegten
    Befehlen ueber die Tastatur*/
    glutKeyboardFunc(key_wave);

    /*Zur Neuberechnung von Werten.
    Erhaelt die Millisekunden bis zum
    Aufruf, die Callback-Funktion und
    einen variablen Wert fuer komplexere
    Callback-Funktionen*/
    glutTimerFunc(step, timer_wave, 0);

/*****************************************
			Start von Freeglut
******************************************/

    /*Startet die Glutanwendung, ab jetzt
    werden die Funktionsaufrufe von Freeglut
    verwaltet!
    Diese Funktion steht immer am Schluss
    der Mainfunktion*/
    glutMainLoop();

    return EXIT_SUCCESS;
}
