#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <regex>
#include "admin.h"
#include "../manager/manager.h"
#include "../property/property.h"
#include "../main.h"
using namespace std;

Admin* aHead = nullptr;
Admin* aTail = nullptr;


void addNewAdmin(string adminId, string adminUserName, string adminPassword) {
    Admin* newAdmin = new Admin;
    newAdmin->adminId = adminId;
    newAdmin->adminUserName = adminUserName;
    newAdmin->adminPassword = adminPassword;
    newAdmin->next = nullptr;
    newAdmin->prev = nullptr;

    if (aHead == NULL) {
        aHead = newAdmin;
    }
    else {
        Admin* temp = aHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newAdmin;
        newAdmin->prev = temp; //doubly
    }

}

void initializeAdmin() {
    addNewAdmin("A1", "junming", "junming123");
    addNewAdmin("A2", "hoiyi", "hoiyi123");
    addNewAdmin("A3", "alan", "alan123");
}

bool searchAdmin(Admin* aHead, string username, string password) {
    Admin* temp = aHead;
    do {
        if (temp->adminUserName == username && temp->adminPassword == password) {
            return true;
        }
        temp = temp->next;
    } while (temp != aHead);
    return false;
}

void loginAdmin() {
    string adminUserName; string adminPassword;
    cout << "======== Admin Login ========" << endl;
    cout << "Enter your username: ";
    cin >> adminUserName;
    cout << "Enter your password: ";
    cin >> adminPassword;
    bool isAdminFound = searchAdmin(aHead, adminUserName, adminPassword);
    if (isAdminFound) {
        cout << "Login Successfully" << endl << endl;
    }
    else {
        cout << "Login Failed. Please double check your username and password" << endl << endl;
        displayMenu();
    }
}

void displayAdminMenu() {
    cout << "======== Admin Operation ========" << endl;
    cout << "1. Add New Manager" << endl;
    cout << "2. Modify Status Manager" << endl;
    cout << "3. Display Tenant Information" << endl;
    cout << "4. Display Properties Information" << endl;
    cout << "5. Logout" << endl;
    cout << "===========================" << endl;
    cout << "Enter your choice: ";
}

void addNewManager(string managerId, string managerUserName, string managerPassword, bool managerStatus) {

    // Ask the user to enter manager details
    cout << endl << "Enter Manager ID: ";
    cin >> managerId;

    // Check if the manager ID already exists in the linked list
    Manager* temp = mHead;
    while (temp != nullptr) {
        if (temp->managerId == managerId) {
            cout << "Manager ID already exists. Please enter a different Manager ID." << endl << endl;
            cout << "Enter Manager ID: ";
            cin >> managerId;
            // Reset the temp pointer to the beginning of the linked list to recheck the new ID
            temp = mHead;
        }
        else {
            temp = temp->next;
        }
    }

    cout << "Enter Manager Username: ";
    cin >> managerUserName;

    cout << "Enter Manager Password: ";
    cin >> managerPassword;

    // Set the managerStatus to true (assuming managerStatus represents an active status)
    managerStatus = true;

    // Ask for confirmation to save the new manager
    char confirm;
    cout << "Do you want to save the new manager? (Y/N): ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        // Create a new Manager node
        Manager* newManager = new Manager;
        newManager->managerId = managerId;
        newManager->managerUsername = managerUserName;
        newManager->managerPassword = managerPassword;
        newManager->managerStatus = managerStatus;
        newManager->next = nullptr;

        // Add the new manager to the linked list
        if (mHead == nullptr) {
            mHead = newManager;
        }
        else {
            Manager* temp = mHead;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newManager;
        }

        cout << endl << "New Manager Details Saved Successfully." << endl << endl;

        // Print the details of the newly added manager
        cout << "New Manager Details:" << endl;
        cout << "Manager ID: " << newManager->managerId << endl;
        cout << "Manager Username: " << newManager->managerUsername << endl;
        cout << "Manager Password: " << newManager->managerPassword << endl;
        cout << "Manager Status: " << (newManager->managerStatus ? "Active" : "Inactive") << endl << endl;
    }
    else {
        cout << endl << "New manager not saved. Operation cancelled." << endl << endl;
    }
}

void modifyManagerStatus() {
    string managerId;
    cout << endl << "Enter Manager ID to search: ";
    cin >> managerId;

    // Search for the manager with the specified managerId
    Manager* temp = mHead;
    bool managerFound = false;
    while (temp != nullptr) {
        if (temp->managerId == managerId) {
            managerFound = true;
            break;
        }
        temp = temp->next;
    }

    if (managerFound) {
        // Manager with the given managerId is found
        char newStatus;
        cout << "Manager Details:" << endl;
        cout << "Manager ID: " << temp->managerId << endl;
        cout << "Manager Username: " << temp->managerUsername << endl;
        cout << "Manager Password: " << temp->managerPassword << endl;
        cout << "Current Manager Status: " << (temp->managerStatus ? "Active" : "Inactive") << endl;
        cout << "Enter the new status (A for Active, I for Inactive): ";
        cin >> newStatus;

        // Update the manager status
        if (newStatus == 'A' || newStatus == 'a') {
            temp->managerStatus = true; // Set to Active
            cout << endl << "Manager Status Updated Successfully." << endl << endl;
        }
        else if (newStatus == 'I' || newStatus == 'i') {
            temp->managerStatus = false; // Set to Inactive
            cout << endl << "Manager Status Updated Successfully." << endl << endl;
        }
        else {
            cout << endl << "Invalid status entered. Status remains unchanged." << endl << endl;
        }

    }
    else {
        cout << endl << "Manager with ID '" << managerId << "' not found." << endl << endl;
    }
}

void displayPropertyByType(const string& propertyType) {
    Property* currentProperty = pHead;
    bool propertyFound = false;

    if (currentProperty == nullptr) {
        cout << "No property in the list." << endl;
        return;
    }

    while (currentProperty != nullptr) {
        if (currentProperty->propertyType == propertyType) {
            propertyFound = true;
            cout << "================================" << endl;
            cout << "Property ID: " << currentProperty->ads_id << endl;
            cout << "Property Name: " << currentProperty->prop_name << endl;
            cout << "Completion Year: " << currentProperty->completion_year << endl;
            cout << "Monthly Rent: " << currentProperty->monthly_rent << endl;
            cout << "Location: " << currentProperty->location << endl;
            cout << "Property Type: " << currentProperty->propertyType << endl;
            cout << "Number of Rooms: " << currentProperty->rooms << endl;
            cout << "Parking: " << currentProperty->parking << endl;
            cout << "Number of Bathrooms: " << currentProperty->bathroom << endl;
            cout << "Size: " << currentProperty->size << endl;
            cout << "Furnished: " << currentProperty->furnished << endl;
            cout << "Facilities: " << currentProperty->facilities << endl;
            cout << "Additional Facilities: " << currentProperty->additional_facilities << endl;
            cout << "Region: " << currentProperty->region << endl;
            cout << "================================" << endl << endl;

            // Ask for user input to continue or go back
            int userInput;
            cout << "Enter '1' to view the next property, '2' to view the previous property, or any other number to exit: ";
            cin >> userInput;

            if (userInput == 2 && currentProperty == pHead) {
                cout << "You are already at the beginning of the list." << endl << endl;
            }
            else if (userInput == 1) {
                // Move to the next property
                currentProperty = currentProperty->next;
            }
            else if (userInput == 2) {
                // Move to the previous property
                currentProperty = currentProperty->prev;
            }
            else {
                // Exit the loop if any other number is entered
                break;
            }
        }
        else {
            currentProperty = currentProperty->next;
        }
    }

    if (!propertyFound) {
        cout << "No properties found for the selected property type: " << propertyType << endl;
    }
}

void choosePropertyType(){
    int choice;
    do {
        cout << endl << "========== Property Type Menu ==========" << endl;
        cout << "1. Condominium" << endl;
        cout << "2. Apartment" << endl;
        cout << "3. Service Residence" << endl;
        cout << "4. Studio" << endl;
        cout << "5. Flat" << endl;
        cout << "6. Duplex" << endl;
        cout << "7. Exit" << endl;
        cout << "=======================================" << endl;
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        cout << endl;

        switch (choice) {
        case 1:
            displayPropertyByType("Condominium");
            break;
        case 2:
            displayPropertyByType("Apartment");
            break;
        case 3:
            displayPropertyByType("Service Residence");
            break;
        case 4:
            displayPropertyByType("Studio");
            break;
        case 5:
            displayPropertyByType("Flat");
            break;
        case 6:
            displayPropertyByType("Duplex");
            break;
        case 7:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please select again." << endl;
        }

        cout << endl;
    } while (choice != 7);

}

// Helper function to extract the numerical value from the monthly_rent string
int extractMonthlyRentValue(const string& rentString) {
    int rentValue = 0;
    string numericalPart;

    // Find the starting index of the numerical part (after "RM ")
    size_t startPos = rentString.find("RM ");
    if (startPos != string::npos) {
        startPos += 3; // Skip "RM "
        size_t endPos = rentString.find(" per month", startPos);
        numericalPart = rentString.substr(startPos, endPos - startPos);
    }

    // Extract numerical value from the numericalPart
    for (char c : numericalPart) {
        if (isdigit(c)) {
            rentValue = rentValue * 10 + (c - '0');
        }
    }

    return rentValue;
}

void displayPropertiesByMonthlyRent() {
    cout << "======== Display Properties by Monthly Rent ========" << endl;
    cout << "Choose an option:" << endl;
    cout << "1. Price less than RM 1000" << endl;
    cout << "2. Price less than RM 2000" << endl;
    cout << "3. Price less than RM 3000" << endl;
    cout << "Enter your choice: ";

    int option;
    cin >> option;

    if (option < 1 || option > 3) {
        cout << "Invalid option. Please choose a valid option (1, 2, or 3)." << endl;
        return;
    }

    // Filter properties by monthly rent based on the chosen option
    int maxMonthlyRent;
    switch (option) {
    case 1:
        maxMonthlyRent = 1000;
        break;
    case 2:
        maxMonthlyRent = 2000;
        break;
    case 3:
        maxMonthlyRent = 3000;
        break;
    }

    // Traverse and display properties with rent less than the chosen maximum rent
    Property* currentProperty = pHead;
    bool found = false;
    while (currentProperty != nullptr) {
        int rentValue = extractMonthlyRentValue(currentProperty->monthly_rent);
        if (rentValue < maxMonthlyRent) {
            found = true;
            cout << "================================" << endl;
            cout << "Property ID: " << currentProperty->ads_id << endl;
            cout << "Property Name: " << currentProperty->prop_name << endl;
            cout << "Completion Year: " << currentProperty->completion_year << endl;
            cout << "Monthly Rent: " << currentProperty->monthly_rent << endl;
            cout << "Location: " << currentProperty->location << endl;
            cout << "Property Type: " << currentProperty->propertyType << endl;
            cout << "Number of Rooms: " << currentProperty->rooms << endl;
            cout << "Parking: " << currentProperty->parking << endl;
            cout << "Number of Bathrooms: " << currentProperty->bathroom << endl;
            cout << "Size: " << currentProperty->size << endl;
            cout << "Furnished: " << currentProperty->furnished << endl;
            cout << "Facilities: " << currentProperty->facilities << endl;
            cout << "Additional Facilities: " << currentProperty->additional_facilities << endl;
            cout << "Region: " << currentProperty->region << endl;
            cout << "================================" << endl << endl;

            // Ask for user input to continue or go back
            int userInput;
            cout << "Enter '1' to view the next property, '2' to view the previous property, or any other number to exit: ";
            cin >> userInput;

            if (userInput == 2 && currentProperty == pHead) {
                cout << "You are already at the beginning of the list." << endl << endl;
            }
            else if (userInput == 1) {
                // Move to the next property
                currentProperty = currentProperty->next;
            }
            else if (userInput == 2) {
                // Move to the previous property
                currentProperty = currentProperty->prev;
            }
            else {
                // Exit the loop if any other number is entered
                break;
            }
        }
        else {
            currentProperty = currentProperty->next;
        }
    }

    if (!found) {
        cout << "No properties found for the selected monthly rent " << endl;
    }
}