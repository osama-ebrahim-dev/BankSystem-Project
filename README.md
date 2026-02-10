# 🏦 Bank Management System (C++)

A console-based **Bank Management System** developed in **C++**, following solid **Object-Oriented Programming (OOP)** principles and a layered architecture.  
The system simulates real-world banking operations with file-based persistence, authentication, authorization, logging, and currency exchange.

---

## 📌 Overview

This project provides a complete banking workflow, including:

- Client and account management  
- Secure user authentication and authorization  
- Transaction processing  
- Currency exchange operations  
- Audit logging and password encryption  

The focus is on **clean code**, **scalability**, and **realistic business logic**.

---

## 🚀 Features

### 🧾 Client Management
- Find clients from text file
- Add new clients
- Update existing clients
- Delete clients
- List all clients
- View balances list

### 💰 Transactions
- Deposit
- Withdraw
- View total balances
- Transaction menu navigation

### 👥 User Management
- Login and logout system
- Role-based permissions
- List users
- Add, update, delete, and find users
- Encrypted user passwords

### 🔐 Security & System
- Session management
- Audit logging (logins and transactions)
- File-based logs
- Password encryption

### 💱 Currency Exchange
- List currencies
- Find currency by code
- Update exchange rates
- Currency calculator

---

## 🧱 Object-Oriented Design

The project is structured using inheritance, encapsulation, and polymorphism.

### 📦 Class Architecture

#### 👤 People 
- `Person`
- `BankClient` *(inherits from Person)*
- `User` *(inherits from Person)*

#### 🖥 Screens & Menus
- `Screen`
  - `MainMenuScreen`
  - `TransactionsMenuScreen`
  - `ManageUsersMenuScreen`
  - `LoginScreen`

#### 🔄 System & Utilities
- `Session`
- `clsAuditLogger`

#### 💱 Currency
- `clsCurrency`

---

## 🧰 Technologies & Tools

- **Language:** C++
- **IDE:** Visual Studio
- **Version Control:** Git & GitHub

### 📚 Custom Libraries
- String Library (custom helper)
- Input Validation Library
- Utility Library
- Messages Library

---

## 📂 Data Persistence

- File-based storage using `.txt` files
- Separate files for:
  - Clients
  - Users
  - Logs
  - Currency data

---

## 👨‍💻 Author

**Osama Ebrahim**  
📧 Email: [osama.ebrahim.dev@gmail.com](mailto:osama.ebrahim.dev@gmail.com)  
🌐 GitHub: [https://github.com/osama-ebrahim-dev](https://github.com/osama-ebrahim-dev)

---

