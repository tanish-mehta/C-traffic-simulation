#include "runSimulations.h"

int main(int argc, char *argv[]) {

  if(argc != 5) {
     fprintf(stderr, "Wrong number of parameters\n");
     exit(0);
  }

  /*Assigning the inputted parameters to variables*/
  int leftCarRate = atoi(argv[1]);
  int rightCarRate = atoi(argv[2]);
  int leftSignalTime = atoi(argv[3]);
  int rightSignalTime = atoi(argv[4]);

  if(leftCarRate<=0 || rightCarRate<=0 || leftSignalTime<1 || rightSignalTime<1){
    fprintf(stderr, "Signal times have to be greater than 1. And arrival rates have to be greater than zero.\n");
    exit(0);
  }

  /* Initialisation of random number generator*/
  const gsl_rng_type *T;
  gsl_rng *r;
  gsl_rng_env_setup();
  T = gsl_rng_default;
  r = gsl_rng_alloc(T);
  gsl_rng_set(r,time(0));

  /*Array to store the results*/
  float individualResult[8]={0};
  int i;
  for (i=0; i<100; i++)
  {
     runOneSimulation(leftSignalTime,rightSignalTime,leftCarRate,rightCarRate, r, individualResult);
  }

  gsl_rng_free(r);

  int j;
  for(j=0;j<8;j++){
    individualResult[j]=individualResult[j]/(float)100.0;
  }
  printf("\nParameter Values:\n    from left:\n       traffic arrival rate: %d\n       traffic light period: %d\n    from right:\n       traffic arrival rate: %d\n       traffic light period: %d\nResults(averaged over 100 runs)\n    from left:\n        number of vehicles: %.0f\n        average waiting time: %.2f\n        maximum waiting time: %.0f\n        clearance time: %.0f\n    from right:\n        number of vehicles: %.0f\n        average waiting time: %.2f\n        maximum waiting time: %.0f\n        clearance time: %.0f\n", leftCarRate,leftSignalTime, rightCarRate,rightSignalTime, individualResult[0], individualResult[1],individualResult[2],individualResult[3],individualResult[4], individualResult[5],individualResult[6],individualResult[7]);
  return 0;
}

extern void runOneSimulation(int leftSignalTime,int rightSignalTime,int leftCarRate,int rightCarRate,
gsl_rng *r,float individualResult[]){

  /*queue variables*/
  int rightQueueClearTime = 0;
  int leftQueueClearTime = 0;
  int leftNumVehicles = 0;
  int rightNumVehicles = 0;
  int leftAllWaitTimes = 0;
  int rightAllWaitTimes = 0;
  int leftMaxWaitTime = 0;
  int rightMaxWaitTime = 0;

  /*Signal states*/
  int leftSignal=1;
  int rightSignal=0;

  /*To keep track of the time remaining in each period of a green signal*/
  int leftTimeRemaining = leftSignalTime;
  int rightTimeRemaning = rightSignalTime;

  /*Variable to make calculation easier*/
  int inQueue=0;
  int calcLeftClearTime=0;
  int calcRightClearTime=0;

  /*To store the random number*/
  double randomRate=0;
  /*Making the rate of car arrival a number between 0 and 1*/
  double leftRateTens= (double)leftCarRate/(double)100;
  double rightRateTens= (double)rightCarRate/(double)100;

  /*To keeep track of iterations in the while loop*/
  int tyme=0;

  /*To make the queues of cars on the road*/
  QUEUE *leftQueue = newQueue();
  QUEUE *rightQueue = newQueue();

    while(((leftQueue->head!=NULL)||(rightQueue->head!=NULL))||tyme<500){

      /*vehicle is added to the queue*/
      if(tyme<500){
        /*generating random number*/
        gsl_rng_set(r,time(0));
        randomRate=gsl_rng_uniform_pos(r);
        /*adding a vehicle to queue if the generated number is smaller than the rate of arrival of a vehicle*/
        if (randomRate<leftRateTens){
          enqueue(leftQueue,tyme);
        }
        /* Performing same functionality for the queue on the right road*/
        if(randomRate < rightRateTens){
          enqueue(rightQueue, tyme);
        }
        /*for testing
        printf("log:%d rog:%d l:%f r:%f rand:%f\n",leftCarRate,rightCarRate,leftRateTens,rightRateTens,randomRate);*/
      }

      /*signal handling. 0=red, 1=green*/
      if(leftSignal==1){
        CAR *car=dequeue(leftQueue);
        if(car!=NULL){
        inQueue=tyme-(car->initialisationTime);
          leftAllWaitTimes+=inQueue;
          leftMaxWaitTime=(inQueue>leftMaxWaitTime)?inQueue:leftMaxWaitTime;
          leftNumVehicles++;
          free(car);}
        if(--leftTimeRemaining==0){
          tyme++;
          leftSignal=0;
          leftTimeRemaining=leftTimeRemaining+leftSignalTime;
          rightSignal=1;
        }
      }
      else if(rightSignal==1){
        CAR *car=dequeue(rightQueue);
        if(car!=NULL){
          inQueue=tyme-(car->initialisationTime);
          rightAllWaitTimes+=inQueue;
          rightMaxWaitTime=(inQueue>rightMaxWaitTime)?inQueue:rightMaxWaitTime;
          rightNumVehicles++;
          free(car);
        }
        if(--rightTimeRemaning==0){
          tyme++;
          rightSignal=0;
          rightTimeRemaning=rightTimeRemaning+rightSignalTime;
          leftSignal=1;
        }
      }


    /*Calculate time it takes for all cars to exit the queue after 500 iterations*/
    if(tyme>=499){
              if(leftQueue->head==NULL && leftQueueClearTime==0){
                  leftQueueClearTime=tyme-500;
              }
              if(rightQueue->head==NULL && rightQueueClearTime==0){
                  rightQueueClearTime=tyme-500;
              }
          }
    tyme++;
    }
    individualResult[0] += leftNumVehicles;
    float temp=(float)(leftAllWaitTimes)/(float)(leftNumVehicles);
    individualResult[1] += temp;
    individualResult[2] += leftMaxWaitTime;
    individualResult[3] += leftQueueClearTime;
    individualResult[4] += rightNumVehicles;
    individualResult[5] += ((float) rightAllWaitTimes /(float)rightNumVehicles);
    individualResult[6] += rightMaxWaitTime;
    individualResult[7] += rightQueueClearTime;
    free(leftQueue);
    free(rightQueue);
  }

     
