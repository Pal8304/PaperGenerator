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

  DynamicArray *questionPaper = createDynamicArray(questionCount);
  for (int i = 0; i < easy; ++i)
  {
    Pair *p = popPriorityQueue(easyPriorityQueue);
    pushDynamicArray(getDynamicArray(p->index, easyQuestions), questionPaper);
    p->frequency += 1;
    insertPriorityQueue(easyPriorityQueue, p);
  }
  for (int i = 0; i < medium; ++i)
  {
    Pair *p = popPriorityQueue(mediumPriorityQueue);
    pushDynamicArray(getDynamicArray(p->index, mediumQuestions), questionPaper);
    p->frequency += 1;
    insertPriorityQueue(mediumPriorityQueue, p);
  }
  for (int i = 0; i < hard; ++i)
  {
    Pair *p = popPriorityQueue(hardPriorityQueue);
    pushDynamicArray(getDynamicArray(p->index, hardQuestions), questionPaper);
    p->frequency += 1;
    insertPriorityQueue(hardPriorityQueue, p);
  }

  for (int i = 0; i < questionPaper->size; ++i)
  {
    Question *question = getDynamicArray(i, questionPaper);
    printLeftRight(question->question, question->difficulty, 0);
  }

  deserializePriorityQueue(easyPriorityQueue, "easy");
  deserializePriorityQueue(mediumPriorityQueue, "medium");
  deserializePriorityQueue(hardPriorityQueue, "hard");

  freePriorityQueue(easyPriorityQueue);
  freePriorityQueue(mediumPriorityQueue);
  freePriorityQueue(hardPriorityQueue);

  freeDynamicArray(easyQuestions);
  freeDynamicArray(mediumQuestions);
  freeDynamicArray(hardQuestions);

  return 0;
}
