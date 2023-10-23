#include<stdio.h> 
#include<stdlib.h>

typedef struct
{
    /* data */
    int first;
    int second;
}Pair;

typedef struct
{
    /* data */
    Pair* array;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->capacity = capacity;
    pq->size = 0;
    pq->array = (Pair*)malloc(sizeof(Pair) * capacity);
    return pq;
}

void swap(Pair* a, Pair* b) {
    Pair temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(PriorityQueue* pq, int ind) {
    int left = 2 * ind + 1;
    int right = 2 * ind + 2;
    int smallest = ind;
    if (left < pq->size && pq->array[left].second < pq->array[smallest].second) {
        smallest = left;
    }
    if (right < pq->size && pq->array[right].second < pq->array[smallest].second) {
        smallest = right;
    }
    if (smallest != ind) {
        swap(&pq->array[ind], &pq->array[smallest]);
        heapify(pq, smallest);
    }
}

// Insertion in Priority Queue
void insert(PriorityQueue* pq, Pair data) {
    if (pq->size == pq->capacity) {
        printf("Memory Full");
        return;
    }
    int i = pq->size;
    pq->array[i] = data;
    pq->size++;
    while (i > 0 && pq->array[i].second < pq->array[(i - 1) / 2].second) {
        swap(&pq->array[i], &pq->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

//Check if pq is empty
int Empty(PriorityQueue* pq) {
    return (pq->size == 0);
}

// Get top element and pop operation
Pair gettop(PriorityQueue* pq) {
    if (pq->size <= 0) {
        printf("Empty");
        Pair empty = { 0,0 };
        return empty;
    }
    if (pq->size == 1) {
        pq->size--;
        return pq->array[0];
    }
    Pair root = pq->array[0];
    pq->array[0] = pq->array[pq->size - 1];
    pq->size--;
    heapify(pq, 0);
    return root;
}
