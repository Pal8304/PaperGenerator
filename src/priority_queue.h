#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/stat.h>

typedef struct Pair Pair;
Pair *createPair(int index, int frequency);
typedef struct PriorityQueue PriorityQueue;
PriorityQueue *createPriorityQueue(int capacity);
void freePriorityQueue(PriorityQueue *pq);
void swap(Pair *a, Pair *b);
void heapifyPriorityQueue(PriorityQueue *pq, int ind);
void insertPriorityQueue(PriorityQueue *pq, Pair *data);
bool isEmpty(PriorityQueue *pq);
Pair *popPriorityQueue(PriorityQueue *pq);
void serializePriorityQueue(PriorityQueue *pq, char *name);
PriorityQueue *deserializePriorityQueue(char *name);
void printPriorityQueue(PriorityQueue *pq);
bool fileExists(const char *fileName);
