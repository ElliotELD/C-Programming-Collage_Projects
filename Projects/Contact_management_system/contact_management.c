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

    int choice; // variable for choosing option
    while (1)
    {
        printf("\n\n================================================================================\n");
        printf("                                 CONTACT MANAGEMENT SYSTEM                      \n");
        printf("================================================================================\n");
        printf("                                                                                \n");
        printf("                            (Choose your Action)                                \n");
        printf("                                                                                \n");
        printf("================================================================================\n");
        printf("  1. Add Contact                                                                \n");
        printf("================================================================================\n");
        printf("  2. View Contacts                                                              \n");
        printf("================================================================================\n");
        printf("  3. Edit Contact                                                               \n");
        printf("================================================================================\n");
        printf("  4. Search Contact                                                             \n");
        printf("================================================================================\n");
        printf("  5. Delete Contact                                                             \n");
        printf("================================================================================\n");
        printf("  6. Save Contacts                                                              \n");
        printf("================================================================================\n");
        printf("  7. Exit                                                                       \n");
        printf("================================================================================\n");
        printf("\nEnter your choice: ");
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
        printf("Please try to delete some Contacts\n");
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
    printf("\n");
    printf("*************************************************\n");
    printf("*                                               *\n");
    printf("*         Contact Added Successfully!           *\n");
    printf("*                                               *\n");
    printf("*************************************************\n");
    printf("\n");
}

// Function to view all contacts
void viewContacts()
{
    if (contactCount == 0)
    {
        printf("\n");
        printf("*************************************************\n");
        printf("*                                               *\n");
        printf("*            No Contacts to Display.            *\n");
        printf("*                                               *\n");
        printf("*************************************************\n");
        printf("\n");
        return;
    }

    // Display each contact
    for (int i = 0; i < contactCount; i++)
    {
        printf("\n");
        printf("=================================================\n");
        printf("                   Contact %d                    \n", i + 1);
        printf("=================================================\n");
        printf(" Name  : %-40s \n", contacts[i].name);
        printf(" Phone : %-40s \n", contacts[i].phone);
        printf(" Email : %-40s \n", contacts[i].email);
        printf("=================================================\n");
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
        printf("\n");
        printf("*************************************************\n");
        printf("*                                               *\n");
        printf("*            Invalid contact index!             *\n");
        printf("*                                               *\n");
        printf("*************************************************\n");
        printf("\n");
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

    printf("\n");
    printf("*************************************************\n");
    printf("*                                               *\n");
    printf("*            Contact edited successfully!       *\n");
    printf("*                                               *\n");
    printf("*************************************************\n");
    printf("\n");
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
            printf("\n");
            printf("*************************************************\n");
            printf("*                                               *\n");
            printf("*                Contact %d                      *\n", i + 1);
            printf("*                                               *\n");
            printf("*************************************************\n");
            printf("* Name  : %-37s *\n", contacts[i].name);
            printf("* Phone : %-37s *\n", contacts[i].phone);
            printf("* Email : %-37s *\n", contacts[i].email);
            printf("*************************************************\n");
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
    // condition
    if (index < 0 || index >= contactCount)
    {
        printf("\n");
        printf("*************************************************\n");
        printf("*                                               *\n");
        printf("*            Invalid contact index!             *\n");
        printf("*                                               *\n");
        printf("*************************************************\n");
        printf("\n");
        return;
    }

    // Shift remaining contacts to fill the gap
    for (int i = index; i < contactCount - 1; i++)
    {
        contacts[i] = contacts[i + 1];
    }
    contactCount--; // Decrement contact count

    printf("\n");
    printf("*************************************************\n");
    printf("*                                               *\n");
    printf("*            Contact deleted successfully!      *\n");
    printf("*                                               *\n");
    printf("*************************************************\n");
    printf("\n");
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

    if (contactCount == 0)
    {
        printf("\n");
        printf("*************************************************\n");
        printf("*                                               *\n");
        printf("*         No contacts to save.                  *\n");
        printf("*                                               *\n");
        printf("*************************************************\n");
        printf("\n");
    }
    else
    {
        printf("\n");
        printf("*************************************************\n");
        printf("*                                               *\n");
        printf("*         Contacts saved successfully!          *\n");
        printf("*                                               *\n");
        printf("*************************************************\n");
        printf("\n");
    }
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
