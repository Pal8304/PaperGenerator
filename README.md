# Paper Generator

My and Nirlep's submission for the Data Structures assignment of Semester 3.

## Problem Statement

Design and develop a question paper formation tool using an efficient data structure. Create three categories for pool of questions namely EASY, MEDIUM and HARD and store in separate files with 25 questions in each category for different topics of data structure subject. System should select questions randomly based on the count and difficulty level entered by the user from each category. Finally, your system should generate a question paper (Nirma University Format) for specified marks entered by user.

### Constraints

- No question(s) must be repeated in the generated paper.
- There must be less similarity between multiple variants of papers generated.

## How to run the code?

```bash
./build.sh
./main
```

## Solution

- Usage of priority queue to store the number of times the questions have appeared in previous papers.

### Why priority queue over circular queue?

- Priority queue allows addition of new questions without disrupting the previous state.
- Also, in a circular queue after some rounds it becomes easier to predict a pattern, whereas with priority queue it is possible to add some randomness.

## References

- Guide for priority queue implementation: [GeeksForGeeks](https://www.geeksforgeeks.org/priority-queue-using-binary-heap/)
- PDF Library used: [PDFGen](https://github.com/AndreRenaud/PDFGen/)
