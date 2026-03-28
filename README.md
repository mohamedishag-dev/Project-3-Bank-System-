# Bank Management System (C++) 🏦

A professional-grade **Bank Management System** featuring a multi-user environment with an integrated **Permissions System**.
This application allows administrators to manage clients and bank staff (users) with specific access levels,
ensuring secure financial operations.

## 🚀 Key Features

 ### 👤 User & Permission Management

- **Role-Based Access Control:** Assign specific permissions to users (e.g., a user can find clients but cannot delete them).
- **Full Access vs. Limited Access:** Support for admin accounts (`-1` permission) and restricted staff accounts.
- **User CRUD:** Add, Delete, Update, and Find bank users stored in `Users.txt`.

 ### 📂 Client Operations (CRUD)

- **Comprehensive Management:** Full control over client records (List, Add, Delete, Update, Find).
- **Duplicate Prevention:** Automatic checks to ensure Account Numbers and Usernames are unique.

 ### 💰 Transactions Module

- **Deposit/Withdraw:** Process financial transactions and update balances instantly.
- **Total Balances:** View the sum of all client balances across the bank.

 ### 🛡️ Security & Validation

- **Login Screen:** Requires valid credentials from `Users.txt` to enter the system.
- **Access Control:** Integrated `CheckAccessPermission` function that blocks unauthorized users from specific menus.

 ### 🛠️ Technical Overview

- **Data Persistence:** Uses dual-file storage (`Clients.txt` and `Users.txt`) with custom parsing logic.
- **Bitwise Permissions:** Uses an `enum` with power-of-two values (1, 2, 4, 8, etc.) to manage complex permission combinations.
- **Clean Architecture:** Modular design with separate functions for data conversion, file handling, and UI screens.

 ### 📂 Data Structure Examples

  #### `Users.txt`

   `Username#//#Password#//#Permissions`
   
```
Admin#//#1234#//#-1
Employee1#//#pass01#//#3
```

  ### `Clients.txt`

   `AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance`
   
```
A100#//#4444#//#Alice Smith#//#010203#//#6500.00
```

---

**Developed by:** [Mohamed Ishag]
