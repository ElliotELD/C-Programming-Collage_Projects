#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100

// Structure to represent a student
struct Student
{
    int rollNo;       // Roll number of the student
    char name[60];    // Name of the student
    float totalMarks; // Total marks obtained by the student
};

// Array to store student records
struct Student students[MAX_STUDENTS];
int numStudents = 0; // Number of students currently stored

// Function to add a new student record
void addStudent()
{
    // Check if maximum limit of students has been reached
    if (numStudents >= MAX_STUDENTS)
    {
        printf("Maximum limit reached!!! Can't add Students.\n");
        return;
    }

    // Input student details from user
    printf("Enter your roll number: ");
    scanf("%d", &students[numStudents].rollNo);
    printf("Enter your name {NO spaace allowed}: ");
    scanf("%s", students[numStudents].name);
    printf("Enter your total marks: ");
    scanf("%f", &students[numStudents].totalMarks);

    numStudents++; // Increment the count of students
}

// Function to display all student records
void displayAllRecords()
{
    // Check if there are no records
    if (numStudents == 0)
    {
        printf("Currently No records found!!!\n");
        return;
    }

    // Print header for the result
    printf("----------__________RESULT__________---------- \n");
    printf("Roll_No\t\tStudent_Name\t\tTotal Marks\n");
    // Iterate over each student record and print details
    for (int i = 0; i < numStudents; i++)
    {
        printf("%d \t\t %s\t\t\t%.2f \n", students[i].rollNo, students[i].name, students[i].totalMarks);
    }
}

// Function to search for a student record by roll number
void searchRecord(int rollNo)
{
    // Iterate over each student record
    for (int i = 0; i < numStudents; i++)
    {
        // If roll number matches, print student details and return
        if (students[i].rollNo == rollNo)
        {
            printf("Roll No: %d\nName: %s\nTotal Marks: %.2f\n", students[i].rollNo, students[i].name, students[i].totalMarks);
            return;
        }
    }
    // If record not found, print message
    printf("Record not found.\n");
}

// Function to update a student record by roll number
void updateRecord(int rollNo)
{
    // Iterate over each student record
    for (int i = 0; i < numStudents; i++)
    {
        // If roll number matches, update name and total marks
        if (students[i].rollNo == rollNo)
        {
            printf("Enter new name: ");
            scanf("%s", students[i].name);
            printf("Enter new total marks: ");
            scanf("%f", &students[i].totalMarks);
            printf("Record updated successfully!!!\n");
            return;
        }
    }
    // If record not found, print message
    printf("Record not found.\n");
}

// Function to delete a student record by roll number
void deleteRecord(int rollNo)
{
    // Iterate over each student record
    for (int i = 0; i < numStudents; i++)
    {
        // If roll number matches, delete the record
        if (students[i].rollNo == rollNo)
        {
            // Shift elements to remove the record
            for (int j = i; j < numStudents - 1; j++)
            {
                students[j] = students[j + 1];
            }
            numStudents--; // Decrement the count of students
            printf("Record deleted successfully!!!\n");
            return;
        }
    }
    // If record not found, print message
    printf("Record not found.\n");
}

// Main function where program execution starts
int main()
{
    int choice, rollNo;

    // Loop to display menu and get user choice
    while (1)
    {
        // Display menu options
        printf("\nMenu:\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Records\n");
        printf("3. Search for a Record\n");
        printf("4. Update a Record\n");
        printf("5. Delete a Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // Switch case to perform actions based on user choice
        switch (choice)
        {
        case 1:
            addStudent();
            break;
        case 2:
            displayAllRecords();
            break;
        case 3:
            printf("Enter roll number to search: ");
            scanf("%d", &rollNo);
            searchRecord(rollNo);
            break;
        case 4:
            printf("Enter roll number to update: ");
            scanf("%d", &rollNo);
            updateRecord(rollNo);
            break;
        case 5:
            printf("Enter roll number to delete: ");
            scanf("%d", &rollNo);
            deleteRecord(rollNo);
            break;
        case 6:
            printf("Exiting program.\n");
            exit(0); // Exit the program
        default:
            printf("Invalid choice. Please enter a number between 1 and 6.\n");
        }
    }

    return 0;
}