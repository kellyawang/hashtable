//(c) 2015 Kelly Wang
//CS 432 Operating Systems
//Duane Bailey

//Implementation for the circular queue

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cirq.h"

//allocate a pointer; pointer= 8bytes; malloc allocates space in memory given the size of struct element*;but returns a pointer to it so need to cast it as (struct element**) which is just a cirq; cirq = element**
cirq cq_alloc(void){ 
  cirq result = (cirq)malloc(sizeof(struct element*));  
  *result = 0; 
  return result;
  
  /* OR:
  return (cirq)calloc(1, sizeof(struct element*)); //returns a pointer to allocated memory
  */

} 

int cq_size(cirq q){
  int size;
  size = 0;
  if (*q == 0) {
    return 0;
    
  } else {
    struct element *nextPtr;
    nextPtr = (*q)->next; 
    size++; //count the tail element

    //while the thing nextPtr points to is not the original tail, increase size
    while(nextPtr != *q) {
      size++;
      nextPtr = nextPtr->next;
    }
    return size; 
  }
}

//add element to the end
void cq_enq(cirq q, void *value){  
  if (*q == 0) {
    *q = (struct element*)malloc(sizeof(struct element**));
    (*q)->data = value; //(**q).data; attach value to the data field of the cirq, q
    (*q)->next = *q; //q is already a pointer to the tail; we attach it to the next field of the cirq, q
  
  } else {
    struct element *newTail = (struct element*)malloc(sizeof(struct element));
    newTail->data = value; //attach value to the new tail 
    newTail->next = (*q)->next; //new tail points to head 
    (*q)->next = newTail; //connect prev tail's next pointer to new tail
    *q = (*q)->next; //reconnect tail pointer to new tail
    
  }
}

//remove first element
//pre: cirq is not empty; tail ptr points to something
//post: return a void pointer
void *cq_deq(cirq q){
  struct element *tailptr;
  struct element *headptr;
  tailptr = *q;
  //printf("deq function in cirq entered\n");
  
  if(tailptr->next == tailptr) {
    void *data = tailptr->data;//the element we're deq'ing
    free(tailptr);
    *q = 0;
    return data;
  }

  if(tailptr != 0) {
    headptr = tailptr->next;//**q.next (*q)->next
    tailptr->next = tailptr->next->next;//skip over the head element
    void *data = headptr->data;//the element we're deq'ing
    //printf("if entered, tailptr not zero\n");
    free(headptr);
    //printf("after free\n");
    return data;
 
  } else {
    return 0;
  }
  
}

void *cq_peek(cirq q){
  if(*q == 0) {
    return 0; 
  } else {
    void *data = (*q)->next->data; //get the data of the "head"; tailptr's next pointer points to the head
    return data;
  }
}

void cq_rot(cirq q){
  if(*q != 0){
    *q = (*q)->next; //simply redirect tail pointer to make it point to the head; head becomes the new tail
  }
}

//free the queue's data that was allocated
void cq_free(cirq q){
  if(*q == 0) {
    free(q);
  } else {
    printf("else?\n");
    int i;
    int size;
    size = cq_size(q);
    for(i = 0; i < size; i++){
      cq_deq(q);
      
    }
    free(q);//free the struct element* pointed to by the cirq
  }
}

  //if(tailp) tailp->next; //make tail pointer skip one
  //...
  //free data from element youre getting rid of
  //return data

