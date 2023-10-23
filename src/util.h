#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

#include "dynamic_array.h"

#ifndef UTIL_DEF
#define UTIL_DEF

void addQuestion(char *question, char *topic, char *difficulty);
char **getQuestionsDifficulty(char *difficulty);
char *readFileContents(char *filePath);

#endif

const char *QUESTION_SEP = "------";

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

char **getQuestionsDifficulty(char *difficulty)
{
    char *dirPath = malloc(100);
    sprintf(dirPath, "%s/%s", "questions", difficulty);

    DIR *d;
    struct dirent *dir;
    d = opendir(dirPath);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            char *contents = readFileContents(dir->d_name);
            // use contents
            // TODO: Add to dynamic array

            free(contents);
        }
    }
    else
    {
        printf("ERROR: Unable to open directory: `%s`", dirPath);
        free(dirPath);
        exit(1);
        return NULL;
    }
    free(dirPath);

    // TODO: return dynamic array
    return NULL;
}

char *readFileContents(char *filePath)
{
    FILE *file = fopen(filePath, "r");
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
