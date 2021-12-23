//
//  employee.cpp
//  CF.Homework105
//
//  Created by Alan Sampson on 12/22/21.
//

#include "employee.hpp"

//  MARK: - Class employee Implementation
/*
 *  MARK: employee::employee() default ctor.
 */
employee::employee(int empID, std::string fName, std::string lName, int stat, int rate, int hrs)
: employeeID { empID }, firstName { fName }, lastName { lName }, payStat { stat }, hours { hrs } {
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
}

/*
 *  MARK: employee::employee() copy ctor.
 */
employee::employee(employee const & that) {
  std::cout << "employee::employee() copy ctor\n";
  employeeID = that.employeeID;
  firstName  = that.firstName;
  lastName   = that.lastName;
  payStat    = that.payStat;
  hourlyRate = that.hourlyRate;
  salary     = that.salary;
  hours      = that.hours;
}

/*
 *  MARK: employee::calculateTaxAmount()
 */
double employee::calculateTaxAmount(void) {
  std::cout << "employee::" << __func__ << "() = ";
  taxRate = .30; //set a flat taxrate 30%
  taxAmount = grossPay * taxRate; //formula to calculate tax amount

  std::cout << taxAmount << '\n';
  return taxAmount;
} //end calculateTaxAmount() function

/*
 *  MARK: employee::calculateNetPay()
 */
double employee::calculateNetPay(void) {
  std::cout << "employee::" << __func__ << "() = ";
  netPay = grossPay - taxAmount;

  std::cout << netPay << '\n';
  return netPay;
} //end

/*
 *  MARK: employee::printData()
 */
void employee::printData(void) const {
  std::cout << std::setprecision(2)
            << std::setiosflags(std::ios::fixed |
                                std::ios::showpoint);
  std::cout << std::setw( 7) << firstName
            << std::setw(10) << lastName
            << std::setw(12) << employeeID
            << std::setw( 4) << hours
            << std::setw(10) << otHours
            << std::setw(10) << grossPay
            << std::setw( 8) << taxAmount
            << std::setw( 8) << netPay
            << std::setw( 7) << ((payStat == 2) ? "Sal" : "Hr")
            << std::endl;
}


//  MARK: - Class employeeSalary Implementation
/*
 *  MARK: employeeSalary::employeeSalary() default ctor.
 */
employeeSalary::employeeSalary(int empID, std::string fName, std::string lName, int stat, int rate, int hrs)
: employee(empID, fName, lName, stat, rate, hrs) {
  std::cout << "employeeSalary::employeeSalary() default ctor\n";

  calculateGrossPay();
  calculateTaxAmount();
  calculateNetPay();
}

/*
 *  MARK: employeeSalary::employeeSalary() copy ctor.
 */
employeeSalary::employeeSalary(employeeSalary const & that) : employee(that) {
  std::cout << "employeeSalary::employeeSalary() copy ctor\n";
}

/*
 *  MARK: employeeSalary::calculateGrossPay()
 */
double employeeSalary::calculateGrossPay(void) {
  std::cout << "employeeSalary::" << __func__ << "() = ";

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

  std::cout << grossPay << '\n';
  return grossPay;
}


//  MARK: - Class employeeHourly Implementation
/*
 *  MARK: employeeHourly::employeeHourly() default ctor.
 */
employeeHourly::employeeHourly(int empID, std::string fName, std::string lName, int stat, int rate, int hrs)
: employee(empID, fName, lName, stat, rate, hrs) {
  std::cout << "employeeHourly::employeeHourly() default ctor\n";

  calculateGrossPay();
  calculateTaxAmount();
  calculateNetPay();
}

/*
 *  MARK: employeeHourly::employeeHourly() copy ctor.
 */
employeeHourly::employeeHourly(employeeHourly const & that) : employee(that) {
  std::cout << "employeeHourly::employeeHourly() copy ctor\n";
}

/*
 *  MARK: employeeHourly::calculateGrossPay
 */
double employeeHourly::calculateGrossPay(void) {
  std::cout << "employeeHourly::" << __func__ << "() = ";

  const double regPay = (40 * hourlyRate);//calculate regular hours
  if ( hours > 40 ) {
    otHours = (hours - 40);//calculate OT hours
    otPay = (otHours * hourlyRate * 1.5);//calculate OT pay
    grossPay = (regPay + otPay);//calculate gross pay
  } //end if clause for gross pay with overtime
  else {
    otHours = 0;
    otPay = 0.0;
    grossPay = regPay;
  }//end else clause for four hours

  std::cout << grossPay << '\n';
  return grossPay;
}
