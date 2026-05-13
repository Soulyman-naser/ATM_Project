# ATM System (Procedural Programming)

## 📝 Overview
This is a comprehensive, console-based ATM Management System built with C++. The project demonstrates the application of Procedural Programming principles, including structured data handling, file input/output, and robust user input validation.

---

## 🚀 Key Features

Based on the implementation in ATM.cpp, the system supports:

- Secure Authentication  
  User login requiring an Account Number and PIN Code verified against stored data.

- Quick Withdraw  
  Pre-defined amounts (20, 50, 100, etc.) for faster transactions.

- Normal Withdraw  
  Custom withdrawal amounts with validation for multiples of 5 and balance sufficiency.

- Deposit System  
  Add funds to the account with input validation for positive numbers.

- Check Balance  
  Real-time balance inquiry for the logged-in user.

- Data Persistence  
  All transactions are updated and saved permanently in a Clients.txt file using a custom separator (#//#).

---

## 🛠️ Technical Implementation

- Language: C++
- Programming Paradigm: Procedural Programming (PP)
- Data Structures:  
  Used struct to manage client profiles and vector for dynamic data handling.
- File Handling:  
  Implemented custom functions to convert records to lines and vice versa for storage.
- Input Validation:  
  Robust handling of invalid inputs using cin.fail() and buffer clearing.

---

## 📂 Project Files

| File | Description |
|------|-------------|
| ATM.cpp | The core source code containing the system logic and console UI menus |
| Clients.txt | Database file where client information is stored |

---

## ⚙️ How to Use

1. Compile the ATM.cpp file using any C++ compiler such as:
   - g++
   - MSVC
   - Code::Blocks
   - Visual Studio

2. Ensure that Clients.txt is located in the same directory as the executable file.

3. Run the program and log in using sample credentials from the text file.

Example:
`txt
Account Number: A222
PIN Code: 1234

## 💡 Why This Project?

This project was developed to simulate real-world ATM operations while improving problem-solving skills and mastering procedural programming concepts in C++.

## 👨‍💻 Author

Sliman Naser  
Computer Science Student passionate about backend development, problem solving, and software engineering.

This project was built as part of my journey to strengthen my C++ and Procedural Programming skills through real-world console applications.