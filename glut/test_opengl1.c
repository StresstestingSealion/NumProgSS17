/*-------------------------------------
	     Freeglut Einführung 1
	 Wissenschaftliches Rechnen 2015
			Christina Börst 	
--------------------------------------*/

#include <math.h>

/*fuer Freeglut noetige Header*/
#include <GL/freeglut.h>
#include <GL/glut.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


/*Die Callback-Funktion, welche von der
glutReshapeFuncton aufgerufen wird, erhaelt
immer die Breite und die Hoehe des Fensters
als Parameter*/
static void
reshape(int width, int height) {

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


static void
display() {

    const int pieces = 25;
    const GLfloat radius = 0.25;
    int i;

    /*hier beginnt der Zeichenspaß!!*/

    /*Entfernen moeglicher Farb- und Tiefendaten
    aus dem letzten Aufruf */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/***********************************
Zeichnen eines Quadrats neben einem 
			Kreis
************************************/

    /*Veraenderungen des Zeichenursprungs
    von letzten Aufrufen elemninieren. Ohne
    eine eingegebene Matrix erhalten wir
    die Identitaet, mit Push wird diese Matrix
    oben auf den Stapel der Matrizen gelegt,
    mit Pop wandert sie wieder herunter.
    So kann man sich eine Hierarchie von Matrizen
    aufbauen und nutzen!*/
    glPushMatrix();

    /*Der Quader soll spaeter neben dem Kreis
    sein, daher schieben wir den Quader etwas
    nach links
    Die Translate erhaelt einen Vektor aus dem
    R^3 und verschiebt den Ursprung um diesen,
    dabei legt sie die Translationsmatrix auf
    den Stapel*/
    /* d fuer double */
    glTranslated(-0.4, 0.0, 0.0);

    /*Festlegen, was wir fuer ein Objekt zeichnen
    wollen, es gibt viele Typen!*/
    glBegin(GL_LINE_LOOP);
    /*Und es werde farbig, Werte zwischen 0 und 1
    nachdem RGB Schema*/
    glColor3f(0.8, 0.0, 0.0);
    glVertex2f(-0.25, -0.25);
    glColor3f(0.0, 0.0, 0.8);
    glVertex2f(-0.25, 0.25);
    glColor3f(0.0, 0.8, 0.0);
    glVertex2f(0.25, 0.25);
    glColor3f(0.4, 0.4, 0.0);
    glVertex2f(0.25, -0.25);

    /*fertig mit dem ersten Objekt*/
    glEnd();

    /*Obere Matrix vom Stapel runter, damit wir wieder
    den alten Ursprung als Ursprung haben*/
    glPopMatrix();

    /*Und das zweite Objekt!
    Nun etwas komplexer, ein Kreis!*/

    glPushMatrix();
    glTranslated(0.4, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.2, 0.2);
    glVertex2f(0.0, 0.0);
    for (i = 0; i <= pieces; i++) {
        glColor3f(0.8, 0.8, 0.8);
        glVertex2f(radius * cos(2.0 * M_PI * i / pieces), radius * sin(2.0 * M_PI * i / pieces));
    }
    glEnd();
    glPopMatrix();


    /*Erzwingen des Zeichnens, damit die Anweisungen
	nicht nur im Speicher verschwinden.
	Abwarten bis alles gezeichnet wurde */
    glFlush();

    /*Optional, wird erst fuer Animationen, mit vielen
	Objekten zum Neuzeichnen notwendig, damit
	Bewegungen fluessig ablaufen koennen*/
    glutSwapBuffers();

}


int
main(int argc, char **argv) {
    /*argc zaehlt die zusaetzlich zum Aufruf
    der Funktion einengebenen Daten
    argv sind die zusaetzlichen Daten */

/****************************************
Grundsaetzliches Erstellen eines Fensters
****************************************/

    /*Initialisieren von Glut, moegliche Daten
    werden an Freeglut uebergeben*/
    glutInit(&argc, argv);

    /*Erstellen eines Fensters*/
    glutCreateWindow("Hello Freeglut!");

    /*Position des Fensters in Pixeln von der
    obenen linken Ecke des Bildschirms ausgehend*/
    glutPositionWindow(150, 100);

    /*Groeße des Fensters in Pixeln*/
    glutReshapeWindow(300, 300);

/*****************************************
Freeglut Callback-Funktionen fuer den 
				Inhalt
******************************************/

    /*Zum Erstellen des Hintergrunds, einrichten
    der Perspektive */
    glutReshapeFunc(reshape);

    /*Zum Erstellen des Fensterinhalts, was soll
    dargestellt werden?*/
    glutDisplayFunc(display);

/*****************************************
			Start von Freeglut
******************************************/
    /*Startet die Glutanwendung, ab jetzt
    werden die Funktionsaufrufe von Freeglut
    verwaltet!
    Diese Funktion steht immer am Schluss
    der Mainfunktion*/
    glutMainLoop();

    return 0;
}
