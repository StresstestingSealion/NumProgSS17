
#ifndef BASIC_H
#define BASIC_H

#include <math.h>
#include <stdbool.h>

/* ------------------------------------------------------------
 * Float type
 * ------------------------------------------------------------ */

#ifdef USE_FLOAT
typedef float real;
#define ABS(x) fabsf(x)
#define SQRT(x) sqrtf(x)
#define REAL_ASIN(x) asinf(x)
#define REAL_ACOS(x) acosf(x)
#else
typedef double real;
#define ABS(x) fabs(x)
#define SQRT(x) sqrt(x)
#define REAL_ASIN(x) asin(x)
#define REAL_ACOS(x) acos(x)
#endif

#ifdef USE_FLOAT
#define SCANF_PREFIX ""
#else
#define SCANF_PREFIX "l"
#endif

/** @brief Pointer to @ref real array. */
typedef real *preal;
/* ------------------------------------------------------------
 * Prefix for C function declarations
 * ------------------------------------------------------------ */

#ifdef __cplusplus
#define HEADER_PREFIX extern "C"
#else
#define HEADER_PREFIX
#endif

/* ------------------------------------------------------------
 * Stopwatch
 * ------------------------------------------------------------ */

typedef struct _stopwatch stopwatch;
typedef stopwatch *pstopwatch;

HEADER_PREFIX pstopwatch
new_stopwatch();

HEADER_PREFIX void
del_stopwatch(pstopwatch sw);

HEADER_PREFIX void
start_stopwatch(pstopwatch sw);

HEADER_PREFIX real
stop_stopwatch(pstopwatch sw);

#endif
