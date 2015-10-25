//(c) 2015 Kelly Wang
//CS 432 Operating Systems
//Duane Bailey

//Header file for circular queue (cirq)

#ifndef CIRQ_H
#define CIRQ_H

//declare a typedef
//'typedef'/ old type name/ new type name to represent it/ name of the type
//typedefs can be used to remove some of the burden of declaring structs
//save a pointer to the tail pointer, which indicates the end of the cirq

typedef struct element **cirq; // cirq now has the type struct element **; ptr to a ptr to a struct element

struct element {
  void *data; //the cirq...data is a pointer to a void thingy
  struct element *next; //pointer to the next element
};

extern cirq cq_alloc(void);// allocate a queue
extern int cq_size(cirq q);// return the size of a queue
extern void cq_enq(cirq q, void *value);// add a value to the queue
extern void *cq_deq(cirq q);// dequeue and return a queue value
extern void *cq_peek(cirq q);// return the value at the queue head
extern void cq_rot(cirq q);// requeue the head element at the tail
extern void cq_free(cirq q);// return all space allocated to queue
#endif

/*
Questions:

How do I return if cirq is empty? return 0? void *?
Deq before free data??
Do we have to free each pointer too? or just the space allocated for the data?
 */
