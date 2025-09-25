#ifndef NR_WRAP_H
#define NR_WRAP_H

#include <math.h>
#include <windows.h>

/* Rename only inside Numerical Recipes headers */
#define fmin   nr_fmin
#define select nr_select
#include "nr.h"
#undef fmin
#undef select

#include "nrutil.h"

#endif
