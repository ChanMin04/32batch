#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

class Employee {
protected:
    int employeeID;
    string name;
    string position;
    string startDate;
    double basicSalary;

public:
    virtual void inputEmployeeData() = 0;
    virtual void displayEmployeeData() = 0;
    virtual double calculateNetSalary() = 0;

    int getEmployeeID() { return employeeID; }
    string getName() { return name; }
    string getPosition() { return position; }
    string getStartDate() { return startDate; }
    double getBasicSalary() { return basicSalary; }
};

class FullTimeEmployee : public Employee {
private:
    int leaveDays;
    double overtimeHours;
    double bonus;
    double taxDeduction;
    double securityDeduction;
    double totalAmount;
    double netSalary;

public:
    void inputEmployeeData() override {
        cout << "Enter Full-Time Employee ID: ";
        cin >> employeeID;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Position: ";
        getline(cin, position);
        cout << "Enter Start Date (DD/MM/YYYY): ";
        cin >> startDate;
        cout << "Enter Basic Salary: ";
        cin >> basicSalary;
        cout << "Enter Leave Days: ";
        cin >> leaveDays;
        cout << "Enter Overtime Hours: ";
        cin >> overtimeHours;
        cout << "Enter Bonus: ";
        cin >> bonus;
        cout << "Enter Tax Deduction Percentage: ";
        cin >> taxDeduction;
        cout << "Enter Security Deduction: ";
        cin >> securityDeduction;
    }

    double calculateNetSalary() override {
        double overtimePay = overtimeHours * 50; // Assume $50/hour for overtime
        totalAmount = basicSalary + bonus + overtimePay - (basicSalary * taxDeduction / 100) - securityDeduction;
        netSalary = totalAmount;
        return netSalary;
    }

    void displayEmployeeData() override {
        cout << left << setw(10) << employeeID
             << setw(15) << name
             << setw(15) << position
             << setw(15) << startDate
             << setw(12) << fixed << setprecision(2) << basicSalary
             << setw(10) << leaveDays
             << setw(12) << overtimeHours
             << setw(12) << bonus
             << setw(12) << taxDeduction
             << setw(12) << securityDeduction
             << setw(12) << netSalary << endl;
    }
};

class PartTimeEmployee : public Employee {
private:
    double workingHours;
    double hourlyWage;
    double taxDeduction;
    double securityDeduction;
    double totalAmount;
    double netSalary;

public:
    void inputEmployeeData() override {
        cout << "Enter Part-Time Employee ID: ";
        cin >> employeeID;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Position: ";
        getline(cin, position);
        cout << "Enter Start Date (DD/MM/YYYY): ";
        cin >> startDate;
        cout << "Enter Basic Salary: ";
        cin >> basicSalary;
        cout << "Enter Working Hours: ";
        cin >> workingHours;
        cout << "Enter Hourly Wage: ";
        cin >> hourlyWage;
        cout << "Enter Tax Deduction Percentage: ";
        cin >> taxDeduction;
        cout << "Enter Security Deduction: ";
        cin >> securityDeduction;
    }

    double calculateNetSalary() override {
        double totalPay = workingHours * hourlyWage;
        totalAmount = totalPay - (totalPay * taxDeduction / 100) - securityDeduction;
        netSalary = totalAmount;
        return netSalary;
    }

    void displayEmployeeData() override {
        cout << left << setw(10) << employeeID
             << setw(15) << name
             << setw(15) << position
             << setw(15) << startDate
             << setw(12) << fixed << setprecision(2) << basicSalary
             << setw(12) << workingHours
             << setw(12) << hourlyWage
             << setw(12) << taxDeduction
             << setw(12) << securityDeduction
             << setw(12) << netSalary << endl;
    }
};

void displayFullTimeEmployees(vector<FullTimeEmployee> &fullTimeEmployees) {
    if (fullTimeEmployees.empty()) {
        cout << "No Full-Time Employees to Display!\n";
        return;
    }
    cout << "\n**** Full-Time Employees ****\n";
    cout << left << setw(10) << "ID"
         << setw(15) << "Name"
         << setw(15) << "Position"
         << setw(15) << "Start Date"
         << setw(12) << "Basic Salary"
         << setw(10) << "Leaves"
         << setw(12) << "Overtime"
         << setw(12) << "Bonus"
         << setw(12) << "Tax Ded."
         << setw(12) << "Sec. Ded."
         << setw(12) << "Net Salary" << endl;
    for (FullTimeEmployee &emp : fullTimeEmployees) {
        emp.calculateNetSalary();
        emp.displayEmployeeData();
    }
    cout << "\n****************************\n";
}

void displayPartTimeEmployees(vector<PartTimeEmployee> &partTimeEmployees) {
    if (partTimeEmployees.empty()) {
        cout << "No Part-Time Employees to Display!\n";
        return;
    }
    cout << "\n**** Part-Time Employees ****\n";
    cout << left << setw(10) << "ID"
         << setw(15) << "Name"
         << setw(15) << "Position"
         << setw(15) << "Start Date"
         << setw(12) << "Basic Salary"
         << setw(12) << "Hours"
         << setw(12) << "Wage"
         << setw(12) << "Tax Ded."
         << setw(12) << "Sec. Ded."
         << setw(12) << "Net Salary" << endl;
    for (PartTimeEmployee &emp : partTimeEmployees) {
        emp.calculateNetSalary();
        emp.displayEmployeeData();
    }
    cout << "\n****************************\n";
}

int main() {
    vector<FullTimeEmployee> fullTimeEmployees;
    vector<PartTimeEmployee> partTimeEmployees;
    int choice;

    do {
        cout << "\n**** Employee Management System ****\n";
        cout << "1. Add Full-Time Employee\n";
        cout << "2. Add Part-Time Employee\n";
        cout << "3. Display Full-Time Employees\n";
        cout << "4. Display Part-Time Employees\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            FullTimeEmployee emp;
            emp.inputEmployeeData();
            fullTimeEmployees.push_back(emp);
            cout << "Full-Time Employee Added Successfully!\n";
            break;
        }
        case 2: {
            PartTimeEmployee emp;
            emp.inputEmployeeData();
            partTimeEmployees.push_back(emp);
            cout << "Part-Time Employee Added Successfully!\n";
            break;
        }
        case 3:
            displayFullTimeEmployees(fullTimeEmployees);
            break;
        case 4:
            displayPartTimeEmployees(partTimeEmployees);
            break;
        case 5:
            cout << "Exiting Program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

void saveFullTimeEmployeesToFile(const vector<FullTimeEmployee>& fullTimeEmployees) {
    ofstream file("FullTimeEmployees.txt");
    if (!file) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }

    file << left << setw(10) << "ID"
         << setw(15) << "Name"
         << setw(15) << "Position"
         << setw(15) << "Start Date"
         << setw(12) << "Basic Salary"
         << setw(10) << "Leaves"
         << setw(12) << "Overtime"
         << setw(12) << "Bonus"
         << setw(12) << "Tax Ded."
         << setw(12) << "Sec. Ded."
         << setw(12) << "Net Salary" << endl;

    for (const FullTimeEmployee& emp : fullTimeEmployees) {
        file << left << setw(10) << emp.getEmployeeID()
             << setw(15) << emp.getName()
             << setw(15) << emp.getPosition()
             << setw(15) << emp.getStartDate()
             << setw(12) << fixed << setprecision(2) << emp.getBasicSalary()
             << setw(10) << "N/A"
             << setw(12) << "N/A"
             << setw(12) << "N/A"
             << setw(12) << "N/A"
             << setw(12) << "N/A"
             << setw(12) << emp.calculateNetSalary() << endl;
    }

    file.close();
    cout << "Full-Time Employees data saved to file successfully!\n";
}

void searchEmployeeByID(const vector<Employee*>& employees, int id) {
    auto it = find_if(employees.begin(), employees.end(), [id](Employee* emp) {
        return emp->getEmployeeID() == id;
    });

    if (it != employees.end()) {
        cout << "Employee found:\n";
        (*it)->displayEmployeeData();
    } else {
        cout << "Employee with ID " << id << " not found.\n";
    }
}

void updateEmployeeDetails(Employee* employee) {
    cout << "Updating details for Employee ID: " << employee->getEmployeeID() << "\n";
    cout << "Enter updated Name: ";
    string updatedName;
    cin.ignore();
    getline(cin, updatedName);
    employee->inputEmployeeData();
    cout << "Details updated successfully!\n";
}

void advancedMenu(vector<Employee*>& employees) {
    int choice;
    do {
        cout << "\n**** Advanced Employee Management ****\n";
        cout << "1. Search Employee by ID\n";
        cout << "2. Update Employee Details\n";
        cout << "3. Save All Full-Time Employees to File\n";
        cout << "4. Return to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int id;
            cout << "Enter Employee ID to search: ";
            cin >> id;
            searchEmployeeByID(employees, id);
            break;
        }
        case 2: {
            int id;
            cout << "Enter Employee ID to update: ";
            cin >> id;
            auto it = find_if(employees.begin(), employees.end(), [id](Employee* emp) {
                return emp->getEmployeeID() == id;
            });
            if (it != employees.end()) {
                updateEmployeeDetails(*it);
            } else {
                cout << "Employee with ID " << id << " not found.\n";
            }
            break;
        }
        case 3:
            saveFullTimeEmployeesToFile(*reinterpret_cast<vector<FullTimeEmployee>*>(&employees));
            break;
        case 4:
            cout << "Returning to Main Menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

void displayAllEmployees(const vector<Employee*>& employees) {
    cout << "\n**** All Employees ****\n";
    for (const auto& emp : employees) {
        emp->displayEmployeeData();
    }
}

int main() {
    vector<Employee*> employees;
    int choice;

    do {
        cout << "\n**** Enhanced Employee Management System ****\n";
        cout << "1. Add Full-Time Employee\n";
        cout << "2. Add Part-Time Employee\n";
        cout << "3. Display All Employees\n";
        cout << "4. Advanced Menu\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            auto emp = new FullTimeEmployee();
            emp->inputEmployeeData();
            employees.push_back(emp);
            break;
        }
        case 2: {
            auto emp = new PartTimeEmployee();
            emp->inputEmployeeData();
            employees.push_back(emp);
            break;
        }
        case 3:
            displayAllEmployees(employees);
            break;
        case 4:
            advancedMenu(employees);
            break;
        case 5:
            cout << "Exiting Program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    for (auto emp : employees) {
        delete emp;
    }

    return 0;
}
