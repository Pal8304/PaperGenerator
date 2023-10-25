#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define DYNAMIC_ARRAY_IMPLEMENTATION
#include "dynamic_array.h"

void addQuestion(char *question, char *topic, char *difficulty);
DynamicArray *getQuestionsDifficulty(char *difficulty);
char *readFileContents(char *filePath);
int getTerminalWidth();
void printCentered(char *str);
void printLeftRight(char *left, char *right, int gap);
char *trim(char *str);

#ifdef UTILS_IMPLEMENTATION

const char *QUESTION_SEP = "ඞ";

/**
 * Adds the given question to the given topic and difficulty.
 *
 * @param question The question to be added.
 * @param topic The topic of the question.
 * @param difficulty The difficulty of the question.
 */
void addQuestion(char *question, char *topic, char *difficulty)
{
    char *filePath = NULL;
    asprintf(&filePath, "%s/%s/%s.txt", "questions", difficulty, topic);

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
    char *dirPath = NULL;
    asprintf(&dirPath, "%s/%s", "questions", difficulty);

    DynamicArray *questions = createDynamicArray(2);

    DIR *d;
    struct dirent *dir;
    d = opendir(dirPath);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            char *filePath = NULL;
            asprintf(&filePath, "%s/%s", dirPath, dir->d_name);
            char *contents = readFileContents(filePath);
            free(filePath);

            int length = strlen(contents);
            if (length == 0 || strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
            {
                // printf("INFO: Skipping empty file: `%s`\n", dir->d_name);
                free(contents);
                continue;
            }

            char *question = trim(strtok(contents, QUESTION_SEP));
            while (question != NULL)
            {
                if (strlen(question) > 0)
                {
                    // printf("INFO: Question: `%s` of file: `%s`\n", question, dir->d_name);
                    pushDynamicArray(createQuestion(question, dir->d_name, difficulty), questions);
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
 * Returns the width of the terminal.
 *
 * @return The width of the terminal.
 */
int getTerminalWidth()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

/**
 * Prints the given string centered.
 *
 * @param str The string to be printed.
 */
void printCentered(char *str)
{
    int width = getTerminalWidth();
    int length = strlen(str);
    int padding = (width - length) / 2;
    for (int i = 0; i < padding; i++)
    {
        printf(" ");
    }
    printf("%s\n", str);
}

/**
 * Prints the given left and right strings with the given gap between them.
 *
 * @param left The left string.
 * @param right The right string.
 * @param gap The gap between the left and right strings.
 */
void printLeftRight(char *left, char *right, int gap)
{
    int width = getTerminalWidth();
    int leftLength = strlen(left);
    int rightLength = strlen(right);
    int padding = width - leftLength - rightLength - 2 * gap;
    for (int i = 0; i < gap; i++)
    {
        printf(" ");
    }
    printf("%s", left);
    for (int i = 0; i < padding; i++)
    {
        printf(" ");
    }
    printf("%s\n", right);
}

/**
 * Returns the contents of the file at the given path.
 *
 * @param filePath The path of the file.
 * @return The contents of the file at the given path.
 */
char *readFileContents(char *filePath)
{
    // printf("INFO: Reading file: `%s`\n", filePath);
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

#endif
