#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

// Global security tax constant
const int SECURITY_TAX = 10;

class Employee {
protected:
    int employeeID;
    string name;
    string position;
    string type;
    string startDate;
    double basicSalary;

public:
    virtual ~Employee() {}

    // Getters
    int getID() const { return employeeID; }
    string getName() const { return name; }
    string getPosition() const { return position; }
    string getType() const { return type; }
    string getStartDate() const { return startDate; }
    double getBasicSalary() const { return basicSalary; }

    // Set employee details
    void setEmployeeData() {
        cout << "Enter Employee ID: ";
        cin >> employeeID;
        cin.ignore();

        cout << "Enter Employee Name: ";
        getline(cin, name);

        while (true) {
            cout << "Enter Employee Position (Fulltime: Barista, Cashier, Supervisor | Part-time: Cleaner, Kitchen Staff, Waiter/Waitress): ";
            getline(cin, position);

            if (position == "Barista" || position == "barista") {
                basicSalary = 1920;
                type = "Fulltime";
                break;
            } else if (position == "Cashier" || position == "cashier") {
                basicSalary = 1790;
                type = "Fulltime";
                break;
            } else if (position == "Supervisor" || position == "supervisor") {
                basicSalary = 2400;
                type = "Fulltime";
                break;
            } else if (position == "Cleaner" || position == "cleaner") {
                basicSalary = 1400;
                type = "Part-time";
                break;
            } else if (position == "Kitchen Staff" || position == "kitchen staff") {
                basicSalary = 1850;
                type = "Part-time";
                break;
            } else if (position == "Waiter" || position == "waiter" || position == "Waitress" || position == "waitress") {
                basicSalary = 1700;
                type = "Part-time";
                break;
            } else {
                cout << "Invalid position. Please enter a valid position." << endl;
            }
        }

        cout << "Enter Start Date (dd/mm/yy): ";
        cin >> startDate;
    }

    // Display employee details
    void displayEmployeeData() const {
        cout << left << setw(20) << "Employee ID" << ": " << employeeID << endl;
        cout << left << setw(20) << "Name" << ": " << name << endl;
        cout << left << setw(20) << "Position" << ": " << position << endl;
        cout << left << setw(20) << "Type" << ": " << type << endl;
        cout << left << setw(20) << "Start Date" << ": " << startDate << endl;
        cout << left << setw(20) << "Basic Salary" << ": " << fixed << setprecision(2) << basicSalary << endl;
    }
};

class FullTime : public Employee {
private:
    int leaveDays;
    double overtimeHours;
    double bonus;
    double overtimePay;
    double grossSalary;
    double netSalary;

public:
    FullTime() : leaveDays(0), overtimeHours(0), bonus(0), overtimePay(0), grossSalary(0), netSalary(0) {}

    void setFullTimeDetails() {
        setEmployeeData();

        cout << "Enter number of leave days: ";
        cin >> leaveDays;

        cout << "Enter overtime hours: ";
        cin >> overtimeHours;

        calculateSalaries();
    }

    void calculateSalaries() {
        // Calculate bonus based on leave days
        if (leaveDays == 0) {
            bonus = 300;
        } else if (leaveDays == 1) {
            bonus = 200;
        } else if (leaveDays == 2) {
            bonus = 100;
        } else {
            bonus = 0;
        }

        overtimePay = ((basicSalary / 30) / 8) * overtimeHours * 2;
        grossSalary = basicSalary + bonus + overtimePay;

        double tax = (grossSalary * 2) / 100;
        netSalary = grossSalary - tax - SECURITY_TAX;
    }

    void displayFullTimeDetails() const {
        displayEmployeeData();
        cout << left << setw(20) << "Leave Days" << ": " << leaveDays << endl;
        cout << left << setw(20) << "Overtime Hours" << ": " << fixed << setprecision(2) << overtimeHours << endl;
        cout << left << setw(20) << "Bonus" << ": $" << bonus << endl;
        cout << left << setw(20) << "Overtime Pay" << ": $" << overtimePay << endl;
        cout << left << setw(20) << "Gross Salary" << ": $" << grossSalary << endl;
        cout << left << setw(20) << "Net Salary" << ": $" << netSalary << endl;
    }

    double getNetSalary() const { return netSalary; }
};

class PartTime : public Employee {
private:
    double workingHours;
    double hourlyRate;
    double grossSalary;
    double netSalary;

public:
    PartTime() : workingHours(0), hourlyRate(0), grossSalary(0), netSalary(0) {}

    void setPartTimeDetails() {
        setEmployeeData();

        cout << "Enter total working hours (monthly): ";
        cin >> workingHours;

        calculateSalaries();
    }

    void calculateSalaries() {
        hourlyRate = (basicSalary / 30) / 8;
        grossSalary = workingHours * hourlyRate;

        double tax = (grossSalary * 2) / 100;
        netSalary = grossSalary - tax - SECURITY_TAX;
    }

    void displayPartTimeDetails() const {
        displayEmployeeData();
        cout << left << setw(20) << "Working Hours" << ": " << fixed << setprecision(2) << workingHours << endl;
        cout << left << setw(20) << "Hourly Rate" << ": $" << hourlyRate << endl;
        cout << left << setw(20) << "Gross Salary" << ": $" << grossSalary << endl;
        cout << left << setw(20) << "Net Salary" << ": $" << netSalary << endl;
    }

    double getNetSalary() const { return netSalary; }
};

vector<FullTime> fullTimeEmployees;
vector<PartTime> partTimeEmployees;

void displayAllEmployeesSorted() {
    struct EmployeeRecord {
        string type;
        double netSalary;
        string name;
    };

    vector<EmployeeRecord> records;

    for (const auto &ft : fullTimeEmployees) {
        records.push_back({"FullTime", ft.getNetSalary(), ft.getName()});
    }
    for (const auto &pt : partTimeEmployees) {
        records.push_back({"PartTime", pt.getNetSalary(), pt.getName()});
    }

    sort(records.begin(), records.end(), [](const EmployeeRecord &a, const EmployeeRecord &b) {
        return a.netSalary > b.netSalary;
    });

    cout << "\nSorted Employees by Net Salary (High to Low):\n";
    for (const auto &record : records) {
        cout << left << setw(15) << record.type << " | " << setw(20) << record.name << " | Net Salary: $" << fixed << setprecision(2) << record.netSalary << endl;
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Employee\n";
        cout << "2. View Full-Time Employees\n";
        cout << "3. View Part-Time Employees\n";
        cout << "4. View All Employees (Sorted by Net Salary)\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string empType;
            cout << "Enter employee type (Fulltime/Part-time): ";
            cin >> empType;

            if (empType == "Fulltime") {
                FullTime ft;
                ft.setFullTimeDetails();
                fullTimeEmployees.push_back(ft);
            } else if (empType == "Part-time") {
                PartTime pt;
                pt.setPartTimeDetails();
                partTimeEmployees.push_back(pt);
            } else {
                cout << "Invalid type!" << endl;
            }
            break;
        }
        case 2:
            for (const auto &ft : fullTimeEmployees) {
                ft.displayFullTimeDetails();
            }
            break;
        case 3:
            for (const auto &pt : partTimeEmployees) {
                pt.displayPartTimeDetails();
            }
            break;
        case 4:
            displayAllEmployeesSorted();
            break;
        case 5:
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice! Try again." << endl;
        }
    }
}
