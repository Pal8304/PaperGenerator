# Paper Generator

My and Palash's submission for the Data Structures assignment of Semester 3.

## Problem Statement

Design and develop a question paper formation tool using an efficient data structure. Create three categories for pool of questions namely EASY, MEDIUM and HARD and store in separate files with 25 questions in each category for different topics of data structure subject. System should select questions randomly based on the count and difficulty level entered by the user from each category. Finally, your system should generate a question paper (Nirma University Format) for specified marks entered by user.

### **Constraints:**
- No question(s) must be repeated in the generated paper.
- There must be less similarity between multiple variants of papers generated.

## Solution proposed by "LashPa"

- Usage of priority queue to store the number of times the questions have appeared in previous papers.

## Implementation

- Libraries used:
    - PDFGen: https://github.com/AndreRenaud/PDFGen/
