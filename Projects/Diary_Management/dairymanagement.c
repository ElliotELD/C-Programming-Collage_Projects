#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100

struct DiaryEntry
{
    char date[20];
    char time[10];
    char description[100];
};

struct DiaryEntry diary[MAX_ENTRIES];
int numEntries = 0;

void addEntry()
{
    if (numEntries < MAX_ENTRIES)
    {
        printf("\nEnter date (dd/mm/yyyy): ");
        scanf("%s", diary[numEntries].date);
        printf("\nEnter time (hh:mm): ");
        scanf("%s", diary[numEntries].time);
        printf("\nEnter description: ");
        scanf(" %[^\n]", diary[numEntries].description);
        numEntries++;
        printf(" **************");
        printf("\n Entry added successfully!!!\n");
        printf(" **************");
    }
    else
    {
        printf("\n Diary is full. Cannot add more entries.\n");
    }
}

void viewEntries()
{
    if (numEntries == 0)
    {
        printf("\n Diary is empty.\n");
    }
    else
    {
        printf(" **************");
        printf("\n Diary Entries:\n");
        printf(" **************");
        for (int i = 0; i < numEntries; i++)
        {
            printf("\n Date:- %s, Time:- %s, Description:- %s\n", diary[i].date, diary[i].time, diary[i].description);
        }
    }
}

void deleteEntry()
{
    if (numEntries == 0)
    {
        printf("\n Diary is empty. Nothing to delete.\n");
    }
    else
    {
        int index;
        printf("\n Enter index of entry to delete (0-%d): ", numEntries - 1);
        scanf("%d", &index);
        if (index >= 0 && index < numEntries)
        {
            for (int i = index; i < numEntries - 1; i++)
            {
                strcpy(diary[i].date, diary[i + 1].date);
                strcpy(diary[i].time, diary[i + 1].time);
                strcpy(diary[i].description, diary[i + 1].description);
            }
            numEntries--;
            printf(" **************");
            printf("Entry deleted successfully!\n");
            printf(" **************");
        }
        else
        {
            printf(" **************");
            printf("Invalid index. Please enter a valid index.\n");
            printf(" **************");
        }
    }
}

int main()
{
    int choice;

    do
    {
        printf("\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-");
        printf("\n*-*-*- Personal Diary Management System *-*-*-*-\n");
        printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n \n");
        printf("1. Add Entry\n");
        printf("2. View Entries\n");
        printf("3. Delete Entry\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addEntry();
            break;
        case 2:
            viewEntries();
            break;
        case 3:
            deleteEntry();
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    return 0;
}
