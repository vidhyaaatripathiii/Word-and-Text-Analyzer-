#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_TEXT 10000
#define MAX_WORDS 1000
#define MAX_LEN 50

struct Word
{
    char name[MAX_LEN];
    int count;
};

char text[MAX_TEXT] = "";

// ---------------- BASIC UTILITIES ----------------

void trimNewline(char str[])
{
    str[strcspn(str, "\n")] = '\0';
}

int isVowel(char ch)
{
    ch = tolower((unsigned char)ch);

    return ch == 'a' || ch == 'e' ||
           ch == 'i' || ch == 'o' || ch == 'u';
}

// ---------------- WORD PROCESSING ----------------

int buildWordList(const char source[], struct Word words[])
{
    char copy[MAX_TEXT];
    char *token;
    int count = 0;
    int i, found, j, len;

    strcpy(copy, source);

    token = strtok(copy, " \t\n\r");

    while(token != NULL)
    {
        char clean[MAX_LEN];

        len = strlen(token);
        j = 0;

        for(i = 0; i < len && j < MAX_LEN - 1; i++)
        {
            if(isalnum((unsigned char)token[i]))
            {
                clean[j++] = tolower(
                    (unsigned char)token[i]
                );
            }
        }

        clean[j] = '\0';

        if(j > 0)
        {
            found = 0;

            for(i = 0; i < count; i++)
            {
                if(strcmp(words[i].name, clean) == 0)
                {
                    words[i].count++;
                    found = 1;
                    break;
                }
            }

            if(!found && count < MAX_WORDS)
            {
                strcpy(words[count].name, clean);
                words[count].count = 1;
                count++;
            }
        }

        token = strtok(NULL, " \t\n\r");
    }

    return count;
}

void sortWords(struct Word words[], int count)
{
    int i, j;
    struct Word temp;

    for(i = 0; i < count - 1; i++)
    {
        for(j = 0; j < count - i - 1; j++)
        {
            if(words[j].count < words[j + 1].count)
            {
                temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
}

int countSentences(const char source[])
{
    int i, count = 0;

    for(i = 0; source[i]; i++)
    {
        if(source[i] == '.' ||
           source[i] == '!' ||
           source[i] == '?')
            count++;
    }

    return count;
}

// ---------------- TEXT INPUT ----------------

void inputText()
{
    char line[500];
    char newText[MAX_TEXT] = "";

    printf("\nEnter your text below.\n");
    printf("Type END on a new line to finish.\n");
    printf("----------------------------------------\n");

    while(fgets(line, sizeof(line), stdin))
    {
        trimNewline(line);

        if(strcmp(line, "END") == 0)
            break;

        if(strlen(newText) + strlen(line) + 2 < MAX_TEXT)
        {
            strcat(newText, line);
            strcat(newText, "\n");
        }
        else
        {
            printf("Maximum text limit reached!\n");
            break;
        }
    }

    if(strlen(newText) > 0)
    {
        strcpy(text, newText);
        printf("\nText saved successfully!\n");
    }
    else
    {
        printf("\nNo text entered!\n");
    }
}

// ---------------- TEXT STATISTICS ----------------

void showStatistics()
{
    struct Word words[MAX_WORDS];

    int characters = 0, letters = 0;
    int digits = 0, spaces = 0;
    int vowels = 0, consonants = 0;
    int paragraphs = 0, inParagraph = 0;
    int i, totalWords = 0;

    if(strlen(text) == 0)
    {
        printf("\nEnter text first!\n");
        return;
    }

    for(i = 0; text[i]; i++)
    {
        unsigned char ch = (unsigned char)text[i];

        characters++;

        if(isalpha(ch))
        {
            letters++;

            if(isVowel(ch))
                vowels++;
            else
                consonants++;
        }

        if(isdigit(ch))
            digits++;

        if(ch == ' ' || ch == '\t')
            spaces++;

        if(!isspace(ch))
            inParagraph = 1;

        if(ch == '\n' && inParagraph)
        {
            paragraphs++;
            inParagraph = 0;
        }
    }

    if(inParagraph)
        paragraphs++;

    totalWords = buildWordList(text, words);

    printf("\n========================================\n");
    printf("          TEXT STATISTICS REPORT\n");
    printf("========================================\n");

    printf("Characters       : %d\n", characters);
    printf("Letters          : %d\n", letters);
    printf("Words            : %d\n", totalWords);
    printf("Unique Words     : %d\n", totalWords);
    printf("Digits           : %d\n", digits);
    printf("Spaces           : %d\n", spaces);
    printf("Vowels           : %d\n", vowels);
    printf("Consonants       : %d\n", consonants);
    printf("Sentences        : %d\n", countSentences(text));
    printf("Paragraphs       : %d\n", paragraphs);

    printf("========================================\n");
}

// ---------------- TOP 10 WORDS ----------------

void frequencyAnalysis()
{
    struct Word words[MAX_WORDS];

    int count, i;

    if(strlen(text) == 0)
    {
        printf("\nEnter text first!\n");
        return;
    }

    count = buildWordList(text, words);
    sortWords(words, count);

    printf("\n========================================\n");
    printf("          TOP 10 WORD FREQUENCY\n");
    printf("========================================\n");

    printf("%-5s %-25s %s\n", "RANK", "WORD", "COUNT");
    printf("----------------------------------------\n");

    for(i = 0; i < count && i < 10; i++)
    {
        printf("%-5d %-25s %d\n",
               i + 1, words[i].name, words[i].count);
    }

    printf("========================================\n");
}

// ---------------- KEYWORD EXTRACTION ----------------

int isStopWord(const char word[])
{
    const char *stopWords[] =
    {
        "the", "is", "are", "am", "a", "an",
        "and", "or", "but", "to", "of", "in",
        "on", "at", "for", "with", "this",
        "that", "it", "was", "were", "be",
        "been", "being", "as", "by", "from",
        "have", "has", "had", "i", "you",
        "he", "she", "we", "they", "my",
        "your", "their", "our", "do", "does",
        "not", "so", "if", "then", "very"
    };

    int i;
    int size = sizeof(stopWords) / sizeof(stopWords[0]);

    for(i = 0; i < size; i++)
    {
        if(strcmp(word, stopWords[i]) == 0)
            return 1;
    }

    return 0;
}

void keywordExtraction()
{
    struct Word words[MAX_WORDS];

    int count, i, found = 0;

    if(strlen(text) == 0)
    {
        printf("\nEnter text first!\n");
        return;
    }

    count = buildWordList(text, words);
    sortWords(words, count);

    printf("\n========== IMPORTANT KEYWORDS ==========\n");

    for(i = 0; i < count && found < 10; i++)
    {
        if(!isStopWord(words[i].name))
        {
            printf("%-20s Frequency: %d\n",
                   words[i].name, words[i].count);
            found++;
        }
    }

    if(found == 0)
        printf("No keywords found!\n");
}

// ---------------- STOP WORD REMOVAL ----------------

void removeStopWords()
{
    struct Word words[MAX_WORDS];

    int count, i, j;

    if(strlen(text) == 0)
    {
        printf("\nEnter text first!\n");
        return;
    }

    count = buildWordList(text, words);

    printf("\n========== FILTERED TEXT ==========\n");

    for(i = 0; i < count; i++)
    {
        if(!isStopWord(words[i].name))
        {
            for(j = 0; j < words[i].count; j++)
                printf("%s ", words[i].name);
        }
    }

    printf("\n");
}

// ---------------- SENTIMENT ANALYSIS ----------------

void sentimentAnalysis()
{
    const char *positive[] =
    {
        "good", "great", "excellent", "happy",
        "love", "beautiful", "amazing", "best",
        "wonderful", "success", "awesome",
        "fantastic", "enjoy", "perfect"
    };

    const char *negative[] =
    {
        "bad", "worst", "sad", "hate",
        "poor", "terrible", "awful", "angry",
        "failure", "disappointed", "horrible",
        "wrong", "problem", "boring"
    };

    struct Word words[MAX_WORDS];

    int count, i, j;
    int positiveCount = 0, negativeCount = 0;

    if(strlen(text) == 0)
    {
        printf("\nEnter text first!\n");
        return;
    }

    count = buildWordList(text, words);

    for(i = 0; i < count; i++)
    {
        for(j = 0; j < 14; j++)
        {
            if(strcmp(words[i].name, positive[j]) == 0)
                positiveCount += words[i].count;

            if(strcmp(words[i].name, negative[j]) == 0)
                negativeCount += words[i].count;
        }
    }

    printf("\n========================================\n");
    printf("           SENTIMENT ANALYSIS\n");
    printf("========================================\n");

    printf("Positive words : %d\n", positiveCount);
    printf("Negative words : %d\n", negativeCount);

    if(positiveCount > negativeCount)
        printf("Result         : POSITIVE TEXT\n");
    else if(negativeCount > positiveCount)
        printf("Result         : NEGATIVE TEXT\n");
    else
        printf("Result         : NEUTRAL / MIXED TEXT\n");

    printf("\nNote: Basic dictionary-based analysis.\n");
    printf("========================================\n");
}

// ---------------- TEXT SUMMARIZATION ----------------

void summarizeText()
{
    char copy[MAX_TEXT];
    char *sentence;
    char best[3][500] = {"", "", ""};
    int bestScore[3] = {-1, -1, -1};

    struct Word words[MAX_WORDS];

    int count, i, j, score;
    int totalSentences = 0;

    if(strlen(text) == 0)
    {
        printf("\nEnter text first!\n");
        return;
    }

    count = buildWordList(text, words);
    strcpy(copy, text);

    sentence = strtok(copy, ".!?\n");

    while(sentence != NULL)
    {
        char sentenceCopy[500];
        char *token;

        score = 0;

        strncpy(sentenceCopy, sentence, sizeof(sentenceCopy) - 1);
        sentenceCopy[sizeof(sentenceCopy) - 1] = '\0';

        token = strtok(sentenceCopy, " \t\r");

        while(token != NULL)
        {
            char clean[MAX_LEN];
            int k = 0, m;

            for(m = 0; token[m] && k < MAX_LEN - 1; m++)
            {
                if(isalnum((unsigned char)token[m]))
                    clean[k++] = tolower((unsigned char)token[m]);
            }

            clean[k] = '\0';

            for(i = 0; i < count; i++)
            {
                if(strcmp(clean, words[i].name) == 0 &&
                   !isStopWord(clean))
                {
                    score += words[i].count;
                    break;
                }
            }

            token = strtok(NULL, " \t\r");
        }

        // Keep the three highest scoring sentences
        for(j = 0; j < 3; j++)
        {
            if(score > bestScore[j])
            {
                for(i = 2; i > j; i--)
                {
                    bestScore[i] = bestScore[i - 1];
                    strcpy(best[i], best[i - 1]);
                }

                bestScore[j] = score;

                strncpy(best[j], sentence, 499);
                best[j][499] = '\0';
                break;
            }
        }

        totalSentences++;
        sentence = strtok(NULL, ".!?\n");
    }

    printf("\n========================================\n");
    printf("             TEXT SUMMARY\n");
    printf("========================================\n");

    if(totalSentences == 0)
        printf("No sentences found!\n");
    else
    {
        for(i = 0; i < 3; i++)
        {
            if(bestScore[i] >= 0)
                printf("%s.\n", best[i]);
        }
    }

    printf("\nExtractive summary based on keyword frequency.\n");
    printf("========================================\n");
}

// ---------------- READABILITY ANALYSIS ----------------

void readabilityAnalysis()
{
    struct Word words[MAX_WORDS];

    int count, i, totalLength = 0;
    int sentences, totalWords = 0;
    float avgLength, avgSentence;

    if(strlen(text) == 0)
    {
        printf("\nEnter text first!\n");
        return;
    }

    count = buildWordList(text, words);

    if(count == 0)
    {
        printf("\nNo words found!\n");
        return;
    }

    for(i = 0; i < count; i++)
    {
        totalLength += strlen(words[i].name) * words[i].count;
        totalWords += words[i].count;
    }

    sentences = countSentences(text);

    if(sentences == 0)
        sentences = 1;

    avgLength = (float)totalLength / totalWords;

    avgSentence = (float)totalWords / sentences;

    printf("\n========================================\n");
    printf("          READABILITY REPORT\n");
    printf("========================================\n");

    printf("Average Word Length     : %.2f\n", avgLength);
    printf("Average Words/Sentence  : %.2f\n", avgSentence);

    if(avgSentence <= 10 && avgLength <= 5)
        printf("Reading Level           : EASY\n");
    else if(avgSentence <= 20 && avgLength <= 7)
        printf("Reading Level           : MODERATE\n");
    else
        printf("Reading Level           : DIFFICULT\n");

    printf("\nNote: This is an approximate heuristic.\n");
    printf("========================================\n");
}

// ---------------- DOCUMENT COMPARISON ----------------

void compareDocuments()
{
    char second[MAX_TEXT];
    char line[500];

    struct Word firstWords[MAX_WORDS];
    struct Word secondWords[MAX_WORDS];

    int firstCount, secondCount;
    int common = 0, i, j;
    int unionCount;
    float similarity;

    if(strlen(text) == 0)
    {
        printf("\nEnter first text before comparing!\n");
        return;
    }

    second[0] = '\0';

    printf("\nEnter second document (END to finish):\n");

    while(fgets(line, sizeof(line), stdin))
    {
        trimNewline(line);

        if(strcmp(line, "END") == 0)
            break;

        if(strlen(second) + strlen(line) + 2 < MAX_TEXT)
        {
            strcat(second, line);
            strcat(second, "\n");
        }
        else
            break;
    }

    firstCount = buildWordList(text, firstWords);
    secondCount = buildWordList(second, secondWords);

    for(i = 0; i < firstCount; i++)
    {
        for(j = 0; j < secondCount; j++)
        {
            if(strcmp(firstWords[i].name,
                      secondWords[j].name) == 0)
            {
                common++;
                break;
            }
        }
    }

    unionCount = firstCount + secondCount - common;

    similarity = unionCount > 0
                 ? (float)common * 100 / unionCount
                 : 0;

    printf("\n========================================\n");
    printf("          DOCUMENT COMPARISON\n");
    printf("========================================\n");

    printf("First Unique Words  : %d\n", firstCount);
    printf("Second Unique Words : %d\n", secondCount);
    printf("Common Words        : %d\n", common);
    printf("Similarity          : %.2f%%\n", similarity);

    printf("========================================\n");
    printf("Based on unique-word overlap, not meaning.\n");
}

// ---------------- MAIN MENU ----------------

int main()
{
    int choice;

    do
    {
        printf("\n\n");
        printf("================================================\n");
        printf("               WORD ANALYZER PRO\n");
        printf("          INTELLIGENT TEXT ANALYSIS\n");
        printf("================================================\n");

        printf("\n1. Enter / Update Text\n");
        printf("2. Text Statistics\n");
        printf("3. Top 10 Word Frequency\n");
        printf("4. Keyword Extraction\n");
        printf("5. Stop Word Removal\n");
        printf("6. Sentiment Analysis\n");
        printf("7. Text Summarization\n");
        printf("8. Readability Analysis\n");
        printf("9. Compare Documents\n");
        printf("10. Exit\n");

        printf("\nEnter Your Choice: ");

        if(scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input!\n");

            while(getchar() != '\n');
            continue;
        }

        while(getchar() != '\n');

        switch(choice)
        {
            case 1:
                inputText();
                break;

            case 2:
                showStatistics();
                break;

            case 3:
                frequencyAnalysis();
                break;

            case 4:
                keywordExtraction();
                break;

            case 5:
                removeStopWords();
                break;

            case 6:
                sentimentAnalysis();
                break;

            case 7:
                summarizeText();
                break;

            case 8:
                readabilityAnalysis();
                break;

            case 9:
                compareDocuments();
                break;

            case 10:
                printf("\nThank You for Using WORD ANALYZER PRO!\n");
                printf("End of Program.\n");
                break;

            default:
                printf("\nInvalid Choice! Try Again.\n");
        }

    } while(choice != 10);

    return 0;
}