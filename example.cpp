#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits> // For numeric_limits
using namespace std;

// Global variable
int security_tax = 10;

class Employee
{
private:
    int employee_ID;
    string employee_name;
    string employee_position;
    string employee_type;
    string start_date;
    double basic_salary;

public:
    // Virtual destructor for polymorphism
    virtual ~Employee() {}

    // Getter methods
    int getEmployeeID() { return employee_ID; }
    string getName() { return employee_name; }
    string getPosition() { return employee_position; }
    string getEmployeeType() { return employee_type; }
    string getStartDate() { return start_date; }
    double getBasicSalary() { return basic_salary; }

    // Default constructor
    Employee() : employee_ID(0), employee_name(""), employee_position(""), employee_type(""), start_date(""), basic_salary(0) {}

    // Set employee data
    void setData()
    {
        cout << "Enter Employee ID: ";
        cin >> employee_ID;
        cin.ignore(); // Clear input buffer
        cout << "Enter Employee Name: ";
        getline(cin, employee_name);

        // Loop until a valid employee position is entered
        while (true)
        {
            cout << "Enter Employee Position (Fulltime- Barista, Cashier, Supervisor (or) Part-time- Cleaner, Kitchen Staff, Waiter, Waitress): ";
            getline(cin, employee_position);

            if (employee_position == "Barista" || employee_position == "barista")
            {
                basic_salary = 1920;
                employee_type = "fulltime";
                break;
            }
            else if (employee_position == "Cashier" || employee_position == "cashier")
            {
                basic_salary = 1790;
                employee_type = "fulltime";
                break;
            }
            else if (employee_position == "Cleaner" || employee_position == "cleaner")
            {
                basic_salary = 1400;
                employee_type = "parttime";
                break;
            }
            else if (employee_position == "Kitchen Staff" || employee_position == "kitchen staff")
            {
                basic_salary = 1850;
                employee_type = "parttime";
                break;
            }
            else if (employee_position == "Waiter" || employee_position == "waiter" || employee_position == "Waitress" || employee_position == "waitress")
            {
                basic_salary = 1700;
                employee_type = "parttime";
                break;
            }
            else if (employee_position == "Supervisor" || employee_position == "supervisor")
            {
                basic_salary = 2400;
                employee_type = "fulltime";
                break;
            }
            else
            {
                cout << "Invalid Employee Position. Please try again." << endl;
            }
        }

        cout << "Enter Employee Start Date (dd/mm/yy): ";
        cin >> start_date;
    }
};

class FullTime : public Employee
{
private:
    int leave_days;
    double overtime_hours = 0;
    double bonus = 0;
    double overtime_fees = 0;
    double total_amount = 0;
    double tax_salary = 0;
    double net_salary = 0;

public:
    FullTime() : leave_days(0), overtime_hours(0.0) {}

    void setFullTimeData()
    {
        setData(); // Set common data from Employee
        cout << "Enter number of leave days: ";
        cin >> leave_days;
        cout << "Enter overtime hours: ";
        cin >> overtime_hours;

        // Calculate bonus based on leave days
        if (leave_days == 0)
        {
            bonus = 300;
        }
        else if (leave_days == 1)
        {
            bonus = 200;
        }
        else if (leave_days == 2)
        {
            bonus = 100;
        }
        else
        {
            bonus = 0;
        }

        // Explicitly calculate total salary to update dependent fields
        calculateFulltimeTotalSalary();
    }

    // Calculate total salary
    double calculateFulltimeTotalSalary()
    {
        double salary = getBasicSalary();

        // Calculate overtime fees
        overtime_fees = (((salary / 30) / 8) * overtime_hours) * 2;

        // Calculate total amount considering leave days and overtime
        if (leave_days < 4 && overtime_hours >= 0)
        {
            total_amount = salary + bonus + overtime_fees;
            // Calculate tax on salary
            tax_salary = (total_amount / 100) * 2;
        }
        else if (leave_days > 4 && overtime_hours > 0)
        {
            total_amount = salary - ((salary / 100) * 1) + overtime_fees - bonus;
            // Calculate tax on salary
            tax_salary = (total_amount / 100) * 2;
        }
        else
        {
            total_amount = salary - bonus + overtime_fees;
            // Calculate tax on salary
            tax_salary = (total_amount / 100) * 2;
        }

        return total_amount;
    }

    double calculateFulltimeTotalNetSalary()
    {
        if (total_amount == 0) // Ensure total_amount is calculated
            calculateFulltimeTotalSalary();

        // Calculate net salary after deductions
        net_salary = total_amount - ((total_amount / 100) * 2) - security_tax;
        return net_salary;
    }

    // setter
    double getOvertimeHours() { return overtime_hours; }
    double getOvertimeFees() { return overtime_fees; }
    double getTaxSalary() { return tax_salary; }
    double getTotalAmount() { return total_amount; }
    double getNetSalary() { return net_salary; }
    int getLeaveDay() { return leave_days; }
    double getBonus() { return bonus; }
};

class PartTime : public Employee
{
private:
    double hourly_wage = 0;
    double working_hours = 0;
    double total_amount = 0;
    double tax_deduction = 0;
    double net_salary = 0;

public:
    PartTime() : working_hours(0) {}

    void setParttimeData()
    {
        setData(); // Set common data from Employee
        cout << "Enter working hours (Monthly): ";
        cin >> working_hours;

        // Calculate salary components after setting data
        calculateParttimeTotalNetSalary();
    }

    double calculateParttimeTotalNetSalary()
    {
        // Calculate hourly wage from basic salary
        double salary = getBasicSalary();
        hourly_wage = (salary / 30) / 8;

        // Calculate gross total amount based on working hours
        total_amount = hourly_wage * working_hours;

        // Calculate tax deduction (2% of total amount)
        tax_deduction = (total_amount / 100) * 2;

        // Calculate net salary after tax and security deduction
        net_salary = total_amount - tax_deduction - security_tax;

        return net_salary;
    }

    // New getters for detailed data
    double getWorkingHours() { return working_hours; }
    double getHourlyWage() { return hourly_wage; }
    double getPartTaxDeduction() { return tax_deduction; }
    double getPartNetSalary() { return net_salary; }
    double getPartTotalAmount() { return total_amount; }
};

// Global vectors to store employees
vector<FullTime> Fulltime_Employees;
vector<PartTime> PartTime_Employees;

int main()
{
    int opt = 0; // Initialize opt to avoid undefined behavior
    cout << "--------------------------------------------" << endl;
    cout << "*---___ Java_Jolt_Cafe Manager __---*" << endl;
    cout << "--------------------------------------------" << endl;
    int fulltime_employee = 0, parttime_employee = 0;
    double fulltime_employee_salary = 0, parttime_employee_salary = 0, monthly_total = 0;
    while (opt != 6)
    {
        cout << "\nMenu" << endl;
        cout << "1. Insert Employee Data \n"
             << "2. Update Employee Data \n"
             << "3. View Fulltime Employees Salary \n"
             << "4. View Parttime Employees Salary \n"
             << "5. View All Employees Salary (Sorted by Net Salary) \n"
             << "6. Exit" << endl;
        cout << "Choose an option: ";
        cin >> opt;

        // Clear invalid input
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and 6." << endl;
            continue;
        }

        cin.ignore(); // Clear input buffer

        switch (opt)
        {
        case 1:
        {
            int n;
            cout << "Enter the number of employees you want to insert: ";
            cin >> n;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            for (int i = 0; i < n; i++)
            {
                cout << "Enter details for Employee " << i + 1 << ":" << endl;
                string employee_type;
                cout << "Which Type Of Employee Data You Want To Insert (fulltime/parttime): ";
                cin >> employee_type;
                cin.ignore(); // Clear buffer after reading employee_type

                if (employee_type == "fulltime")
                {
                    FullTime New_Employee;
                    New_Employee.setFullTimeData();
                    cout << endl;
                    Fulltime_Employees.push_back(New_Employee);
                    fulltime_employee++;
                    fulltime_employee_salary += New_Employee.calculateFulltimeTotalNetSalary();
                }
               #include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

// Base Employee Class
class Employee {
protected:
    int employeeID;
    string name;
    string position;
    string startDate;
    double basicSalary;

public:
    Employee() : employeeID(0), name(""), position(""), startDate(""), basicSalary(0.0) {}
    virtual ~Employee() {}

    // Getters
    int getEmployeeID() const { return employeeID; }
    string getName() const { return name; }
    string getPosition() const { return position; }
    string getStartDate() const { return startDate; }
    double getBasicSalary() const { return basicSalary; }

    // Setters
    void setBaseData() {
        cout << "Enter Employee ID: ";
        cin >> employeeID;
        cin.ignore(); // Clear newline
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Position: ";
        getline(cin, position);
        cout << "Enter Start Date (YYYY-MM-DD): ";
        cin >> startDate;
        cout << "Enter Basic Salary: ";
        cin >> basicSalary;
    }

    virtual void displayDetails() const = 0; // Pure virtual function
};

// Full-Time Employee Class
class FullTime : public Employee {
private:
    int leaveDays;
    double overtimeHours;
    double overtimeRate;
    double bonus;
    double taxDeduction;
    double netSalary;

public:
    FullTime() : leaveDays(0), overtimeHours(0.0), overtimeRate(0.0), bonus(0.0), taxDeduction(0.0), netSalary(0.0) {}

    void setFullTimeData() {
        setBaseData();
        cout << "Enter Leave Days: ";
        cin >> leaveDays;
        cout << "Enter Overtime Hours: ";
        cin >> overtimeHours;
        cout << "Enter Overtime Rate: ";
        cin >> overtimeRate;
        cout << "Enter Bonus: ";
        cin >> bonus;
    }

    double calculateNetSalary() {
        double grossSalary = basicSalary + (overtimeHours * overtimeRate) + bonus;
        taxDeduction = grossSalary * 0.1; // 10% tax deduction
        netSalary = grossSalary - taxDeduction;
        return netSalary;
    }

    void displayDetails() const override {
        cout << left << setw(10) << employeeID
             << setw(15) << name
             << setw(15) << position
             << setw(12) << startDate
             << setw(12) << fixed << setprecision(2) << basicSalary
             << setw(10) << leaveDays
             << setw(10) << overtimeHours
             << setw(10) << bonus
             << setw(12) << fixed << setprecision(2) << netSalary << endl;
    }
};

// Part-Time Employee Class
class PartTime : public Employee {
private:
    double workingHours;
    double hourlyWage;
    double taxDeduction;
    double netSalary;

public:
    PartTime() : workingHours(0.0), hourlyWage(0.0), taxDeduction(0.0), netSalary(0.0) {}

    void setPartTimeData() {
        setBaseData();
        cout << "Enter Working Hours: ";
        cin >> workingHours;
        cout << "Enter Hourly Wage: ";
        cin >> hourlyWage;
    }

    double calculateNetSalary() {
        double grossSalary = workingHours * hourlyWage;
        taxDeduction = grossSalary * 0.05; // 5% tax deduction
        netSalary = grossSalary - taxDeduction;
        return netSalary;
    }

    void displayDetails() const override {
        cout << left << setw(10) << employeeID
             << setw(15) << name
             << setw(15) << position
             << setw(12) << startDate
             << setw(12) << fixed << setprecision(2) << basicSalary
             << setw(10) << workingHours
             << setw(12) << fixed << setprecision(2) << netSalary << endl;
    }
};

// Global Vectors to Store Employees
vector<FullTime> fullTimeEmployees;
vector<PartTime> partTimeEmployees;

// Utility Functions
void addEmployee() {
    string type;
    cout << "Enter Employee Type (fulltime/parttime): ";
    cin >> type;

    if (type == "fulltime") {
        FullTime newEmployee;
        newEmployee.setFullTimeData();
        newEmployee.calculateNetSalary();
        fullTimeEmployees.push_back(newEmployee);
        cout << "Full-Time Employee Added Successfully!\n";
    } else if (type == "parttime") {
        PartTime newEmployee;
        newEmployee.setPartTimeData();
        newEmployee.calculateNetSalary();
        partTimeEmployees.push_back(newEmployee);
        cout << "Part-Time Employee Added Successfully!\n";
    } else {
        cout << "Invalid Employee Type!\n";
    }
}

void viewFullTimeEmployees() {
    if (fullTimeEmployees.empty()) {
        cout << "No Full-Time Employees Found!\n";
        return;
    }

    // Display Table Headers
    cout << "\n***** Full-Time Employees *****\n";
    cout << left << setw(10) << "ID"
         << setw(15) << "Name"
         << setw(15) << "Position"
         << setw(12) << "Start Date"
         << setw(12) << "Basic Sal."
         << setw(10) << "Leaves"
         << setw(10) << "Overtime"
         << setw(10) << "Bonus"
         << setw(12) << "Net Salary" << endl;

    // Display Each Employee
    for (const auto &emp : fullTimeEmployees) {
        emp.displayDetails();
    }
}

void viewPartTimeEmployees() {
    if (partTimeEmployees.empty()) {
        cout << "No Part-Time Employees Found!\n";
        return;
    }

    // Display Table Headers
    cout << "\n***** Part-Time Employees *****\n";
    cout << left << setw(10) << "ID"
         << setw(15) << "Name"
         << setw(15) << "Position"
         << setw(12) << "Start Date"
         << setw(12) << "Basic Sal."
         << setw(10) << "Hours"
         << setw(12) << "Net Salary" << endl;

    // Display Each Employee
    for (const auto &emp : partTimeEmployees) {
        emp.displayDetails();
    }
}

int main() {
    int choice;

    do {
        cout << "\n***** Employee Management System *****\n";
        cout << "1. Add Employee\n";
        cout << "2. View Full-Time Employees\n";
        cout << "3. View Part-Time Employees\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addEmployee();
            break;
        case 2:
            viewFullTimeEmployees();
            break;
        case 3:
            viewPartTimeEmployees();
            break;
        case 4:
            cout << "Exiting Program. Goodbye!\n";
            break;
        default:
            cout << "Invalid Choice!\n";
        }
    } while (choice != 4);

    return 0;
}
