//This file is the main file to run propertyManagement system

#include <iostream>
#include "tenant/tenant.h"
#include "admin/admin.h"
#include "manager/manager.h"
#include "main.h"
using namespace std;

void displayMenuList() {
    cout << "======== Main Menu ========" << endl;
    cout << "1. Login as Tenant" << endl;
    cout << "2. Login as Manager" << endl;
    cout << "3. Login as Admin" << endl;
    cout << "4. Register as Tenant" << endl;
    cout << "5. Exit" << endl;
    cout << "===========================" << endl;
    cout << "Enter your choice: ";
}

void displayMenu() {
    int choice;

    string managerId;
    string managerUserName;
    string managerPassword;
    bool managerStatus = false;

    initializeTenant(); //initialize the current tenant into linkedlist first
    initializeAdmin(); //initialize the current admin into linkedlist first
    displayMenuList();
    cin >> choice;
    if (cin.fail()) //validate the input, ensure it is integer only continue with loop
    {
        // clear error flags
        cin.clear();
        // Wrong input remains on the stream, so you need to get rid of it
        cin.ignore();
        cout << "Invalid choice. Please try again." << endl;
        displayMenu();
    }
    else
    {
        switch (choice) {
        case 1:
            cout << endl;
            loginTenant();
            break;
        case 2:
            cout << endl;
            break;
        case 3:
            cout << endl;
            loginAdmin();
            cin >> choice;
            switch (choice) {
            case 1:
                addNewManager(managerId, managerUserName, managerPassword, managerStatus);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                displayMenu();
            }
            break;
        case 4:
            cout << endl;
            signUpTenant();
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            displayMenu();
        }
    }

    cout << endl;
}

int main()
{
    displayMenu();
    return 0;
}
