#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "util.c"
#include "util.h"

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

  if (questionCount > 75)
  {
    printf("ERROR: Questions count can't be greater than 75\n");
    return 1;
  }
  if (easy > 25 || medium > 25 || hard > 25)
  {
    printf("ERROR: Questions from any category can't be greater than 25\n");
    return 1;
  }

  DynamicArray *easyQuestions = getQuestionsDifficulty("easy");
  DynamicArray *mediumQuestions = getQuestionsDifficulty("medium");
  DynamicArray *hardQuestions = getQuestionsDifficulty("hard");

  PriorityQueue *easyPriorityQueue = serializePriorityQueue("easy");
  PriorityQueue *mediumPriorityQueue = serializePriorityQueue("medium");
  PriorityQueue *hardPriorityQueue = serializePriorityQueue("hard");

  DynamicArray *questionPaper = createDynamicArray(questionCount);
  addQuestionsToPaper(easyPriorityQueue, easyQuestions, questionPaper, easy);
  addQuestionsToPaper(mediumPriorityQueue, mediumQuestions, questionPaper, medium);
  addQuestionsToPaper(hardPriorityQueue, hardQuestions, questionPaper, hard);

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
  pdf_object *page = pdf_append_page(pdf);

  pdf_add_text_wrap(
      pdf, page, "Nirma University",
      24, 0, PDF_A4_HEIGHT - 40, 0, PDF_BLACK, PDF_A4_WIDTH,
      PDF_ALIGN_CENTER, NULL);
  pdf_add_text_wrap(
      pdf, page, "Institute of Technology",
      16, 0, PDF_A4_HEIGHT - 54, 0, PDF_BLACK, PDF_A4_WIDTH,
      PDF_ALIGN_CENTER, NULL);
  pdf_add_text_wrap(
      pdf, page, "B. Tech. in Computer Science and Engineering, Semester - III",
      12, 0, PDF_A4_HEIGHT - 66, 0, PDF_BLACK, PDF_A4_WIDTH,
      PDF_ALIGN_CENTER, NULL);
  pdf_add_text_wrap(
      pdf, page, "2CS301 Data Structures and Algorithms",
      12, 0, PDF_A4_HEIGHT - 78, 0, PDF_BLACK, PDF_A4_WIDTH,
      PDF_ALIGN_CENTER, NULL);

  pdf_add_text_wrap(
      pdf, page, "Roll No:",
      12, 50, PDF_A4_HEIGHT - 105, 0, PDF_BLACK, PDF_A4_WIDTH,
      PDF_ALIGN_LEFT, NULL);
  pdf_add_rectangle(pdf, page, 100, PDF_A4_HEIGHT - 110, 70, 20, 1, PDF_BLACK);
  pdf_add_text_wrap(
      pdf, page, "Supervisor's initial with date:",
      12, PDF_A4_WIDTH - 205, PDF_A4_HEIGHT - 100, 0, PDF_BLACK, 100,
      PDF_ALIGN_LEFT, NULL);
  pdf_add_rectangle(pdf, page, PDF_A4_WIDTH - 110, PDF_A4_HEIGHT - 110, 70, 20, 1, PDF_BLACK);

  pdf_add_text_wrap(
      pdf, page, "Instructions:",
      12, 50, PDF_A4_HEIGHT - 125, 0, PDF_BLACK, PDF_A4_WIDTH,
      PDF_ALIGN_LEFT, NULL);
  pdf_add_text_wrap(
      pdf, page, "1. Attempt all questions.\n2. Figures to the right indicate difficulty\n3. Use a section-wise separate answer book.\n4. Draw neat sketches wherever necessary.\n5. Assume necessary data wherever required.",
      12, 120, PDF_A4_HEIGHT - 125, 0, PDF_BLACK, PDF_A4_WIDTH,
      PDF_ALIGN_LEFT, NULL);

  pdf_set_font(pdf, "Times-Bold");
  pdf_add_text_wrap(
      pdf, page, "SECTION - I", 14, 0, PDF_A4_HEIGHT - 200, 0, PDF_BLACK, PDF_A4_WIDTH,
      PDF_ALIGN_CENTER, NULL);
  pdf_set_font(pdf, "Times-Roman");

  float temp;
  float gap = 230;
  float offset = 20;
  int index = 0;
  for (int i = 0; i < questionPaper->size; ++i)
  {
    Question *question = getDynamicArray(index++, questionPaper);
    char *questionText = NULL;
    asprintf(&questionText, "Q.%d %s", index, question->question);
    int y = PDF_A4_HEIGHT - gap;
    pdf_add_text_wrap(pdf, page, questionText, 12, 50, y, 0, PDF_BLACK, PDF_A4_WIDTH - 150,
                      PDF_ALIGN_LEFT, &temp);
    pdf_add_text(pdf, page, question->difficulty, 12, PDF_A4_WIDTH - 70, y, PDF_BLACK);
    gap += 6 + temp;
    if (gap >= PDF_A4_HEIGHT - offset)
    {
      gap = offset;
      page = pdf_append_page(pdf);
    }
    free(questionText);
    if (index == easy)
    {
      pdf_set_font(pdf, "Times-Bold");
      pdf_add_text_wrap(
          pdf, page, "SECTION - II", 14, 0, PDF_A4_HEIGHT - gap, 0, PDF_BLACK, PDF_A4_WIDTH,
          PDF_ALIGN_CENTER, &temp);
      pdf_set_font(pdf, "Times-Roman");
      gap += 12 + temp;
    }
    if (index == easy + medium)
    {
      pdf_set_font(pdf, "Times-Bold");
      pdf_add_text_wrap(
          pdf, page, "SECTION - III", 14, 0, PDF_A4_HEIGHT - gap, 0, PDF_BLACK, PDF_A4_WIDTH,
          PDF_ALIGN_CENTER, &temp);
      pdf_set_font(pdf, "Times-Roman");
      gap += 12 + temp;
    }
  }
  // for (int i = 0; i < questionPaper->size; ++i)
  // {
  //   Question *question = getDynamicArray(i, questionPaper);
  //   char *questionText = NULL;
  //   asprintf(&questionText, "%d. %s", i + 1, question->question);
  //   int y = PDF_A4_HEIGHT - gap;
  //   pdf_add_text_wrap(pdf, page, questionText, 12, 50, y, 0, PDF_BLACK, PDF_A4_WIDTH - 150, PDF_ALIGN_LEFT, &temp);
  //   pdf_add_text(pdf, page, question->difficulty, 12, PDF_A4_WIDTH - 50, y, PDF_BLACK);
  //   gap += 10 + temp;
  //   temp = 0;
  //   free(questionText);
  // }

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
