//(c) 2015 Kelly Wang
//CS 432 Operating Systems
//Duane Bailey

//Implementation for a hash table
//look up external chaining
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "cirq.h"
#include "hash.h"

typedef struct pair *p;

//a key value pair
struct pair {
  char *k; 
  void *v; 
};

//allocate memory and initialize values
hash ht_alloc(int buckets){
  hash h = (struct hashTable*)malloc(sizeof(struct hashTable)); 
  h->table = (cirq*)calloc(buckets, sizeof(cirq)); //allocate one cirq per number of buckets

  h->size = buckets; 
  return h;
} 

//add a key value pair
void ht_put(hash h, char *key, void *value){
  printf("ht_put entered\n");
  int index;
  index = locate(h, key);//hash function to map key to its bucket  
  printf("hash code index=%d\n", index);
  cirq q = (h->table)[index];
  
  if((h->table)[index] == 0){ //if hash table empty at that slot allocate it
    printf("SPECIAL CASE entered\n");
    (h->table)[index] = cq_alloc(); //store a pointer to an allocated cirq at index
    printf("reached cq_alloc\n");
  } 

  printf("outside the SPECIAL CASE\n");
  //here: make sure kv doesn't already exist
   
  if (find(q, key)){
    printf("IF key already exists\n");
    p kv = (*q)->data;
    kv->k = key;
    kv->v = value;
    
    } else { 
    //    printf("ELSE key doesn't exist\n");
    p kv = (p)malloc(sizeof(struct pair));
    kv->k = key;
    kv->v = value;
    printf("queue%d:\n", cq_size(q));
    cq_enq(q, kv); //enq the kv at the cirq at index 
    printf("here\n");
  } //else
  printf("HERE?!???\n");
} 

void *ht_get(hash h, char *key){
  int index;
  index = locate(h, key);

  cirq q = (h->table)[index];
  if (find(q, key)) { //if key is found, return the corres value
    p kv = (*q)->data;
    void *value = kv->v; //since we rotated the cirq, q now points to the element w/ the matching key
    return value;
  } else {
    return 0;
  } 
  //return result; //return the actual value of the pair
} 

//return all space allocated by table
void ht_free(hash h){
  int i;
  for (i = 0; i < h->size; i++) { 
    if ((h->table)[i] != 0) {
      cq_free((h->table)[i]);
    }  
  }
  free(h->table);
  free(h);
  
  //go through buckets and cq_free everything if its not an empty slot
  //then free the pointer to the hashtable etc...make sure frees match the allocs
} 

int find(cirq q, char *key) {
  printf("find entered\n");
  int i;
  printf("size of q:%d\n", cq_size(q));
  /*

    WHY DOES IT BREAK HERE????

   */

  //iterate through the cirq in one bucket
  //return 1 if find a matching key
  for (i = 0; i < cq_size(q); i++){
    
    p kv = (*q)->data;
    if (strcmp(kv->k, key)) { //found
      return 1;
      
    } else { //not found
      cq_rot(q);
      //q = q->next;
    }
  }
  return 0; //return result?
}

//locate computes the hash function which is for now, sum of ascii values of characters in the key
int locate(hash h, char *key){
  int result;
  result = 0;
  int s;
  s = h->size;
  while (*key != '\0') {
    //printf("%d mod %d = %d\n", (result + *key), s, (result+*key)%s);
    result = (result + *key) % s; //what if its negative??
    //printf("the result =%d, the key=%d\n", result, *key);
    key++;
    //printf("next key:%d\n", *key);
  }
  return result;
}

//int main(int argc, char **argv) {
//  return 0;
//}

//number of elements to add, size in bytes of an element, allocated memory is filled with 0's
//(cirq)calloc(sizeof(element*), 1);
