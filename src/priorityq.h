#include<stdio.h> 
#include<stdlib.h>

struct Pair
{
    /* data */
    int first;
    int second;
};

struct PriorityQueue
{
    /* data */
    Pair *array;
    int size;
    int capacity;
};

PriorityQueue *createPriorityQueue(int capacity){
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->capacity = capacity;
    pq->size = 0;
    pq->array = (Pair*)malloc(sizeof(Pair)*capacity);
}

void heapify(PriorityQueue *pq, int ind){
    int left = 2*ind + 1;
    int right = 2*ind + 2;
    int smallest = ind;
    if(left < pq->size && pq->array[left].second < pq->array[smallest].second){
        smallest = left;
    }
    if(right < pq->size && pq->array[right].second < pq->array[smallest].second){
        smallest = right;
    }
    if(smallest != ind){ 
        Pair temp = pq->array[ind]; //swapping unconventional
        pq->array[ind] = pq->array[smallest];
        pq->array[smallest] = temp;
        heapify(pq,smallest);
    }
}

void insert(PriorityQueue *pq, Pair data){
    if(pq->size == pq->capacity){
        printf("Memory Full");
        return;
    }
    
}