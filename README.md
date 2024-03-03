# CS253
Car Rental System
# Car Rental System

## Overview
This project implements a car rental system that allows users to rent cars, manage customer and employee information, and perform various administrative tasks. The system is designed with classes for cars, users (including customers, employees, and managers), and functionality to manage databases stored in .csv files.

## Classes
### Car
- Attributes:
  - `model`: The model of the car.
  - `available`: Boolean indicating whether the car is available for rent.
  - `req_record`: Minimum required record for renting the car.
  - `price`: Price of renting the car.
  - `car_health`: Health status of the car(between 0 and 500).
  - `owner`: 0 for not rented, 1 for customer, 2 for employee.
  - `id`: Unique identifier for the car.
  - `name`: Name of the car.
  - `return_date_dd`, `return_date_mm`, `return_date_yyyy`: Return date of the car.
- Constructor: Initializes a car object with the provided attributes.

### User
- Attributes:
  - `name`: Name of the user.
  - `id`: Unique identifier for the user.
  - `password`: Password of the user.

### Customer
- Inherits from User.
- Additional Attributes:
  - `cust_record`: Customer's record.
- Constructor: Initializes a customer object with the provided attributes.
- Functions:
  - `get_cust_record()`: Returns the customer's record.
  - `show_available_cars()`: Displays available cars for rent.
  - `show_rented_cars()`: Displays cars rented by the customer.
  - `rent_car()`: Rents a car.
  - `check_fine()`: Checks if the customer has any fines.
  - `clear_dues()`: Clears any due payments by submitting rented cars with a return date less than or equal to today's date.

### Employee
- Inherits from User.
- Additional Attributes:
  - `emp_record`: Employee's record.
- Constructor: Initializes an employee object with the provided attributes.
- Functions:
  - `get_emp_record()`: Returns the employee's record.
  - `show_available_cars()`: Displays available cars for rent.
  - `show_rented_cars()`: Displays cars rented by the employee.
  - `rent_car()`: Rents a car.
  - `check_fine()`: Checks if the employee has any fines.
  - `clear_dues()`: Clears any due payments by submitting rented cars with a return date less than or equal to today's date.

### Manager
- Inherits from User.
- Functions:
  - `check_all_cars()`: Checks information about all cars.
  - `add_customer(customer *cust)`: Adds a new customer to the database.
  - `update_customer(customer *cust)`: Updates information of an existing customer.
  - `delete_customer(string id)`: Deletes a customer from the database.
  - `add_employee(employee *emp)`: Adds a new employee to the database.
  - `update_employee(employee *emp)`: Updates information of an existing employee.
  - `delete_employee(string id)`: Deletes an employee from the database.
  - `add_car(car *new_car)`: Adds a new car to the database.
  - `update_car(string m)`: Updates information of an existing car.
  - `delete_car(string m)`: Deletes a car from the database.

## Databases
- `customers.csv`: Stores information about customers.
- `employees.csv`: Stores information about employees.
- `manager.csv`: Stores information about managers.
- `cars.csv`: Stores information about cars.

## How to Use:

1. **Compilation:**
   - To compile the program, use any C++ compiler (e.g., g++, clang++, etc.).
   - Example command: `g++ -o car_rental_system car_rental_system.cpp`

2. **Execution:**
   - After compilation, execute the program by running the compiled binary.
   - Example command: `./car_rental_system`

3. **Functionality:**
   - Upon running the program, users are prompted to either log in or register.
   - If logging in:
     - Users are prompted to choose between customer, employee, or manager login.
     - Depending on the choice, the appropriate login procedure is followed.
   - If registering:
     - Users are prompted to choose between customer, employee, or manager registration.
     - Upon choosing, users need to provide necessary information for registration.
   - The system checks for existing users and performs the respective actions accordingly.
   - The session continues until the user chooses to terminate.

## File Structure:

- **car_rental_system.cpp:** This is the main source code file containing the implementation of the Car Rental System.
- **customers.csv, employee.csv, manager.csv:** These CSV files store user data for customers, employees, and managers, respectively.

## How Functions Run After Compilation:

After compilation, the C++ code is converted into machine-readable binary code by the compiler. When the program is executed, the operating system loads this binary code into memory and starts executing it. Here's how the functions run after compilation:

1. **Main Function:**
   - The main function is the entry point of the program.
   - It initializes the system and enters a loop where users are prompted for actions (login, register, or terminate).

2. **User Input:**
   - The program uses `cin` to get user input for actions such as login, register, or terminate.
   - Based on the input, the program proceeds with the appropriate action.

3. **Login/Register Functions:**
   - These functions handle user authentication and registration processes.
   - They interact with the user, request necessary information, and perform actions based on the provided data.

4. **Data Validation:**
   - The program validates user input and checks for existing records in CSV files to ensure data integrity.

5. **Session Management:**
   - The session continues until the user chooses to terminate by entering the corresponding option.

6. **Dynamic Memory Allocation:**
   - The program uses dynamic memory allocation (`new`) to create instances of user objects (customer, employee, manager) during login and registration.

7. **Function Calls:**
   - Various functions such as `valid_user`, `cust_registration`, `emp_registration`, `man_registration`, etc., are called based on user actions and data processing requirements.

8. **Error Handling:**
   - The program handles invalid inputs and errors gracefully by displaying appropriate messages to the user.

9. **Termination:**
   - Upon termination, the program exits the loop and ends execution.

## Additional Notes:

- Ensure that the CSV files (`customers.csv`, `employee.csv`, `manager.csv`) are present in the same directory as the compiled binary for proper functioning of the system.
- For any issues or inquiries, please send an email to [harshit22@iitk.ac.in](mailto:harshit22@iitk.ac.in)

Thank you for using the Car Rental System! Enjoy your experience!
