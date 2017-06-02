
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "surface3d.h"
#include "basic.h"


/* ------------------------------------------------------------
 helper
 ------------------------------------------------------------ */
static real
sqr(real x) {
  return x * x;
}

static real 
min3(real x, real y, real z) {
  return (x < y ? (z < x ? z : x) : (z < y ? z : y));
}

static real
min(real a, real b) {
  return (a < b ? a : b);
}

static real 
max(real x, real y) {
  return (x < y ? y : x);
}


static char *
readline(char *buf, int bufsize, FILE * in, int * ln)
{
  char     *line;

  (void) bufsize;

  do {
    line = fgets(buf, 80, in);
    (*ln)++;
  } while (line && line[0] == '#');

  return line;
}

/* ------------------------------------------------------------
 Constructor and destructor
 ------------------------------------------------------------ */

psurface3d
new_surface3d(int vertices, int edges, int triangles)
{
  psurface3d gr;

  gr = (psurface3d) calloc(1, sizeof(surface3d));
  gr->x = (real(*)[3]) calloc(vertices, sizeof(real[3]));
  gr->e = (int(*)[2]) calloc(edges, sizeof(int[2]));
  gr->t = (int(*)[3]) calloc(triangles, sizeof(int[3]) );
  gr->s = (int(*)[3]) calloc(triangles, sizeof(int[3]) );
  gr->n = (real(*)[3]) calloc(triangles, sizeof(real[3]) );

  gr->vertices = vertices;
  gr->edges = edges;
  gr->triangles = triangles;

  gr->hmin = 1e30;
  gr->hmax = 0.0;

  return gr;
}

void
prepare_surface3d(psurface3d gr)
{
  const     real(*x)[3] = (const real(*)[3]) gr->x;
  const     int(*t)[3] = (const int(*)[3]) gr->t;
  real(*n)[3] = gr->n;
  real      dx[3], dy[3], dz[3];
  real      norm, height, hmin, hmax, a, b, c;
  int      triangles = gr->triangles;
  int      i;

  hmin = 1e30;
  hmax = 0.0;

  for (i = 0; i < triangles; i++) {
    dx[0] = x[t[i][1]][0] - x[t[i][0]][0];
    dx[1] = x[t[i][1]][1] - x[t[i][0]][1];
    dx[2] = x[t[i][1]][2] - x[t[i][0]][2];

    dy[0] = x[t[i][2]][0] - x[t[i][0]][0];
    dy[1] = x[t[i][2]][1] - x[t[i][0]][1];
    dy[2] = x[t[i][2]][2] - x[t[i][0]][2];

    dz[0] = x[t[i][2]][0] - x[t[i][1]][0];
    dz[1] = x[t[i][2]][1] - x[t[i][1]][1];
    dz[2] = x[t[i][2]][2] - x[t[i][1]][2];

    n[i][0] = dx[1] * dy[2] - dx[2] * dy[1];
    n[i][1] = dx[2] * dy[0] - dx[0] * dy[2];
    n[i][2] = dx[0] * dy[1] - dx[1] * dy[0];
    norm =
      SQRT(sqr(n[i][0]) + sqr(n[i][1]) + sqr(n[i][2]));
    n[i][0] /= norm;
    n[i][1] /= norm;
    n[i][2] /= norm;

    a = SQRT(sqr(dx[0]) + sqr(dx[1]) + sqr(dx[2]));
    b = SQRT(sqr(dy[0]) + sqr(dy[1]) + sqr(dy[2]));
    c = SQRT(sqr(dz[0]) + sqr(dz[1]) + sqr(dz[2]));

    height = 2.0 * min3(a, b, c);

    a *= a;
    b *= b;
    c *= c;

    height = SQRT(2 * (a * b + b * c + a * c) - (a * a + b * b + c * c))
      / height;

    hmin = min(hmin, height);
    hmax = max(hmax, height);
  }

  gr->hmin = hmin;
  gr->hmax = hmax;
}

void
del_surface3d(psurface3d gr)
{
  free(gr->n);
  free(gr->s);
  free(gr->t);
  free(gr->e);
  free(gr->x);
  free(gr);
}

/* ------------------------------------------------------------
 * Debugging
 * ------------------------------------------------------------ */


int
check_surface3d(psurface3d gr)
{
  int      vertices = gr->vertices;
  int      edges = gr->edges;
  int      triangles = gr->triangles;
  const     int(*e)[2] = (const int(*)[2]) gr->e;
  const     int(*t)[3] = (const int(*)[3]) gr->t;
  const     int(*s)[3] = (const int(*)[3]) gr->s;
  int      i, j, problems;

  problems = 0;

  for (i = 0; i < edges; i++)
    for (j = 0; j < 2; j++)
      if (e[i][j] >= vertices) {
	(void) printf(" Vertex %u in edge %u out of bounds\n", j, i);
	problems++;
      }

  for (i = 0; i < triangles; i++)
    for (j = 0; j < 3; j++) {
      if (t[i][j] >= vertices) {
	(void) printf(" Vertex %u in triangle %u out of bounds\n", j, i);
	problems++;
      }

      if (s[i][j] >= edges) {
	(void) printf(" Edge %u in triangle %u out of bounds\n", j, i);
	problems++;
      }
      else {
	if (e[s[i][j]][0] == t[i][(j + 1) % 3]) {
	  if (e[s[i][j]][1] != t[i][(j + 2) % 3]) {
	    (void) printf(" Mismatched edge %u in triangle %u\n", j, i);
	    problems++;
	  }
	}
	else {
	  if (e[s[i][j]][0] != t[i][(j + 2) % 3] || e[s[i][j]][1]
	      != t[i][(j + 1) % 3]) {
	    (void) printf(" *Mismatched edge %u in triangle %u\n", j, i);
	    problems++;
	  }
	}
      }
    }

  return problems;
}


psurface3d
read_surface3d(const char *filename)
{
  psurface3d gr;
  FILE     *in;
  
  int      vertices, edges, triangles;
  real(*x)[3];
  int(*e)[2];
  int(*t)[3];
  int(*s)[3];
  char      buf[80];
  char     *line;
  int      i, ln;

  in = fopen(filename, "r");
  
  if (in == 0) {
    (void) fprintf(stderr, "Could not open file \"%s\" for reading\n",
		   filename);
    return 0;
  }

  ln = 0;
  line = readline(buf, 80, in, &ln);

  if (line == 0 || sscanf(line, "%d %d %d", &vertices, &edges, &triangles)
      != 3) {
    (void) fprintf(stderr, "Could not read first line of file \"%s\"\n",
		   filename);

    fclose(in);

    return 0;
  }

  gr = new_surface3d(vertices, edges, triangles);
  x = gr->x;
  e = gr->e;
  t = gr->t;
  s = gr->s;

  for (i = 0; i < vertices; i++) {
    line = readline(buf, 80, in, &ln);

    if (line == 0 || sscanf(line, "%" SCANF_PREFIX "f %" SCANF_PREFIX "f %"
			    SCANF_PREFIX "f", x[i], x[i] + 1, x[i] + 2)
	!= 3) {
      (void) fprintf(stderr,
		     "Could not read vertex %u in line %u of file \"%s\"\n",
		     i, ln, filename);
      del_surface3d(gr);


      fclose(in);

    }
  }

  for (i = 0; i < edges; i++) {
    line = readline(buf, 80, in, &ln);

    if (line == 0 || sscanf(line, "%d %d", e[i], e[i] + 1) != 2) {
      (void) fprintf(stderr,
		     "Could not read edge %u in line %u of file \"%s\"\n", i,
		     ln, filename);
      del_surface3d(gr);


      fclose(in);

    }
  }

  for (i = 0; i < triangles; i++) {
    line = readline(buf, 80, in, &ln);

    if (line == 0 || sscanf(line, "%d %d %d  %d %d %d", t[i], t[i] + 1,
			    t[i] + 2, s[i], s[i] + 1, s[i] + 2)
	!= 6) {
      (void) fprintf(stderr,
		     "Could not read triangle %u in line %u of file \"%s\"\n",
		     i, ln, filename);
      del_surface3d(gr);

      fclose(in);
    }
  }

  fclose(in);
  
  prepare_surface3d(gr);

  return gr;
}
