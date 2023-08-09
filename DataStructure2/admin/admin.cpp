#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <regex>
#include "admin.h"
#include "../manager/manager.h"
#include "../property/property.h"
#include "../tenant/tenant.h"
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

bool searchAdmin(string username, string password) {
    while (aHead != nullptr) {
        if (aHead->adminUserName == username && aHead->adminPassword == password) {
            return true;
        }
        aHead = aHead->next;
    }
    return false;
}

void loginAdmin() {
    string adminUserName; 
    string adminPassword;
    cout << "======== Admin Login ========" << endl;
    cout << "Enter your username: ";
    cin >> adminUserName;
    cout << "Enter your password: ";
    cin >> adminPassword;
    bool isAdminFound = searchAdmin(adminUserName, adminPassword);
    if (isAdminFound) {
        cout << endl << "Login successful. Welcome, " << adminUserName << " !" << endl << endl;
        displayAdminMenu();
    }
    else {
        cout << "Login failed. Please try again." << endl << endl;
        displayMenu();
    }
}

void displayAdminMenu() {
    int adminOption;
    bool adminLogIn = true;

    while (adminLogIn)
    {
        cout << "======== Admin Menu ========" << endl;
        cout << "1. Add New Manager" << endl;
        cout << "2. Modify Status Manager" << endl;
        cout << "3. Display Tenant Information" << endl;
        cout << "4. Display Properties Information based on Monthly Rent" << endl;
        cout << "5. Display Properties Information based on Property Type" << endl;
        cout << "6. Logout" << endl;
        cout << "===========================" << endl;
        cout << "Enter your choice: ";

        cin >> adminOption;
        switch (adminOption)
        {
        case 1:
            addNewManager();
            break;
        case 2:
            modifyManagerStatus();
            break;
        case 3:
            chooseTenantStatus();
            break;
        case 4:
            displayPropertiesByMonthlyRent();
            break;
        case 5:
            choosePropertyType();
            break;
        case 6:
            adminLogIn = false;
            cout << "Logged out successfully." << endl;
            break;
        default:
            cout << "Invalid Option. Please Try Again." << endl;
            break;
        }
    }
}

void addNewManager() {

    string managerUsername;
    string managerPassword;
    bool managerStatus = true;

    // Ask the user to enter manager details
    cout << "Enter Manager Username: ";
    cin >> managerUsername;

    cout << "Enter Manager Password: ";
    cin >> managerPassword;

    // Ask for confirmation to save the new manager
    char confirm;
    cout << "Do you want to save the new manager? (Y/N): ";
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y') {
        addInManager(managerUsername, managerPassword, managerStatus);

        // Print the details of the newly added manager
        cout << endl << "New Manager Details Saved Successfully." << endl;
        cout << "Manager Username: " << managerUsername << endl;
        cout << "Manager Password: " << managerPassword << endl;
        cout << "Manager Status: " << (managerStatus ? "Active" : "Inactive") << endl << endl;
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
    int batchSize = 1;
    int pageNum = 1;
    bool propertyFound = false;

    if (currentProperty == nullptr) {
        cout << "No property in the list." << endl;
        return;
    }

    while (currentProperty != nullptr) {
        if (currentProperty->propertyType == propertyType) {
            propertyFound = true;
            cout << endl;
            cout << "============== PAGE " << pageNum << " ===============" << endl;
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
            cout << "============== PAGE " << pageNum << " ===============" << endl << endl;

            // Check if the current page is full (batchSize reached)
            if (pageNum % batchSize == 0) {
                // Ask for user input to continue or go back
                int userInput;
                cout << "Enter '1' to view the next page, '2' to view the previous page, or any other number to exit: ";
                cin >> userInput;

                if (userInput == 2 && pageNum <= batchSize) {
                    cout << "You are already at the beginning of the list." << endl;
                }
                else if (userInput == 1) {
                    // Move to the next page
                    currentProperty = currentProperty->next;
                    pageNum = pageNum + 1;
                }
                else if (userInput == 2) {
                    // Move to the previous page
                    currentProperty = currentProperty->prev;
                    pageNum = pageNum - batchSize;
                }
                else {
                    // Exit the loop if any other number is entered
                    break;
                }
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
        cout << endl;
        cout << "========== Property Type Menu ==========" << endl;
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
    
    int option;

    while (true) {
        cout << endl;
        cout << "======== Display Properties by Monthly Rent ========" << endl;
        cout << "Choose an option:" << endl;
        cout << "1. Price less than RM 1000" << endl;
        cout << "2. Price less than RM 2000" << endl;
        cout << "3. Price less than RM 3000" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> option;

        if (option >= 1 && option <= 4) {
            break; // Valid choice, exit the loop
        }
        else {
            cout << "Invalid option. Please choose a valid option !" << endl;
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer
        }
    }

    if (option == 4) {
        cout << endl << "Exiting..." << endl << endl;
        return; // Exit the function if option 4 is chosen
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
    int batchSize = 1;
    int pageNum = 1;
    bool found = false;

    while (currentProperty != nullptr) {
        int rentValue = extractMonthlyRentValue(currentProperty->monthly_rent);
        if (rentValue < maxMonthlyRent) {
            found = true;
            cout << endl;
            cout << "============== PAGE " << pageNum << " ===============" << endl;
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
            cout << "============== PAGE " << pageNum << " ===============" << endl << endl;

            // Check if the current page is full (batchSize reached)
            if (pageNum % batchSize == 0) {
                // Ask for user input to continue or go back
                int userInput;
                cout << "Enter '1' to view the next page, '2' to view the previous page, or any other number to exit: ";
                cin >> userInput;

                if (userInput == 2 && pageNum <= batchSize) {
                    cout << "You are already at the beginning of the list." << endl;
                }
                else if (userInput == 1) {
                    // Move to the next page
                    currentProperty = currentProperty->next;
                    pageNum = pageNum + 1;
                }
                else if (userInput == 2) {
                    // Move to the previous page
                    currentProperty = currentProperty->prev;
                    pageNum = pageNum - batchSize;
                }
                else {
                    // Exit the loop if any other number is entered
                    break;
                }
            }
        }
        else {
            currentProperty = currentProperty->next;
        }
    }

    // Display a message if no properties are found for the selected monthly rent
    if (!found) {
        cout << "No properties found for the selected monthly rent." << endl;
    }
}

// Function to display the admin menu
void chooseTenantStatus() {
    cout << endl;
    cout << "======== Select Tenant Status ========" << endl;
    cout << "1. Display Active Tenants" << endl;
    cout << "2. Display Inactive Tenants" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        displayTenantsByIsActive(true); // Display active tenants
        break;
    case 2:
        displayTenantsByIsActive(false); // Display inactive tenants
        break;
    case 3:
        cout << endl << "Exiting..." << endl << endl;
        return; // Exit the function and return to the main menu
    default:
        cout << "Invalid choice. Please choose a valid option !" << endl;
        chooseTenantStatus(); // Display the admin menu again
        break;
    }
}

// Function to display tenant details based on isActive
void displayTenantsByIsActive(bool isActive) {
    Tenant* currentTenant = tHead;

    if (currentTenant == nullptr) {
        cout << "No tenant in the list." << endl;
        return;
    }

    int batchSize = 1; // Number of tenants to display per page
    int pageNum = 1;    // Current page number
    bool found = false; // To keep track if any tenants are found for the given isActive status

    while (currentTenant != nullptr) {
        // Check if the current tenant matches the isActive status
        if (currentTenant->isActive == isActive) {
            found = true;
            cout << endl;
            cout << "============== PAGE " << pageNum << " ===============" << endl;
            cout << "Tenant ID: " << currentTenant->tenantId << endl;
            cout << "Tenant Name: " << currentTenant->tenantName << endl;
            cout << "Username: " << currentTenant->tenantUserName << endl;
            cout << "Email: " << currentTenant->tenantEmail << endl;
            cout << "Property ID: " << currentTenant->propertyId << endl;
            cout << "Payment History: " << currentTenant->paymentHistory << endl;
            cout << "Lease Renewed: " << (currentTenant->leaseRenewed ? "Yes" : "No") << endl;
            cout << "Is Active: " << (currentTenant->isActive ? "Yes" : "No") << endl;
            cout << "============== PAGE " << pageNum << " ===============" << endl << endl;

            // Check if the current page is full (batchSize reached)
            if (pageNum % batchSize == 0) {
                // Ask for user input to continue or go back
                int userInput;
                cout << "Enter '1' to view the next page, '2' to view the previous page, or any other number to exit: ";
                cin >> userInput;

                if (userInput == 2 && pageNum <= batchSize) {
                    cout << "You are already at the beginning of the list." << endl;
                }
                else if(userInput == 1) {
                    // Move to the next page
                    currentTenant = currentTenant->next;
                    pageNum = pageNum + 1;
                }
                else if (userInput == 2 && pageNum > batchSize) {
                    // Move to the previous page
                    currentTenant = currentTenant->prev;
                    pageNum = pageNum - batchSize;
                }
                else {
                    // Exit the loop if any other number is entered
                    break;
                }
            }
            else {
                currentTenant = currentTenant->next;
            }
        }
        else {
            currentTenant = currentTenant->next;
        }
    }

    // Display a message if no tenants are found for the selected isActive status
    if (!found) {
        cout << "No tenants found for the selected status." << endl;
    }
}