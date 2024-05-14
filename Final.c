#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_EMPLOYEES 100
#define MAX_NAME_LENGTH 50
#define NUM_DEPARTMENTS 5

typedef struct 
{
    char name[MAX_NAME_LENGTH];
    int employee_id;
    float salary;
    char department[MAX_NAME_LENGTH];
    char email[MAX_NAME_LENGTH];
    char phone[MAX_NAME_LENGTH];
    char address[MAX_NAME_LENGTH];
} Employee;

typedef struct 
{
    char name[MAX_NAME_LENGTH];
} Department;

int isValidDepartment(const char *department);
void addEmployee(Employee *employees, int *num_employees);
void displayEmployees(Employee *employees, int num_employees);
void saveToFile(Employee *employees, int num_employees, const char *filename);
void loadFromFile(Employee *employees, int *num_employees, const char *filename);
void searchEmployee(Employee *employees, int num_employees);
void updateEmployee(Employee *employees, int num_employees);
void deleteEmployee(Employee *employees, int *num_employees);
void sortEmployeesByID(Employee *employees, int num_employees);
void calculateDepartmentSalary(Employee *employees, int num_employees);
void displayTopPaidEmployees(Employee *employees, int num_employees, int N);
void clearInputBuffer();
void importEmployeesFromFile(Employee *employees, int *num_employees);
void correctDepartmentName(char *department);
void displayUserManual();

Department departments[NUM_DEPARTMENTS] = 
{
    {"HR"},
    {"Finance"},
    {"IT"},
    {"Marketing"},
    {"Operations"}
};

int main() 
{
    Employee *employees = (Employee *)malloc(MAX_EMPLOYEES * sizeof(Employee));
    if (employees == NULL) 
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    int num_employees = 0;
    int choice;
    int topN;
    char filename[100];

    do 
    {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee Record\n");
        printf("5. Delete Employee Record\n");
        printf("6. Save to File\n");
        printf("7. Load from File\n");
        printf("8. Sort Employees by ID\n");
        printf("9. Calculate Department-wise Salary\n");
        printf("10. Display Top N Paid Employees\n");
        printf("11. Exit\n");
        printf("12. Display User Manual\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch (choice) 
        {
            case 1:
                addEmployee(employees, &num_employees);
                break;
            case 2:
                displayEmployees(employees, num_employees);
                break;
            case 3:
                searchEmployee(employees, num_employees);
                break;
            case 4:
                updateEmployee(employees, num_employees);
                break;
            case 5:
                deleteEmployee(employees, &num_employees);
                break;
            case 6:
                printf("Enter the name of the file to save to: ");
                scanf("%s", filename);
                saveToFile(employees, num_employees, filename);
                break;
            case 7:
                printf("Enter the name of the file to load from: ");
                scanf("%s", filename);
                loadFromFile(employees, &num_employees, filename);
                break;
            case 8:
                sortEmployeesByID(employees, num_employees);
                break;
            case 9:
                calculateDepartmentSalary(employees, num_employees);
                break;
            case 10:
                printf("Enter the number of top paid employees to display: ");
                if (scanf("%d", &topN) != 1 || topN < 1) 
                {
                    printf("Invalid input. Please enter a positive integer.\n");
                    clearInputBuffer();
                    break;
                }
                displayTopPaidEmployees(employees, num_employees, topN);
                break;
            case 11:
                printf("Exiting...\n");
                break;
            case 12:
                displayUserManual();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 11);

    free(employees);
    return 0;
}

void clearInputBuffer() 
{
    while (getchar() != '\n');
}

void addEmployee(Employee *employees, int *num_employees) 
{
    int choice;
    printf("Employee Management System\n");
    printf("1. Add employee manually\n");
    printf("2. Import employees from file\n");
    printf("3. Back\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1) 
    {
        printf("Invalid input. Please enter a number.\n");
        clearInputBuffer();
        return;
    }

    switch (choice) 
    {
        case 1:
            if (*num_employees >= MAX_EMPLOYEES) 
            {
                printf("Maximum number of employees reached.\n");
                return;
            }

            clearInputBuffer(); // Clear the buffer before taking a multi-word input
            printf("Enter employee name: ");
            fgets(employees[*num_employees].name, MAX_NAME_LENGTH, stdin);
            employees[*num_employees].name[strcspn(employees[*num_employees].name, "\n")] = '\0'; // Remove trailing newline

            printf("Enter employee ID: ");
            scanf("%d", &employees[*num_employees].employee_id);

            printf("Enter employee salary: ");
            scanf("%f", &employees[*num_employees].salary);

            clearInputBuffer(); // Clear the buffer before taking a multi-word input
            printf("Enter employee department[HR, Finance, IT, Marketing, Operations]: ");
            fgets(employees[*num_employees].department, MAX_NAME_LENGTH, stdin);
            employees[*num_employees].department[strcspn(employees[*num_employees].department, "\n")] = '\0'; // Remove trailing newline
            correctDepartmentName(employees[*num_employees].department);

            printf("Enter employee email: ");
            fgets(employees[*num_employees].email, MAX_NAME_LENGTH, stdin);
            employees[*num_employees].email[strcspn(employees[*num_employees].email, "\n")] = '\0'; // Remove trailing newline

            printf("Enter employee phone: ");
            fgets(employees[*num_employees].phone, MAX_NAME_LENGTH, stdin);
            employees[*num_employees].phone[strcspn(employees[*num_employees].phone, "\n")] = '\0'; // Remove trailing newline

            printf("Enter employee address: ");
            fgets(employees[*num_employees].address, MAX_NAME_LENGTH, stdin);
            employees[*num_employees].address[strcspn(employees[*num_employees].address, "\n")] = '\0'; // Remove trailing newline

            (*num_employees)++;
            break;
        case 2:
            importEmployeesFromFile(employees, num_employees);
            break;
        case 3:
            break;
        default:
            printf("Invalid choice.\n");
    }
}

int isValidDepartment(const char *department) 
{
    const char *validDepartments[] = {"HR", "Finance", "IT", "Marketing", "Operations"};
    for (int i = 0; i < NUM_DEPARTMENTS; i++) 
    {
        if (strcasecmp(department, validDepartments[i]) == 0) 
        {
            return 1; // Valid department name found
        }
    }
    return 0; // Department name not found in the list of valid departments
}

void correctDepartmentName(char *department) 
{
    for (int i = 0; department[i]; i++) 
    {
        department[i] = toupper(department[i]);
    }
}

void importEmployeesFromFile(Employee *employees, int *num_employees) 
{
    char filename[100];
    printf("Enter the name of the file to import from: ");
    scanf("%s", filename);

    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        printf("File not found or unable to open.\n");
        return;
    }

    while (*num_employees < MAX_EMPLOYEES &&
           fscanf(file, "%49[^,],%d,%f,%49[^,],%49[^,],%49[^,],%49[^\n]",
                  employees[*num_employees].name,
                  &employees[*num_employees].employee_id,
                  &employees[*num_employees].salary,
                  employees[*num_employees].department,
                  employees[*num_employees].email,
                  employees[*num_employees].phone,
                  employees[*num_employees].address) == 7) {
        
        // Check if the department name is valid
        if (!isValidDepartment(employees[*num_employees].department)) {
            printf("Invalid department '%s' for employee '%s'. Skipping...\n",
                   employees[*num_employees].department,
                   employees[*num_employees].name);
            continue; // Skip this employee
        }

        (*num_employees)++;
    }

    fclose(file);
    printf("Employees imported from file successfully.\n");
}

void displayEmployees(Employee *employees, int num_employees) 
{
    if (num_employees == 0) 
    {
        printf("No employees to display.\n");
        return;
    }

    for (int i = 0; i < num_employees; i++) 
    {
        printf("Employee %d:\n", i + 1);
        printf("  Name: %s\n", employees[i].name);
        printf("  ID: %d\n", employees[i].employee_id);
        printf("  Salary: %.2f\n", employees[i].salary);
        printf("  Department: %s\n", employees[i].department);
        printf("  Email: %s\n", employees[i].email);
        printf("  Phone: %s\n", employees[i].phone);
        printf("  Address: %s\n", employees[i].address);
    }
}

void saveToFile(Employee *employees, int num_employees, const char *filename) 
{
    FILE *file = fopen(filename, "w");
    if (file == NULL) 
    {
        printf("Unable to open file for writing.\n");
        return;
    }

    for (int i = 0; i < num_employees; i++) 
    {
        fprintf(file, "%s,%d,%.2f,%s,%s,%s,%s\n",
                employees[i].name,
                employees[i].employee_id,
                employees[i].salary,
                employees[i].department,
                employees[i].email,
                employees[i].phone,
                employees[i].address);
    }

    fclose(file);
    printf("Employee records saved to file successfully.\n");
}

void loadFromFile(Employee *employees, int *num_employees, const char *filename) 
{
    FILE *file = fopen(filename, "r");
    if (file == NULL) 
    {
        printf("File not found or unable to open.\n");
        return;
    }

    *num_employees = 0; // Reset the count before loading from the file
    while (*num_employees < MAX_EMPLOYEES &&
           fscanf(file, "%49[^,],%d,%f,%49[^,],%49[^,],%49[^,],%49[^\n]",
                  employees[*num_employees].name,
                  &employees[*num_employees].employee_id,
                  &employees[*num_employees].salary,
                  employees[*num_employees].department,
                  employees[*num_employees].email,
                  employees[*num_employees].phone,
                  employees[*num_employees].address) == 7) {
        
        // Check if the department name is valid
        if (!isValidDepartment(employees[*num_employees].department)) 
        {
            printf("Invalid department '%s' for employee '%s'. Skipping...\n",
                   employees[*num_employees].department,
                   employees[*num_employees].name);
            continue; // Skip this employee
        }

        (*num_employees)++;
    }

    fclose(file);
    printf("Employees loaded from file successfully.\n");
}

void searchEmployee(Employee *employees, int num_employees) 
{
    int employee_id;
    printf("Enter the employee ID to search for: ");
    scanf("%d", &employee_id);

    for (int i = 0; i < num_employees; i++) 
    {
        if (employees[i].employee_id == employee_id) 
        {
            printf("Employee found:\n");
            printf("  Name: %s\n", employees[i].name);
            printf("  ID: %d\n", employees[i].employee_id);
            printf("  Salary: %.2f\n", employees[i].salary);
            printf("  Department: %s\n", employees[i].department);
            printf("  Email: %s\n", employees[i].email);
            printf("  Phone: %s\n", employees[i].phone);
            printf("  Address: %s\n", employees[i].address);
            return;
        }
    }

    printf("Employee with ID %d not found.\n", employee_id);
}

void updateEmployee(Employee *employees, int num_employees) 
{
    int employee_id;
    printf("Enter the employee ID to update: ");
    scanf("%d", &employee_id);

    for (int i = 0; i < num_employees; i++) 
    {
        if (employees[i].employee_id == employee_id) 
        {
            printf("Enter new details for the employee:\n");

            clearInputBuffer(); // Clear the buffer before taking a multi-word input
            printf("Enter employee name: ");
            fgets(employees[i].name, MAX_NAME_LENGTH, stdin);
            employees[i].name[strcspn(employees[i].name, "\n")] = '\0'; // Remove trailing newline

            printf("Enter employee salary: ");
            scanf("%f", &employees[i].salary);

            clearInputBuffer(); // Clear the buffer before taking a multi-word input
            printf("Enter employee department: ");
            fgets(employees[i].department, MAX_NAME_LENGTH, stdin);
            employees[i].department[strcspn(employees[i].department, "\n")] = '\0'; // Remove trailing newline
            correctDepartmentName(employees[i].department);

            printf("Enter employee email: ");
            fgets(employees[i].email, MAX_NAME_LENGTH, stdin);
            employees[i].email[strcspn(employees[i].email, "\n")] = '\0'; // Remove trailing newline

            printf("Enter employee phone: ");
            fgets(employees[i].phone, MAX_NAME_LENGTH, stdin);
            employees[i].phone[strcspn(employees[i].phone, "\n")] = '\0'; // Remove trailing newline

            printf("Enter employee address: ");
            fgets(employees[i].address, MAX_NAME_LENGTH, stdin);
            employees[i].address[strcspn(employees[i].address, "\n")] = '\0'; // Remove trailing newline

            printf("Employee record updated successfully.\n");
            return;
        }
    }

    printf("Employee with ID %d not found.\n", employee_id);
}

void deleteEmployee(Employee *employees, int *num_employees) 
{
    int employee_id;
    printf("Enter the employee ID to delete: ");
    scanf("%d", &employee_id);

    for (int i = 0; i < *num_employees; i++) 
    {
        if (employees[i].employee_id == employee_id) 
        {
            for (int j = i; j < *num_employees - 1; j++) 
            {
                employees[j] = employees[j + 1]; // Shift employees to fill the gap
            }
            (*num_employees)--;
            printf("Employee record deleted successfully.\n");
            return;
        }
    }

    printf("Employee with ID %d not found.\n", employee_id);
}

void sortEmployeesByID(Employee *employees, int num_employees) 
{
    for (int i = 0; i < num_employees - 1; i++) 
    {
        for (int j = 0; j < num_employees - i - 1; j++) 
        {
            if (employees[j].employee_id > employees[j + 1].employee_id) 
            {
                Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
    printf("Employees sorted by ID.\n");
}

void calculateDepartmentSalary(Employee *employees, int num_employees) 
{
    float departmentSalaries[NUM_DEPARTMENTS] = {0};

    for (int i = 0; i < num_employees; i++) 
    {
        for (int j = 0; j < NUM_DEPARTMENTS; j++) 
        {
            if (strcasecmp(employees[i].department, departments[j].name) == 0) 
            {
                departmentSalaries[j] += employees[i].salary;
                break;
            }
        }
    }

    for (int i = 0; i < NUM_DEPARTMENTS; i++) 
    {
        printf("Total salary for %s department: %.2f\n", departments[i].name, departmentSalaries[i]);
    }
}

void displayTopPaidEmployees(Employee *employees, int num_employees, int N) 
{
    if (N > num_employees) 
    {
        N = num_employees;
    }

    // Sort employees by salary in descending order
    for (int i = 0; i < num_employees - 1; i++) 
    {
        for (int j = 0; j < num_employees - i - 1; j++) 
        {
            if (employees[j].salary < employees[j + 1].salary) 
            {
                Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }

    printf("Top %d paid employees:\n", N);
    for (int i = 0; i < N; i++) 
    {
        printf("Employee %d:\n", i + 1);
        printf("  Name: %s\n", employees[i].name);
        printf("  ID: %d\n", employees[i].employee_id);
        printf("  Salary: %.2f\n", employees[i].salary);
        printf("  Department: %s\n", employees[i].department);
        printf("  Email: %s\n", employees[i].email);
        printf("  Phone: %s\n", employees[i].phone);
        printf("  Address: %s\n", employees[i].address);
    }
}

// Function to display the user manual
void displayUserManual() 
{
    printf("\nEmployee Management System User Manual\n");
    printf("Table of Contents\n");
    printf("\t1. Introduction\n");
    printf("\t2. System Requirements\n");
    printf("\t3. Installation\n");
    printf("\t4. Program Overview\n");
    printf("\t5. Main Menu Options\n");
    printf("\t\t5.1 Add Employee\n");
    printf("\t\t5.2 Display Employees\n");
    printf("\t\t5.3 Search Employee\n");
    printf("\t\t5.4 Update Employee Record\n");
    printf("\t\t5.5 Delete Employee Record\n");
    printf("\t\t5.6 Save to File\n");
    printf("\t\t5.7 Load from File\n");
    printf("\t\t5.8 Sort Employees by ID\n");
    printf("\t\t5.9 Calculate Department-wise Salary\n");
    printf("\t\t5.10 Display Top N Paid Employees\n");
    printf("\t\t5.11 Exit\n");
    printf("\t6. Additional Features\n");
    printf("\t7. Troubleshooting\n");

    printf("\nIntroduction\n");
    printf("The Employee Management System is designed to help you manage employee information efficiently.\n");
    printf("This system allows you to add, display, search, update, delete, save, and load employee records.\n");

    printf("\nSystem Requirements\n");
    printf("Operating System: Any OS with support for C programming (e.g., Windows, Linux, macOS)\n");
    printf("Compiler: GCC or any standard C compiler\n");
    printf("Memory: At least 1 MB of free RAM\n");

    printf("\nInstallation\n");
    printf("1. Ensure you have a C compiler installed (e.g., GCC).\n");
    printf("2. Download the source code file (employee_management.c).\n");
    printf("3. Compile the source code using a C compiler:\n");
    printf("   gcc employee_management.c -o employee_management\n");
    printf("4. Run the executable:\n");
    printf("   ./employee_management\n");

    printf("\nProgram Overview\n");
    printf("When you run the program, you will see the main menu with various options to manage employee records.\n");
    printf("You can navigate through these options to perform different operations on the employee data.\n");

    printf("\nMain Menu Options\n");
    printf("Add Employee\n");
    printf("1. Select option 1 from the main menu to add a new employee.\n");
    printf("2. Enter the employee’s name, ID, salary, department, email, phone, and address.\n");

    printf("\nDisplay Employees\n");
    printf("1. Select option 2 from the main menu to display all employee records.\n");
    printf("2. The program will list all the employee records.\n");

    printf("\nSearch Employee\n");
    printf("1. Select option 3 from the main menu to search for an employee.\n");
    printf("2. Choose the search criteria:\n");
    printf("   1. Name\n");
    printf("   2. Department\n");
    printf("   3. Salary Range\n");
    printf("3. Enter the search parameters based on your choice.\n");

    printf("\nUpdate Employee Record\n");
    printf("1. Select option 4 from the main menu to update an employee's record.\n");
    printf("2. Enter the employee ID of the record you want to update.\n");
    printf("3. Update the employee’s name, salary, department, email, phone, and address as prompted.\n");

    printf("\nDelete Employee Record\n");
    printf("1. Select option 5 from the main menu to delete an employee's record.\n");
    printf("2. Enter the employee ID of the record you want to delete.\n");

    printf("\nSave to File\n");
    printf("1. Select option 6 from the main menu to save employee records to a file.\n");
    printf("2. The program saves the records to a text file specified by the user.\n");

    printf("\nLoad from File\n");
    printf("1. Select option 7 from the main menu to load employee records from a file.\n");
    printf("2. The program loads records from a chosen text file.\n");

    printf("\nSort Employees by ID\n");
    printf("1. Select option 8 from the main menu to sort employee records by their ID.\n");
    printf("2. The program sorts the records and displays them.\n");

    printf("\nCalculate Department-wise Salary\n");
    printf("1. Select option 9 from the main menu to calculate total salaries by department.\n");
    printf("2. The program displays the total salary for each department.\n");

    printf("\nDisplay Top N Paid Employees\n");
    printf("1. Select option 10 from the main menu to display the top N paid employees.\n");
    printf("2. Enter the number of top paid employees to display.\n");

    printf("\nExit\n");
    printf("1. Select option 11 from the main menu to exit the program.\n");

    printf("\nAdditional Features\n");
    printf("Back Function: After each operation, the program prompts you to press Enter to return to the main menu.\n");
    printf("Clear Input Buffer: Ensures no leftover characters interfere with the next input.\n");

    printf("\nTroubleshooting\n");
    printf("Invalid Input: If you enter an invalid input, the program will prompt you to enter a valid one.\n");
    printf("Ensure you are entering the correct data type as requested.\n");
    printf("File Errors: If the program cannot open a file, ensure the file exists and you have the correct permissions to access it.\n");
    printf("Memory Allocation Errors: If the program runs out of memory, try freeing up system memory and running the program again.\n");
}
