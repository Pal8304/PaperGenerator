#include <ctype.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define DYNAMIC_ARRAY_IMPLEMENTATION
#include "dynamic_array.h"
#include "priority_queue.h"

void addQuestion(char *question, char *topic, char *difficulty);
DynamicArray *getQuestionsDifficulty(char *difficulty);
char *readFileContents(char *filePath);
int getTerminalWidth(void);
void printCentered(char *str);
void printLeftRight(char *left, char *right, int gap);
char *readFileContents(char *filePath);
void addQuestionsToPaper(PriorityQueue *pq, DynamicArray *questions,
                         DynamicArray *question_paper, int count);
char *trim(char *str);

#ifdef UTILS_IMPLEMENTATION

#endif
