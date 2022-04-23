#include "queue.h"

/*Creates a new car to add to the queue*/
extern CAR *node(int initialisationTime){
   if(initialisationTime<-1)
   {
      fprintf(stderr, "Time parameter is nor valide: %s: %d\n",__FILE__, __LINE__);
      exit(0);
   }
   CAR *a=(CAR *)malloc(sizeof(CAR));
   if(a== NULL)
   {
      fprintf(stderr, "Memory allocation error: %s: %d\n",__FILE__, __LINE__);
      exit(0);
   }

   a->initialisationTime = initialisationTime;
   a->next= NULL;
   return a;
}

/*Create queue with null values*/
extern QUEUE* newQueue(){
   QUEUE *a=(QUEUE*)malloc(sizeof(QUEUE));

   if (a==NULL)
   {
      fprintf(stderr, "Memory allocation error: %s: %d\n",__FILE__, __LINE__);
      exit(0);
   }
   a->head=NULL;
   a->tail=NULL;
   return a;
}

/* Remove a vehicle from the queue*/
extern CAR *dequeue(QUEUE *queue){
   /*check if there are any vehicles left in the queue*/
   if(queue->head==NULL)
   {
        return NULL;
   }

   CAR *passedCar=queue->head;
   queue->head=queue->head->next;

   if (queue->head==NULL){
      queue->tail=NULL;
   }
      return passedCar;
}


/*Add a vehicle to the queu*/
extern void enqueue(QUEUE *l, int time){
   CAR *new=node(time);
   if(l->tail==NULL){
      l->tail=new;
      l->head=new;
      return;
   }
   l->tail->next= new;
   l->tail=new;
}
