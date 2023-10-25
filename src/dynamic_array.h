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

#ifdef DYNAMIC_ARRAY_IMPLEMENTATION

typedef struct Question
{
    char *question;
    char *topic;
    char *difficulty;
} Question;

Question *
createQuestion(char *q, char *topic, char *difficulty)
{
    Question *question = (Question *)malloc(sizeof(Question));
    question->question = q;
    question->topic = topic;
    question->difficulty = difficulty;
    return question;
}

void freeQuestion(Question *question)
{
    free(question->question);
    free(question->difficulty);
    free(question->topic);
    free(question);
}

typedef struct DynamicArray
{
    Question **data;
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
    array->data = (Question **)malloc(sizeof(Question *) * capacity);
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
void pushDynamicArray(Question *data, DynamicArray *array)
{
    // printf("INFO: Pushing `%s` to dynamic array.\n", data);
    if (array->size == array->capacity)
    {
        array->capacity *= 2;
        array->data = (Question **)realloc(array->data, sizeof(Question *) * array->capacity);
    }
    *(array->data + array->size++) = data;
    // printf("INFO: Pushed `%s` to dynamic array.\n", data);
}

/**
 * Returns the data at the given index in the dynamic array.
 *
 * @param index The index of the data to be returned.
 * @param array The pointer to the dynamic array.
 * @return The data at the given index in the dynamic array.
 */
Question *getDynamicArray(int index, DynamicArray *array)
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
        printf("\"%s\"", (*(array->data + i))->question);
        if (i != array->size - 1)
            printf(", \n");
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
    for (int i = 0; i < array->size; i++)
    {
        free(array->data[i]);
    }
    array->data = (Question **)realloc(array->data, 0);
    free(array->data);
    free(array);
}

#endif