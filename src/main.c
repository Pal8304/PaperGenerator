#include <stdio.h>
#include <stdlib.h>

#define UTILS_IMPLEMENTATION
#include "util.h"

#define PRIORITY_QUEUE_IMPLEMENTATION
#include "priority_queue.h"

int main(void)
{
  printCentered("---Welcome to Paper Generator!---");

  int questionCount;
  printf("Enter the number of questions for this paper: ");
  scanf("%d", &questionCount);

  int easy, medium, hard;
  printf("Enter the number of easy, medium and hard questions respectively: ");
  scanf("%d %d %d", &easy, &medium, &hard);

  int total = easy + medium + hard;
  if (total != questionCount)
  {
    printf("ERROR: The sum of easy, medium and hard questions should be equal to the total number of questions.\n");
    return 1;
  }

  DynamicArray *easyQuestions = getQuestionsDifficulty("easy");
  DynamicArray *mediumQuestions = getQuestionsDifficulty("medium");
  DynamicArray *hardQuestions = getQuestionsDifficulty("hard");

  PriorityQueue *easyPriorityQueue = serializePriorityQueue("easy");
  PriorityQueue *mediumPriorityQueue = serializePriorityQueue("medium");
  PriorityQueue *hardPriorityQueue = serializePriorityQueue("hard");

  printDynamicArray(easyQuestions);
  printf("%d\n", easyQuestions->size);

  freePriorityQueue(easyPriorityQueue);
  freePriorityQueue(mediumPriorityQueue);
  freePriorityQueue(hardPriorityQueue);

  freeDynamicArray(easyQuestions);
  freeDynamicArray(mediumQuestions);
  freeDynamicArray(hardQuestions);

  return 0;
}
