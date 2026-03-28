# 📘 Client Management System (C++)
## Overview
This project is a menu-driven Client Management System built in C++. It allows users to manage client records (add, update, delete, search, and list) with persistent storage in files. The system emphasizes structured programming, modular design, and user-friendly interfaces.

## ✨ Features
- Load and save client data from files
- Add new clients with validation
- Update or delete existing clients
- Search for clients by account number
- Display all client records in a formatted list
- Menu-driven interface with clear navigation

### 🔹 Data Handling
- `SplitString()` → Splits a line into tokens.
- `ConverLineDataToRecord()` → Converts a line of text into a client record.
- `LoadClientsDataFromFile()` → Loads client data from a file into memory.
- `ConverRecordToLine()` → Converts a client record back into a line.
- `SaveClientsDataToFile()` → Saves all client records to file.
- `AddDataLineToFile()` → Appends a new client record to file.

---

### 🔹 Client Operations
- `ReadClientAccountNumber()` → Reads account number from user input.
- `PrintClientRecord()` → Prints a single client record.
- `PrintAllClientsRecord()` → Prints all client records.
- `PrintAllClientsData()` → Displays all client data in a formatted table.
- `FindClientByAccountNumber()` → Searches for a client by account number.
- `ClientExistsByAccountNumber()` → Checks if a client exists.
- `ReadNewClient()` → Reads new client details from user input.
- `AddNewClients()` → Adds new clients to the system.
- `UpdateClient()` → Updates client information.
- `DeleteClientByAccountNumber()` → Deletes a client by account number.
- `ChangeClientRecord()` → Modifies an existing client record.
- `UpdateClientByAccountNumber()` → Updates client data by account number.

---

### 🔹 Menu & Screens
- `ShowMainMenue()` → Displays the main menu.
- `ReadGoMainMenueOptions()` → Reads user’s menu choice.
- `PerfromMainMenueOption()` → Executes selected menu option.
- `ShowClientList()` → Shows list of all clients.
- `ShowAddNewClients()` → Screen for adding new clients.
- `ShowUpdateClientInfo()` → Screen for updating client info.
- `ShowDeleteClientScreen()` → Screen for deleting clients.
- `ShowFindClient()` → Screen for searching clients.
- `ShowEndScreen()` → Displays exit screen.
- `GoBackToMainMenue()` → Returns to main menu.

---

## ✅ Future Improvements
- Add login/authentication system 🔐  
- Implement sorting and advanced searching 🔎  
- Improve UI with better formatting 🎨  
- Add error handling and input validation ⚡  

---
