// display property 1. Next 5 2. Previous 5 3. Sort 4. Search 5. Save fav 6.rent property 7. rent histry
// - Sort and display property information in descending order based on monthly rent, location, and size as per square feet.
// (merge sort, quick sort)
// - Search and display property details based on tenant/customer decision.
// (idk what search ask hoi yi)
// - Save their favorite property

// - Place a rent request the desired property that is stored in the favorite list.

// -Display property renting history

#include <iostream>
#include "tenant.h"
#include "../main.h"
#include "../property/property.h"

using namespace std;
// -------------------------
// LINKED LIST FUNCTION
// -------------------------

Tenant* tHead = nullptr;
Tenant* tTail = nullptr;


void addNewTenant(string tenantId, string tenantName, string tenantUserName, string tenantPassword, string tenantEmail, string propertyId, string paymentHistory, bool leaseRenewed, bool isActive) {
    Tenant* newTenant = new Tenant;
    newTenant->tenantId = tenantId;
    newTenant->tenantName = tenantName;
    newTenant->tenantUserName = tenantUserName;
    newTenant->tenantPassword = tenantPassword;
    newTenant->tenantEmail = tenantEmail;
    newTenant->propertyId = propertyId;
    newTenant->paymentHistory = paymentHistory;
    newTenant->leaseRenewed = leaseRenewed;
    newTenant->isActive = isActive;
    newTenant->next = nullptr;
    newTenant->prev = nullptr;

    if (tHead == NULL) {
        tHead = newTenant;
    }
    else {
        Tenant* temp = tHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newTenant;
        newTenant->prev = temp; //doubly
    }

}

void initializeTenant() {
    addNewTenant("T1", "Jun Ming", "junming", "junming123", "jm@gmail.com", "100323185", "Paid on time", true, false);
    addNewTenant("T2", "Hoi Yi", "hoiyi", "hoiyi123", "hy@gmail.com", "100203973", "Paid on time", true, true);
    addNewTenant("T3", "Alan", "alan", "alan123", "alan@gmail.com", "100323128", "Paid on time", true, true);
}

bool searchTenant(Tenant* tHead, string username, string password) {
    Tenant* temp = tHead;
    do {
        if (temp->tenantUserName == username && temp->tenantPassword == password) {
            return true;
        }
        temp = temp->next;
    } while (temp != tHead);
    return false;
}
// -------------------------
// DISPLAY FUNCTION
// -------------------------
void signUpTenant() {
    string tenantName; string tenantUserName; string tenantPassword; string tenantEmail;
    cout << "======== Tenant Sign Up ========" << endl;
    cout << "Enter your name: ";
    cin >> tenantName;
    cout << "Enter your username: ";
    cin >> tenantUserName;
    cout << "Enter your password: ";
    cin >> tenantPassword;
    cout << "Enter your email: ";
    cin >> tenantEmail;
    addNewTenant("T4", tenantName, tenantUserName, tenantPassword, tenantEmail, "100191767", "Paid on time", false, false);
    cout << endl << "You have successfully signed up " << endl << endl;
    displayMenu();
}

void loginTenant() {
    string tenantUserName; string tenantPassword;
    cout << "======== Tenant Login ========" << endl;
    cout << "Enter your username: ";
    cin >> tenantUserName;
    cout << "Enter your password: ";
    cin >> tenantPassword;
    bool isTenantFound = searchTenant(tHead, tenantUserName, tenantPassword);
    if (isTenantFound) {
        cout << "Login Successfully" << endl << endl;
        displayTenantMenu();
    }
    else {
        cout << "Login Failed. Please double check your username and password" << endl << endl;
        displayMenu();
    }
    cout << endl;
}

void displayTenantMenu() {
    cout << "======== Tenant Operation ========" << endl;
    cout << "1. View Property" << endl;
    cout << "2. Sort Property" << endl;
    cout << "3. Search Property" << endl;
    cout << "4. Rent History" << endl;
    cout << "5. Sign Out" << endl;
    cout << "===========================" << endl;
    cout << "Enter your choice: ";
    inputTenantMenu();
}

void displayTenantPropertyMenu() {
    inputTenantPropertyMenu();
    cout << "======== Tenant Operation ========" << endl;
    cout << "1. Next" << endl;
    cout << "2. Previous" << endl;
    cout << "3. Save property into favourite" << endl;
    cout << "4. Rent Property" << endl;
    cout << "5. Back to Menu" << endl;
    cout << "===========================" << endl;
    cout << "Enter your choice: ";
}

void inputTenantMenu() {
    int choice;
    cin >> choice;
    if (cin.fail()) //validate the input, ensure it is integer only continue with loop
    {
        // clear error flags
        cin.clear();
        // Wrong input remains on the stream, so you need to get rid of it
        cin.ignore();
        cout << "Invalid choice. Please try again." << endl;
        displayTenantMenu();
    }
    else
    {
        switch (choice) {
        case 1:             //View Property
            cout << endl;
            displayTenantPropertyMenu();
            break;
        case 2:             //Sort Property
            cout << endl;
            break;
        case 3:             //Search Property
            cout << endl;
            break;
        case 4:             //Rent History
            cout << endl;
            break;
        case 5:             //Sign Out
            cout << " You have signed out! Come Back Next Time!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            displayTenantMenu();
        }
    }

    cout << endl;
}

void inputTenantPropertyMenu() {
    displayProperty();
    int choice;
    cin >> choice;
    if (cin.fail()) //validate the input, ensure it is integer only continue with loop
    {
        // clear error flags
        cin.clear();
        // Wrong input remains on the stream, so you need to get rid of it
        cin.ignore();
        cout << "Invalid choice. Please try again." << endl;
        displayTenantPropertyMenu();
    }
    else
    {
        switch (choice) {
        case 1:             //View Property, Next Page
            cout << endl;
            break;
        case 2:             //View Property, Previous Page
            cout << endl;
            break;
        case 3:             //Save property into favourite
            cout << endl;
            break;
        case 4:             //Rent Property
            cout << endl;
            break;
        case 5:             //Back to TenantMenu
            cout << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            displayTenantPropertyMenu();
        }
    }

    cout << endl;
}

// void displayAllTenants() {
//     if (tHead == nullptr) {
//         cout << "No tenants in the list." << endl;
//         return;
//     }

//     cout << "======== All Tenant Information ========" << endl;
//     Tenant *temp = tHead;
//     do {
//         displayTenantDetails(temp);
//         temp = temp->next;
//     } while (temp != NULL);
// }

// void displayTenantDetails(Tenant* tenant) {
//     string tenantId = tenant->tenantId; 
//     cout << "Tenant ID: " << tenant->tenantId << endl;
//     cout << "Tenant Name: " << tenant->tenantName << endl;
//     cout << "Tenant Username: " << tenant->tenantUserName << endl;
//     cout << "Tenant Email: " << tenant->tenantEmail << endl;
//     cout << "Property ID: " << tenant->propertyId << endl;
//     cout << "Payment History: " << tenant->paymentHistory << endl;
//     cout << "Lease Renewed: " << (tenant->leaseRenewed ? "Yes" : "No") << endl;
//     cout << "================================" << endl;
// }