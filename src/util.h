#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#include "dynamic_array.h"

#ifndef UTIL_H
#define UTIL_H

void addQuestion(char *question, char *topic, char *difficulty);
DynamicArray *getQuestionsDifficulty(char *difficulty);
char *readFileContents(char *filePath);
char *trim(char *str);

#endif

const char *QUESTION_SEP = "------";

/**
 * Adds the given question to the given topic and difficulty.
 *
 * @param question The question to be added.
 * @param topic The topic of the question.
 * @param difficulty The difficulty of the question.
 */
void addQuestion(char *question, char *topic, char *difficulty)
{
    char *filePath = malloc(1000);
    sprintf(filePath, "%s/%s/%s.txt", "questions", difficulty, topic);

    FILE *file = fopen(filePath, "a");
    if (file == NULL)
    {
        printf("ERROR: Unable to open file: `%s`!\n", filePath);
        free(filePath);
        exit(1);
        return;
    }
    free(filePath);

    fprintf(file, "%s\n\n%s\n\n", question, QUESTION_SEP);
    fclose(file);
}

/**
 * Returns the questions of the given difficulty.
 *
 * @param difficulty The difficulty of the questions.
 * @return The questions of the given difficulty in a DynamicArray.
 */
DynamicArray *getQuestionsDifficulty(char *difficulty)
{
    char *dirPath = malloc(100);
    sprintf(dirPath, "%s/%s", "questions", difficulty);

    DynamicArray *questions = createDynamicArray(2);

    DIR *d;
    struct dirent *dir;
    d = opendir(dirPath);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            char *filePath = malloc(1000);
            sprintf(filePath, "%s/%s", dirPath, dir->d_name);
            char *contents = readFileContents(filePath);
            free(filePath);

            int length = strlen(contents);
            if (length == 0 || strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
            {
                printf("INFO: Skipping empty file: `%s`\n", dir->d_name);
                free(contents);
                continue;
            }

            char *question = trim(strtok(contents, QUESTION_SEP));
            while (question != NULL)
            {
                if (strlen(question) > 0)
                {
                    printf("INFO: Question: `%s` of file: `%s`\n", question, dir->d_name);
                    pushDynamicArray(question, questions);
                }
                question = trim(strtok(NULL, QUESTION_SEP));
            }
        }
    }
    else
    {
        printf("ERROR: Unable to open directory: `%s`\n", dirPath);
        free(dirPath);
        exit(1);
        return NULL;
    }
    free(dirPath);

    return questions;
}

/**
 * Returns the contents of the file at the given path.
 *
 * @param filePath The path of the file.
 * @return The contents of the file at the given path.
 */
char *readFileContents(char *filePath)
{
    printf("INFO: Reading file: `%s`\n", filePath);
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        printf("ERROR: Unable to open file: `%s`!\n", filePath);
        exit(1);
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    int length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc((length + 1) * sizeof(char));
    if (buffer)
    {
        fread(buffer, 1, length, file);
    }
    fclose(file);
    return buffer;
}

/**
 * Trims the given string.
 * https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
 *
 * @param str The string to be trimmed.
 * @return The trimmed string.
 */
char *trim(char *str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if (str == NULL)
    {
        return NULL;
    }
    if (str[0] == '\0')
    {
        return str;
    }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while (isspace((unsigned char)*frontp))
    {
        ++frontp;
    }
    if (endp != frontp)
    {
        while (isspace((unsigned char)*(--endp)) && endp != frontp)
        {
        }
    }

    if (frontp != str && endp == frontp)
        *str = '\0';
    else if (str + len - 1 != endp)
        *(endp + 1) = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if (frontp != str)
    {
        while (*frontp)
        {
            *endp++ = *frontp++;
        }
        *endp = '\0';
    }

    return str;
}
