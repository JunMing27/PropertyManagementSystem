// display property 1. Next 5 2. Previous 5 3. Sort 4. Search 5. Save fav 6.rent property 7. rent histry
// - Sort and display property information in descending order based on monthly rent, location, and size as per square feet.
// (merge sort, quick sort)
// - Search and display property details based on tenant/customer decision.
// (idk what search ask hoi yi)
// - Save their favorite property

// - Place a rent request the desired property that is stored in the favorite list.

// -Display property renting history

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "tenant.h"
#include "../property/property.h"
#include "../admin/admin.h"
#include "../main.h"

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
        //displayTenantMenu();
    }
    else {
        cout << "Login Failed. Please double check your username and password" << endl << endl;
        displayMenu();
    }
    cout << endl;
}

void displayTenantMenu() {
    cout << "======== Tenant Operation ========" << endl;
    cout << "1. Next" << endl;
    cout << "2. Previous" << endl;
    cout << "3. Sort" << endl;
    cout << "4. Search" << endl;
    cout << "5. Save fav" << endl;
    cout << "6. Rent Property" << endl;
    cout << "7. Rent History" << endl;
    cout << "8. Logout" << endl;
    cout << "===========================" << endl;
    cout << "Enter your choice: ";
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

// Function to partition the properties based on their monthly rent for Quick Sort
int partitionMonthlyRent(vector<Property*>& properties, int low, int high) {
    int pivotValue = extractMonthlyRentValue(properties[high]->monthly_rent);
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (extractMonthlyRentValue(properties[j]->monthly_rent) >= pivotValue) {
            i++;
            swap(properties[i], properties[j]);
        }
    }

    swap(properties[i + 1], properties[high]);
    return i + 1;
}

// Function to implement Quick Sort for sorting properties based on their monthly rent
void quickSortMonthlyRent(vector<Property*>& properties, int low, int high) {
    if (low < high) {
        int pivotIndex = partitionMonthlyRent(properties, low, high);
        quickSortMonthlyRent(properties, low, pivotIndex - 1);
        quickSortMonthlyRent(properties, pivotIndex + 1, high);
    }
}

// Function to sort and display property information in descending order based on monthly rent using Quick Sort
void displayPropertyMonthlyRent() {
    int batchSize = 3;
    int pageNum = 1;
    Property* currentProperty = pHead;

    if (currentProperty == nullptr) {
        cout << "No property in the list." << endl;
        return;
    }

    // Create a vector to store the properties
    vector<Property*> properties;

    // Add properties to the vector
    while (currentProperty != nullptr) {
        properties.push_back(currentProperty);
        currentProperty = currentProperty->next;
    }

    // Sort the properties vector based on monthly rent in descending order using Quick Sort
    quickSortMonthlyRent(properties, 0, properties.size() - 1);

    // Display the properties in batches with navigation options
    int propertyIndex = 0;
    int totalProperties = properties.size();

    while (propertyIndex < totalProperties) {
        cout << "============== PAGE " << pageNum << " ===============" << endl;
        for (int i = propertyIndex; i < min(propertyIndex + batchSize, totalProperties); i++) {
            Property* prop = properties[i];
            cout << "Property ID: " << prop->ads_id << endl;
            cout << "Property Name: " << prop->prop_name << endl;
            cout << "Completion Year: " << prop->completion_year << endl;
            cout << "Monthly Rent: " << prop->monthly_rent << endl;
            cout << "Location: " << prop->location << endl;
            cout << "Property Type: " << prop->propertyType << endl;
            cout << "Number of Rooms: " << prop->rooms << endl;
            cout << "Parking: " << prop->parking << endl;
            cout << "Number of Bathrooms: " << prop->bathroom << endl;
            cout << "Size: " << prop->size << endl;
            cout << "Furnished: " << prop->furnished << endl;
            cout << "Facilities: " << prop->facilities << endl;
            cout << "Additional Facilities: " << prop->additional_facilities << endl;
            cout << "Region: " << prop->region << endl;
            cout << "============== PROPERTY " << (i + 1) << " ===============" << endl << endl;
        }

        // Ask for user input to continue or go back
        int userInput;
        cout << "Enter '1' to view the next properties, '2' to view the previous properties, or any other number to exit: ";
        cin >> userInput;

        if (userInput == 2 && propertyIndex == 0) {
            cout << "You are already at the beginning of the list." << endl;
        }
        else if (userInput == 1) {
            // Move to the next batch of properties
            propertyIndex += batchSize;
            pageNum++;
        }
        else if (userInput == 2) {
            // Move to the previous batch of properties
            propertyIndex = max(0, propertyIndex - batchSize);
            pageNum = max(1, pageNum - 1);
        }
        else {
            // Exit the loop if any other number is entered
            break;
        }
    }
}

// Helper function to extract the numeric part of the "size" field
int extractSizeValue(const string& sizeString) {
    // Remove all non-digit characters from the sizeString
    string numericPart;
    for (char c : sizeString) {
        if (isdigit(c)) {
            numericPart += c;
        }
    }
    // Convert the numeric part to an integer
    int sizeValue;
    istringstream(numericPart) >> sizeValue;
    return sizeValue;
}

int partitionSize(vector<Property*>& properties, int low, int high) {
    int pivot = extractSizeValue(properties[high]->size);
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (extractSizeValue(properties[j]->size) >= pivot) {
            i++;
            swap(properties[i], properties[j]);
        }
    }
    swap(properties[i + 1], properties[high]);
    return i + 1;
}

void quickSortSize(vector<Property*>& properties, int low, int high) {
    if (low < high) {
        int pi = partitionSize(properties, low, high);
        quickSortSize(properties, low, pi - 1);
        quickSortSize(properties, pi + 1, high);
    }
}

void displayPropertySize() {
    int batchSize = 3; // Display 3 properties per page
    int pageNum = 1;
    Property* currentProperty = pHead;

    if (currentProperty == nullptr) {
        cout << "No property in the list." << endl;
        return;
    }

    // Create a vector to store the properties
    vector<Property*> properties;

    // Add properties to the vector
    while (currentProperty != nullptr) {
        properties.push_back(currentProperty);
        currentProperty = currentProperty->next;
    }

    // Sort the properties vector based on size in descending order using Quick Sort
    quickSortSize(properties, 0, properties.size() - 1);

    // Display the properties in batches with navigation options
    int propertyIndex = 0;
    int totalProperties = properties.size();

    while (propertyIndex < totalProperties) {
        cout << "============== PAGE " << pageNum << " ===============" << endl;
        for (int i = propertyIndex; i < min(propertyIndex + batchSize, totalProperties); i++) {
            Property* prop = properties[i];
            cout << "Property ID: " << prop->ads_id << endl;
            cout << "Property Name: " << prop->prop_name << endl;
            cout << "Completion Year: " << prop->completion_year << endl;
            cout << "Monthly Rent: " << prop->monthly_rent << endl;
            cout << "Location: " << prop->location << endl;
            cout << "Property Type: " << prop->propertyType << endl;
            cout << "Number of Rooms: " << prop->rooms << endl;
            cout << "Parking: " << prop->parking << endl;
            cout << "Number of Bathrooms: " << prop->bathroom << endl;
            cout << "Size: " << prop->size << endl;
            cout << "Furnished: " << prop->furnished << endl;
            cout << "Facilities: " << prop->facilities << endl;
            cout << "Additional Facilities: " << prop->additional_facilities << endl;
            cout << "Region: " << prop->region << endl;
            cout << "============== PROPERTY " << (i + 1) << " ===============" << endl << endl;
        }

        // Ask for user input to continue or go back
        int userInput;
        cout << "Enter '1' to view the next properties, '2' to view the previous properties, or any other number to exit: ";
        cin >> userInput;

        if (userInput == 2 && propertyIndex == 0) {
            cout << "You are already at the beginning of the list." << endl;
        }
        else if (userInput == 1) {
            // Move to the next batch of properties
            propertyIndex += batchSize;
            pageNum++;
        }
        else if (userInput == 2) {
            // Move to the previous batch of properties
            propertyIndex = max(0, propertyIndex - batchSize);
            pageNum = max(1, pageNum - 1);
        }
        else {
            // Exit the loop if any other number is entered
            break;
        }
    }
}

// Helper function to compare two location strings for descending order sorting
bool compareLocationDesc(const string& location1, const string& location2) {
    return location1 > location2;
}

// Merge two sorted parts of the array during merge sort
void mergeLocation(vector<Property*>& properties, int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    vector<Property*> leftArray(leftSize);
    vector<Property*> rightArray(rightSize);

    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = properties[left + i];
    }
    for (int i = 0; i < rightSize; i++) {
        rightArray[i] = properties[mid + 1 + i];
    }

    int leftIndex = 0;
    int rightIndex = 0;
    int mergedIndex = left;

    while (leftIndex < leftSize && rightIndex < rightSize) {
        if (compareLocationDesc(leftArray[leftIndex]->location, rightArray[rightIndex]->location)) {
            properties[mergedIndex] = leftArray[leftIndex];
            leftIndex++;
        }
        else {
            properties[mergedIndex] = rightArray[rightIndex];
            rightIndex++;
        }
        mergedIndex++;
    }

    while (leftIndex < leftSize) {
        properties[mergedIndex] = leftArray[leftIndex];
        leftIndex++;
        mergedIndex++;
    }

    while (rightIndex < rightSize) {
        properties[mergedIndex] = rightArray[rightIndex];
        rightIndex++;
        mergedIndex++;
    }
}

// Merge sort algorithm for sorting properties based on location in descending order
void mergeSortLocation(vector<Property*>& properties, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortLocation(properties, left, mid);
        mergeSortLocation(properties, mid + 1, right);
        mergeLocation(properties, left, mid, right);
    }
}

void displayPropertyLocation() {
    vector<Property*> propertyVector;

    // Traverse the linked list and add each property node's pointer to the vector
    Property* currentProperty = pHead;
    while (currentProperty != nullptr) {
        propertyVector.push_back(currentProperty);
        currentProperty = currentProperty->next;
    }

    // Sort the vector based on location in descending order using merge sort
    mergeSortLocation(propertyVector, 0, propertyVector.size() - 1);

    int batchSize = 5;
    int pageNum = 1;
    int startIndex = 0;
    int endIndex = min(startIndex + batchSize - 1, static_cast<int>(propertyVector.size() - 1));

    if (propertyVector.empty()) {
        cout << "No property in the list." << endl;
        return;
    }

    while (startIndex <= endIndex) {
        cout << "============== PAGE " << pageNum << " ===============" << endl;
        for (int i = startIndex; i <= endIndex; i++) {
            Property* currentProperty = propertyVector[i];
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
            cout << "============== PROPERTY " << (i + 1) << " ===============" << endl << endl;
        }

        // Ask for user input to continue or go back
        int userInput;
        cout << "Enter '1' to view the next page, '2' to view the previous page, or any other number to exit: ";
        cin >> userInput;

        if (userInput == 2 && startIndex == 0) {
            cout << "You are already at the beginning of the list." << endl;
        }
        else if (userInput == 1 && endIndex == propertyVector.size() - 1) {
            cout << "You are already at the end of the list." << endl;
        }
        else if (userInput == 1) {
            // Move to the next page
            startIndex = min(endIndex + 1, static_cast<int>(propertyVector.size() - 1));
            endIndex = min(startIndex + batchSize - 1, static_cast<int>(propertyVector.size() - 1));
            pageNum++;
        }
        else if (userInput == 2) {
            // Move to the previous page
            endIndex = max(startIndex - 1, 0);
            startIndex = max(endIndex - batchSize + 1, 0);
            pageNum--;
        }
        else {
            // Exit the loop if any other number is entered
            break;
        }
    }
}

void choosePropertySort() {
    int choice;
    do {
        cout << endl;
        cout << "========== Property Information Menu ==========" << endl;
        cout << "1. Sort Monthly Rent (Desc)" << endl;
        cout << "2. Sort Location (Desc)" << endl;
        cout << "3. Sort Size as per square feet (Desc)" << endl;
        cout << "4. Exit" << endl;
        cout << "=======================================" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        cout << endl;

        switch (choice) {
        case 1:
            displayPropertyMonthlyRent();
            break;
        case 2:
            displayPropertyLocation();
            break;
        case 3:
            displayPropertySize();
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please select again." << endl;
        }

        cout << endl;
    } while (choice != 4);

}