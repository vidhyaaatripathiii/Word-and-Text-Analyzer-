# WORD ANALYZER PRO

## Project Overview

WORD ANALYZER PRO is a menu-driven text analysis application developed using the C programming language. It allows users to enter text and perform different types of analysis on it.

The program provides features such as word frequency analysis, keyword extraction, stop-word removal, sentiment analysis, text summarization, readability analysis, and document comparison.

It uses various C programming concepts, including structures, arrays, strings, functions, loops, conditional statements, and string-handling functions.

## Objective

The main objective of this project is to develop a text analysis tool using the C programming language that can process user-provided text and display useful information about it.

The project aims to:
- Analyze the structure and content of a text.
- Identify frequently used words and important keywords.
- Perform basic sentiment analysis.
- Generate a short summary of the entered text.
- Evaluate the readability of the text.
- Compare two documents based on their common words.

## Features

1. **Text Input:** Allows users to enter multiple lines of text until they type `END`.

2. **Text Statistics:** Displays information such as character count, letters, digits, spaces, vowels, consonants, paragraphs, and word statistics.

3. **Word Frequency Analysis:** Identifies frequently occurring words and displays the top 10 words based on their frequency.

4. **Keyword Extraction:** Extracts important keywords by filtering out commonly used stop words.

5. **Stop Word Removal:** Removes common words from the text and displays the remaining words.

6. **Sentiment Analysis:** Performs basic sentiment analysis by checking predefined positive and negative words in the text.

7. **Text Summarization:** Generates a short summary by selecting sentences based on the frequency of important words.

8. **Readability Analysis:** Calculates average word length and average words per sentence to classify the text as easy, moderate, or difficult.

9. **Document Comparison:** Compares two documents by identifying common unique words and calculating their similarity percentage.

10. **Menu-Driven Interface:** Provides a menu that allows users to select different analysis operations.

## Algorithm

1. Start the program.
2. Display the main menu containing different text analysis options.
3. Ask the user to enter text.
4. Store the entered text in a character array.
5. Allow the user to select an operation from the menu.
6. Perform the selected operation:
   - Calculate text statistics.
   - Analyze word frequency.
   - Extract important keywords.
   - Remove stop words.
   - Perform sentiment analysis.
   - Generate a text summary.
   - Analyze readability.
   - Compare two documents.
7. Display the result of the selected operation.
8. Allow the user to select another operation.
9. Repeat the process until the user chooses the Exit option.
10. Stop the program.

## Test Cases

| Test Case | Input / Condition | Expected Result |
|---|---|---|
| 1 | Enter a paragraph of text | Text should be stored successfully. |
| 2 | Enter text containing letters, digits, and spaces | Text statistics should be displayed. |
| 3 | Enter a paragraph containing repeated words | Word frequency should identify frequently occurring words. |
| 4 | Enter text containing common words and important keywords | Keyword extraction should filter out stop words. |
| 5 | Enter text containing predefined positive words | Positive sentiment count should increase. |
| 6 | Enter text containing predefined negative words | Negative sentiment count should increase. |
| 7 | Enter text containing multiple sentences | Text summarization should display selected sentences. |
| 8 | Enter a short and simple paragraph | Readability analysis should classify the text. |
| 9 | Compare two documents containing some common words | Common words and similarity percentage should be displayed. |
| 10 | Enter an invalid menu choice | The program should display an appropriate message. |

## Team Members & Contributions

### 1. Vidhya Tripathi
- Led the overall project development and coordination.
- Made the major contribution to the project code along with Ishaan.
- Designed and prepared the project presentation (PPT).
- Created and prepared the GitHub README file.
- Contributed to the implementation and integration of the major features.

### 2. Ishaan Painuly
- Made a major contribution to the coding and development of the project.
- Worked collaboratively with Vidhya on implementing the main program features.
- Contributed to the program logic, functions, and text-processing operations.
- Assisted in integrating and reviewing different parts of the code.

### 3. Shreyan Joshi
- Contributed to selected parts of the project code.
- Prepared and performed test cases for different project features.
- Checked program outputs and verified the working of different operations.
- Assisted in identifying errors and reviewing the results.
- Contributed to project testing and result verification.

## Collaborative Contributions

All three team members participated in the overall development process.

- **Vidhya Tripathi:** Major contribution to coding, project coordination, PPT preparation, and README documentation.
- **Ishaan Painuly:** Major contribution to coding, program logic, and implementation of features.
- **Shreyan Joshi:** Testing, test case preparation, output verification, and selected coding contributions.

The project was developed through teamwork, with members contributing to different stages of implementation, documentation, testing, and verification.

## Conclusion

WORD ANALYZER PRO demonstrates how the C programming language can be used to develop a menu-driven text analysis application.

The project combines different programming concepts and string-processing techniques to perform multiple text analysis operations. It also provides practical experience in using structures, arrays, functions, loops, conditional statements, and library functions.

Overall, this project helped us understand the practical implementation of C programming concepts while developing a useful text analysis tool.
