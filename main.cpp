
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <climits>

#include "employee.hpp"


//  MARK: - Global Constants
static
auto dlm = std::string(76, '-');

#ifdef INTERACTIVE_
static
size_t interactiveLoad(size_t nr, employee * employees[]);

#else   /* INTERACTIVE_ */

static
size_t discreteLoad(size_t nr, employee * employees[]);
static
size_t discreteLoad(std::vector<employee *> & empvec);

#endif  /* INTERACTIVE_ */

void printHeader(void);
void showResults(size_t employeeCounter, employee * employees[]);
void showResults(std::vector<employee *> & empvec);

//  ----+----|----+----|----+----|----+----|----+----|----+----|
/*
 *  MARK: main()
 */
int main(int argc, char const * argv[]) {

  size_t employeeCounter = 0;

  employee * employees[100];

#ifdef INTERACTIVE_

  employeeCounter = interactiveLoad(100, employees);

#else   /* INTERACTIVE_ */

  employeeCounter = discreteLoad(100, employees);

  auto empvec = std::vector<employee *>();
  discreteLoad(empvec);
  // std::vector<employeeHourly *> empvec;

#endif  /* INTERACTIVE_ */

  printHeader();
  showResults(employeeCounter, employees);

  std::cout << dlm
            << std::endl;

#ifndef INTERACTIVE_
  std::cout << "\n\n";

  printHeader();
  showResults(empvec);

  std::cout << dlm
            << std::endl;

#endif  /* INTERACTIVE_ */

  return 0;
} //end main

void printHeader(void) {
  std::cout << '\n';
  std::cout << std::setw(45) << "-PAYROLL REPORT-"
            << std::endl;
  std::cout << dlm
            << std::endl;
  std::cout << std::setw( 7) << "F-NAME"
            << std::setw(10) << "L-NAME"
            << std::setw(12) << "EMPLOYEE-ID"
            << std::setw( 4) << "HW"
            << std::setw(10) << "OT-HOURS"
            << std::setw(10) << "GROSS"
            << std::setw( 8) << "TAX"
            << std::setw( 8) << "NETPAY"
            << std::setw( 7) << "S/H"
            << std::endl;
  std::cout << dlm
            << std::endl; 
  // end printHeader() function
}

void showResults(size_t employeeCounter, employee * employees[]) {
  for (size_t i_ = 0; i_ < employeeCounter; ++i_) {
    employees[ i_ ]->printData();
  }
}

void showResults(std::vector<employee *> & empvec) {
  for (auto const em : empvec) {
    em->printData();
  }
}

#ifdef INTERACTIVE_

static
size_t interactiveLoad(size_t nr, employee * employees[]) {
  size_t employeeCounter = 0;
  size_t totalEmployeeCount = 0;
  std::string fName;
  std::string lName;
  int empID = 0;
  int stat = 0;
  int rate = 0;
  int hrs = 0;

  std::cout << "Enter # of employees you want to process:  ";
  std::cin >> totalEmployeeCount;

  while (employeeCounter < totalEmployeeCount) {
    stat = 0;
    std::cout << "Is employee " << employeeCounter + 1
              << " hourly or salary? (enter 1 for hourly / 2 for salary): ";
    std::cin >> stat;
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
    std::cout << " . . . " << stat << '\n';

    if (stat == 1) {
      std::cout << "Instantiating and HOURLY employee object inherited from base class employee"
                << std::endl
                << std::endl;
      std::cout << "Enter employee's ID: ";
      std::cin >> empID;
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
      std::cout << "Enter employee's first name: ";
      std::cin >> fName;
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
      std::cout << "Enter employee's last name: ";
      std::cin >> lName;
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
      std::cout << "Enter employee's hourly wage: ";
      std::cin >> rate;
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
      std::cout << "Enter employee's hours for this week: ";
      std::cin >> hrs;
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');

      employees[employeeCounter] = new employeeHourly();

      employees[employeeCounter]->setVariables( empID, fName, lName, stat, rate, hrs );
      employees[employeeCounter]->calculateGrossPay();
      employees[employeeCounter]->calculateTaxAmount();
      employees[employeeCounter]->calculateNetPay();

      std::cout << std::endl
                << std::endl;

      employeeCounter++;
    } //end if 
    else {
    //if employee is NOT hourly (Salary clause)
      std::cout << "instantialting a SALARY employee object in herited from base class employee"
                << std::endl
                << std::endl;
      std::cout << "Enter employee's ID: ";
      std::cin >> empID;
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
      std::cout << "Enter employee's first name: ";
      std::cin >> fName;
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
      std::cout << "Enter employee's last name: ";
      std::cin >> lName;
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
      std::cout << "Enter employee's hourly wage: ";
      std::cin >> rate;
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
      std::cout << "Enter employee's hours for this week: ";
      std::cin >> hrs;
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');

      employees[employeeCounter] = new employeeSalary();

      employees[employeeCounter]->setVariables(empID, fName, lName, stat,rate, hrs);
      std::cout <<
      employees[employeeCounter]->calculateGrossPay() << '\n';
      std::cout <<
      employees[employeeCounter]->calculateTaxAmount() << '\n';
      std::cout <<
      employees[employeeCounter]->calculateNetPay() << '\n';

      std::cout << std::endl
                << std::endl;

      employeeCounter++;
    } //end else
  }//end while

  return employeeCounter;
}

#else   /* INTERACTIVE_ */

struct sampledata {
  int empId;
  std::string forname;
  std::string surname;
  int rate;
  int stat;
  int hrs;
};

static
std::vector<sampledata> const sdata {
  { 11, "Norma", "Snockers", 40'000, 2, 48, },
  { 21, "Irma",   "Nalias",      15, 1, 50, },
};

static
size_t discreteLoad(size_t nr, employee * employees[]) {
  size_t employeeCounter = 0;
  std::string fName;
  std::string lName;
  int empID = 0;
  int stat = 0;
  int rate = 0;
  int hrs = 0;

  for (auto const & sd : sdata) {
    fName = sd.forname;
    lName = sd.surname;
    empID = sd.empId;;
    stat = sd.stat;
    rate = sd.rate;
    hrs = sd.hrs;

    if (stat == 2) {
      employees[employeeCounter] = new employeeSalary(
        empID, fName, lName, stat, rate, hrs);
    }
    else {
      employees[employeeCounter] = new employeeHourly(
        empID, fName, lName, stat, rate, hrs);
    }

    // employee[employeeCounter]->setVariables(empID, fName, lName, stat,rate, hrs);
    // employees[employeeCounter]->calculateGrossPay();
    // employees[employeeCounter]->calculateTaxAmount();
    // employees[employeeCounter]->calculateNetPay();

    employeeCounter++;
  }

  return employeeCounter;
}
static
size_t discreteLoad(std::vector<employee *> & empvec) {
  std::string fName;
  std::string lName;
  int empID = 0;
  int stat = 0;
  int rate = 0;
  int hrs = 0;

  for (auto const & sd : sdata) {
    fName = sd.forname;
    lName = sd.surname;
    empID = sd.empId;;
    stat = sd.stat;
    rate = sd.rate;
    hrs = sd.hrs;

    if (sd.stat == 2) {
      empvec.push_back(
        new employeeSalary(empID, fName, lName, stat, rate, hrs)
      );
    }
    else {
      empvec.push_back(
        new employeeHourly(empID, fName, lName, stat, rate, hrs)
      );
    }
  }

  return empvec.size();
}

#endif  /* INTERACTIVE_ */
