#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
#define MAX_PETS 100
#define MAX_STRING 100
 
typedef struct {
    int id;
    char name[MAX_STRING];
    char breed[MAX_STRING];
    int age;
    char gender[MAX_STRING];
    char description[MAX_STRING];
    char availability[MAX_STRING];
} Pet;
 
Pet pets[MAX_PETS];
int pet_count = 0;
 
// Function prototypes
void load_pets(const char *filename);
void save_pets(const char *filename);
void add_pet();
void list_pets();
void list_pets_sorted(int sort_criteria);
void update_pet();
void delete_pet();
void search_pets();
void search_pets_by_criteria();
void clear_input_buffer();
void to_lower(char *str);
int validate_input(const char *input, int is_numeric);
void menu();
 
int main() {
    const char *filename = "pets.csv";
    load_pets(filename);
 
    int choice;
    do {
        menu();
        printf("\nEnter your choice (1-7): ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();
 
        switch (choice) {
            case 1: add_pet(); break;
            case 2: {
                printf("\nSort by:\n1. Name\n2. Age\n3. Breed\nEnter choice: ");
                int sort_choice;
                scanf("%d", &sort_choice);
                clear_input_buffer();
                list_pets_sorted(sort_choice);
                break;
            }
            case 3: update_pet(); break;
            case 4: delete_pet(); break;
            case 5: search_pets_by_criteria(); break;
            case 6: save_pets(filename); break;
            case 7: save_pets(filename); printf("Data saved. Exiting...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
 
    return 0;
}
 
void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
 
void to_lower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}
 
int validate_input(const char *input, int is_numeric) {
    if (strlen(input) == 0) return 0;
 
    if (is_numeric) {
        for (int i = 0; input[i]; i++) {
            if (!isdigit(input[i])) return 0;
        }
    }
    return 1;
}
 
void load_pets(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("No existing data found. Starting fresh.\n");
        return;
    }
 
    char line[512];
    while (fgets(line, sizeof(line), file) && pet_count < MAX_PETS) {
        char *token = strtok(line, ",");
        if (!token) continue;
 
        pets[pet_count].id = atoi(token);
 
        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(pets[pet_count].name, token, MAX_STRING - 1);
 
        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(pets[pet_count].breed, token, MAX_STRING - 1);
 
        token = strtok(NULL, ",");
        if (!token) continue;
        pets[pet_count].age = atoi(token);
 
        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(pets[pet_count].gender, token, MAX_STRING - 1);
 
        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(pets[pet_count].description, token, MAX_STRING - 1);
 
        token = strtok(NULL, "\n");
        if (!token) continue;
        strncpy(pets[pet_count].availability, token, MAX_STRING - 1);
 
        pet_count++;
    }
 
    fclose(file);
    printf("Loaded %d pets from file.\n", pet_count);
}
 
void save_pets(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error saving data!\n");
        return;
    }
 
    for (int i = 0; i < pet_count; i++) {
        fprintf(file, "%d,%s,%s,%d,%s,%s,%s,%s\n",
        pets[i].id, pets[i].name, pets[i].breed, pets[i].age,
        pets[i].gender, pets[i].description, pets[i].availability);

    }
 
    fclose(file);
    printf("Data saved successfully!\n");
}
 
void add_pet() {
    if (pet_count >= MAX_PETS) {
        printf("Maximum pet capacity reached!\n");
        return;
    }
 
    char input[MAX_STRING];
 
    // Generate unique ID
    int new_id = 1;
    for (int i = 0; i < pet_count; i++) {
        if (pets[i].id >= new_id) {
            new_id = pets[i].id + 1;
        }
    }
    pets[pet_count].id = new_id;
 
    do {
        printf("Enter Name: ");
        fgets(input, MAX_STRING, stdin);
        input[strcspn(input, "\n")] = 0;
    } while (!validate_input(input, 0));
    strncpy(pets[pet_count].name, input, MAX_STRING - 1);
 
    do {
        printf("Enter Breed: ");
        fgets(input, MAX_STRING, stdin);
        input[strcspn(input, "\n")] = 0;
    } while (!validate_input(input, 0));
    strncpy(pets[pet_count].breed, input, MAX_STRING - 1);
 
    do {
        printf("Enter Age (0-30): ");
        fgets(input, MAX_STRING, stdin);
        input[strcspn(input, "\n")] = 0;
    } while (!validate_input(input, 1) || atoi(input) < 0 || atoi(input) > 30);
    pets[pet_count].age = atoi(input);
 
    do {
        printf("Enter Gender (Male/Female): ");
        fgets(input, MAX_STRING, stdin);
        input[strcspn(input, "\n")] = 0;
        to_lower(input);
    } while (strcmp(input, "male") != 0 && strcmp(input, "female") != 0);
    strncpy(pets[pet_count].gender, input, MAX_STRING - 1);
 
    printf("Enter Description: ");
    fgets(pets[pet_count].description, MAX_STRING, stdin);
    pets[pet_count].description[strcspn(pets[pet_count].description, "\n")] = 0;
 
    do {
        printf("Enter Availability (Available/On Hold/Adopted): ");
        fgets(input, MAX_STRING, stdin);
        input[strcspn(input, "\n")] = 0;
        to_lower(input);
    } while (strcmp(input, "available") != 0 && 
             strcmp(input, "on hold") != 0 && 
             strcmp(input, "adopted") != 0);
    strncpy(pets[pet_count].availability, input, MAX_STRING - 1);
 
    pet_count++;
    printf("Pet added successfully! ID assigned: %d\n", new_id);
}
 
int compare_by_name(const void *a, const void *b) {
    return strcmp(((Pet*)a)->name, ((Pet*)b)->name);
}
 
int compare_by_age(const void *a, const void *b) {
    return ((Pet*)a)->age - ((Pet*)b)->age;
}
 
int compare_by_breed(const void *a, const void *b) {
    return strcmp(((Pet*)a)->breed, ((Pet*)b)->breed);
}
 
void list_pets_sorted(int sort_criteria) {
    if (pet_count == 0) {
        printf("No pets in the system.\n");
        return;
    }
 
    // Create a temporary array for sorting
    Pet sorted_pets[MAX_PETS];
    memcpy(sorted_pets, pets, sizeof(Pet) * pet_count);
 
    switch (sort_criteria) {
        case 1: // Sort by name
            qsort(sorted_pets, pet_count, sizeof(Pet), compare_by_name);
            break;
        case 2: // Sort by age
            qsort(sorted_pets, pet_count, sizeof(Pet), compare_by_age);
            break;
        case 3: // Sort by breed
            qsort(sorted_pets, pet_count, sizeof(Pet), compare_by_breed);
            break;
        default:
            printf("Invalid sorting criteria.\n");
            return;
    }
 
    printf("\nList of Pets:\n");
    printf("%-5s %-15s %-15s %-5s %-10s %-30s %-15s\n",
           "ID", "Name", "Breed", "Age", "Gender", "Description", "Availability");
    printf("--------------------------------------------------------------------------------\n");
 
    for (int i = 0; i < pet_count; i++) {
        printf("%-5d %-15s %-15s %-5d %-10s %-30s %-15s\n",
               sorted_pets[i].id, sorted_pets[i].name, sorted_pets[i].breed,
               sorted_pets[i].age, sorted_pets[i].gender,
               sorted_pets[i].description, sorted_pets[i].availability);
    }
}
 
void update_pet() {
    if (pet_count == 0) {
        printf("No pets in the system.\n");

return;
    }
 
    int id;
    printf("Enter Pet ID to update: ");
    scanf("%d", &id);
    clear_input_buffer();
 
    for (int i = 0; i < pet_count; i++) {
        if (pets[i].id == id) {
            char input[MAX_STRING];
 
            do {
                printf("Enter new Name (or press Enter to keep '%s'): ", pets[i].name);
                fgets(input, MAX_STRING, stdin);
                input[strcspn(input, "\n")] = 0;
                if (strlen(input) > 0) {
                    strncpy(pets[i].name, input, MAX_STRING - 1);
                }
            } while (strlen(input) > 0 && !validate_input(input, 0));
 
            // Similar pattern for other fields...
            printf("Pet updated successfully!\n");
            return;
        }
    }
 
    printf("Pet with ID %d not found!\n", id);
}
 
void search_pets_by_criteria() {
    printf("\nSearch by:\n");
    printf("1. Breed\n");
    printf("2. Age Range\n");
    printf("3. Availability\n");
 
    int choice;
    printf("Enter choice: ");
    scanf("%d", &choice);
    clear_input_buffer();
 
    switch (choice) {
        case 1: {
            char breed[MAX_STRING];
            printf("Enter Breed: ");
            fgets(breed, MAX_STRING, stdin);
            breed[strcspn(breed, "\n")] = 0;
 
            printf("\nSearch Results:\n");
            printf("%-5s %-15s %-15s %-5s %-10s %-30s %-15s\n",
                   "ID", "Name", "Breed", "Age", "Gender", "Description", "Availability");
            printf("--------------------------------------------------------------------------------\n");
 
            int found = 0;
            for (int i = 0; i < pet_count; i++) {
                if (strcasecmp(pets[i].breed, breed) == 0) {
                    printf("%-5d %-15s %-15s %-5d %-10s %-30s %-15s\n",
                           pets[i].id, pets[i].name, pets[i].breed,
                           pets[i].age, pets[i].gender,
                           pets[i].description, pets[i].availability);
                    found = 1;
                }
            }
            if (!found) printf("No matching pets found.\n");
            break;
        }
        case 2: {
            int min_age, max_age;
            printf("Enter minimum age: ");
            scanf("%d", &min_age);
            printf("Enter maximum age: ");
            scanf("%d", &max_age);
            clear_input_buffer();
 
            printf("\nSearch Results:\n");
            printf("%-5s %-15s %-15s %-5s %-10s %-30s %-15s\n",
                   "ID", "Name", "Breed", "Age", "Gender", "Description", "Availability");
            printf("--------------------------------------------------------------------------------\n");
 
            int found = 0;
            for (int i = 0; i < pet_count; i++) {
                if (pets[i].age >= min_age && pets[i].age <= max_age) {
                    printf("%-5d %-15s %-15s %-5d %-10s %-30s %-15s\n",
                           pets[i].id, pets[i].name, pets[i].breed,
                           pets[i].age, pets[i].gender,
                           pets[i].description, pets[i].availability);
                    found = 1;
                }
            }
            if (!found) printf("No matching pets found.\n");
            break;
        }
        case 3: {
            char availability[MAX_STRING];
            printf("Enter Availability (Available/On Hold/Adopted): ");
            fgets(availability, MAX_STRING, stdin);
            availability[strcspn(availability, "\n")] = 0;
            to_lower(availability);
 
            printf("\nSearch Results:\n");
            printf("%-5s %-15s %-15s %-5s %-10s %-30s %-15s\n",
                   "ID", "Name", "Breed", "Age", "Gender", "Description", "Availability");
            printf("--------------------------------------------------------------------------------\n");
 
            int found = 0;
            for (int i = 0; i < pet_count; i++) {
                if
(strcasecmp(pets[i].availability, availability) == 0) {
                    printf("%-5d %-15s %-15s %-5d %-10s %-30s %-15s\n",
                           pets[i].id, pets[i].name, pets[i].breed,
                           pets[i].age, pets[i].gender,
                           pets[i].description, pets[i].availability);
                    found = 1;
                }
            }
            if (!found) printf("No matching pets found.\n");
            break;
        }
        default:
            printf("Invalid choice.\n");
    }
}
 
void menu() {
    printf("\n=== Pet Adoption Management System ===\n");
    printf("1. Add Pet\n");
printf("2. List Pets (with sorting options)\n");
    printf("3. Update Pet\n");
    printf("4. Delete Pet\n");
    printf("5. Search Pets\n");
    printf("6. Save Data\n");
    printf("7. Exit\n");
}
 
void delete_pet() {
    if (pet_count == 0) {
        printf("No pets in the system.\n");
        return;
    }
 
    int id;
    printf("Enter Pet ID to delete: ");
    scanf("%d", &id);
    clear_input_buffer();
 
    for (int i = 0; i < pet_count; i++) {
        if (pets[i].id == id) {
            // Ask for confirmation
            char confirm;
            printf("Are you sure you want to delete %s (ID: %d)? (y/n): ", 
                   pets[i].name, pets[i].id);
            scanf(" %c", &confirm);
            clear_input_buffer();
 
            if (tolower(confirm) == 'y') {
                // Shift remaining elements left
                for (int j = i; j < pet_count - 1; j++) {
                    pets[j] = pets[j + 1];
                }
                pet_count--;
                printf("Pet deleted successfully!\n");
            } else {
                printf("Deletion cancelled.\n");
            }
            return;
        }
    }
 
    printf("Pet with ID %d not found!\n", id);
}