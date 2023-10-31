#include <stdlib.h>
#include <stdio.h>

typedef struct Question Question;
Question *createQuestion(char *q, char *topic, char *difficulty);
void freeQuestion(Question *question);

typedef struct DynamicArray DynamicArray;
DynamicArray *createDynamicArray(int capacity);
void pushDynamicArray(Question *data, DynamicArray *array);
Question *getDynamicArray(int index, DynamicArray *array);
void printDynamicArray(DynamicArray *array);
void freeDynamicArray(DynamicArray *array);
