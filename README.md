# Bank System Project

## Overview

This project is a console-based banking system written in C++ using object-oriented programming. It manages users, clients, transactions, and currency exchange operations through a menu-driven interface.

## Features

- User authentication and login flow
- User management with permissions
- Client list, add, update, delete, and search
- Deposit, withdraw, transfer, and balance operations.
- Tracking operations.
- Login activity tracking
- Currency exchange screens and rate lookup
- Data stored in local text files

## Project Structure

- app/: main application entry point
- core/: core classes for users, clients, person, login tracking, and shared logic
- screens/: feature-based UI screens
  - auth/: login and main menu screens
  - clients/: client-related operations
  - users/: user management screens
  - currency/: currency exchange screens
  - common/: shared screen base class
- global/: application-level global state and shared values
- libs/: local reusable libraries and helper classes
- data/: project data files such as users, clients, transfer logs, and rates

## How to Run

From the project root, compile the application with:

```bash
g++ app/main.cpp -Icore -Ilibs -Iscreens/auth -Iscreens/clients -Iscreens/users -Iscreens/currency -Iscreens/common -Iglobal -o app/main.exe
```

Then run:

```bash
./app/main.exe
```

## Notes

The application uses local C++ helper libraries under the libs folder for validation, strings, dates, and utility functions. The global state is managed outside the screen layer to keep shared values such as the current user and app settings centralized.
