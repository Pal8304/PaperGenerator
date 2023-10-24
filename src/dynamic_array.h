#include <stdlib.h>
#include <stdio.h>

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

typedef struct DynamicArray DynamicArray;
DynamicArray *createDynamicArray(int capacity);
void pushDynamicArray(char *data, DynamicArray *array);
char *getDynamicArray(int index, DynamicArray *array);
void printDynamicArray(DynamicArray *array);
void freeDynamicArray(DynamicArray *array);

#endif

typedef struct DynamicArray
{
    char **data;
    int size;
    int capacity;
} DynamicArray;

/**
 * Initializes a dynamic array with the given capacity.
 *
 * @param capacity The initial capacity of the dynamic array.
 * @return The pointer to the dynamic array.
 */
DynamicArray *createDynamicArray(int capacity)
{
    DynamicArray *array = (DynamicArray *)malloc(sizeof(DynamicArray));
    array->data = (char **)malloc(sizeof(char *) * capacity);
    array->size = 0;
    array->capacity = capacity;
    return array;
}

/**
 * Pushes the given data to the dynamic array.
 *
 * @param data The data to be pushed to the dynamic array.
 * @param array The pointer to the dynamic array.
 */
void pushDynamicArray(char *data, DynamicArray *array)
{
    printf("INFO: Pushing `%s` to dynamic array.\n", data);
    if (array->size == array->capacity)
    {
        array->capacity *= 2;
        array->data = (char **)realloc(array->data, sizeof(char *) * array->capacity);
    }
    *(array->data + array->size++) = data;
    printf("INFO: Pushed `%s` to dynamic array.\n", data);
}

/**
 * Returns the data at the given index in the dynamic array.
 *
 * @param index The index of the data to be returned.
 * @param array The pointer to the dynamic array.
 * @return The data at the given index in the dynamic array.
 */
char *getDynamicArray(int index, DynamicArray *array)
{
    if (index < 0 || index >= array->size)
    {
        printf("ERROR: Index out of bounds!\n");
        exit(1);
    }
    return array->data[index];
}

/**
 * Prints the dynamic array.
 *
 * @param array The pointer to the dynamic array.
 */
void printDynamicArray(DynamicArray *array)
{
    printf("[");
    for (int i = 0; i < array->size; i++)
    {
        printf("\"%s\"", *(array->data + i));
        if (i != array->size - 1)
            printf(", ");
    }
    printf("]\n");
}

/**
 * Frees the memory allocated to the dynamic array.
 *
 * @param array The pointer to the dynamic array.
 */
void freeDynamicArray(DynamicArray *array)
{
    // for (int i = 0; i < array->size; i++)
    // {
    //     free(array->data[i]);
    // }
    array->data = (char **)realloc(array->data, 0);
    free(array->data);
    free(array);
}
