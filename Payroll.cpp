#include <iostream>
#include <fstream>
#include <vector>
#include <sstream> 
#include <iomanip>
#include <limits>

using namespace std;

struct Employee // Reference: w3schools - https://www.w3schools.com/cpp/cpp_structs.asp
{
	string id;
	string name;
	double rateOfPay;
};

const double TAX_FREE_ALLOWANCE = 12570.0;
const double TAX_RATE = 0.20;

class employee 
{
public:
	string empID; //Refrence: w3schools - https://www.w3schools.com/cpp/cpp_classes.asp
	string empName; // Refrence: w3schools - https://www.w3schools.com/cpp/cpp_classes.asp
	double empRateOfPay;
};


vector<string> readEmployeeNames(const string& filename) // Reference: w3schools - https://www.w3schools.com/cpp/cpp_vectors.asp#:~:text=C%2B%2B%20Vector,remove%20elements%20from%20an%20array
{
	vector<string> names;
	ifstream file(filename);
	string name;
	while (getline(file, name)) 
	{
		if (!name.empty()) 
		{
			names.push_back(name);
		}
	}
	file.close();
	return names;
}

vector<Employee> readEmployeeDetails(const string& filename) // Reference: w3schools - https://www.w3schools.com/cpp/cpp_vectors.asp#:~:text=C%2B%2B%20Vector,remove%20elements%20from%20an%20array
{
	vector<Employee> employees;
	ifstream file(filename);
	string line;
	while (getline(file, line)) 
	{
		stringstream ss(line); // References: geeksforgeeks - https://www.geeksforgeeks.org/processing-strings-using-stdistringstream/
		Employee emp;
		ss >> emp.id >> emp.rateOfPay; 
		getline(ss >> ws, emp.name); // extract the rest as name
		employees.push_back(emp);
	}
	file.close();
	return employees;
}

double calculateTax(double monthly_income) //Reference: w3schools - https://www.w3schools.com/cpp/ref_keyword_double.asp
{
	double annual_income = monthly_income * 12;
	double taxable_income = max(0.0, annual_income - TAX_FREE_ALLOWANCE);
	double annual_tax = taxable_income * TAX_RATE;
	return annual_tax / 12;
}

void processPayroll(const vector<Employee>& employees) 
{
	ofstream payrollFile("payroll_report.txt"); // Reference: w3schools - https://www.w3schools.com/cpp/cpp_files.asp

	for (const auto& emp : employees) 
	{
		double hours_worked;
		cout << "Enter hours worked for " << emp.name << ": ";
		while (!(cin >> hours_worked) || hours_worked < 0) 
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');// Reference: geeksforgeeks - https://www.geeksforgeeks.org/cin-ignore-function-in-cpp/
			cout << "Invalid input. Enter a valid number of hours: ";
		}

		double monthly_income = hours_worked * emp.rateOfPay;
		double tax = calculateTax(monthly_income);
		double net_income = monthly_income - tax;

		cout << fixed << setprecision(2); // Reference: w3schools - https://www.w3schools.com/cpp/ref_iostream_cout.asp#:~:text=The%20number%20of%20decimal%20places,with%20the%20setprecision()%20manipulator.&text=Represents%20integers%20as%20hexadecimal%20digits.&text=If%20a%20width%20is%20specified,output%20aligned%20to%20the%20right.
		cout << "--------------------------------------------" << endl;
		cout << "Employee ID: " << emp.id << endl;
		cout << "Employee Name: " << emp.name << endl;
		cout << "Rate of Pay: " << emp.rateOfPay << endl;
		cout << "Hours Worked: " << hours_worked << endl;
		cout << "Monthly Pay Before Tax: " << monthly_income << endl;
		cout << "Tax Deducted: " << tax << endl;
		cout << "Monthly Pay After Tax: " << net_income << endl;
		cout << "--------------------------------------------" << endl;

		// Write to file
		payrollFile << fixed << setprecision(2); // References: w3schools - https://www.w3schools.com/cpp/ref_iostream_cout.asp#:~:text=The%20number%20of%20decimal%20places,with%20the%20setprecision()%20manipulator.&text=Represents%20integers%20as%20hexadecimal%20digits.&text=If%20a%20width%20is%20specified,output%20aligned%20to%20the%20right.
		payrollFile << "--------------------------------------------" << endl;
		payrollFile << "Employee ID: " << emp.id << endl;
		payrollFile << "Employee Name: " << emp.name << endl;
		payrollFile << "Rate of Pay: " << emp.rateOfPay << endl;
		payrollFile << "Hours Worked: " << hours_worked << endl;
		payrollFile << "Monthly Pay Before Tax: " << monthly_income << endl;
		payrollFile << "Tax Deducted: " << tax << endl;
		payrollFile << "Monthly Pay After Tax: " << net_income << endl;
		payrollFile << "--------------------------------------------" << endl;
	}

	payrollFile.close(); // Close file
	cout << "Payroll report has been saved to 'payroll_report.txt'." << endl;
}

void fileWriteAndRead() 
{
	char data[100];

	ofstream outfile("C:\\Users\\Osase\\Downloads\\names42.txt"); // Write to file
	cout << "Writing to the file" << endl;
	cout << "Enter your name: " << endl;
	cin.ignore();
	cin.getline(data, 100);
	outfile << data << endl;
	outfile.close();

	ifstream infile("C:\\Users\\Osase\\Downloads\\names42.txt");// Read from file
	cout << "Reading from the file: " << endl;
	infile >> data;
	cout << data << endl;
	infile.close();

	ifstream infile2("C:\\Users\\Osase\\Downloads\\employees.txt");// Read from file
	cout << "Reading from the file: " << endl;
	infile2 >> data;
	cout << data << endl;
	infile2.close();

}

int main() 
{
	Employee emp;

	emp.id;
	emp.name;
	emp.rateOfPay; 
	

	string namesFile = ("C:\\Users\\User\\Downloads\\names42.txt");
	string employeesFile = ("C:\\Users\\User\\Downloads\\employees.txt");

	vector<string> employeeNames = readEmployeeNames(namesFile);
	vector<Employee> employees = readEmployeeDetails(employeesFile);

	if (employees.empty()) 
	{
		cout << "No employee data found." << endl;
		return 1;
	}

	processPayroll(employees);
	fileWriteAndRead();// Call function for writing and reading user input
	return 0;
}

/* 
 * Copyright © 2026 Osasere H. Ero. All rights reserved.
 * Proprietary and confidential. Unauthorized copying of this file, via any medium, is strictly prohibited.
 */
