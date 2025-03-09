#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

// Structure definition for a record
typedef struct {
    int part_number;
    char part_name[50];
    float part_size;
    char part_size_metric[10];
    float part_cost;
} Record;

// Global variables
int numRecords = 0;  // Tracks the number of records
static int numChanges = 0;  // Tracks the number of changes

// Function to print the menu
void printMenu() {
    printf("\nMenu:\n");
    printf("1) Print all records\n");
    printf("2) Add record\n");
    printf("3) Delete the last record\n");
    printf("4) Print number of records\n");
    printf("5) Print database size\n");
    printf("6) Print number of changes\n");
    printf("7) Exit\n");
    printf("Please enter your selection > ");
}

// Function to add a new record
void addRecord(Record** database) {
    // Allocate new memory
    Record* newDatabase = malloc((numRecords + 1) * sizeof(Record));
    if (newDatabase == NULL) {
        printf("Error: Memory allocation failed!\n");
        return;
    }

    // Copy the old data to the new memory (using pointer arithmetic)
    for (int i = 0; i < numRecords; i++) {
        *(newDatabase + i) = *(*database + i);
    }

    // Free the old memory
    free(*database);

    // Get new record data from the user
    printf("Enter part number: ");
    if (scanf_s("%d", &newDatabase[numRecords].part_number) != 1) {
        printf("Error: Invalid input for part number!\n");
        free(newDatabase);
        return;
    }

    printf("Enter part name: ");
    scanf_s("%s", newDatabase[numRecords].part_name, (unsigned)_countof(newDatabase[numRecords].part_name));

    printf("Enter part size: ");
    if (scanf_s("%f", &newDatabase[numRecords].part_size) != 1) {
        printf("Error: Invalid input for part size!\n");
        free(newDatabase);
        return;
    }

    printf("Enter part size metric: ");
    scanf_s("%s", newDatabase[numRecords].part_size_metric, (unsigned)_countof(newDatabase[numRecords].part_size_metric));

    printf("Enter part cost: ");
    if (scanf_s("%f", &newDatabase[numRecords].part_cost) != 1) {
        printf("Error: Invalid input for part cost!\n");
        free(newDatabase);
        return;
    }

    // Assign new memory to the database
    *database = newDatabase;

    numRecords++;
    numChanges++;
    printf("Record added successfully!\n");
}

// Function to delete the last record
void deleteLastRecord(Record** database) {
    if (numRecords == 0) {
        printf("No records to delete.\n");
        return;
    }

    // Allocate new memory for the reduced number of records
    Record* newDatabase = malloc((numRecords - 1) * sizeof(Record));
    if (newDatabase == NULL) {
        printf("Error: Memory allocation failed!\n");
        return;
    }

    // Copy the old data to the new memory (excluding the last record)
    for (int i = 0; i < numRecords - 1; i++) {
        *(newDatabase + i) = *(*database + i);
    }

    // Free the old memory
    free(*database);

    // Assign the new memory to the database
    *database = newDatabase;

    numRecords--;
    numChanges++;
    printf("Last record deleted successfully!\n");
}

// Function to print all records
void printRecords(Record* database) {
    if (numRecords == 0) {
        printf("No records to display.\n");
        return;
    }

    for (int i = 0; i < numRecords; i++) {
        printf("Record %d:\n", i + 1);
        printf("Part number: %d\n", database[i].part_number);
        printf("Part name: %s\n", database[i].part_name);
        printf("Part size: %.2f %s\n", database[i].part_size, database[i].part_size_metric);
        printf("Part cost: $%.2f\n", database[i].part_cost);
        printf("--------------------\n");
    }
}

// Function to print the number of records
void printNumRecords() {
    printf("Number of records: %d\n", numRecords);
}

// Function to print the database size
void printDatabaseSize() {
    printf("Database size: %zu bytes\n", numRecords * sizeof(Record));
}

// Function to print the number of changes
void printNumChanges() {
    printf("Number of changes made: %d\n", numChanges);
}

int main(int argc, char* argv[]) {
    Record* database = NULL;
    int choice;

    do {
        printMenu();
        if (scanf_s("%d", &choice) != 1) {
            printf("Invalid input! Exiting...\n");
            break;
        }

        switch (choice) {
        case 1:
            printRecords(database);
            break;
        case 2:
            addRecord(&database);
            break;
        case 3:
            deleteLastRecord(&database);
            break;
        case 4:
            printNumRecords();
            break;
        case 5:
            printDatabaseSize();
            break;
        case 6:
            printNumChanges();
            break;
        case 7:
            printf("Exiting the program...\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 7);

    free(database);  // Free dynamically allocated memory before exiting
    return 0;
}
