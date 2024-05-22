#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_WORDS 10
#define WORD_LENGTH 10

void generateRandomWords(char words[MAX_WORDS][WORD_LENGTH]);
int calculateWPM(int wordCount, int elapsedTime);

int main()
{
    int startTime, endTime, elapsedTime;
    int wordCount = MAX_WORDS;
    char wordsToType[MAX_WORDS][WORD_LENGTH];
    char input[WORD_LENGTH];

    srand(time(NULL));
    generateRandomWords(wordsToType);

    printf("Welcome to Typing Tutor!\n");
    printf("Type the following words as fast as you can:\n");
    for (int i = 0; i < MAX_WORDS; i++)
    {
        printf("%s ", wordsToType[i]);
    }
    printf("\nPress Enter after each word.\n");

    startTime = time(NULL);

    for (int i = 0; i < MAX_WORDS; i++)
    {
        scanf("%s", input);
        // You can add comparison and error handling here if needed
    }

    endTime = time(NULL);
    elapsedTime = endTime - startTime;

    int WPM = calculateWPM(wordCount, elapsedTime);

    printf("You typed %d words in %d seconds.\n", wordCount, elapsedTime);
    printf("Your typing speed is approximately %d words per minute.\n", WPM);

    return 0;
}

void generateRandomWords(char words[MAX_WORDS][WORD_LENGTH])
{
    char wordList[5][WORD_LENGTH] = {"apple", "banana", "orange", "grape", "kiwi"};
    for (int i = 0; i < MAX_WORDS; i++)
    {
        strcpy(words[i], wordList[rand() % 5]);
    }
}

int calculateWPM(int wordCount, int elapsedTime)
{
    return (int)((float)wordCount / ((float)elapsedTime / 60.0));
}
