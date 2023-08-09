//This file is the main file to run propertyManagement system

#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include "tenant/tenant.h"
#include "admin/admin.h"
#include "manager/manager.h"
#include "property/property.h"
#include "favouriteProperty/favProp.h"
#include "rentRequest/rentRequest.h"
#include "main.h"
using namespace std;

void displayMenuList() {
    cout << "======== Mudah Apartment ========" << endl;
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
        case 1:             // Login as Tenant
            cout << endl;
            loginTenant();
            break;
        case 2:             // Login as Manager
            cout << endl;
            loginManager();
            break;
        case 3:             // Login as Admin
            cout << endl;
            loginAdmin();
            break;
        case 4:             // Register as Tenant
            cout << endl;
            signUpTenant();
            break;
        case 5:             // Exit
            cout << "Exiting..." << endl;
            exit(0);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            displayMenu();
        }
    }

    cout << endl;
}

//store logged in user information 
tempUser* tempHead = nullptr;
tempUser* tempTail = nullptr;
void addNewTempUser(string userId)
{
    tempUser* newTempUser = new tempUser;
    newTempUser->userId = userId;
    newTempUser->prev = nullptr;
    newTempUser->next = nullptr;

    if (tempHead == NULL) {
        tempHead = newTempUser;
    }
    else {
        tempUser* temp = tempHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTempUser;
        newTempUser->prev = temp;
    }
}

string getTempUser()
{
    tempUser* currentTempUser = tempHead;
    return currentTempUser->userId;
}

void cleanTempUser() {
    tempUser* currentTempUser = tempHead;
    while (tempHead != nullptr) {
        tempUser* temp = tempHead;
        tempHead = tempHead->next;
        delete temp;
    }
}

int main()
{
    initializeTenant(); //initialize the current tenant into linkedlist first
    initializeAdmin(); //initialize the current admin into linkedlist first
    initializeManager(); //initialize the current manager into linkedlist first
    initializeProperty(); //initialize the current property from csv file into linkedlist first
    displayMenu();
    return 0;
}
