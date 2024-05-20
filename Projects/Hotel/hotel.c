#include <stdio.h>
#include <string.h>

// Structure to describe a hotel
struct Hotel
{
    char name[50];
    char address[100];
    int grade;
    float avgRoomCharge;
    int numRooms;
};

// Function prototypes
void printHotelsByGrade(struct Hotel hotels[], int numHotels, int targetGrade);
void printHotelsWithLessCharge(struct Hotel hotels[], int numHotels, float maxCharge);

int main()
{
    struct Hotel hotels[50]; // Assuming maximum 50 hotels

    int numHotels;
    printf("Enter the number of hotels: ");
    scanf("%d", &numHotels);

    // Input hotel details
    for (int i = 0; i < numHotels; i++)
    {
        printf("\nEnter details for Hotel %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", hotels[i].name);
        printf("Address: ");
        scanf("%s", hotels[i].address);
        printf("Grade (1-5): ");
        scanf("%d", &hotels[i].grade);
        printf("Average Room Charge: ");
        scanf("%f", &hotels[i].avgRoomCharge);
        printf("Number of Rooms: ");
        scanf("%d", &hotels[i].numRooms);
    }

    // Menu for operations
    int choice;
    float maxCharge;
    printf("\nMenu:\n");
    printf("1. Print hotels of a given grade in order of charges\n");
    printf("2. Print hotels with room charges less than a given value\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
    {
        int targetGrade;
        printf("Enter the grade: ");
        scanf("%d", &targetGrade);
        printHotelsByGrade(hotels, numHotels, targetGrade);
        break;
    }
    case 2:
    {
        printf("Enter the maximum room charge: ");
        scanf("%f", &maxCharge);
        printHotelsWithLessCharge(hotels, numHotels, maxCharge);
        break;
    }
    default:
        printf("Invalid choice!\n");
    }

    return 0;
}

// Function to print hotels of a given grade in order of charges
void printHotelsByGrade(struct Hotel hotels[], int numHotels, int targetGrade)
{
    printf("\nHotels with grade %d in order of charges:\n", targetGrade);
    printf("Name\t\t\tAddress\t\t\tAvg Room Charge\n");
    printf("--------------------------------------------------------\n");

    // Sorting hotels by average room charge
    for (int i = 0; i < numHotels - 1; i++)
    {
        for (int j = 0; j < numHotels - i - 1; j++)
        {
            if (hotels[j].grade == targetGrade && hotels[j].avgRoomCharge > hotels[j + 1].avgRoomCharge)
            {
                // Swap hotels
                struct Hotel temp = hotels[j];
                hotels[j] = hotels[j + 1];
                hotels[j + 1] = temp;
            }
        }
    }

    // Print hotels
    for (int i = 0; i < numHotels; i++)
    {
        if (hotels[i].grade == targetGrade)
        {
            printf("%-20s %-30s %.2f\n", hotels[i].name, hotels[i].address, hotels[i].avgRoomCharge);
        }
    }
}

// Function to print hotels with room charges less than a given value
void printHotelsWithLessCharge(struct Hotel hotels[], int numHotels, float maxCharge)
{
    printf("\nHotels with room charges less than %.2f:\n", maxCharge);
    printf("Name\t\t\tAddress\t\t\tAvg Room Charge\n");
    printf("--------------------------------------------------------\n");

    // Print hotels with charges less than the given value
    for (int i = 0; i < numHotels; i++)
    {
        if (hotels[i].avgRoomCharge < maxCharge)
        {
            printf("%-20s %-30s %.2f\n", hotels[i].name, hotels[i].address, hotels[i].avgRoomCharge);
        }
    }
}
