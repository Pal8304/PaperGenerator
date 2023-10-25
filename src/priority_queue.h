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
Pair topPriorityQueue(PriorityQueue *pq);
void deserializePriorityQueue(PriorityQueue *pq, char *name);
PriorityQueue *serializePriorityQueue(char *name);
void printPriorityQueue(PriorityQueue *pq);
bool fileExists(const char *fileName);

#ifdef PRIORITY_QUEUE_IMPLEMENTATION

typedef struct Pair
{
    int index;
    int frequency;
} Pair;

Pair *createPair(int index, int frequency)
{
    Pair *pair = (Pair *)malloc(sizeof(Pair));
    pair->index = index;
    pair->frequency = frequency;
    return pair;
}

typedef struct PriorityQueue
{
    Pair **array;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue *createPriorityQueue(int capacity)
{
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->capacity = capacity;
    pq->size = 0;
    pq->array = (Pair **)malloc(sizeof(Pair *) * capacity);
    return pq;
}

void freePriorityQueue(PriorityQueue *pq)
{
    for (int i = 0; i < pq->size; ++i)
    {
        free(pq->array[i]);
    }
    free(pq->array);
    free(pq);
}

void swap(Pair *a, Pair *b)
{
    Pair temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyPriorityQueue(PriorityQueue *pq, int ind)
{
    int left = 2 * ind + 1;
    int right = 2 * ind + 2;
    int smallest = ind;
    if (left < pq->size && pq->array[left]->frequency < pq->array[smallest]->frequency)
    {
        smallest = left;
    }
    if (right < pq->size && pq->array[right]->frequency < pq->array[smallest]->frequency)
    {
        smallest = right;
    }
    if (smallest != ind)
    {
        swap(pq->array[ind], pq->array[smallest]);
        heapifyPriorityQueue(pq, smallest);
    }
}

// Insertion in Priority Queue
void insertPriorityQueue(PriorityQueue *pq, Pair *data)
{
    if (pq->size == pq->capacity)
    {
        printf("ERROR: Unable to insert into PriorityQueue, overflow!");
        exit(1);
    }
    int i = pq->size;
    pq->array[i] = data;
    pq->size++;
    while (i > 0 && pq->array[i]->frequency < pq->array[(i - 1) / 2]->frequency)
    {
        swap(pq->array[i], pq->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Check if pq is empty
bool isEmpty(PriorityQueue *pq)
{
    return (pq->size == 0);
}

// Get top element and pop operation
Pair topPriorityQueue(PriorityQueue *pq)
{
    if (pq->size <= 0)
    {
        printf("Empty\n");
        Pair empty = {0, 0};
        return empty;
    }
    if (pq->size == 1)
    {
        pq->size--;
        return *pq->array[0];
    }
    Pair root = *pq->array[0];
    pq->array[0] = pq->array[pq->size - 1];
    pq->size--;
    heapifyPriorityQueue(pq, 0);
    return root;
}

const char *sep = "\n";
void deserializePriorityQueue(PriorityQueue *pq, char *name)
{
    FILE *fp;
    char *filePath = NULL;
    asprintf(&filePath, "%s.pq.txt", name);
    fp = fopen(filePath, "w");
    free(filePath);

    fprintf(fp, "%d%s", pq->capacity, sep);
    fprintf(fp, "%d%s", pq->size, sep);
    for (int i = 0; i < pq->size; ++i)
    {
        fprintf(fp, "%d %d", pq->array[i]->index, pq->array[i]->frequency);
        fprintf(fp, sep);
    }
    fclose(fp);
}

PriorityQueue *serializePriorityQueue(char *name)
{
    FILE *fp;
    char *filePath = NULL;
    asprintf(&filePath, "%s.pq.txt", name);
    fp = fopen(filePath, "r");
    if (!fileExists(filePath))
    {
        printf("INFO: PQ FILE DOESN'T EXIST\n");
        free(filePath);
        PriorityQueue *pq = createPriorityQueue(75);
        DynamicArray *questions = getQuestionsDifficulty(name);
        printf("INFO: Creating priority queue of size: %d\n", questions->size);
        for (int i = 0; i < questions->size; ++i)
        {
            insertPriorityQueue(pq, createPair(i, 0));
        }
        freeDynamicArray(questions);
        deserializePriorityQueue(pq, name);
        return pq;
    }
    free(filePath);

    printf("INFO: Reading pq file...\n");
    int capacity, size;
    fscanf(fp, "%d", &capacity);
    fscanf(fp, "%d", &size);
    printf("INFO: PQ capacity read: %d, size read: %d\n", capacity, size);
    PriorityQueue *pq = createPriorityQueue(capacity);
    for (int i = 0; i < size; ++i)
    {
        int index, frequency;
        fscanf(fp, "%d %d", &index, &frequency);
        Pair *pair = createPair(index, frequency);
        insertPriorityQueue(pq, pair);
    }
    return pq;
}

void printPriorityQueue(PriorityQueue *pq)
{
    printf("INFO: Size: %d\n", pq->size);
    printf("INFO: Capacity: %d\n", pq->capacity);
    for (int i = 0; i < pq->size; ++i)
    {
        printf("INFO: Pair at index `%d` : `{%d, %d}`\n", i, pq->array[i]->index, pq->array[i]->frequency);
    }
}

bool fileExists(const char *fileName)
{
    struct stat buffer;
    return stat(fileName, &buffer) == 0 ? true : false;
}

#endif
