#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

typedef struct
{
    int id;
    char name[50];
    int marks[5];
    float average;
} Student;

void addStudent();
void searchStudent();
void modifyStudent();
void deleteStudent();
void generateMarkSheet();
void displayMenu();

int main()
{
    while (1)
    {
        displayMenu();
    }
    return 0;
}

void displayMenu()
{
    int choice;
    printf("\n*** Student Record System ***\n");
    printf("1. Add Student\n");
    printf("2. Search Student\n");
    printf("3. Modify Student\n");
    printf("4. Delete Student\n");
    printf("5. Generate Mark-sheet\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar(); // To consume the newline character left by scanf

    switch (choice)
    {
    case 1:
        addStudent();
        break;
    case 2:
        searchStudent();
        break;
    case 3:
        modifyStudent();
        break;
    case 4:
        deleteStudent();
        break;
    case 5:
        generateMarkSheet();
        break;
    case 6:
        exit(0);
        break;
    default:
        printf("Invalid choice! Please try again.\n");
    }
}

void addStudent()
{
    FILE *file = fopen(FILE_NAME, "ab");
    if (!file)
    {
        printf("Error opening file!\n");
        return;
    }

    Student student;
    printf("Enter Student ID: ");
    scanf("%d", &student.id);
    getchar(); // To consume the newline character left by scanf

    printf("Enter Student Name: ");
    fgets(student.name, sizeof(student.name), stdin);
    student.name[strcspn(student.name, "\n")] = '\0'; // Remove the newline character

    printf("Enter marks for 5 subjects:\n");
    int total = 0;
    for (int i = 0; i < 5; i++)
    {
        printf("Subject %d: ", i + 1);
        scanf("%d", &student.marks[i]);
        total += student.marks[i];
    }
    student.average = total / 5.0;

    fwrite(&student, sizeof(Student), 1, file);
    fclose(file);

    printf("Student record added successfully!\n");
}

void searchStudent()
{
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file)
    {
        printf("Error opening file!\n");
        return;
    }

    int id;
    printf("Enter Student ID to search: ");
    scanf("%d", &id);

    Student student;
    int found = 0;
    while (fread(&student, sizeof(Student), 1, file))
    {
        if (student.id == id)
        {
            printf("Student found!\n");
            printf("ID: %d\n", student.id);
            printf("Name: %s\n", student.name);
            printf("Marks: ");
            for (int i = 0; i < 5; i++)
            {
                printf("%d ", student.marks[i]);
            }
            printf("\nAverage: %.2f\n", student.average);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Student with ID %d not found.\n", id);
    }

    fclose(file);
}

void modifyStudent()
{
    FILE *file = fopen(FILE_NAME, "rb+");
    if (!file)
    {
        printf("Error opening file!\n");
        return;
    }

    int id;
    printf("Enter Student ID to modify: ");
    scanf("%d", &id);

    Student student;
    int found = 0;
    while (fread(&student, sizeof(Student), 1, file))
    {
        if (student.id == id)
        {
            printf("Student found!\n");
            getchar(); // To consume the newline character left by scanf
            printf("Enter new name: ");
            fgets(student.name, sizeof(student.name), stdin);
            student.name[strcspn(student.name, "\n")] = '\0'; // Remove the newline character

            printf("Enter new marks for 5 subjects:\n");
            int total = 0;
            for (int i = 0; i < 5; i++)
            {
                printf("Subject %d: ", i + 1);
                scanf("%d", &student.marks[i]);
                total += student.marks[i];
            }
            student.average = total / 5.0;

            fseek(file, -sizeof(Student), SEEK_CUR);
            fwrite(&student, sizeof(Student), 1, file);
            found = 1;
            printf("Student record updated successfully!\n");
            break;
        }
    }

    if (!found)
    {
        printf("Student with ID %d not found.\n", id);
    }

    fclose(file);
}

void deleteStudent()
{
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file)
    {
        printf("Error opening file!\n");
        return;
    }

    int id;
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    FILE *tempFile = fopen("temp.dat", "wb");
    if (!tempFile)
    {
        printf("Error opening temporary file!\n");
        fclose(file);
        return;
    }

    Student student;
    int found = 0;
    while (fread(&student, sizeof(Student), 1, file))
    {
        if (student.id == id)
        {
            found = 1;
        }
        else
        {
            fwrite(&student, sizeof(Student), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove(FILE_NAME);
        rename("temp.dat", FILE_NAME);
        printf("Student record deleted successfully!\n");
    }
    else
    {
        printf("Student with ID %d not found.\n", id);
    }
}

void generateMarkSheet()
{
    FILE *file = fopen(FILE_NAME, "rb");
    if (!file)
    {
        printf("Error opening file!\n");
        return;
    }

    int id;
    printf("Enter Student ID to generate mark-sheet: ");
    scanf("%d", &id);

    Student student;
    int found = 0;
    while (fread(&student, sizeof(Student), 1, file))
    {
        if (student.id == id)
        {
            printf("\n*** Mark-sheet ***\n");
            printf("ID: %d\n", student.id);
            printf("Name: %s\n", student.name);
            printf("Marks: ");
            for (int i = 0; i < 5; i++)
            {
                printf("%d ", student.marks[i]);
            }
            printf("\nAverage: %.2f\n", student.average);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Student with ID %d not found.\n", id);
    }

    fclose(file);
}