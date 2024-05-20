#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure to hold contact information
typedef struct
{
    char name[50];  // Contact name
    char phone[15]; // Contact phone number
    char email[50]; // Contact email address
} Contact;

// Define an array to hold the contacts and a counter for the number of contacts
Contact contacts[100];
int contactCount = 0;
const char *fileName = "contacts.dat"; // File to save and load contacts

// Function Prototypes
void addContact();
void viewContacts();
void editContact();
void searchContact();
void deleteContact();
void saveContacts();
void loadContacts();

int main()
{
    loadContacts(); // Load contacts from the file at the start

    int choice;
    while (1)
    {
        // Display menu options
        printf("\nContact Management System\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Edit Contact\n");
        printf("4. Search Contact\n");
        printf("5. Delete Contact\n");
        printf("6. Save Contacts\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); // Get user choice

        // Perform action based on user choice
        switch (choice)
        {
        case 1:
            addContact();
            break;
        case 2:
            viewContacts();
            break;
        case 3:
            editContact();
            break;
        case 4:
            searchContact();
            break;
        case 5:
            deleteContact();
            break;
        case 6:
            saveContacts();
            break;
        case 7:
            saveContacts(); // Save contacts before exiting
            exit(0);
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}

// Function to add a new contact
void addContact()
{
    if (contactCount >= 100)
    {
        printf("Contact list is full!\n");
        return;
    }

    // Get contact details from the user
    printf("Enter name: ");
    scanf(" %[^\n]", contacts[contactCount].name);
    printf("Enter phone: ");
    scanf(" %[^\n]", contacts[contactCount].phone);
    printf("Enter email: ");
    scanf(" %[^\n]", contacts[contactCount].email);

    contactCount++; // Increment contact count
    printf("Contact added successfully!\n");
}

// Function to view all contacts
void viewContacts()
{
    if (contactCount == 0)
    {
        printf("No contacts to display.\n");
        return;
    }

    // Display each contact
    for (int i = 0; i < contactCount; i++)
    {
        printf("Contact %d\n", i + 1);
        printf("Name: %s\n", contacts[i].name);
        printf("Phone: %s\n", contacts[i].phone);
        printf("Email: %s\n", contacts[i].email);
        printf("\n");
    }
}

// Function to edit an existing contact
void editContact()
{
    int index;
    printf("Enter contact index to edit (1-%d): ", contactCount);
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= contactCount)
    {
        printf("Invalid contact index!\n");
        return;
    }

    // Get new contact details from the user
    printf("Editing Contact %d\n", index + 1);
    printf("Enter new name: ");
    scanf(" %[^\n]", contacts[index].name);
    printf("Enter new phone: ");
    scanf(" %[^\n]", contacts[index].phone);
    printf("Enter new email: ");
    scanf(" %[^\n]", contacts[index].email);

    printf("Contact edited successfully!\n");
}

// Function to search for contacts by name
void searchContact()
{
    char name[50];
    printf("Enter name to search: ");
    scanf(" %[^\n]", name);

    // Display contacts that match the search term
    for (int i = 0; i < contactCount; i++)
    {
        if (strstr(contacts[i].name, name) != NULL)
        {
            printf("Contact %d\n", i + 1);
            printf("Name: %s\n", contacts[i].name);
            printf("Phone: %s\n", contacts[i].phone);
            printf("Email: %s\n", contacts[i].email);
            printf("\n");
        }
    }
}

// Function to delete a contact by index
void deleteContact()
{
    int index;
    printf("Enter contact index to delete (1-%d): ", contactCount);
    scanf("%d", &index);
    index--;

    if (index < 0 || index >= contactCount)
    {
        printf("Invalid contact index!\n");
        return;
    }

    // Shift remaining contacts to fill the gap
    for (int i = index; i < contactCount - 1; i++)
    {
        contacts[i] = contacts[i + 1];
    }
    contactCount--; // Decrement contact count

    printf("Contact deleted successfully!\n");
}

// Function to save contacts to a file
void saveContacts()
{
    FILE *file = fopen(fileName, "wb");
    if (!file)
    {
        printf("Failed to open file for writing!\n");
        return;
    }
    // Write contact count and contacts to the file
    fwrite(&contactCount, sizeof(int), 1, file);
    fwrite(contacts, sizeof(Contact), contactCount, file);
    fclose(file);
    printf("Contacts saved successfully!\n");
}

// Function to load contacts from a file
void loadContacts()
{
    FILE *file = fopen(fileName, "rb");
    if (!file)
    {
        return; // No file to load
    }
    // Read contact count and contacts from the file
    fread(&contactCount, sizeof(int), 1, file);
    fread(contacts, sizeof(Contact), contactCount, file);
    fclose(file);
}
