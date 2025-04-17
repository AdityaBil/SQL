#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>
#include<dirent.h>

// Constants
#define MAX_ROWS 100
#define MAX_COLS 10
#define MAX_STR_LEN 50
#define MAX_DB_NAME 50
#define MAX_LOGIN_ID 50
#define MAX_PASSWORD 5
#define HASH_SIZE 64

// Structure declarations
struct Cell {
    char str_value[MAX_STR_LEN];
    int int_value;
    float float_value;
    char data_type;
};

struct Table {
    char name[MAX_DB_NAME];
    int rows;
    int columns;
    char row_names[MAX_ROWS][MAX_STR_LEN];
    char column_names[MAX_COLS][MAX_STR_LEN];
    struct Cell data[MAX_ROWS][MAX_COLS];
    char column_types[MAX_COLS];
};

struct Book {
    char title[50];
    char author[50];
    int available;
    char due_date[20];
};

struct Train {
    char name[50];
    int number;
    char time[20];
    char date[20];
    char location[50];
};

struct Ticket {
    char personal_id[20];
    char train_name[50];
    float ticket_price;
};

struct Contact {
    char name[50];
    char phone[20];
    char email[50];
    char address[100];
};

struct Office {
    char department[50];
    char employee_name[50];
    char position[50];
    float salary;
    char join_date[20];
};

struct Student {
    char name[50];
    int roll_number;
    char course[50];
    char department[50];
    float cgpa;
    char admission_date[20];
};

// Define Student Structure
typedef struct {
    int roll;
    char name[50];
    char course[50];
    float marks;
} Student;

// Function Prototypes
void encrypt(char *str, int key);
void decrypt(char *str, int key);
void store_password(const char *password);
int authenticate_user(void);
void initialize_password_storage(void);
int login_or_register(void);
int is_valid_database_name(const char *name);
void show_existing_databases(void);
int create_database(void);
int access_database(void);
void Delete_Database(void);
void Table_sorting(void);
void Student_Management(void);
void Library_Management(void);
void Ticket_Management(void);
void Employee_Management(void);
void Book_Management(void);
void Movie_Management(void);
void Music_Management(void);
void Restaurant_Management(void);
void Hotel_Management(void);
void Car_Management(void);
void Contact_Management(void);
int pre_made_libraries(void);
void sort_table(struct Table *table, int column_index, int ascending);
void display_sorted_table(struct Table *table);
void test_table_sorting(void);
void Modify_Table(void);
void create_table_in_database(char *database_name);
int show_tables_in_database(char *database_name);
void modify_existing_table(char *database_name);
void Office_Management(void);
void display_table_data(char *database_name);
void sort_table_in_database(char *database_name);
void display_zron_logo();
void input_table_data(char *database_name);

// Function implementations
void encrypt(char *str, int key) {
    while (*str) {
        *str = *str + key;
        str++;
    }
}

void decrypt(char *str, int key) {
    while (*str) {
        *str = *str - key;
        str++;
    }
}

void store_password(const char *password) {
    FILE *fptr = fopen("passwords.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file to store password\n");
        return;
    }
    fprintf(fptr, "%s\n", password);
    fclose(fptr);
}

void initialize_password_storage(void) {
    char stored_password[5] = "pass"; // Example 4-character password
    int key = 4; // Example encryption key

    // Encrypt the stored password
    encrypt(stored_password, key);

    // Store the encrypted password
    store_password(stored_password);
}

int is_valid_database_name(const char *name) {
    if (name == NULL || strlen(name) == 0 || strlen(name) >= MAX_DB_NAME) {
        return 0;
    }
    
    // Check for invalid characters
    for (int i = 0; name[i] != '\0'; i++) {
        if (!isalnum(name[i]) && name[i] != '_' && name[i] != '-') {
            return 0;
        }
    }
    return 1;
}

int authenticate_user(void) {
    char login_id[MAX_LOGIN_ID];
    char password[MAX_PASSWORD];
    char stored_login_id[MAX_LOGIN_ID];
    char stored_password[MAX_PASSWORD];
    int key = 4;

    printf("Enter login ID: ");
    if (scanf("%49s", login_id) != 1) {
        printf("Invalid input\n");
        while (getchar() != '\n'); // Clear input buffer
        return 0;
    }

    printf("Enter 4-character password: ");
    if (scanf("%4s", password) != 1) {
        printf("Invalid input\n");
        while (getchar() != '\n'); // Clear input buffer
        return 0;
    }

    // Read stored credentials
    FILE *fptr = fopen("credentials.txt", "r");
    if (fptr == NULL) {
        printf("Error reading credentials\n");
        return 0;
    }

    if (fscanf(fptr, "%49s\n%4s\n", stored_login_id, stored_password) != 2) {
        printf("Error reading stored credentials\n");
        fclose(fptr);
        return 0;
    }
    fclose(fptr);

    // Encrypt the entered password
    encrypt(password, key);

    // Check if login ID and encrypted password match the stored values
    if (strcmp(login_id, stored_login_id) == 0 && strcmp(password, stored_password) == 0) {
        // Decrypt the password for further use
        decrypt(password, key);
        return 1; // Authentication successful
    } else {
        printf("Invalid login ID or password\n");
        return 0; // Authentication failed
    }
}

int login_or_register(void) {
    int choice;
    char new_login_id[MAX_LOGIN_ID];
    char new_password[MAX_PASSWORD];
    int key = 4;

    printf("\n========== Authentication System ==========\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("Enter your choice: ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input\n");
        while (getchar() != '\n');
        return 0;
    }

    if (choice == 1) {
        return authenticate_user();
    } else if (choice == 2) {
        printf("Enter new login ID (max 49 chars): ");
        if (scanf("%49s", new_login_id) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');
            return 0;
        }

        printf("Enter new 4-character password: ");
        if (scanf("%4s", new_password) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');
            return 0;
        }

        // Encrypt the new password
        encrypt(new_password, key);

        // Store the new login ID and encrypted password
        FILE *fptr = fopen("credentials.txt", "w");
        if (fptr == NULL) {
            printf("Error opening file to store credentials\n");
            return 0;
        }
        
        if (fprintf(fptr, "%s\n%s\n", new_login_id, new_password) < 0) {
            printf("Error writing credentials\n");
            fclose(fptr);
            return 0;
        }
        
        fclose(fptr);
        printf("Registration successful! Please login with your new credentials.\n");
        return login_or_register(); // Recursive call to login after registration
    } else {
        printf("Invalid choice\n");
        return 0;
    }
}

// Function to sort table based on a column
void sort_table(struct Table* table, int column_index, int ascending) {
    if (column_index < 0 || column_index >= table->columns) {
        printf("Invalid column index for sorting!\n");
        return;
    }

    struct Cell* temp_column = malloc(table->rows * sizeof(struct Cell));
    int* indices = malloc(table->rows * sizeof(int));
    
    if (temp_column == NULL || indices == NULL) {
        printf("Memory allocation failed!\n");
        free(temp_column);
        free(indices);
        return;
    }
    
    for (int i = 0; i < table->rows; i++) {
        indices[i] = i;
        temp_column[i] = table->data[i][column_index];
    }

    char data_type = table->column_types[column_index];
    
    for (int i = 0; i < table->rows - 1; i++) {
        for (int j = 0; j < table->rows - i - 1; j++) {
            int swap = 0;
            
            switch(data_type) {
                case 'i':
                    swap = ascending ? 
                        (temp_column[j].int_value > temp_column[j+1].int_value) :
                        (temp_column[j].int_value < temp_column[j+1].int_value);
                    break;
                case 'f':
                    swap = ascending ? 
                        (temp_column[j].float_value > temp_column[j+1].float_value) :
                        (temp_column[j].float_value < temp_column[j+1].float_value);
                    break;
                case 's':
                    swap = ascending ? 
                        (strcmp(temp_column[j].str_value, temp_column[j+1].str_value) > 0) :
                        (strcmp(temp_column[j].str_value, temp_column[j+1].str_value) < 0);
                    break;
            }
            
            if (swap) {
                struct Cell temp_cell = temp_column[j];
                temp_column[j] = temp_column[j+1];
                temp_column[j+1] = temp_cell;
                
                int temp_index = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = temp_index;
            }
        }
    }

    struct Table temp_table = *table;
    
    for (int i = 0; i < table->rows; i++) {
        strcpy(temp_table.row_names[i], table->row_names[indices[i]]);
        for (int j = 0; j < table->columns; j++) {
            temp_table.data[i][j] = table->data[indices[i]][j];
        }
    }
    
    *table = temp_table;
    
    free(temp_column);
    free(indices);
    
    printf("Table sorted successfully based on column %s (%s)\n", 
           table->column_names[column_index], 
           ascending ? "ascending" : "descending");
}

// Function to display sorted table
void display_sorted_table(struct Table* table) {
    // Display column headers
    printf("\nTable: %s\n", table->name);
    for (int i = 0; i < table->columns; i++) {
        printf("%-15s", table->column_names[i]);
    }
    printf("\n");
    
    // Display separator
    for (int i = 0; i < table->columns * 15; i++) {
        printf("-");
    }
    printf("\n");
    
    // Display data
    for (int i = 0; i < table->rows; i++) {
        for (int j = 0; j < table->columns; j++) {
            switch(table->column_types[j]) {
                case 'i':
                    printf("%-15d", table->data[i][j].int_value);
                    break;
                case 'f':
                    printf("%-15.2f", table->data[i][j].float_value);
                    break;
                case 's':
                    printf("%-15s", table->data[i][j].str_value);
                    break;
            }
        }
        printf("\n");
    }
}

// Function to test the sorting functionality
void test_table_sorting() {
    struct Table test_table;
    strcpy(test_table.name, "Test Table");
    test_table.rows = 5;
    test_table.columns = 3;
    
    // Set column names and types
    strcpy(test_table.column_names[0], "ID");
    strcpy(test_table.column_names[1], "Name");
    strcpy(test_table.column_names[2], "Score");
    
    test_table.column_types[0] = 'i';  // Integer
    test_table.column_types[1] = 's';  // String
    test_table.column_types[2] = 'f';  // Float
    
    // Add sample data
    for (int i = 0; i < test_table.rows; i++) {
        // ID column
        test_table.data[i][0].int_value = 5 - i;
        
        // Name column
        sprintf(test_table.data[i][1].str_value, "Person%d", i+1);
        
        // Score column
        test_table.data[i][2].float_value = (float)(rand() % 100);
    }
    
    printf("Original Table:\n");
    display_sorted_table(&test_table);
    
    printf("\nSorting by ID (ascending):\n");
    sort_table(&test_table, 0, 1);
    display_sorted_table(&test_table);
    
    printf("\nSorting by Name (ascending):\n");
    sort_table(&test_table, 1, 1);
    display_sorted_table(&test_table);
    
    printf("\nSorting by Score (descending):\n");
    sort_table(&test_table, 2, 0);
    display_sorted_table(&test_table);
}

void Modify_Table(void) {
    char database_name[MAX_DB_NAME];
    printf("\nEnter database name: ");
    scanf("%49s", database_name);

    char table_name[MAX_STR_LEN];
    printf("Enter table name: ");
    scanf("%49s", table_name);

    char table_filename[MAX_STR_LEN];
    snprintf(table_filename, sizeof(table_filename), "%s_%s.db", database_name, table_name);

    FILE *fptr = fopen(table_filename, "r");
    if (fptr == NULL) {
        printf("Table does not exist\n");
        return;
    }

    struct Table table;
    fscanf(fptr, "Table: %s\nRows: %d\nColumns: %d\n\n", table.name, &table.rows, &table.columns);
    
    // Read column names and types
    fscanf(fptr, "Column Names: ");
    for (int i = 0; i < table.columns; i++) {
        fscanf(fptr, "%s", table.column_names[i]);
    }
    fscanf(fptr, "\nColumn Types: ");
    for (int i = 0; i < table.columns; i++) {
        fscanf(fptr, " %c", &table.column_types[i]);
    }

    // Read data
    fscanf(fptr, "\n\nData:\n");
    for (int i = 0; i < table.rows; i++) {
        for (int j = 0; j < table.columns; j++) {
            switch(table.column_types[j]) {
                case 'i':
                    fscanf(fptr, "%d", &table.data[i][j].int_value);
                    break;
                case 'f':
                    fscanf(fptr, "%f", &table.data[i][j].float_value);
                    break;
                case 's':
                    fscanf(fptr, "%s", table.data[i][j].str_value);
                    break;
            }
        }
    }
    fclose(fptr);

    // Display current table data
    printf("\nCurrent table data:\n");
    display_sorted_table(&table);

    // Modification options
    int choice;
    do {
        printf("\nModification options:\n");
        printf("1. Modify specific cell\n");
        printf("2. Sort table by column\n");
        printf("3. Save and exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: {
                int row, col;
                printf("Enter row index (0-%d): ", table.rows - 1);
                scanf("%d", &row);
                printf("Enter column index (0-%d): ", table.columns - 1);
                scanf("%d", &col);

                if (row >= 0 && row < table.rows && col >= 0 && col < table.columns) {
                    printf("Enter new value for %s (%c): ", table.column_names[col], table.column_types[col]);
                    switch(table.column_types[col]) {
                        case 'i':
                            scanf("%d", &table.data[row][col].int_value);
                            break;
                        case 'f':
                            scanf("%f", &table.data[row][col].float_value);
                            break;
                        case 's':
                            scanf("%49s", table.data[row][col].str_value);
                            break;
                    }
                    printf("Cell modified successfully!\n");
                } else {
                    printf("Invalid indices!\n");
                }
                break;
            }
            case 2: {
                int col, ascending;
                printf("Enter column index to sort (0-%d): ", table.columns - 1);
                scanf("%d", &col);
                printf("Sort order (1-ascending, 0-descending): ");
                scanf("%d", &ascending);
                if (col >= 0 && col < table.columns) {
                    sort_table(&table, col, ascending);
                    printf("\nSorted table:\n");
                    display_sorted_table(&table);
                } else {
                    printf("Invalid column index!\n");
                }
                break;
            }
            case 3: {
                // Save modified table
                fptr = fopen(table_filename, "w");
                if (fptr == NULL) {
                    printf("Error saving table\n");
                    return;
                }
                fprintf(fptr, "Table: %s\nRows: %d\nColumns: %d\n\n", table.name, table.rows, table.columns);
                fprintf(fptr, "Column Names: ");
                for (int i = 0; i < table.columns; i++) {
                    fprintf(fptr, "%s ", table.column_names[i]);
                }
                fprintf(fptr, "\nColumn Types: ");
                for (int i = 0; i < table.columns; i++) {
                    fprintf(fptr, "%c ", table.column_types[i]);
                }
                fprintf(fptr, "\n\nData:\n");

                for (int i = 0; i < table.rows; i++) {
                    for (int j = 0; j < table.columns; j++) {
                        switch(table.column_types[j]) {
                            case 'i':
                                fprintf(fptr, "%d ", table.data[i][j].int_value);
                                break;
                            case 'f':
                                fprintf(fptr, "%.2f ", table.data[i][j].float_value);
                                break;
                            case 's':
                                fprintf(fptr, "%s ", table.data[i][j].str_value);
                                break;
                        }
                    }
                    fprintf(fptr, "\n");
                }
                fclose(fptr);
                printf("Table saved successfully!\n");
                break;
            }
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 3);
}

void show_existing_databases(void) {
    DIR *d;
    struct dirent *dir;
    int count = 0;
    
    d = opendir(".");
    if (d == NULL) {
        printf("Error accessing directory\n");
        return;
    }

    printf("\nExisting Databases:\n");
    while ((dir = readdir(d)) != NULL) {
        if (strstr(dir->d_name, ".db") != NULL) {
            char *name = strdup(dir->d_name);
            if (name) {
                name[strlen(name) - 3] = '\0';
                printf("%d. %s\n", ++count, name);
                free(name);
            }
        }
    }
    closedir(d);

    if (count == 0) {
        printf("No databases found.\n");
    }
}

void create_table_in_database(char *database_name) {
    if (!is_valid_database_name(database_name)) {
        printf("Invalid database name\n");
        return;
    }

    char filename[MAX_DB_NAME + 4];
    snprintf(filename, sizeof(filename), "%s.db", database_name);

    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Database does not exist\n");
        return;
    }
    fclose(fptr);

    char table_name[MAX_STR_LEN];
    int rows, cols;

    printf("Enter table name: ");
    if (scanf("%49s", table_name) != 1) {
        printf("Invalid input\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter number of rows (max %d): ", MAX_ROWS);
    if (scanf("%d", &rows) != 1 || rows <= 0 || rows > MAX_ROWS) {
        printf("Invalid number of rows\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter number of columns (max %d): ", MAX_COLS);
    if (scanf("%d", &cols) != 1 || cols <= 0 || cols > MAX_COLS) {
        printf("Invalid number of columns\n");
        while (getchar() != '\n');
        return;
    }

    // Create table file
    char table_filename[MAX_STR_LEN];
    snprintf(table_filename, sizeof(table_filename), "%s_%s.db", database_name, table_name);
    
    fptr = fopen(table_filename, "w");
    if (fptr == NULL) {
        printf("Error creating table\n");
        return;
    }

    fprintf(fptr, "Table: %s\nRows: %d\nColumns: %d\n\n", table_name, rows, cols);
    fclose(fptr);

    // Update database file to include the new table
    fptr = fopen(filename, "a");
    if (fptr == NULL) {
        printf("Error updating database\n");
        return;
    }

    fprintf(fptr, "%s\n", table_name);
    fclose(fptr);
    printf("Table created successfully!\n");
}

int show_tables_in_database(char *database_name) {
    if (!is_valid_database_name(database_name)) {
        printf("Invalid database name\n");
        return 0;
    }

    char filename[MAX_DB_NAME + 4];
    snprintf(filename, sizeof(filename), "%s.db", database_name);

    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Database does not exist\n");
        return 0;
    }

    char line[MAX_STR_LEN];
    int found_tables = 0;
    int count = 0;

    // Skip database name line
    if (fgets(line, sizeof(line), fptr) == NULL) {
        printf("Error reading database file\n");
        fclose(fptr);
        return 0;
    }

    // Skip "Tables:" line
    if (fgets(line, sizeof(line), fptr) == NULL) {
        printf("Error reading database file\n");
        fclose(fptr);
        return 0;
    }

    printf("\nTables in database '%s':\n", database_name);
    while (fgets(line, sizeof(line), fptr) != NULL) {
        line[strcspn(line, "\n")] = 0; // Remove newline
        if (strlen(line) > 0) {
            printf("%d. %s\n", ++count, line);
            found_tables = 1;
        }
    }

    fclose(fptr);
    if (!found_tables) {
        printf("No tables found in the database.\n");
    }
    return found_tables;
}

void modify_existing_table(char *database_name) {
    if (!show_tables_in_database(database_name)) {
        return;
    }

    char table_name[MAX_STR_LEN];
    printf("\nEnter table name to modify: ");
    if (scanf("%49s", table_name) != 1) {
        printf("Invalid input\n");
        while (getchar() != '\n');
        return;
    }

    char table_filename[MAX_STR_LEN];
    snprintf(table_filename, sizeof(table_filename), "%s_%s.db", database_name, table_name);

    FILE *fptr = fopen(table_filename, "r");
    if (fptr == NULL) {
        printf("Table does not exist\n");
        return;
    }
    fclose(fptr);

    printf("Table modification will be implemented in a future update.\n");
}

int access_database(void) {
    DIR *d;
    struct dirent *dir;
    char database_names[100][MAX_DB_NAME];  // Array to store database names
    int count = 0;
    
    d = opendir(".");
    if (d == NULL) {
        printf("Error accessing directory\n");
        return -1;
    }

    printf("\nExisting Databases:\n");
    while ((dir = readdir(d)) != NULL && count < 100) {
        if (strstr(dir->d_name, ".db") != NULL) {
            char *name = strdup(dir->d_name);
            if (name) {
                name[strlen(name) - 3] = '\0';  // Remove .db extension
                strcpy(database_names[count], name);
                printf("%d. %s\n", count + 1, name);
                free(name);
                count++;
            }
        }
    }
    closedir(d);

    if (count == 0) {
        printf("No databases found.\n");
        return -1;
    }

    int choice;
    printf("\nEnter database name to access: ");
    if (scanf("%d", &choice) != 1 || choice < 1 || choice > count) {
        printf("Invalid choice\n");
        while (getchar() != '\n');
        return -1;
    }

    // Use the selected database name
    char *database_name = database_names[choice - 1];
    
    if (!is_valid_database_name(database_name)) {
        printf("Invalid database name\n");
        return -1;
    }

    char filename[MAX_DB_NAME + 4];
    snprintf(filename, sizeof(filename), "%s.db", database_name);

    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("Database does not exist\n");
        return -1;
    }

    // Check if database is empty
    fseek(fptr, 0, SEEK_END);
    if (ftell(fptr) == 0) {
        printf("Database is empty\n");
        fclose(fptr);
        return -1;
    }
    fseek(fptr, 0, SEEK_SET);

    int menu_choice;
    do {
        printf("\n========== Database: %s ==========\n", database_name);
        printf("1. Show tables\n");
        printf("2. Create table\n");
        printf("3. Input table data\n");
        printf("4. Modify table\n");
        printf("5. Display table data\n");
        printf("6. Sort table\n");
        printf("7. Back to main menu\n");
        printf("Enter your choice: ");

        if (scanf("%d", &menu_choice) != 1) {
            printf("Invalid input\n");
            while (getchar() != '\n');
            continue;
        }

        switch (menu_choice) {
            case 1:
                if (!show_tables_in_database(database_name)) {
                    printf("No tables found in the database.\n");
                }
                break;
            case 2:
                create_table_in_database(database_name);
                break;
            case 3:
                input_table_data(database_name);
                break;
            case 4:
                Modify_Table();
                break;
            case 5:
                display_table_data(database_name);
                break;
            case 6:
                sort_table_in_database(database_name);
                break;
            case 7:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (menu_choice != 7);
    
    fclose(fptr);
    return 0;
}

void Delete_Database() {
    char database_name[MAX_DB_NAME];
    printf("\nEnter database name to delete: ");
    if (scanf("%49s", database_name) != 1) {
        printf("Invalid input\n");
        while (getchar() != '\n');
        return;
    }

    char filename[MAX_DB_NAME + 4];
    snprintf(filename, sizeof(filename), "%s.db", database_name);

    if (remove(filename) == 0) {
        printf("Database deleted successfully\n");
    } else {
        printf("Error deleting database\n");
    }
}

void display_table_data(char *database_name) {
    char table_name[MAX_STR_LEN];
    printf("\nEnter table name to display: ");
    if (scanf("%49s", table_name) != 1) {
        printf("Invalid input\n");
        while (getchar() != '\n');
        return;
    }

    char table_filename[MAX_STR_LEN];
    snprintf(table_filename, sizeof(table_filename), "%s_%s.db", database_name, table_name);

    FILE *fptr = fopen(table_filename, "r");
    if (fptr == NULL) {
        printf("Table does not exist\n");
        return;
    }

    struct Table table;
    char line[MAX_STR_LEN];
    
    // Read table header
    fscanf(fptr, "Table: %s\nRows: %d\nColumns: %d\n\n", 
           table.name, &table.rows, &table.columns);

    // Display column headers
    printf("\nTable: %s\n", table.name);
    printf("Columns: ");
    for (int i = 0; i < table.columns; i++) {
        printf("%s ", table.column_names[i]);
    }
    printf("\n");

    // Display data
    printf("\nData:\n");
    while (fgets(line, sizeof(line), fptr) != NULL) {
        printf("%s", line);
    }

    fclose(fptr);
}

void sort_table_in_database(char *database_name) {
    char table_name[MAX_STR_LEN];
    printf("\nEnter table name to sort: ");
    if (scanf("%49s", table_name) != 1) {
        printf("Invalid input\n");
        while (getchar() != '\n');
        return;
    }

    char table_filename[MAX_STR_LEN];
    snprintf(table_filename, sizeof(table_filename), "%s_%s.db", database_name, table_name);

    FILE *fptr = fopen(table_filename, "r");
    if (fptr == NULL) {
        printf("Table does not exist\n");
        return;
    }

    struct Table table;
    fscanf(fptr, "Table: %s\nRows: %d\nColumns: %d\n\n", 
           table.name, &table.rows, &table.columns);

    // Display available columns for sorting
    printf("\nAvailable columns for sorting:\n");
    for (int i = 0; i < table.columns; i++) {
        printf("%d. %s\n", i + 1, table.column_names[i]);
    }

    int column_choice;
    printf("\nEnter column number to sort by: ");
    if (scanf("%d", &column_choice) != 1 || column_choice < 1 || column_choice > table.columns) {
        printf("Invalid column choice\n");
        fclose(fptr);
        return;
    }

    int sort_order;
    printf("Sort order (1 for ascending, 0 for descending): ");
    if (scanf("%d", &sort_order) != 1 || (sort_order != 0 && sort_order != 1)) {
        printf("Invalid sort order\n");
        fclose(fptr);
        return;
    }

    // Sort the table
    sort_table(&table, column_choice - 1, sort_order);
    
    // Display sorted table
    display_sorted_table(&table);

    fclose(fptr);
}

void display_zron_logo() {
    printf("\n");
    printf("+-----------------------------------------+\n");
    printf(" _______ _____ ___       _  _____ \n");
    printf("|___   / |  ___| \\    | |/ /  _ \\\n");
    printf("   /  /  | |__ | |\\   | || | | | |\n");
    printf("  /  /   |  __|| | \\  | || | | | |\n");
    printf(" /  /__  | |___| |  \\ / /| | |_| |\n");
    printf("/_____ |  \\____\\   \\_/  \\___ / \n");
    printf("+-----------------------------------------+\n");
    printf("\n");
}

// Function to input table data
void input_table_data(char *database_name) {
    char table_name[MAX_STR_LEN];
    printf("\nEnter table name: ");
    if (scanf("%49s", table_name) != 1) {
        printf("Invalid input\n");
        while (getchar() != '\n');
        return;
    }

    char table_filename[MAX_STR_LEN];
    snprintf(table_filename, sizeof(table_filename), "%s_%s.db", database_name, table_name);

    FILE *fptr = fopen(table_filename, "w");
    if (fptr == NULL) {
        printf("Error creating table file\n");
        return;
    }

    int rows, cols;
    printf("Enter number of rows: ");
    scanf("%d", &rows);
    printf("Enter number of columns: ");
    scanf("%d", &cols);

    if (rows <= 0 || cols <= 0 || rows > MAX_ROWS || cols > MAX_COLS) {
        printf("Invalid dimensions. Maximum allowed: %d rows, %d columns\n", MAX_ROWS, MAX_COLS);
        fclose(fptr);
        return;
    }

    struct Table table;
    strcpy(table.name, table_name);
    table.rows = rows;
    table.columns = cols;

    // Input column names and types
    printf("\nEnter column information:\n");
    for (int i = 0; i < cols; i++) {
        printf("Column %d name: ", i + 1);
        scanf("%49s", table.column_names[i]);
        do {
            printf("Column %d type (i-integer, f-float, s-string): ", i + 1);
            scanf(" %c", &table.column_types[i]);
        } while (table.column_types[i] != 'i' && table.column_types[i] != 'f' && table.column_types[i] != 's');
    }

    // Input data
    printf("\nEnter table data:\n");
    for (int i = 0; i < rows; i++) {
        printf("Row %d:\n", i + 1);
        for (int j = 0; j < cols; j++) {
            printf("Enter %s (%c): ", table.column_names[j], table.column_types[j]);
            switch(table.column_types[j]) {
                case 'i':
                    scanf("%d", &table.data[i][j].int_value);
                    break;
                case 'f':
                    scanf("%f", &table.data[i][j].float_value);
                    break;
                case 's':
                    scanf("%49s", table.data[i][j].str_value);
                    break;
            }
        }
    }

    // Save table to file
    fprintf(fptr, "Table: %s\nRows: %d\nColumns: %d\n\n", table.name, table.rows, table.columns);
    fprintf(fptr, "Column Names: ");
    for (int i = 0; i < table.columns; i++) {
        fprintf(fptr, "%s ", table.column_names[i]);
    }
    fprintf(fptr, "\nColumn Types: ");
    for (int i = 0; i < table.columns; i++) {
        fprintf(fptr, "%c ", table.column_types[i]);
    }
    fprintf(fptr, "\n\nData:\n");

    // Save data
    for (int i = 0; i < table.rows; i++) {
        for (int j = 0; j < table.columns; j++) {
            switch(table.column_types[j]) {
                case 'i':
                    fprintf(fptr, "%d ", table.data[i][j].int_value);
                    break;
                case 'f':
                    fprintf(fptr, "%.2f ", table.data[i][j].float_value);
                    break;
                case 's':
                    fprintf(fptr, "%s ", table.data[i][j].str_value);
                    break;
            }
        }
        fprintf(fptr, "\n");
    }

    fclose(fptr);
    printf("\nTable created and data saved successfully!\n");
}

int create_database(void) {
    char db_name[50];
    printf("Enter database name: ");
    scanf("%s", db_name);
    
    // Create database file
    char filename[100];
    sprintf(filename, "%s.db", db_name);
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error creating database file.\n");
        return 0;
    }
    
    // Write initial database structure
    fprintf(file, "DATABASE %s\n", db_name);
    fprintf(file, "TABLES 0\n");
    fclose(file);
    
    printf("Database '%s' created successfully.\n", db_name);
    return 1;
}

int main() {
    // Initialize password system
    initialize_password_storage();
    
    // Login or Register menu
    while (!login_or_register()) {
        printf("\nPlease try again or register a new account.\n");
    }
    
    // Display logo once after successful login
    display_zron_logo();
    printf("Welcome to the Database Management System.\n\n");
    
    int choice;
    do {
        printf("Database Management System\n");
        printf("1. Show Existing Databases\n");
        printf("2. Create Database\n");
        printf("3. Access Database\n");
        printf("4. Delete Database\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch(choice) {
            case 1:
                show_existing_databases();
                break;
            case 2:
                create_database();
                break;
            case 3:
                access_database();
                break;
            case 4:
                Delete_Database();
                break;
            case 5:
                printf("\nThank you for using Database Management System\n");
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while(choice != 5);
    
    return 0;
}