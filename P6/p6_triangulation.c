/*---------------------------------------------------------------*/
/*		     Numerische Programmierung 	 	 	 */
/* 	Serie 6 - Visualisierung von Oberflaechentriangulationen */
/* ------------------------------------------------------------- */
/*	Autoren: 				 		 */
/*	Versionsnummer:						 */
/*---------------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/freeglut.h>
#include <GL/glut.h>

#include "surface3d.h"

#ifndef M_PI
/* Copied from math.h  */
#define M_PI		3.14159265358979323846
#endif


/* ------------------------------------------------------------
* Global variable
*-------------------------------------------------------------*/

psurface3d gr;
static int old_position_x, old_position_y;
static float angle_x = 0.0;
static float angle_y = 0.0;
static float old_angle_x, old_angle_y;
static float trans_x = 0.0;
static float trans_y = 0.0;
static float trans_z = 0.0;

float angle = 0.0;
float zoomFactor = 1.0; /* Global, if you want. Modified by user input. Initially 1.0 */

int grid_only = 0;

/* Translation */
static void
translate(double x, double y, double z) {

    GLfloat T[16];

    T[0] = 1.0;  T[4] = 0.0;  T[8] = 0.0;  T[12] = x;
    T[1] = 0.0;  T[5] = 1.0;  T[9] = 0.0;  T[13] = y;
    T[2] = 0.0;  T[6] = 0.0;  T[10] = 1.0;  T[14] = z;
    T[3] = 0.0;  T[7] = 0.0;  T[11] = 0.0;  T[15] = 1.0;

    glMultMatrixf(T);

}

static void
rotate_x(double a) {

    GLfloat R[16];

    R[0] = 1.0;  R[4] = 0.0;  R[8] = 0.0;  R[12] = 0.0;
    R[1] = 0.0;  R[5] = cos(a);  R[9] = -sin(a);  R[13] = 0.0;
    R[2] = 0.0;  R[6] = sin(a);  R[10] = cos(a);  R[14] = 0.0;
    R[3] = 0.0;  R[7] = 0.0;  R[11] = 0.0;  R[15] = 1.0;

    glMultMatrixf(R);

}


static void
rotate_y(double a) {

    GLfloat R[16];

    R[0] = cos(a);  R[4] = 0.0;  R[8] = sin(a);  R[12] = 0.0;
    R[1] = 0.0;  R[5] = 1.0;  R[9] = 0.0;  R[13] = 0.0;
    R[2] = -sin(a);  R[6] = 0.0;  R[10] = cos(a);  R[14] = 0.0;
    R[3] = 0.0;  R[7] = 0.0;  R[11] = 0.0;  R[15] = 1.0;

    glMultMatrixf(R);
}


/* Drawing complete surface triangulation */
static void
display_mesh() {

    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    GLfloat p[4], a[4], d[4];

    // set Viewport
    glViewport(0, 0, width, height);

    // clear buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set camera position (zoom)
    gluLookAt(0, 0, zoomFactor, 0, 0, -1, 0, 1, 0);

    /* Hintergrundfarbe */
    glClearColor(0.0, 0.0, 0.0, 1.0);


    glPushMatrix();

    // rotate
    rotate_x(angle_x);
    rotate_y(angle_y);

    // translate
    translate(trans_x, trans_y, trans_z);

    real (*x)[3] = gr->x;

    if (!grid_only) {

        int triangles = gr->triangles;
        int (*t)[3] = gr->t;
        real (*n)[3] = gr->n;
        int start, mid, end;
        glColor3d(1.0, 0.0, 0.0);
        glBegin(GL_TRIANGLES);
        for (int i = 0; i < triangles; i++) {
            start = t[i][0];
            mid = t[i][1];
            end = t[i][2];
            glNormal3f(n[i][0], n[i][1], n[i][2]);
            glVertex3f(x[start][0], x[start][1], x[start][2]);
            glVertex3f(x[mid][0], x[mid][1], x[mid][2]);
            glVertex3f(x[end][0], x[end][1], x[end][2]);
        }
        glEnd();

    } else {

        int edges = gr->edges;
        int (*e)[2] = gr->e;
        int start, end;
        glColor3d(0.0, 1.0, 0.0);
        glBegin(GL_LINES);
        for (int i = 0; i < edges; i++) {
            start = e[i][0];
            end = e[i][1];
            glVertex3f(x[start][0], x[start][1], x[start][2]);
            glVertex3f(x[end][0], x[end][1], x[end][2]);
        }
        glEnd();

    }

    glPopMatrix();


    /*nun Beleuchtung und Modelleigenschaften*/
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    /*Beleuchtung muss auch sein !*/
    glEnable(GL_LIGHTING);
    /*Anschalten der ersten Lampe! ;-)*/
    glEnable(GL_LIGHT0);

    /*Position unserer Lampe*/
    p[0] = -2.0;
    p[1] = 2.0;
    p[2] = 2.0;
    p[3] = 1.0;
    glLightfv(GL_LIGHT0, GL_POSITION, p);

    /*Ambientes Licht ist nicht aus einer Quelle gerichtet,
    sondern durchflutete den Raum und sorgt fuer die
    Helligkeit*/
    a[0] = 0.6;
    a[1] = 0.6;
    a[2] = 0.6;
    a[3] = 1.0;
    glLightfv(GL_LIGHT0, GL_AMBIENT, a);

    /*Licht aus einer Richtung wird erst beim Auftreffen
    gestreut, sorgt dafuer, dass es Hoehen und Tiefen er-
    haellt*/
    d[0] = 1.0;
    d[1] = 1.0;
    d[2] = 1.0;
    d[3] = 1.0;
    glLightfv(GL_LIGHT0, GL_DIFFUSE, d);
    /*Werte sind hier als RGBA Farben (d.h. RGB inklusive
    der Deckkraft) bzw. Postitionen und
    Intensitaeten zu interpretieren*/

    /*Materialeigenschaften, wie wird das Licht gestreut*/
    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT, GL_AMBIENT, a);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, d);

    /*Damit getestet wird, ob in dem Gebiet schon
    etwas gezeichnet wurde. Glut zeichnet in
    beliebiger Reihenfolge, was zu Fehlern
    im Erscheinungbild fuehren kann.
    (Obwohl der Pixel nicht zu sehen sein sollte,
    wurde er spaeter berechnet und erscheint doch)
    Außerdem muss fuer verdeckte Objekte
    nicht mehr gerechnet werden (Zeitersparnis). */
    glEnable(GL_DEPTH_TEST);


    glFlush();
    glutSwapBuffers();

}

/* Reshape of a triangulation */
static void
reshape_mesh(int width, int height) {

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width > height) {
        glScalef((double) height / width, 1.0, 1.0);
    } else {
        glScalef(1.0, (double) width / height, 1.0);
    }

    /*Perspektive festlegen:
    Dabei wird das Objekt in 3D gezeichnet und
    dann auf eine Flaeche projeziert
    1. Winkel entlang der Y-Achse
    2. Aspektratio entlang X-Achse (Verhaeltnis
    Breite zu Hoehe)
    3.Entfernung Betrachter zur nahen Z-Flaeche
    4.Entfernung Betrachter zur fernen Z-Flaeche
    */
    gluPerspective(35.0, 1.0, 1.0, 300.0);


}


/* Mouse movement on a triangulation */
static void
mouse_mesh(int button, int state, int position_y, int position_x) {

    (void) state;

    if (button == 3) zoomFactor += 0.25;
    if (button == 4) zoomFactor -= 0.25;

    /*Ersetzten der alten Positionen durch die neu
    ermittelten*/
    old_position_x = position_x;
    old_position_y = position_y;

    old_angle_x = angle_x;
    old_angle_y = angle_y;

    /*sorgt dafuer, dass die display wieder aufgerufen
    wird und damit die Veraenderungen gezeichnet*/
    glutPostRedisplay();

}


/* Motion on a triangulation */
static void
motion_mesh(int position_y, int position_x) {

    /*Bestimmung des noetigen Winkels zur Umsetzung
    der, mit der Mouse durchgefuehrten, Bewegung*/
    angle_x = 0.01 * (old_angle_x + (position_x - old_position_x));
    angle_y = 0.01 * (old_angle_y + (position_y - old_position_y));

    /*sorgt dafuer, dass die display wieder aufgerufen
    wird und damit die Veraenderungen gezeichnet*/
    glutPostRedisplay();

}

/* Key input for triangulation */
static void
key_mesh(unsigned char key, int x, int y) {

    (void) x;
    (void) y;

    /*Beschreibung, welche Folgen das
    Druecken einer Taste hat.
    Hier: 'esc' fuehrt zum Beenden (Fenster wird
    geschlossen)
    Alles andere hat keine Wirkung!*/
    switch (key) {
        case 27 :
            exit(EXIT_SUCCESS);
        case 'g':
            grid_only = 1 - grid_only;
            break;
        case 'z':
            zoomFactor += 0.05;
            break;
        case 'h':
            zoomFactor -= 0.05;
            break;
        case 'a':
            trans_x += 0.5;
            break;
        case 'd':
            trans_x -= 0.5;
            break;
        case 'w':
            trans_y += 0.5;
            break;
        case 's':
            trans_y -= 0.5;
            break;
        case 'r':
            zoomFactor = 0.0;
            angle_x = 0.0;
            angle_y = 0.0;
            trans_x = 0.0;
            trans_y = 0.0;
            trans_z = 0.0;
            break;
        default :
            break;
    }
    glutPostRedisplay();

}

void normalize() {




}


/* last but not least the main function */
int
main(int argc, char **argv) {


    /* Reading mesh */
    if (argc > 1) {
        gr = read_surface3d(argv[1]);
        printf("read %s", argv[1]);
    } else {
        printf("No input file!\n");
        return EXIT_SUCCESS;
    }

    glutInit(&argc, argv);
    glutCreateWindow("P6 Triangulation");
    glutPositionWindow(150, 100);
    glutReshapeWindow(900, 900);

    glutReshapeFunc(reshape_mesh);
    glutDisplayFunc(display_mesh);
    glutMouseFunc(mouse_mesh);
    glutMotionFunc(motion_mesh);
    glutKeyboardFunc(key_mesh);

    glutMainLoop();

    return EXIT_SUCCESS;
}
