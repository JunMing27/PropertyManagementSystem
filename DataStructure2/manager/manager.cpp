// Manager 
// - Display registered tenant details (in tenant.cpp)
// - Search tenant details (in tenant.cpp)
// - Delete tenant account based on inactivity status (in tenant.cpp)
// - Summarize top 10 based on fav property list and generate a report (in favProp.cpp)
// - manage tenancy process, should be yes or no or text based input (in rentRequest.cpp)
// - manage payment of confirmed tenancy (in payment.cpp)


#include <iostream>
#include <string>
#include "manager.h"
#include "../tenant/tenant.h"
#include "../main.h"
#include "../favouriteProperty/favProp.h"
#include "../rentRequest/rentRequest.h"
#include "../payment/payment.h"

using namespace std;

Manager* mHead = nullptr;
Manager* mTail = nullptr;

void addNewManager(string managerId, string managerUsername, string managerPassword, bool managerStatus) {
    Manager* newManager = new Manager;
    newManager->managerId = managerId;
    newManager->managerUsername = managerUsername;
    newManager->managerPassword = managerPassword;
    newManager->managerStatus = managerStatus;

    if (mHead == nullptr) {
        mHead = newManager;
        mTail = newManager;
    }
    else {
        mTail->next = newManager;
        newManager->prev = mTail;
        mTail = newManager;
    }
}

void initializeManager() {
    addNewManager("M1", "junming", "junming123", "true");
    addNewManager("M2", "hoiyi", "hoiyi123", "false");
    addNewManager("M3", "alan", "alan123", "true");
}


bool searchManager(string username, string password)
{
    while (mHead != nullptr) {
        if (mHead->managerUsername == username && mHead->managerPassword == password) {
            return true;
        }
        mHead = mHead->next;
    }
    return false;
}


void logout()
{
    cout << "Logged out successfully." << endl;
}

void loginManager()
{
    string managerUsername;
    string managerPassword;
    cout << "======== Manager Login ========" << endl;
    cout << "Enter username: ";
    cin >> managerUsername;
    cout << "Enter password: ";
    cin >> managerPassword;
    bool loggedIn = searchManager(managerUsername, managerPassword);
    if (loggedIn) {
        cout << endl <<"Login successful. Welcome, " << managerUsername << " !";
        displayManagerMenu();
    }
    else {
        cout << "Login failed. Please try again." << endl;
        displayMenu();
    }
    cout << endl;
}

void displayManagerMenu()
{
    int managerOption;
    bool managerLogIn = true;

    while (managerLogIn)
    {
        cout << endl << "======== Manager Menu ========" << endl;
        cout << "1. Display all tenants' details" << endl;
        cout << "2. Search tenant details" << endl;
        cout << "3. Delete inactive tenants" << endl;
        cout << "4. Summarize top 10 properties" << endl;
        cout << "5. Manage tenancy process" << endl;
        cout << "6. Manage payment" << endl;
        cout << "7. Logout" << endl;
        cout << "Enter your choice: ";

        cin >> managerOption;
        switch (managerOption)
        {
        case 1:
            showAllTenants();
            break;
        case 2:
            searchTenantDetails();
            break;
        case 3:
            displayDeleteInactiveTenants();
            break;
        case 4:
            summarizeTop10FavProp();
            break;
        case 5:
            manageTenancyProcess();
            break;
        case 6:
            managePayment();
            break;
        case 7:
            managerLogIn = false;
            logout();
            break;
        default:
            cout << "Invalid Option. Please Try Again." << endl;
            break;
        }
    }
    
}

