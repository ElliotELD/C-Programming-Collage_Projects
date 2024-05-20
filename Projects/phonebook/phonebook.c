#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_PHONE_LEN 15
#define FILENAME "phonebook.dat"

typedef struct
{
    char name[MAX_NAME_LEN];
    char phone[MAX_PHONE_LEN];
} Contact;

void addContact();
void listContacts();
void modifyContact();
void searchContact();
void deleteContact();
void displayMenu();

int main()
{
    int choice;

    while (1)
    {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline character

        switch (choice)
        {
        case 1:
            addContact();
            break;
        case 2:
            listContacts();
            break;
        case 3:
            modifyContact();
            break;
        case 4:
            searchContact();
            break;
        case 5:
            deleteContact();
            break;
        case 6:
            exit(0);
        default:
            printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void displayMenu()
{
    printf("\nPhonebook Application\n");
    printf("1. Add Contact\n");
    printf("2. List Contacts\n");
    printf("3. Modify Contact\n");
    printf("4. Search Contact\n");
    printf("5. Delete Contact\n");
    printf("6. Exit\n");
}

void addContact()
{
    FILE *file = fopen(FILENAME, "ab");
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    Contact contact;
    printf("Enter name: ");
    fgets(contact.name, MAX_NAME_LEN, stdin);
    contact.name[strcspn(contact.name, "\n")] = '\0'; // Remove newline

    printf("Enter phone number: ");
    fgets(contact.phone, MAX_PHONE_LEN, stdin);
    contact.phone[strcspn(contact.phone, "\n")] = '\0'; // Remove newline

    fwrite(&contact, sizeof(Contact), 1, file);
    fclose(file);
    printf("Contact added successfully.\n");
}

void listContacts()
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    Contact contact;
    printf("\nContacts List:\n");
    printf("-------------------------------\n");
    while (fread(&contact, sizeof(Contact), 1, file))
    {
        printf("Name: %s\n", contact.name);
        printf("Phone: %s\n", contact.phone);
        printf("-------------------------------\n");
    }
    fclose(file);
}

void modifyContact()
{
    FILE *file = fopen(FILENAME, "rb+");
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    char searchName[MAX_NAME_LEN];
    printf("Enter the name of the contact to modify: ");
    fgets(searchName, MAX_NAME_LEN, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; // Remove newline

    Contact contact;
    int found = 0;
    long pos;

    while ((pos = ftell(file), fread(&contact, sizeof(Contact), 1, file)))
    {
        if (strcmp(contact.name, searchName) == 0)
        {
            found = 1;
            printf("Enter new name: ");
            fgets(contact.name, MAX_NAME_LEN, stdin);
            contact.name[strcspn(contact.name, "\n")] = '\0'; // Remove newline

            printf("Enter new phone number: ");
            fgets(contact.phone, MAX_PHONE_LEN, stdin);
            contact.phone[strcspn(contact.phone, "\n")] = '\0'; // Remove newline

            fseek(file, pos, SEEK_SET);
            fwrite(&contact, sizeof(Contact), 1, file);
            printf("Contact modified successfully.\n");
            break;
        }
    }

    if (!found)
    {
        printf("Contact not found.\n");
    }

    fclose(file);
}

void searchContact()
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    char searchName[MAX_NAME_LEN];
    printf("Enter the name of the contact to search: ");
    fgets(searchName, MAX_NAME_LEN, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; // Remove newline

    Contact contact;
    int found = 0;

    while (fread(&contact, sizeof(Contact), 1, file))
    {
        if (strcmp(contact.name, searchName) == 0)
        {
            printf("\nContact Found:\n");
            printf("Name: %s\n", contact.name);
            printf("Phone: %s\n", contact.phone);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Contact not found.\n");
    }

    fclose(file);
}

void deleteContact()
{
    FILE *file = fopen(FILENAME, "rb");
    if (!file)
    {
        perror("Unable to open file");
        return;
    }

    char searchName[MAX_NAME_LEN];
    printf("Enter the name of the contact to delete: ");
    fgets(searchName, MAX_NAME_LEN, stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; // Remove newline

    FILE *tempFile = fopen("temp.dat", "wb");
    if (!tempFile)
    {
        perror("Unable to open temporary file");
        fclose(file);
        return;
    }

    Contact contact;
    int found = 0;

    while (fread(&contact, sizeof(Contact), 1, file))
    {
        if (strcmp(contact.name, searchName) == 0)
        {
            found = 1;
        }
        else
        {
            fwrite(&contact, sizeof(Contact), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (found)
    {
        remove(FILENAME);
        rename("temp.dat", FILENAME);
        printf("Contact deleted successfully.\n");
    }
    else
    {
        remove("temp.dat");
        printf("Contact not found.\n");
    }
}
