# CS253
Car Rental System

## Overview
This project implements a car rental system that allows users to rent cars, manage customer and employee information, and perform various administrative tasks.

## Classes
### Car
- Attributes: model, available, req_record, price, car_health, owner, id, name, return_date_dd, return_date_mm, return_date_yyyy
- Constructor: Initializes a car object with the provided attributes.

### User
- Attributes: name, id, password

### Customer
- Inherits from User.
- Additional Attributes: cust_record
- Functions: get_cust_record(), show_available_cars(), show_rented_cars(), rent_car(), check_fine(), clear_dues()

### Employee
- Inherits from User.
- Additional Attributes: emp_record
- Functions: get_emp_record(), show_available_cars(), show_rented_cars(), rent_car(), check_fine(), clear_dues()

### Manager
- Inherits from User.
- Functions: check_all_cars(), add_customer(), update_customer(), delete_customer(), add_employee(), update_employee(), delete_employee(), add_car(), update_car(), delete_car()

## Databases
- customers.csv, employees.csv, manager.csv, cars.csv

## How to Use:
1. **Compilation:** Compile with any C++ compiler.
2. **Execution:** Run the compiled binary.
3. **Functionality:** Log in or register as customer, employee, or manager.
4. **File Structure:** car_rental_system.cpp, customers.csv, employee.csv, manager.csv

## Assumptions:
- A fine is imposed per day after the return date.
- Customer or employee record decrements by 1 per day after the return date.

For inquiries, email [harshit22@iitk.ac.in](mailto:harshit22@iitk.ac.in)
