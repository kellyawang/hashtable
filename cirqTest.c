#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cirq.h"

int main(int argc, char **argv) {
  printf("test main started\n");
  //test cq_alloc
  cirq q = cq_alloc();
  
  //test cq_size
  int size = cq_size(q);
  printf("size of the cirq:%d\n", size);
  
  //cq_enq
  cq_enq(q, "apples");
  size = cq_size(q);
  printf("size of the cirq:%d\n", size);
  
  cq_enq(q, "bananas");
  int one = 1;
  cq_enq(q, &one);
  int two = 2;
  cq_enq(q, &two);
  int three = 3;
  cq_enq(q, &three);
  int four = 4;
  cq_enq(q, &four);
  int five = 5;
  cq_enq(q, &five);

  size = cq_size(q);
  printf("size of the cirq:%d\n", size);

  //*cq_peek
  printf("peek:%s\n", (char*)cq_peek(q));

  //*cq_deq
  printf("deq apples?%s.\n", (char*)cq_deq(q));
  printf("deq bananas?%s.\n", (char*)cq_deq(q));
  printf("deq 1: %d\n", *((int*)cq_deq(q)));
  printf("deq 2: %d\n", *((int*)cq_deq(q)));
  printf("deq 3: %d\n", *((int*)cq_deq(q)));
  printf("deq 4: %d\n", *((int*)cq_deq(q)));
  printf("deq 5: %d\n", *((int*)cq_deq(q)));
  
  //cq_rot
 
  //cq_free
  printf("test free:\n");
  size = cq_size(q);
  printf("size before freeing:%d\n", size);  
  cq_free(q);
  printf("size after freeing:%d\n", size);  
  // size = cq_size(q);
  //printf("size of the cirq after freeing:%d\n", size);


  return 0;
}
