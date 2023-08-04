#include <iostream>
#include <fstream>
#include <string>
#include "admin.h"
#include "../manager/manager.h"
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
        displayAdminMenu();
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