//
//  employee.hpp
//  CF.Homework105
//
//  Created by Alan Sampson on 12/22/21.
//

#pragma once
#ifndef employee_hpp
#define employee_hpp

#include <iostream>
#include <iomanip>
#include <string>
#include <climits>

//  ----+----|----+----|----+----|----+----|----+----|----+----|----+----|
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
           int hrs = 0);

  employee(employee const & that);

  employee(employee &&) = default;
  virtual
  employee & operator=(employee const &) = default;
  virtual
  ~employee();

  //  pure virtual function.
  virtual double calculateGrossPay(void) = 0;

  virtual
  double calculateTaxAmount(void);
  virtual
  double calculateNetPay(void);
  virtual
  void printData(void) const;
};

//  ----+----|----+----|----+----|----+----|----+----|----+----|----+----|
class employeeSalary : public employee {
public:
  employeeSalary(int empID = 0,
                 std::string fName = "",
                 std::string lName = "",
                 int stat = 0,
                 int rate = 0,
                 int hrs = 0);

  employeeSalary(employeeSalary const & that);

  employeeSalary(employeeSalary &&) = default;
  virtual
  employeeSalary & operator=(employeeSalary const &) = default;
  virtual
  ~employeeSalary();

  //  Implement pure virtusl function
  virtual
  double calculateGrossPay(void) override;
};  //end EmployeeSalary class

//  ----+----|----+----|----+----|----+----|----+----|----+----|----+----|
class employeeHourly : public employee {
public:
  // employeeHourly() = default;
  employeeHourly(int empID = 0,
                 std::string fName = "",
                 std::string lName = "",
                 int stat = 0,
                 int rate = 0,
                 int hrs = 0);

  employeeHourly(employeeHourly const & that);

  employeeHourly(employeeHourly &&) = default;
  virtual
  employeeHourly & operator=(employeeHourly const &) = default;
  virtual
  ~employeeHourly();

  //  Implement pure virtusl function
  virtual
  double calculateGrossPay(void) override;
};  //end EmployeeHourly class
//  ----+----|----+----|----+----|----+----|----+----|----+----|----+----|

#endif /* employee_hpp */
