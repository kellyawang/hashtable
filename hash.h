//(c) 2015 Kelly Wang
//CS 432 Operating Systems
//Duane Bailey

//Header file for hash table
#include "cirq.h"

#ifndef HASH_H
#define HASH_H
typedef struct hashTable *hash;// hashTable pointer

struct hashTable {
  int size; //number of buckets in the hash table
  cirq *table;//array of circular queues (pointers...)
  
};

extern hash ht_alloc(int buckets);// allocate a hash table
extern void ht_put(hash h, char *key, void *value);// add a key/value pair
extern void *ht_get(hash h, char *key);// get a value based on key
extern void ht_free(hash h);// return all space allocated by table

extern int find(cirq q, char *key); //whether or not bucket already contains a given key
extern int locate(hash h, char *key); //compute hash function given a key
#endif
/*
 The linear-probing approach causes us to wrap around the array and find the next available slot.

 */
