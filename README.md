# Bank Extension – Console Banking System with Transactions (C++)

This repository contains the **Bank Extension**, an extended **console-based banking system** written in **C++**, designed to manage client records and perform financial transactions.

This project is an **enhanced version of Bank 1 Project**, where transaction features were added to transform the system from a basic client manager into a **more realistic banking simulation**.

The project continues the practical application path based on  
**Cplusplus Problems V3**, and represents a clear step forward toward building **feature-complete console applications**.

---

## 📂 Project Overview
The **Bank Extension** follows the **Divide and Conquer principle**, where each operation is implemented in a **dedicated, reusable function**, ensuring clarity, maintainability, and scalability.

Client data is stored persistently using a text file:
- **ClientsRecords.txt**

The project simulates a lightweight banking database using **file handling techniques**.

---

## 🧱 Core Features

### 🔹 Client Management
- Add new clients
- Delete existing clients
- Update client information
- Find clients by account number
- Display all clients in a formatted table

### 🔹 Transactions Management (New)
- Deposit money into client accounts
- Withdraw money with balance validation
- Display total balances of all clients
- Dedicated transaction menu separated from the main menu

---

## 🧾 Transactions System Design
The transaction system is implemented as a **separate menu loop**, allowing users to:
- Perform multiple transactions consecutively
- Switch between deposit, withdrawal, and balance overview
- Return safely to the main menu at any time

Each transaction:
- Loads client data from file
- Modifies balances safely in memory
- Rewrites the updated data back to the file

---

## 🛠️ Technologies Used
- **Language:** C++
- **File Handling:** `<fstream>`
- **Data Structures:** `struct`, `vector`
- **Formatting:** `<iomanip>`
- **Standard Libraries:** `<iostream>`, `<string>`, `<cctype>`

---

## 📐 Project Structure & Design
- Client data is represented using a **struct** (`stClientData`)
- Menu navigation is handled using:
  - `enMenuOptions` (Main Menu)
  - `enTransactionsMenu` (Transactions Menu)
- Each feature is divided into:
  - Operation function (business logic)
  - Screen function (UI responsibility)
- File operations are centralized and reused across the system
- Program execution relies on **loop-based menus** until the user chooses to exit

---

## 🎯 Learning Objectives
This project reinforces and expands the following concepts:

- Designing **multi-level menu systems**
- Separating logic between main features and sub-features
- Applying **Divide and Conquer** on a larger scale
- Managing persistent data with file rewriting
- Building modular and extendable console applications

---

## 🧠 Concepts & Skills Demonstrated in This Code

### 🔹 C++ Fundamentals
- Control flow (`if`, `switch`)
- Loop structures (`for`, `while`, `do-while`)
- Input/output handling

### 🔹 Functions & Modularity
- Clear separation of responsibilities
- Passing data by value and reference
- Reusable helper functions
- Logical grouping of features

### 🔹 Structures & Enums
- Modeling real-world entities using `struct`
- Safe and readable menu handling using `enum`

### 🔹 Vectors & Data Handling
- Managing dynamic collections of clients
- Searching, updating, and iterating over vectors
- Synchronizing memory data with file data

### 🔹 File Handling
- Reading structured data from text files
- Writing and rewriting files to reflect updates
- Simulating database behavior using flat files

### 🔹 String Manipulation
- Custom string splitting using delimiters
- Numeric conversions (`stof`)
- Clean console formatting

### 🔹 Console UI Design
- Menu-driven navigation
- Separate screens for each operation
- Confirmation prompts for critical actions
- Tabular data presentation

---

## 🧪 Recommended Development Environment
- **Visual Studio (Windows)**

The project is compatible with any modern C++ compiler that supports standard libraries.

---

## 📌 Important Notes
- This project is **educational** and not intended for production use
- Data persistence is file-based (no databases)
- The transaction system is a **major functional extension**
- Start by selecting:
  - **[2] Add New Client**
  to initialize the data file

---

## 🔄 Project Evolution
This project represents a natural evolution from **Bank 1 Project** by introducing:
- Financial transactions
- Nested menu systems
- More realistic banking workflows

---

## 🙏 Acknowledgment
Special thanks to:
- **Programming Advices**
- **Professor Abouhodhoud**

for providing a structured learning roadmap focused on **clean code**, **practical thinking**, and **real-world application design**.

---

⭐ If you find this project useful, feel free to star the repository and use it as a reference for building more advanced C++ systems.
