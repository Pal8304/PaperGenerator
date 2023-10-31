#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "priority_queue.h"
#include "dynamic_array.h"

typedef struct Pair
{
    int index;
    int frequency;
} Pair;

/**
 * Creates a pair with the given data.
 *
 * @param index The index of the question.
 * @param frequency The frequency of the question.
 *
 * @return The pointer to the pair.
 */
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

/**
 * Initializes a priority queue with the given capacity.
 *
 * @param capacity The initial capacity of the priority queue.
 * @return The pointer to the priority queue.
 */
PriorityQueue *createPriorityQueue(int capacity)
{
    PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    pq->capacity = capacity;
    pq->size = 0;
    pq->array = (Pair **)malloc(sizeof(Pair *) * capacity);
    return pq;
}

/**
 * Frees the memory allocated to the priority queue.
 *
 * @param pq The pointer to the priority queue.
 */
void freePriorityQueue(PriorityQueue *pq)
{
    for (int i = 0; i < pq->size; ++i)
    {
        free(pq->array[i]);
    }
    free(pq->array);
    free(pq);
}

/**
 * Swaps the given pairs.
 *
 * @param a The pointer to the first pair.
 * @param b The pointer to the second pair.
 */
void swap(Pair *a, Pair *b)
{
    Pair temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Heapifies the priority queue. Used in pop operation.
 *
 * @param pq The pointer to the priority queue.
 * @param ind The index to start heapifying from.
 */

void heapifyPriorityQueue(PriorityQueue *pq, int ind)
{
    int left = 2 * ind + 1;
    int right = 2 * ind + 2;
    int smallest = ind;

    // Check if left child is smallest.
    if (left < pq->size && pq->array[left]->frequency < pq->array[smallest]->frequency)
    {
        smallest = left;
    }

    // Check if right child is smallest.
    if (right < pq->size && pq->array[right]->frequency < pq->array[smallest]->frequency)
    {
        smallest = right;
    }

    // If smallest is not ind, swap smallest with ind and heapify.
    if (smallest != ind)
    {
        swap(pq->array[ind], pq->array[smallest]);
        heapifyPriorityQueue(pq, smallest);
    }
}

/**
 * Inserts the given pair into the priority queue.
 *
 * @param pq The pointer to the priority queue.
 * @param data The pointer to the pair to be inserted.
 */
void insertPriorityQueue(PriorityQueue *pq, Pair *data)
{
    // Check if the queue is full
    if (pq->size == pq->capacity)
    {
        printf("ERROR: Unable to insert into PriorityQueue, overflow!");
        exit(1);
    }

    // Insert the new item at the end of the array
    int i = pq->size;
    pq->array[i] = data;
    pq->size++;

    // Swap the new item with its parent until it is no longer smaller than its parent
    while (i > 0 && pq->array[i]->frequency < pq->array[(i - 1) / 2]->frequency)
    {
        swap(pq->array[i], pq->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/**
 * Checks if the priority queue is empty.
 *
 * @param pq The pointer to the priority queue.
 * @return `true` if the priority queue is empty, `false` otherwise.
 */
bool isEmpty(PriorityQueue *pq)
{
    return (pq->size == 0);
}

/**
 * Pops the top element from the priority queue.
 *
 * @param pq The pointer to the priority queue.
 * @return The pointer to the pair popped.
 */
Pair *popPriorityQueue(PriorityQueue *pq)
{
    if (pq->size <= 0)
    {
        printf("ERROR: Cannot pop from empty priority queue.\n");
        return NULL;
    }
    if (pq->size == 1)
    {
        pq->size--;
        Pair *ret = createPair(pq->array[0]->index, pq->array[0]->frequency);
        free(pq->array[0]);
        return ret;
    }

    // remove the top element from the heap
    Pair *ret = createPair(pq->array[0]->index, pq->array[0]->frequency);
    free(pq->array[0]);
    pq->array[0] = pq->array[pq->size - 1];
    pq->size--;

    // restore the heap property
    heapifyPriorityQueue(pq, 0);
    return ret;
}

const char *sep = "\n";

/**
 * Serializes the priority queue to a file (`{name}.pq.txt`).
 *
 * @param pq The pointer to the priority queue.
 * @param name The name of the priority queue.
 */
void serializePriorityQueue(PriorityQueue *pq, char *name)
{
    FILE *fp;
    char *filePath = NULL;
    asprintf(&filePath, "%s.pq.txt", name);
    fp = fopen(filePath, "w");
    free(filePath);

    // Write the capacity and size of the priority queue.
    fprintf(fp, "%d%s", pq->capacity, sep);
    fprintf(fp, "%d%s", pq->size, sep);

    // Write each node's index and frequency.
    for (int i = 0; i < pq->size; ++i)
    {
        fprintf(fp, "%d %d", pq->array[i]->index, pq->array[i]->frequency);
        fprintf(fp, "%s", sep);
    }

    fclose(fp);
}

/**
 * Deserializes the priority queue from a file (`{name}.pq.txt`).
 *
 * @param name The name of the priority queue.
 * @return The pointer to the priority queue.
 */
PriorityQueue *deserializePriorityQueue(char *name)
{
    // Create the file path.
    FILE *fp;
    char *filePath = NULL;
    asprintf(&filePath, "%s.pq.txt", name);

    // If the file doesn't exist, create a new priority queue.
    if (!fileExists(filePath))
    {
        free(filePath);
        PriorityQueue *pq = createPriorityQueue(75);
        DynamicArray *questions = getQuestionsDifficulty(name);
        for (int i = 0; i < questions->size; ++i)
        {
            insertPriorityQueue(pq, createPair(i, 0));
        }
        freeDynamicArray(questions);
        serializePriorityQueue(pq, name);
        return pq;
    }

    fp = fopen(filePath, "r");
    // Otherwise, read the priority queue from the file.
    free(filePath);
    int capacity, size;
    fscanf(fp, "%d", &capacity);
    fscanf(fp, "%d", &size);
    PriorityQueue *pq = createPriorityQueue(capacity);
    for (int i = 0; i < size; ++i)
    {
        int index, frequency;
        fscanf(fp, "%d %d", &index, &frequency);
        Pair *pair = createPair(index, frequency);
        insertPriorityQueue(pq, pair);
    }
    fclose(fp);
    return pq;
}

/**
 * Prints the priority queue.
 *
 * @param pq The pointer to the priority queue.
 */
void printPriorityQueue(PriorityQueue *pq)
{
    printf("INFO: Size: %d\n", pq->size);
    printf("INFO: Capacity: %d\n", pq->capacity);
    for (int i = 0; i < pq->size; ++i)
    {
        printf("INFO: Pair at index `%d` : `{%d, %d}`\n",
               i, pq->array[i]->index,
               pq->array[i]->frequency);
    }
}

/**
 * Checks if the file exists.
 *
 * @param fileName The name of the file.
 * @return `true` if the file exists, `false` otherwise.
 */
bool fileExists(const char *fileName)
{
    struct stat buffer;
    return stat(fileName, &buffer) == 0 ? true : false;
}
