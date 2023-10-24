#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "priorityq.h"

int main(void)
{
  // PriorityQueue *pq = createPriorityQueue(100);
  // Pair test1 = {1, 5};
  // Pair test2 = {0, 10};
  // Pair test3 = {3, 1};
  // insert(pq, test1);
  // insert(pq, test2);
  // insert(pq, test3);
  // for (int i = 0; i < 3; i++)
  // {
  //   Pair top = gettop(pq);
  //   printf("(%d, %d)\n", top.first, top.second);
  // }
  // free(pq->array);
  // free(pq);

  DynamicArray *array = getQuestionsDifficulty("easy");
  printDynamicArray(array);

  printf("%s\n", getDynamicArray(5, array));

  freeDynamicArray(array);

  return 0;
}
