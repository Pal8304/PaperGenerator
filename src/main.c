#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UTILS_IMPLEMENTATION
#include "util.h"

#define PRIORITY_QUEUE_IMPLEMENTATION
#include "priority_queue.h"

#include "../external_libraries/pdfgen.h"
#include "../external_libraries/pdfgen.c"

int main(void)
{
  printCentered("---Welcome to Paper Generator!---");

  int questionCount;
  printf("Enter the number of questions for this paper: ");
  scanf("%d", &questionCount);

  int easy, medium, hard;
  printf("Enter the number of easy, medium and hard questions respectively: ");
  scanf("%d %d %d", &easy, &medium, &hard);

  int total = easy + medium + hard;
  if (total != questionCount)
  {
    printf("ERROR: The sum of easy, medium and hard questions should be equal to the total number of questions.\n");
    return 1;
  }

  DynamicArray *easyQuestions = getQuestionsDifficulty("easy");
  DynamicArray *mediumQuestions = getQuestionsDifficulty("medium");
  DynamicArray *hardQuestions = getQuestionsDifficulty("hard");

  PriorityQueue *easyPriorityQueue = serializePriorityQueue("easy");
  PriorityQueue *mediumPriorityQueue = serializePriorityQueue("medium");
  PriorityQueue *hardPriorityQueue = serializePriorityQueue("hard");

  DynamicArray *questionPaper = createDynamicArray(questionCount);
  for (int i = 0; i < easy; ++i)
  {
    Pair *p = popPriorityQueue(easyPriorityQueue);
    pushDynamicArray(getDynamicArray(p->index, easyQuestions), questionPaper);
    p->frequency += 1;
    insertPriorityQueue(easyPriorityQueue, p);
  }
  for (int i = 0; i < medium; ++i)
  {
    Pair *p = popPriorityQueue(mediumPriorityQueue);
    pushDynamicArray(getDynamicArray(p->index, mediumQuestions), questionPaper);
    p->frequency += 1;
    insertPriorityQueue(mediumPriorityQueue, p);
  }
  for (int i = 0; i < hard; ++i)
  {
    Pair *p = popPriorityQueue(hardPriorityQueue);
    pushDynamicArray(getDynamicArray(p->index, hardQuestions), questionPaper);
    p->frequency += 1;
    insertPriorityQueue(hardPriorityQueue, p);
  }

  for (int i = 0; i < questionPaper->size; ++i)
  {
    Question *question = getDynamicArray(i, questionPaper);
    printLeftRight(question->question, question->difficulty, 0);
  }

  char *pdf_title = NULL;
  asprintf(&pdf_title, "Question Paper %d", (int)time(NULL));
  struct pdf_info info = {
      .creator = "Nirma University",
      .producer = "Nirma University",
      .title = {*pdf_title},
      .author = "Nirma University",
      .subject = "Question Paper",
      .date = "Today"};
  struct pdf_doc *pdf = pdf_create(PDF_A4_WIDTH, PDF_A4_HEIGHT, &info);
  pdf_set_font(pdf, "Times-Roman");
  pdf_append_page(pdf);

  pdf_add_text(pdf, NULL, "Question Paper", 32, 50, PDF_A4_HEIGHT - 40, PDF_BLACK);
  float temp;
  float gap = 62;
  for (int i = 0; i < questionPaper->size; ++i)
  {
    Question *question = getDynamicArray(i, questionPaper);
    char *questionText = NULL;
    asprintf(&questionText, "%d. %s", i + 1, question->question);
    int y = PDF_A4_HEIGHT - gap;
    pdf_add_text_wrap(pdf, NULL, questionText, 12, 50, y, 0, PDF_BLACK, PDF_A4_WIDTH - 150, PDF_ALIGN_LEFT, &temp);
    pdf_add_text(pdf, NULL, question->difficulty, 12, PDF_A4_WIDTH - 50, y, PDF_BLACK);
    gap += 10 + temp;
    temp = 0;
    free(questionText);
  }

  char *fileName = NULL;
  asprintf(&fileName, "papers/%s.pdf", pdf_title);
  pdf_save(pdf, fileName);
  pdf_destroy(pdf);

  free(fileName);
  free(pdf_title);

  deserializePriorityQueue(easyPriorityQueue, "easy");
  deserializePriorityQueue(mediumPriorityQueue, "medium");
  deserializePriorityQueue(hardPriorityQueue, "hard");

  freePriorityQueue(easyPriorityQueue);
  freePriorityQueue(mediumPriorityQueue);
  freePriorityQueue(hardPriorityQueue);

  freeDynamicArray(easyQuestions);
  freeDynamicArray(mediumQuestions);
  freeDynamicArray(hardQuestions);

  return 0;
}
