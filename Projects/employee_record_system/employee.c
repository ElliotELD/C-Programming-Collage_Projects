#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "employees.dat"

// Define the structure for an employee
struct Employee
{
    int id;
    char name[50];
    char designation[50];
    float salary;
};

// Function prototypes
void addRecord(FILE *file);
void searchRecord(FILE *file);
void modifyRecord(FILE *file);
void deleteRecord(FILE *file);

int main()
{
    FILE *file = fopen(FILE_NAME, "rb+"); // Open file in read/write mode

    if (file == NULL)
    {
        // If file does not exist, create it
        file = fopen(FILE_NAME, "wb+");
        if (file == NULL)
        {
            printf("Error in opening file!");
            return 1;
        }
    }

    int choice;
    do
    {
        // Display menu
        printf("\nEmployee Record System\n");
        printf("1. Add Record\n");
        printf("2. Search Record\n");
        printf("3. Modify Record\n");
        printf("4. Delete Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            addRecord(file);
            break;
        case 2:
            searchRecord(file);
            break;
        case 3:
            modifyRecord(file);
            break;
        case 4:
            deleteRecord(file);
            break;
        case 5:
            printf("Exiting program.\n");
            break;
        default:
            printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);

    fclose(file); // Close the file
    return 0;
}

// Function to add a record to the file
void addRecord(FILE *file)
{
    struct Employee emp;

    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Employee Name: ");
    scanf("%s", emp.name);
    printf("Enter Employee Designation: ");
    scanf("%s", emp.designation);
    printf("Enter Employee Salary: ");
    scanf("%f", &emp.salary);

    fseek(file, 0, SEEK_END); // Move to the end of the file
    fwrite(&emp, sizeof(struct Employee), 1, file);
    printf("Record added successfully.\n");
}

// Function to search for a record in the file
void searchRecord(FILE *file)
{
    struct Employee emp;
    int id;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    rewind(file); // Move file pointer to the beginning

    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file))
    {
        if (emp.id == id)
        {
            printf("Employee ID: %d\n", emp.id);
            printf("Employee Name: %s\n", emp.name);
            printf("Employee Designation: %s\n", emp.designation);
            printf("Employee Salary: %.2f\n", emp.salary);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Employee with ID %d not found.\n", id);
    }
}

// Function to modify a record in the file
void modifyRecord(FILE *file)
{
    struct Employee emp;
    int id;
    printf("Enter Employee ID to modify: ");
    scanf("%d", &id);

    rewind(file); // Move file pointer to the beginning

    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file))
    {
        if (emp.id == id)
        {
            found = 1; // Set found flag
            printf("Enter new Employee Name: ");
            scanf("%s", emp.name);
            printf("Enter new Employee Designation: ");
            scanf("%s", emp.designation);
            printf("Enter new Employee Salary: ");
            scanf("%f", &emp.salary);

            fseek(file, -sizeof(struct Employee), SEEK_CUR); // Move file pointer back
            fwrite(&emp, sizeof(struct Employee), 1, file);  // Write modified record
            printf("Record modified successfully.\n");
            break; // Exit loop once record is modified
        }
    }

    if (!found)
    {
        printf("Employee with ID %d not found.\n", id);
    }
}

// Function to delete a record from the file
void deleteRecord(FILE *file)
{
    struct Employee emp;
    int id;
    FILE *tempFile = fopen("temp.dat", "wb"); // Open a temporary file

    if (tempFile == NULL)
    {
        printf("Error in opening temporary file!");
        return;
    }

    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    rewind(file); // Move file pointer to the beginning

    int found = 0;
    while (fread(&emp, sizeof(struct Employee), 1, file))
    {
        if (emp.id != id)
        {
            fwrite(&emp, sizeof(struct Employee), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);             // Remove the original file
    rename("temp.dat", FILE_NAME); // Rename the temporary file to original name

    if (found)
    {
        file = fopen(FILE_NAME, "rb+"); // Reopen the new file
        printf("Record deleted successfully.\n");
    }
    else
    {
        printf("Employee with ID %d not found.\n", id);
        file = fopen(FILE_NAME, "rb+"); // Reopen the original file
    }
}