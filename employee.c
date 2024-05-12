#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define MAX_NAME_LENGTH 50
#define NUM_DEPARTMENTS 5

typedef struct 
{
    char name[MAX_NAME_LENGTH];
    int employee_id;
    float salary;
    char department[MAX_NAME_LENGTH];
} Employee;

typedef struct 
{
    char name[MAX_NAME_LENGTH];
} Department;

void addEmployee(Employee employees[], int *num_employees);
void displayEmployees(Employee employees[], int num_employees);
void saveToFile(Employee employees[], int num_employees);
void loadFromFile(Employee employees[], int *num_employees);
void searchEmployee(Employee employees[], int num_employees);
void updateEmployee(Employee employees[], int num_employees);
void deleteEmployee(Employee employees[], int *num_employees);
void sortEmployeesByID(Employee employees[], int num_employees);
void calculateDepartmentSalary(Employee employees[], int num_employees);
void displayTopPaidEmployees(Employee employees[], int num_employees, int N);
void back();
void clearInputBuffer();
void importEmployeesFromFile(Employee employees[], int *num_employees);

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
    Employee employees[MAX_EMPLOYEES];
    int num_employees = 0;
    int choice;
    int topN;

    loadFromFile(employees, &num_employees);

    do 
    {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee Record\n");
        printf("5. Delete Employee Record\n");
        printf("6. Save to File\n");
        printf("7. Sort Employees by ID\n");
        printf("8. Calculate Department-wise Salary\n");
        printf("9. Display Top N Paid Employees\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        switch(choice) 
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
                saveToFile(employees, num_employees);
                break;
            case 7:
                sortEmployeesByID(employees, num_employees);
                break;
            case 8:
                calculateDepartmentSalary(employees, num_employees);
                break;
            case 9:
                printf("Enter the number of top paid employees to display: ");
                if (scanf("%d", &topN) != 1 || topN < 1) 
                {
                    printf("Invalid input. Please enter a positive integer.\n");
                    clearInputBuffer();
                    break;
                }
                displayTopPaidEmployees(employees, num_employees, topN);
                break;
            case 10:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        if(choice != 10) 
        {
            back();
        }
    } while(choice != 10);

    return 0;
}

void back() 
{
    printf("Press Enter to return to the previous menu...");
    clearInputBuffer(); // Clear the input buffer
    getchar(); // Wait for user to press Enter
}

void addEmployee(Employee employees[], int *num_employees) 
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

            printf("Enter employee name: ");
            scanf("%s", employees[*num_employees].name);
            printf("Enter employee ID: ");
            scanf("%d", &employees[*num_employees].employee_id);
            printf("Enter employee salary: ");
            scanf("%f", &employees[*num_employees].salary);
            printf("Enter employee department[HR, Finance, IT, Marketing, Operations]: ");
            scanf("%s", employees[*num_employees].department);
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

void importEmployeesFromFile(Employee employees[], int *num_employees) 
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

    while (fscanf(file, "%s %d %f %s", employees[*num_employees].name,
                  &employees[*num_employees].employee_id, &employees[*num_employees].salary,
                  employees[*num_employees].department) != EOF) 
                  {
        (*num_employees)++;
        if (*num_employees >= MAX_EMPLOYEES) 
        {
            printf("Maximum number of employees reached.\n");
            break;
        }
    }

    fclose(file);
    printf("Employees imported from file successfully.\n");
}

void displayEmployees(Employee employees[], int num_employees) 
{
    if (num_employees == 0) 
    {
        printf("No employees to display.\n");
        return;
    }

    printf("Employee Records:\n");
    for (int i = 0; i < num_employees; i++) 
    {
        printf("Name: %s, ID: %d, Salary: %.2f, Department: %s\n",
               employees[i].name, employees[i].employee_id,
               employees[i].salary, employees[i].department);
    }
    back(); // After displaying employees, go back to the previous menu
}

void saveToFile(Employee employees[], int num_employees) 
{
    FILE *file = fopen("employee_records.txt", "w");
    if (file == NULL) 
    {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < num_employees; i++) 
    {
        fprintf(file, "%s %d %.2f %s\n", employees[i].name, employees[i].employee_id,
                employees[i].salary, employees[i].department);
    }

    fclose(file);
    printf("Data saved to file successfully.\n");
    back(); // After saving data to file, go back to the previous menu
}

void loadFromFile(Employee employees[], int *num_employees) 
{
    FILE *file = fopen("employee_records.txt", "r");
    if (file == NULL) 
    {
        printf("File not found or unable to open.\n");
        return;
    }

    while (fscanf(file, "%s %d %f %s", employees[*num_employees].name,
                  &employees[*num_employees].employee_id, &employees[*num_employees].salary,
                  employees[*num_employees].department) != EOF) {
        (*num_employees)++;
    }

    fclose(file);
    printf("Data loaded from file successfully.\n");
}

void searchEmployee(Employee employees[], int num_employees) 
{
    if (num_employees == 0) {
        printf("No employees to search.\n");
        return;
    }

    int employee_id;
    printf("Enter the employee ID to search for: ");
    scanf("%d", &employee_id);

    for (int i = 0; i < num_employees; i++) 
    {
        if (employees[i].employee_id == employee_id) 
        {
            printf("Employee found:\n");
            printf("Name: %s, ID: %d, Salary: %.2f, Department: %s\n",
                   employees[i].name, employees[i].employee_id,
                   employees[i].salary, employees[i].department);
            return;
        }
    }

    printf("Employee with ID %d not found.\n", employee_id);
    back(); // After searching for an employee, go back to the previous menu
}

void updateEmployee(Employee employees[], int num_employees) 
{
    if (num_employees == 0) 
    {
        printf("No employees to update.\n");
        return;
    }

    int employee_id;
    printf("Enter the employee ID to update: ");
    scanf("%d", &employee_id);

    for (int i = 0; i < num_employees; i++) 
    {
        if (employees[i].employee_id == employee_id) 
        {
            printf("Enter new name: ");
            scanf("%s", employees[i].name);
            printf("Enter new salary: ");
            scanf("%f", &employees[i].salary);
            printf("Enter new department: ");
            scanf("%s", employees[i].department);
            printf("Employee record updated successfully.\n");
            return;
        }
    }

    printf("Employee with ID %d not found.\n", employee_id);
    back(); // After updating an employee, go back to the previous menu
}

void deleteEmployee(Employee employees[], int *num_employees) 
{
    if (*num_employees == 0) 
    {
        printf("No employees to delete.\n");
        return;
    }

    int employee_id;
    printf("Enter the employee ID to delete: ");
    scanf("%d", &employee_id);

    int found = 0;
    for (int i = 0; i < *num_employees; i++) 
    {
        if (employees[i].employee_id == employee_id) 
        {
            for (int j = i; j < *num_employees - 1; j++) 
            {
                employees[j] = employees[j + 1];
            }
            (*num_employees)--;
            printf("Employee record deleted successfully.\n");
            found = 1;
            break;
        }
    }

    if (!found) 
    {
        printf("Employee with ID %d not found.\n", employee_id);
    }
    back(); // After deleting an employee, go back to the previous menu
}

void sortEmployeesByID(Employee employees[], int num_employees) 
{
    for (int i = 0; i < num_employees - 1; i++) {
        for (int j = 0; j < num_employees - i - 1; j++) {
            if (employees[j].employee_id > employees[j + 1].employee_id) 
            {
                Employee temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
    printf("Employees sorted by ID successfully.\n");
    back(); // After sorting employees, go back to the previous menu
}

void calculateDepartmentSalary(Employee employees[], int num_employees) 
{
    if (num_employees == 0) 
    {
        printf("No employees in the company.\n");
        return;
    }

    float totalSalary = 0;
    for (int i = 0; i < NUM_DEPARTMENTS; i++) 
    {
        char departmentName[MAX_NAME_LENGTH];
        strcpy(departmentName, departments[i].name);
        float departmentSalary = 0;
        for (int j = 0; j < num_employees; j++) 
        {
            if (strcmp(employees[j].department, departmentName) == 0) 
            {
                departmentSalary += employees[j].salary;
            }
        }
        printf("Total salary for department %s: %.2f\n", departmentName, departmentSalary);
        totalSalary += departmentSalary;
    }
    printf("Total salary for all departments: %.2f\n", totalSalary);
    back(); // After calculating department-wise salary, go back to the previous menu
}

void displayTopPaidEmployees(Employee employees[], int num_employees, int N) 
{
    if (num_employees == 0) 
    {
        printf("No employees in the company.\n");
        return;
    }

    if (N > num_employees) 
    {
        printf("Number of top paid employees exceeds total number of employees.\n");
        return;
    }

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

    printf("Top %d Paid Employees:\n", N);
    for (int i = 0; i < N; i++) 
    {
        printf("Name: %s, ID: %d, Salary: %.2f, Department: %s\n",
               employees[i].name, employees[i].employee_id,
               employees[i].salary, employees[i].department);
    }
    back(); // After displaying top paid employees, go back to the previous menu
}

void clearInputBuffer() 
{
    while (getchar() != '\n');
}
