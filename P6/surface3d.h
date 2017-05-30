
#ifndef SURFACE3D_H
#define SURFACE3D_H

#include "basic.h"

/* Three dimensional surface representation */
typedef struct _surface3d surface3d;

typedef surface3d *psurface3d;

struct _surface3d {
  /* Number of vertices */
  int vertices;
  /* Number of edges */
  int edges;
  /* Number of triangles */
  int triangles;

  /* Vertex coordinates */
  real (*x)[3];
  /* Edge vertices */
  int (*e)[2];
  /* Triangle vertices, counter-clockwise */
  int (*t)[3];
  /* Triangle edges, s[i][j] opposite t[i][j] */
  int (*s)[3];

  /* Normal vectors */
  real (*n)[3];

  /* Minimal mesh size */
  real hmin;
  /* Maximal mesh size */
  real hmax;
};

/* ------------------------------------------------------------
 * Constructor and destructor
 * ------------------------------------------------------------ */
psurface3d
new_surface3d(int vertices, int edges, int triangles);

/* Computes the normal vectors and the minimal and maximal mesh size. */
void
prepare_surface3d(psurface3d gr);

void
del_surface3d(psurface3d gr);

/* ------------------------------------------------------------
 * File I/O
 * ------------------------------------------------------------ */
/* Read geometrical information of a surface mesh from a given file
 * using the following ascii representation.
 *
 * The file format is the following:<br><br>
 * <code>
 * {vertices} {edges} {triangles}<br>
 * {x[0][0]} {x[0][1]} {x[0][2]}<br>
 * ...<br>
 * {x[{vertices}-1][0]} {x[{vertices}-1][1]} {x[{vertices}-1][2]}<br>
 * {e[0][0]} {e[0][1]}<br>
 * ...<br>
 * {e[{edges}-1][0]} {e[{edges}-1][1]}<br>
 * {t[0][0]} {t[0][1]} {t[0][2]}
 * {s[0][0]} {s[0][1]} {s[0][2]}<br>
 * ...<br>
 * {t[{triangles}-1][0]} {t[{triangles}-1][1]} {t[{triangles}-1][2]}
 * {s[{triangles}-1][0]} {s[{triangles}-1][1]} {s[{triangles}-1][2]}<br>
 * </code>
 */
psurface3d
read_surface3d(const char *filename);

#endif
