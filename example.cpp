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
        cout << "\n==============================================\n";
        cout << "\t Enter Employee Details" << endl;
        cout << "==============================================\n";

        cout << "\nEnter Employee ID: ";
        cin >> employee_ID;
        cin.ignore(); // Clear input buffer
        cout << "Enter Employee Name: ";
        getline(cin, employee_name);

        // Loop until a valid employee position is entered
        while (true)
        {
            cout << "Enter Employee Position (e.g., Barista, Cashier, Supervisor): ";
            getline(cin, employee_position);

            if (employee_position == "Barista" || employee_position == "barista")
            {
                basic_salary = 1920;
                employee_type = "Fulltime";
                break;
            }
            else if (employee_position == "Cashier" || employee_position == "cashier")
            {
                basic_salary = 1790;
                employee_type = "Fulltime";
                break;
            }
            else if (employee_position == "Cleaner" || employee_position == "cleaner")
            {
                basic_salary = 1400;
                employee_type = "Parttime";
                break;
            }
            else if (employee_position == "Kitchen Staff" || employee_position == "kitchen staff")
            {
                basic_salary = 1850;
                employee_type = "Parttime";
                break;
            }
            else if (employee_position == "Waiter" || employee_position == "waiter" || employee_position == "Waitress" || employee_position == "waitress")
            {
                basic_salary = 1700;
                employee_type = "Parttime";
                break;
            }
            else if (employee_position == "Supervisor" || employee_position == "supervisor")
            {
                basic_salary = 2400;
                employee_type = "Fulltime";
                break;
            }
            else
            {
                cout << "Invalid Employee Position. Please try again." << endl;
            }
        }

        cout << "Enter Employee Start Date (dd/mm/yy): ";
        cin >> start_date;
        cout << "==============================================\n\n";
    }

    void getData()
    {
        // Display with a tidy table design
        cout << left << setw(20) << "ID" << ": " << setw(20) << employee_ID << endl;
        cout << left << setw(20) << "Name" << ": " << setw(20) << employee_name << endl;
        cout << left << setw(20) << "Position" << ": " << setw(20) << employee_position << endl;
        cout << left << setw(20) << "Type" << ": " << setw(20) << employee_type << endl;
        cout << left << setw(20) << "Start Date" << ": " << setw(20) << start_date << endl;
        cout << left << setw(20) << "Basic Salary" << ": " << setw(20) << fixed << setprecision(2) << basic_salary << endl;
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

        calculateFulltimeTotalSalary();
    }

    double calculateFulltimeTotalSalary()
    {
        double salary = getBasicSalary();

        // Calculate overtime fees
        overtime_fees = (((salary / 30) / 8) * overtime_hours) * 2;

        // Calculate total amount considering leave days and overtime
        if (leave_days < 4 && overtime_hours >= 0)
        {
            total_amount = salary + bonus + overtime_fees;
            tax_salary = (total_amount / 100) * 2;
        }
        else if (leave_days > 4 && overtime_hours > 0)
        {
            total_amount = salary - ((salary / 100) * 1) + overtime_fees - bonus;
            tax_salary = (total_amount / 100) * 2;
        }
        else
        {
            total_amount = salary - bonus + overtime_fees;
            tax_salary = (total_amount / 100) * 2;
        }

        return total_amount;
    }

    double calculateFulltimeTotalNetSalary()
    {
        if (total_amount == 0)
            calculateFulltimeTotalSalary();

        net_salary = total_amount - ((total_amount / 100) * 2) - security_tax;
        return net_salary;
    }

    void getFullTimeData()
    {
        calculateFulltimeTotalSalary();
        calculateFulltimeTotalNetSalary();

        cout << "\n==============================================" << endl;
        cout << "\t Full-Time Employee Details" << endl;
        cout << "==============================================\n";
        getData();
        cout << left << setw(20) << "Leave Days" << ": " << setw(20) << leave_days << endl;
        cout << left << setw(20) << "Overtime Hours" << ": " << setw(20) << fixed << setprecision(2) << overtime_hours << endl;
        cout << left << setw(20) << "Overtime Fees" << ": $" << setw(20) << fixed << setprecision(2) << overtime_fees << endl;
        cout << left << setw(20) << "Bonus" << ": $" << setw(20) << fixed << setprecision(2) << bonus << endl;
        cout << left << setw(20) << "Tax Deduction" << ": $" << setw(20) << fixed << setprecision(2) << tax_salary << endl;
        cout << left << setw(20) << "Security Deduction" << ": $" << setw(20) << security_tax << endl;
        cout << left << setw(20) << "Total Amount" << ": $" << setw(20) << fixed << setprecision(2) << total_amount << endl;
        cout << left << setw(20) << "Total Net Amount" << ": $" << setw(20) << fixed << setprecision(2) << net_salary << endl;
        cout << "==============================================\n";
    }
};

class PartTime : public Employee
{
private:
    double hourly_wage = 0;
    double hours_worked = 0;
    double total_wage = 0;

public:
    void setPartTimeData()
    {
        setData(); // Set common data from Employee

        cout << "Enter hourly wage: ";
        cin >> hourly_wage;
        cout << "Enter hours worked: ";
        cin >> hours_worked;

        calculatePartTimeTotalWage();
    }

    double calculatePartTimeTotalWage()
    {
        total_wage = hourly_wage * hours_worked;
        return total_wage;
    }

    void getPartTimeData()
    {
        calculatePartTimeTotalWage();

        cout << "\n==============================================" << endl;
        cout << "\t Part-Time Employee Details" << endl;
        cout << "==============================================\n";
        getData();
        cout << left << setw(20) << "Hourly Wage" << ": $" << setw(20) << fixed << setprecision(2) << hourly_wage << endl;
        cout << left << setw(20) << "Hours Worked" << ": " << setw(20) << fixed << setprecision(2) << hours_worked << endl;
        cout << left << setw(20) << "Total Wage" << ": $" << setw(20) << fixed << setprecision(2) << total_wage << endl;
        cout << "==============================================\n";
    }
};

void displayMenu()
{
    cout << "\n==============================================";
    cout << "\n Employee Management System";
    cout << "\n==============================================";
    cout << "\n1. Add Full-Time Employee";
    cout << "\n2. Add Part-Time Employee";
    cout << "\n3. Display Full-Time Employee Details";
    cout << "\n4. Display Part-Time Employee Details";
    cout << "\n5. Exit";
    cout << "\n==============================================\n";
    cout << "Enter your choice: ";
}

int main()
{
    vector<FullTime> fullTimeEmployees;
    vector<PartTime> partTimeEmployees;
    int choice;

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            FullTime ft;
            ft.setFullTimeData();
            fullTimeEmployees.push_back(ft);
            break;
        }
        case 2:
        {
            PartTime pt;
            pt.setPartTimeData();
            partTimeEmployees.push_back(pt);
            break;
        }
        case 3:
        {
            for (const auto &ft : fullTimeEmployees)
            {
                ft.getFullTimeData();
            }
            break;
        }
        case 4:
        {
            for (const auto &pt : partTimeEmployees)
            {
                pt.getPartTimeData();
            }
            break;
        }
        case 5:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}
