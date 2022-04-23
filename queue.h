#ifndef __INCLUDES__
#define __INCLUDES__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#endif


#ifndef __QUEUE_H
#define __QUEUE_H

typedef struct cars
{
   int initialisationTime;
   struct cars *next;
}CAR;

typedef struct queue
{
   CAR *head;
   CAR *tail;
   int finalWaitingTime;
   int carCount;
   int maxWait;
   int emptyingTime;
}QUEUE;


extern CAR *node(int);
extern QUEUE* newQueue();
extern CAR *dequeue(QUEUE *);
extern void enqueue(QUEUE *, int);

/*extern void updateStats(QUEUE *, int);
 * extern CAR *headCar(QUEUE *);
 * extern void changeStopLength(CAR *);
 * extern int hasNoCars(QUEUE **);*/


#endif
