// display property 1. Next 5 2. Previous 5 3. Sort 4. Search 5. View fav 6.rent property 7. rent histry
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
#include "../favouriteProperty/favProp.h"

using namespace std;
// -------------------------
// LINKED LIST FUNCTION
// -------------------------

Tenant* tHead = nullptr;
Tenant* tTail = nullptr;
tempUser tempUserObj;
string tempUserId;
void addNewTenant(string tenantId, string tenantName, string tenantUserName, string tenantPassword, string tenantEmail, string propertyId, bool isRent, string paymentHistory, bool leaseRenewed, bool isActive) {
    Tenant* newTenant = new Tenant;
    newTenant->tenantId = tenantId;
    newTenant->tenantName = tenantName;
    newTenant->tenantUserName = tenantUserName;
    newTenant->tenantPassword = tenantPassword;
    newTenant->tenantEmail = tenantEmail;
    newTenant->propertyId = propertyId;
    newTenant->isRent = isRent;
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
    addNewTenant("T1", "Jun Ming", "junming", "junming123", "jm@gmail.com", "", true, "Paid on time", true, false);
    addNewTenant("T2", "Hoi Yi", "hoiyi", "hoiyi123", "hy@gmail.com", "", true, "Paid on time", true, true);
    addNewTenant("T3", "Alan", "alan", "alan123", "alan@gmail.com", "", false, "Paid on time", true, true);
}

bool searchTenant(Tenant* tHead, string username, string password) {
    Tenant* temp = tHead;
    do {
        if (temp->tenantUserName == username && temp->tenantPassword == password) {
            //if user is in this list, store user Id as temporary data T1
            addNewTempUser(temp->tenantId);
            return true;
            break;
        }
        temp = temp->next;
    } while (temp != nullptr);
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
    addNewTenant("T4", tenantName, tenantUserName, tenantPassword, tenantEmail, "", false, "Paid on time", false, false);
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
    cout << "2. View Favourite Property" << endl;
    cout << "3. Sort Property" << endl;
    cout << "4. Search Property" << endl;
    cout << "5. Rent History" << endl;
    cout << "6. Sign Out" << endl;
    cout << "==================================" << endl;
    cout << "Enter your choice: ";
    inputTenantMenu();
}

void displayTenantPropertyMenu() {
    cout << "======== Tenant Operation ========" << endl;
    cout << "1. Next" << endl;
    cout << "2. Previous" << endl;
    cout << "3. Save property into favourite" << endl;
    cout << "4. Back to Menu" << endl;
    cout << "==================================" << endl;
    cout << "Enter your choice: ";
}

void displayTenantFavPropMenu() {
    cout << "======== Tenant Operation ========" << endl;
    cout << "1. Next" << endl;
    cout << "2. Previous" << endl;
    cout << "3. Rent This Property" << endl;
    cout << "4. Back to Menu" << endl;
    cout << "==================================" << endl;
    cout << "Enter your choice: ";
}

void displayTenantRentPropMenu() {
    cout << "======== Tenant Operation ========" << endl;
    cout << "1. Next" << endl;
    cout << "2. Previous" << endl;
    cout << "3. Back to Menu" << endl;
    cout << "==================================" << endl;
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
            inputTenantPropertyMenu();
            break;
        case 2:             //View Favourite Property
            cout << endl;
            displayFavPropTenant();
            break;
        case 3:             //Sort Property
            cout << endl;
            break;
        case 4:             //Search Property
            inputTenantPropertySearch();
            cout << endl;
            break;
        case 5:             //Rent History
            tenantDisplayTenancy(getTempUser());
            cout << endl;
            break;
        case 6:             //Sign Out
            cout << " You have signed out! Come Back Next Time!" << endl;
            cleanTempUser();
            displayMenu();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            displayTenantMenu();
        }
    }

    cout << endl;
}

void tenantRentProperty(string tenantId, string newPropertyId) {
    Tenant* temp = tHead;
    while (temp != NULL) {
        if (temp->tenantId == tenantId) {
            if (temp->propertyId == "") {
                temp->propertyId = newPropertyId;
                cout << "Successfully sent rent request for this property." << endl << endl;
                break;
            }
            else {
                cout << "Failed to add property. You have existing tenancy already" << endl << endl;
            }
        }
        temp = temp->next;
    }
}

void tenantDisplayTenancy(string tenantId) {
    Tenant* temp = tHead;
    while (temp != NULL) {
        if (temp->tenantId == tenantId && temp->propertyId != "" && temp->isRent == true) {
            displayTenantTenancyPropInfo(temp->propertyId);
            tenantDisplayTenancyMenu();
            break;
        }else{
            cout << "You have not rented any Property. You will need approval from manager after sending rent request." << endl << endl;
            displayTenantMenu();
        }
        temp = temp->next;
    }
}

void tenantDisplayTenancyMenu() {
    cout << "======== Tenant Operation ========" << endl;
    cout << "1. Back to Menu" << endl;
    cout << "==================================" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        displayTenantMenu();
    }
    else {
        cout << "Invalid choice. Please try again." << endl;
    }
}
