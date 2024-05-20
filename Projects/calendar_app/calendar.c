#include <stdio.h>

// Function to get the day of the week for a given date using Zeller's Congruence
int getDayOfWeek(int day, int month, int year)
{
    if (month < 3)
    {
        month += 12;
        year -= 1;
    }
    int K = year % 100;
    int J = year / 100;
    int h = (day + (13 * (month + 1)) / 5 + K + (K / 4) + (J / 4) + (5 * J)) % 7;
    return (h + 6) % 7; // Adjusting to make Sunday = 0
}

// Function to get the name of the day from the day number
const char *getDayName(int dayOfWeek)
{
    const char *dayNames[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    return dayNames[dayOfWeek];
}

// Function to check if a year is a leap year
int isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Function to get the number of days in a month
int getDaysInMonth(int month, int year)
{
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
    {
        return 29;
    }
    return daysInMonth[month - 1];
}

// Function to print the calendar for a given month and year
void printMonthCalendar(int month, int year)
{
    const char *monthNames[] = {"January", "February", "March", "April", "May", "June",
                                "July", "August", "September", "October", "November", "December"};

    printf("     %s %d\n", monthNames[month - 1], year);
    printf("Su Mo Tu We Th Fr Sa\n");

    int firstDay = getDayOfWeek(1, month, year);
    int daysInMonth = getDaysInMonth(month, year);

    // Print leading spaces
    for (int i = 0; i < firstDay; i++)
    {
        printf("   ");
    }

    // Print days of the month
    for (int day = 1; day <= daysInMonth; day++)
    {
        printf("%2d ", day);
        if ((day + firstDay) % 7 == 0)
        {
            printf("\n");
        }
    }
    if ((daysInMonth + firstDay) % 7 != 0)
    {
        printf("\n");
    }
}

// Main function
int main()
{
    int choice;
    do
    {
        printf("Calendar Application\n");
        printf("1. Find the day for a given date\n");
        printf("2. Display the calendar for a month\n");
        printf("3. Exit\n");
        printf("Enter your choice (1, 2, or 3): ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            int day, month, year;
            printf("Enter date (DD MM YYYY): ");
            scanf("%d %d %d", &day, &month, &year);
            int dayOfWeek = getDayOfWeek(day, month, year);
            printf("The day is: %s\n", getDayName(dayOfWeek));
        }
        else if (choice == 2)
        {
            int month, year;
            printf("Enter month and year (MM YYYY): ");
            scanf("%d %d", &month, &year);
            printMonthCalendar(month, year);
        }
        else if (choice != 3)
        {
            printf("Invalid choice\n");
        }
    } while (choice != 3);

    return 0;
}
