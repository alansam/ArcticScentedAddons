
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <climits>

// using namespace std;

//  ----+----|----+----|----+----|----+----|----+----|----+----|
class employee {
protected:
  double salary;
  double hourlyRate;
  double taxRate;
  double taxAmount;
  double grossPay;
  double netPay;
  double otPay;
  int hours;
  int otHours;
  int payStat;
  int employeeID;
  std::string firstName;
  std::string lastName;

public:
  employee(int empID = 0,
           std::string fName = "",
           std::string lName = "",
           int stat = 0,
           int rate = 0,
           int hrs = 0) :
           employeeID { empID },
           firstName { fName },
           lastName { lName },
           payStat { stat },
           hours { hrs } {
    std::cout << "employee::employee() default ctor\n";    
    if (payStat == 1) {
      hourlyRate = rate;
      salary = 0.0;
    }
    else if (payStat == 2) {
      salary = rate;
      hourlyRate = 0.0;
    }
    else {
      salary = 0.0;
      hourlyRate = 0.0;
    }
  };
  employee(employee const & that) {
    std::cout << "employee::employee() copy ctor\n";
    employeeID = that.employeeID;
    firstName  = that.firstName;
    lastName   = that.lastName;
    payStat    = that.payStat;
    hourlyRate = that.hourlyRate;
    salary     = that.salary;
    hours      = that.hours;
  }
  employee(employee &&) = default;
  employee & operator=(employee const &) = default;
  virtual
  ~employee() = default;

  void setVariables(int empID,
                    std::string fName,
                    std::string lName,
                    int stat,
                    int rate,
                    int hrs) {
    employeeID = empID;
    firstName = fName;
    lastName = lName;
    payStat = stat;

    if (payStat == 1) {
      hourlyRate = rate;
    }
    else {
      salary = rate;
    }

    hours = hrs;
  } //declare function to calculate gross pay

// public:
  virtual double calculateGrossPay(void) = 0;
  virtual void tell(void) const = 0;

  double calculateTaxAmount(void) {
    taxRate = .30; //set a flat taxrate 30%
    taxAmount = grossPay * taxRate; //formula to calculate tax amount
    return taxAmount;
  } //end calculateTaxAmount() function

  double calculateNetPay(void) {
    netPay = grossPay - taxAmount;
    return netPay;
  } //end

  void printData(void) const {
    std::cout << std::setprecision(2)
              << std::setiosflags(std::ios::fixed |
                                  std::ios::showpoint);
    std::cout << std::setw( 7) << firstName
              << std::setw(10) << lastName
              << std::setw(12) << employeeID
              << std::setw( 8) << hours
              << std::setw( 6) << otHours
              << std::setw(10) << grossPay
              << std::setw( 8) << netPay
              << std::setw( 8) << otPay
              << std::setw( 7) << ((payStat == 2) ? "Sal" : "Hr")
              << std::endl;
  } //end printData() function
};  //end employee class
//  ----+----|----+----|----+----|----+----|----+----|----+----|

class employeeSalary : public employee {
public:
  employeeSalary(int empID = 0,
           std::string fName = "",
           std::string lName = "",
           int stat = 0,
           int rate = 0,
           int hrs = 0) 
    : employee(empID, fName, lName, stat, rate, hrs) {
    std::cout << "employeeSalary::employeeSalary() default ctor\n";    
  }
  employeeSalary(employeeSalary const & that) : employee(that) {
    std::cout << "employeeSalary::employeeSalary() copy ctor\n";
  }
  employeeSalary(employeeSalary &&) = default;
  employeeSalary & operator=(employeeSalary const &) = default;
  virtual
  ~employeeSalary() = default;

  virtual
  double calculateGrossPay(void) override {
    std::cout << "employeeSalary::" << __func__ << "()\n";

    double regPay = salary / 52;
    double hourlyRate = regPay / 40;

    if (hours > 40) {
      otHours = (hours - 40);//calculate OT hours
      otPay = (otHours * hourlyRate);//calculate OT pay
      grossPay = (regPay + otPay);
    }
    else if (hours <= 40) {
      otHours = 0;
      otPay = 0.0;
      grossPay = regPay;
    }

    return grossPay;
  }

  virtual
  void tell(void) const override {
    std::cout << "employeeSalary::" << __func__ << "()\n";
  }
};  //end EmployeeSalary class 
//  ----+----|----+----|----+----|----+----|----+----|----+----|

class employeeHourly : public employee {
public:
  // employeeHourly() = default;
  employeeHourly(int empID = 0,
           std::string fName = "",
           std::string lName = "",
           int stat = 0,
           int rate = 0,
           int hrs = 0)
    : employee(empID, fName, lName, stat, rate, hrs) {
    std::cout << "employeeHourly::employeeHourly() default ctor\n";
  }
  employeeHourly(employeeHourly const & that) : employee(that) {
    std::cout << "employeeHourly::employeeHourly() copy ctor\n";
  }
  employeeHourly(employeeHourly &&) = default;
  employeeHourly & operator=(employeeHourly const &) = default;
  virtual
  ~employeeHourly() = default;

  virtual
  double calculateGrossPay(void) override {
    std::cout << "employeeHourly::" << __func__ << "()\n";

    const double regPay = (40 * hourlyRate);//calculate regular hours
    if (hours > 40) {
      otHours = (hours - 40);//calculate OT hours
      otPay = (otHours * hourlyRate * 1.5);//calculate OT pay
      grossPay = (regPay + otPay);//calculate gross pay
    } //enf if clause for gross pay with overtime
    else {
      otHours = 0;
      otPay = 0.0;
      grossPay = regPay;
    }//end else clause for four hours
    return grossPay;
  } //end calculateGrossPay() function

  virtual
  void tell(void) const override {
    std::cout << "employeeHourly::" << __func__ << "()\n";
  }
};  //end EmployeeHourly class
//  ----+----|----+----|----+----|----+----|----+----|----+----|

//  ----+----|----+----|----+----|----+----|----+----|----+----|

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
      std::cout <<
      employees[employeeCounter]->calculateGrossPay() << '\n';
      std::cout <<
      employees[employeeCounter]->calculateTaxAmount() << '\n';
      std::cout <<
      employees[employeeCounter]->calculateNetPay() << '\n';

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
  { 11, "Norma", "Snockers", 26, 2, 40, },
  { 21, "Irma",  "Naliias",  15, 1, 50, },
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
        empID, fName, lName, stat,rate, hrs);
    }
    else {
      employees[employeeCounter] = new employeeHourly(
        empID, fName, lName, stat,rate, hrs);
    }

    employees[employeeCounter]->tell();

    // employee[employeeCounter]->setVariables(empID, fName, lName, stat,rate, hrs);
    std::cout <<
    employees[employeeCounter]->calculateGrossPay() << '\n';
    std::cout <<
    employees[employeeCounter]->calculateTaxAmount() << '\n';
    std::cout <<
    employees[employeeCounter]->calculateNetPay() << '\n';

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

static
auto dlm = std::string(76, '-');

void printHeader(void) {
  std::cout << '\n';
  std::cout << std::setw(45) << "-PAYROLL REPORT-"
            << std::endl;
  std::cout << dlm
            << std::endl;
  std::cout << "F-NAME"
               "  L-NAME"
               "    EMPLOYEE-ID"
               "    HW"
               "   OT-HOURS"
               "  GROSS"
               "    TAX"
               "   NETPAY"
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
