#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define NUM_QUESTIONS 5

typedef struct
{
    char question[256];
    char options[4][256];
    char correct_option;
} Question;

Question quiz[NUM_QUESTIONS] = {
    {"What does CPU stand for?",
     {"A. Central Process Unit", "B. Central Processing Unit", "C. Computer Personal Unit", "D. Central Processor Unit"},
     'B'},
    {"Which of the following is an operating system?",
     {"A. Python", "B. C++", "C. Linux", "D. HTML"},
     'C'},
    {"What does RAM stand for?",
     {"A. Random Access Memory", "B. Read Access Memory", "C. Run Accept Memory", "D. None of these"},
     'A'},
    {"Which language is used for web development?",
     {"A. C", "B. Python", "C. Java", "D. JavaScript"},
     'D'},
    {"Which one is a volatile memory?",
     {"A. Hard Disk", "B. ROM", "C. RAM", "D. SSD"},
     'C'}};

void start_quiz()
{
    int score = 0;
    char user_option;

    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        printf("%s\n", quiz[i].question);
        for (int j = 0; j < 4; j++)
        {
            printf("%s\n", quiz[i].options[j]);
        }

        printf("Your answer: ");
        scanf(" %c", &user_option);

        if (toupper(user_option) == quiz[i].correct_option)
        {
            printf("Correct!\n");
            score++;
        }
        else
        {
            printf("Wrong! The correct answer is %c\n", quiz[i].correct_option);
        }
        printf("\n");
    }

    printf("Your total score is: %d out of %d\n", score, NUM_QUESTIONS);
}

int main()
{
    printf("Welcome to the Computer Knowledge Quiz!\n");
    printf("You will be asked %d questions.\n", NUM_QUESTIONS);
    printf("For each correct answer, you will get 1 point.\n\n");

    start_quiz();

    return 0;
}
