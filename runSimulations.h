#ifndef __INCLUDES__
#define __INCLUDES__
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#endif

#ifndef __RUNSIMULATIONS_H
#define __RUNSIMULATIONS_H
#include "queue.h"
/*#include "signals.h"*/
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <time.h>

extern void runOneSimulation(int, int, int, int,gsl_rng *, float[]);
/*extern void addCar(int, LINE **, gsl_rng *);
 * extern void removeCar(LINE **, LINE **, SIGNALS **, gsl_rng *);*/

#endif

                                                                                                   
