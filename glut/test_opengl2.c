/*-------------------------------------
	     Freeglut Einführung 2
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

/*			Motion		*/
static int old_position_x, old_position_y;
static float angle_x = 0.0;
static float angle_y = 0.0;
static float old_angle_x, old_angle_y;

float angle = 0.0;


static void
reshape(int width, int height) {
    GLfloat p[4], a[4], d[4];

    glViewport(0, 0, width, height);

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
    gluPerspective(35.0, 1.0, 1.0, 30.0);

    /*Verschieben des Standpunkts zur besseren
    Betrachtung*/
    /* f fuer float*/
    glTranslatef(0.0, 0.0, -10.0);


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

}


static void
display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    /* Hintergrundfarbe */
    glClearColor(0.0, 0.0, 0.0, 1.0);

    /*Umsetzten der Bewegungen aus der Motion*/
    glRotatef(angle_x, 1.0, 0.0, 0.0);
    glRotatef(angle_y, 0.0, 1.0, 0.0);

    /*Umsetzen der Bewegung aus der timer*/
    glRotatef(angle, 0.0, 1.0, 0.0);


    glColor3f(0.0, 0.2, 0.6);

    /*Die Glut-Funktion =)*/
    glutSolidTeapot(0.5);

    glPopMatrix();
    glPushMatrix();

    glRotatef(angle, 0.0, 1.0, 0.0);

    glTranslatef(2.0, 0.0, 0.0);
    glColor3f(0.8, 0.0, 0.0);

    /*Erstellen einer Netzkugel
    Paramter:
    Radius, Anzahl horizontale und vertikale
    Kreise*/
    glutWireSphere(0.3, 10, 20);


    glPopMatrix();

    glFlush();
    glutSwapBuffers();

}

/*Registriert, wenn ein Mousebutton genutzt wird,
button gibt dabei an, welcher button (left, middle
and right), state registriert ob er gedrueckt oder
losgelassen wird und die letzten beiden sind fuer
die Postition der der Mouse*/
static void
mouse(int button, int state, int position_y, int position_x) {

    (void) button;
    (void) state;

    /*Ersetzten der alten Positionen durch die neu
    ermittelten*/
    old_position_x = position_x;
    old_position_y = position_y;

    old_angle_x = angle_x;
    old_angle_y = angle_y;
}

static void
motion(int position_y, int position_x) {


    /*Bestimmung des noetigen Winkels zur Umsetzung
    der, mit der Mouse durchgefuehrten, Bewegung*/
    angle_x = old_angle_x + (position_x - old_position_x);
    angle_y = old_angle_y + (position_y - old_position_y);

    /*sorgt dafuer, dass die display wieder aufgerufen
    wird und damit die Veraenderungen gezeichnet*/
    glutPostRedisplay();
}


/*Funktion zur stetigen Aktualisierung des Fensters */
static void
timer(int value) {

    /*wegen -Wextra*/
    (void) value;

    /*Winkel um den wir die Obejkte drehen wollen*/
    angle += 2.0f;
    /*Um nicht unnoetig große Winkel nach einer
    360° Runde zu bekommen*/
    if (angle > 360) {
        angle -= 360;
    }

    glutPostRedisplay();

    /*Die Finktion ruft sich selbst wieder auf,
    damit die Bewegung erneut durchgefuehrt werden
    kann!!*/
    glutTimerFunc(10, timer, 0);
}


/*Umsetzen von vorher festgelegten Tastenaufrufen
dabei werden einmal die Taste und die Position
der Mouse an die Funktion uebergeben*/
static void
key(unsigned char key, int x, int y) {


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
            break;
        default :
            break;
    }

}


int
main(int argc, char **argv) {

    glutInit(&argc, argv);
    glutCreateWindow("Rolling Teaparty XD");
    glutPositionWindow(150, 100);
    glutReshapeWindow(300, 300);

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    /*Zur Ermitterlung der Bewegungen
    der Mouse ueber dem GlutFenster*/
    glutMouseFunc(mouse);

    /*Zum Umsetzten der Bewegung der
    Maus in eine Bewegung im Bild*/
    glutMotionFunc(motion);

    /*Zur Umsetzung von vorher festgelegten
    Befehlen ueber die Tastatur*/
    glutKeyboardFunc(key);

    /*Zur Neuberechnung von Werten.
    Erhaelt die Millisekunden bis zum
    Aufruf, die Callback-Funktion und
    einen variablen Wert fuer komplexere
    Callback-Funktionen*/
    glutTimerFunc(50, timer, 0);

    glutMainLoop();

    return 0;
}
