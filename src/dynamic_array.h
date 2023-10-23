#include <stdlib.h>
#include <stdio.h>

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

struct DynamicArray;
struct DynamicArray *createDynamicArray(int capacity);
void freeDynamicArray(struct DynamicArray *array);

#endif

// Dynamic array of strings implementation
struct DynamicArray
{
    char **data;
    int size;
    int capacity;
};

struct DynamicArray *createDynamicArray(int capacity)
{
    struct DynamicArray *array = (struct DynamicArray *)malloc(sizeof(struct DynamicArray));
    array->data = (char **)malloc(sizeof(char *) * capacity);
    array->size = 0;
    array->capacity = capacity;
    return array;
}

void freeDynamicArray(struct DynamicArray *array)
{
    for (int i = 0; i < array->size; i++)
    {
        free(array->data[i]);
    }
    free(array->data);
    free(array);
}
