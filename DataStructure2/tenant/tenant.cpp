// display property 1. Next 5 2. Previous 5 3. Sort 4. Search 5. View fav 6.rent property 7. rent histry
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
#include<utility>
#include<map>
#include "tenant.h"
#include "../property/property.h"
#include "../admin/admin.h"
#include "../main.h"
#include "../property/property.h"
#include "../favouriteProperty/favProp.h"
#include "../rentRequest/rentRequest.h"

using namespace std;
// -------------------------
// LINKED LIST FUNCTION
// -------------------------

Tenant* tHead = nullptr;
Tenant* tTail = nullptr;
tempUser tempUserObj;
string tempUserId;
void addNewTenant(string tenantName, string tenantUserName, string tenantPassword, string tenantEmail, bool isActive) {
    Tenant* temp = tHead;
    Tenant* newTenant = new Tenant;
    newTenant->tenantId = incrementTenantId(temp);
    newTenant->tenantName = tenantName;
    newTenant->tenantUserName = tenantUserName;
    newTenant->tenantPassword = tenantPassword;
    newTenant->tenantEmail = tenantEmail;
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
    addNewTenant("Jun Ming", "junming", "junming123", "jm@gmail.com", false);
    addNewTenant("Hoi Yi", "hoiyi", "hoiyi123", "hy@gmail.com", true);
    addNewTenant("Alan", "alan", "alan123", "alan@gmail.com", true);
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
    addNewTenant(tenantName, tenantUserName, tenantPassword, tenantEmail, true);
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
        cout << endl << "Login successful. Welcome, " << tenantUserName << " !" << endl << endl;
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
            choosePropertySort();
            break;
        case 4:             //Search Property
            inputTenantPropertySearch();
            cout << endl;
            break;
        case 5:             //Rent History
            tenantDisplayRentRequest(getTempUser());
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



void tenantDisplayTenancyMenu() {
    cout << "======== Tenant Operation ========" << endl;
    cout << "1. Pay" << endl;
    cout << "2. Back to Menu" << endl;
    cout << "==================================" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        cout << "You have paid for the rental!" << endl << endl;
        displayTenantMenu();
    }
    else if (choice == 2) {
        displayTenantMenu();
    }
    else {
        cout << "Invalid choice. Please try again." << endl;
        tenantDisplayTenancyMenu();
    }
}

void inputTenantPropertySearch() {
    int inputSearchCriteria;
    string searchCriteria;
    int inputSearchMethod;
    string searchMethod;
    string searchInput;
    cout << "======== Search Criteria ========" << endl;
    cout << "1. Property Name" << endl;
    cout << "2. Location" << endl;
    cout << "3. Region" << endl;
    cout << "4. Back" << endl;
    cout << "==================================" << endl;
    cout << "Enter your choice: ";
    cin >> inputSearchCriteria;
    if (inputSearchCriteria == 1) {
        searchCriteria = "propertyName";
    }
    else if (inputSearchCriteria == 2) {
        searchCriteria = "location";
    }
    else if (inputSearchCriteria == 3) {
        searchCriteria = "region";
    }
    else if (inputSearchCriteria == 4) {
        displayTenantMenu();
    }
    else {
        cout << "Invalid Input..... Redirecting to search property Menu......" << endl << endl;
        // Back to search menu if any other number is entered
        inputTenantPropertySearch();
    }
    cout << "======== Search Method ========" << endl;
    cout << "1. Linear Search" << endl;
    cout << "2. Binary Search" << endl;
    cout << "==================================" << endl;
    cout << "Enter your choice: ";
    cin >> inputSearchMethod;
    if (inputSearchMethod == 1) {
        searchMethod = "linear";
    }
    else if (inputSearchMethod == 2) {
        searchMethod = "binary";
    }
    else {
        cout << "Invalid Input..... Redirecting to search property Menu......" << endl << endl;
        // Back to search menu if any other number is entered
        inputTenantPropertySearch();
    }
    if (searchCriteria != "" && searchMethod != "") {
        cout << "Enter your search Input: ";
        getline(cin >> ws, searchInput);
        //Run search
        linearOrBinary(searchCriteria, searchMethod, searchInput);
    }
}

void displayTenantPropertySearchMenu() {
    cout << "======== Tenant Operation ========" << endl;
    cout << "1. Next" << endl;
    cout << "2. Previous" << endl;
    cout << "3. Back" << endl;
    cout << "==================================" << endl;
}

string returnTenantNameWithID(string id) {
    Tenant* temp = tHead;
    do {
        if (temp->tenantId == id) {
            //if user is in this list, store user Id as temporary data T1
            return temp->tenantName;
            break;
        }
        temp = temp->next;
    } while (temp != nullptr);
    return NULL;
}

string incrementTenantId(Tenant* tHead) {
    Tenant* current = tHead;
    if (tHead == nullptr) {
        string firstId = "T1";
        return firstId;
    }
    while (current->next != nullptr) {
        current = current->next;
    }
    // get the last id and get the integer value behind T
    string lastId = current->tenantId;
    int lastIdInteger;
    istringstream(lastId.substr(1)) >> lastIdInteger;
    lastIdInteger++;
    string mergedNewId = "T" + to_string(lastIdInteger);

    return mergedNewId;
}

//Hoi Yi Part
//display all tenants
void showAllTenants()
{
    Tenant* current = tHead;
    if (current == nullptr)
    {
        cout << "Tenant List is Empty." << endl;
    }
    else
    {
        while (current != nullptr)
        {
            /*cout << "Tenant ID: " << current->tenantId << endl;
            cout << "Tenant Name: " << current->tenantName << endl;
            cout << "Tenant Username: " << current->tenantUserName << endl;
            cout << "Tenant Email: " << current->tenantEmail << endl;
            cout << "Property ID: " << current->propertyId << endl;
            cout << "Payment History: " << current->paymentHistory << endl;
            cout << "Lease Renewed: " << (current->leaseRenewed ? "Yes" : "No") << endl;
            cout << "================================" << endl;*/
            displaySingleTenant(current);
            current = current->next;
        }
    }


}


//search tenant details (linear search)
bool isTenantFound;
Tenant* searchTenantById(Tenant* tHead, string tenantId)
{
    Tenant* temp = tHead;
    isTenantFound = false;
    while (temp != nullptr) {
        if (temp->tenantId == tenantId) {
            isTenantFound = true;
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void displaySingleTenant(Tenant* tenant)
{
    if (tenant != nullptr)
    {
        cout << "=======================================" << endl;
        cout << "Tenant ID: " << tenant->tenantId << endl;
        cout << "Tenant Name: " << tenant->tenantName << endl;
        cout << "Tenant UserName: " << tenant->tenantUserName << endl;
        cout << "Tenant Password: " << tenant->tenantPassword << endl;
        cout << "Tenant Email: " << tenant->tenantEmail << endl;
        cout << "=======================================" << endl;
    }
    else {
        cout << "Tenant pointer is null." << endl;
    }
}

void searchTenantDetails()
{
    string tenantID;
    cout << "Enter tenant ID to search: ";
    cin >> tenantID;

    Tenant* foundTenant = searchTenantById(tHead, tenantID);
    if (isTenantFound) {
        cout << "Tenant found!" << endl;
        displaySingleTenant(foundTenant);
    }
    else {
        cout << "Tenant not found with ID: " << tenantID << endl;
    }
}

//delete inactive tenant
void deleteInactive(Tenant** tHead, string tenantId)
{
    Tenant* current = *tHead;
    //loop through list, stop when found
    while (current != nullptr && current->tenantId != tenantId)
    {
        current = current->next;
    }

    //if found
    if (current != nullptr) {
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        }
        else {
            *tHead = current->next; // update the head if deleting the first tenant
        }

        if (current->next != nullptr) {
            current->next->prev = current->prev;
        }

        delete current;
        cout << "Tenant with id: " << tenantId << " deleted successfully." << endl;
    }
    else {
        cout << "Tenant not found with id: " << tenantId << endl;
    }
     
}

void displayDeleteInactiveTenants()
{
    Tenant* current = tHead;
    bool foundInactive = false;

    while (current != nullptr)
    {
        if (!current->isActive) //inactive
        {
            //display
            cout << endl << "Inactive Tenant Details:" << endl;
            displaySingleTenant(current);
            foundInactive = true;
        }
        current = current->next;
    }

    if (!foundInactive)
    {
        cout << "No inactive tenants found." << endl;
        return;
    }
    else
    {
        //ask user whether want delete
        string tenantID;
        cout << "Enter tenant ID to delete or type 'exit' to cancel: ";
        cin >> tenantID;

        if (tenantID == "exit")
        {
            cout << "Operation cancelled." << endl;
            return;
        }
        else
        {
            deleteInactive(&tHead, tenantID);
            showAllTenants();
        }
    }

}


// Alan Part
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

// Function to compare two properties based on monthly rent, location, and size
bool comparePropertiesMergeSort(Property* prop1, Property* prop2) {
    // First, compare based on monthly rent (descending order)
    int rentValue1 = extractMonthlyRentValue(prop1->monthly_rent);
    int rentValue2 = extractMonthlyRentValue(prop2->monthly_rent);

    if (rentValue1 != rentValue2) {
        return rentValue1 > rentValue2;
    }

    // If the monthly rent is the same, compare based on location (alphabetical order)
    if (prop1->location != prop2->location) {
        return prop1->location < prop2->location;
    }

    // If both monthly rent and location are the same, compare based on size (descending order)
    int sizeValue1 = extractSizeValue(prop1->size);
    int sizeValue2 = extractSizeValue(prop2->size);

    return sizeValue1 > sizeValue2;
}

// Function to perform merge sort on the properties based on multiple criteria
Property* mergeSortProperties(Property* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    Property* middle = findMiddleMergeSort(head);
    Property* nextToMiddle = middle->next;
    middle->next = nullptr;

    Property* left = mergeSortProperties(head);
    Property* right = mergeSortProperties(nextToMiddle);

    return mergeProperties(left, right);
}

// Function to find the middle of the linked list for merge sort
Property* findMiddleMergeSort(Property* head) {
    Property* slow = head;
    Property* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

// Function to merge two sorted linked lists for merge sort
Property* mergeProperties(Property* left, Property* right) {
    Property dummy;
    Property* current = &dummy;

    while (left != nullptr && right != nullptr) {
        if (comparePropertiesMergeSort(left, right)) {
            current->next = left;
            left = left->next;
        }
        else {
            current->next = right;
            right = right->next;
        }
        current = current->next;
    }

    if (left != nullptr) {
        current->next = left;
    }
    else {
        current->next = right;
    }

    return dummy.next;
}

// Function to display properties after sorting based on multiple criteria
void displayPropertiesByMultipleCriteriaMergeSort() {
    cout << endl;
    cout << "======== Display Properties by Multiple Criteria ========" << endl;

    // Perform merge sort on the properties based on multiple criteria
    pHead = mergeSortProperties(pHead);

    // Traverse and display the sorted properties
    Property* currentProperty = pHead;
    int pageNum = 1;
    int batchSize = 1;

    while (currentProperty != nullptr) {
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
        currentProperty = currentProperty->next;
    }
}

// Function to compare two properties based on monthly rent, location, and size
bool comparePropertiesQuickSort(Property* prop1, Property* prop2) {
    // First, compare based on monthly rent (descending order)
    int rentValue1 = extractMonthlyRentValue(prop1->monthly_rent);
    int rentValue2 = extractMonthlyRentValue(prop2->monthly_rent);

    if (rentValue1 != rentValue2) {
        return rentValue1 > rentValue2;
    }

    // If the monthly rent is the same, compare based on location (alphabetical order)
    if (prop1->location != prop2->location) {
        return prop1->location < prop2->location;
    }

    // If both monthly rent and location are the same, compare based on size (descending order)
    int sizeValue1 = extractSizeValue(prop1->size);
    int sizeValue2 = extractSizeValue(prop2->size);

    return sizeValue1 > sizeValue2;
}

// Function to perform quicksort on the properties based on multiple criteria
Property* quickSortProperties(Property* head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }

    Property* pivot = findPivotQuickSort(head);
    Property* smallerHead = nullptr;
    Property* largerHead = nullptr;
    Property* equalHead = nullptr;
    partitionPropertiesQuickSort(head, pivot, smallerHead, equalHead, largerHead);

    smallerHead = quickSortProperties(smallerHead);
    largerHead = quickSortProperties(largerHead);

    return concatenatePropertiesQuickSort(smallerHead, equalHead, largerHead);
}

// Function to find the pivot for quicksort
Property* findPivotQuickSort(Property* head) {
    // For simplicity, we can choose the last property as the pivot
    Property* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

// Function to partition the properties for quicksort
void partitionPropertiesQuickSort(Property* head, Property* pivot, Property*& smallerHead, Property*& equalHead, Property*& largerHead) {
    Property* smaller = nullptr;
    Property* equal = nullptr;
    Property* larger = nullptr;

    Property* current = head;
    while (current != nullptr) {
        Property* next = current->next;
        if (comparePropertiesQuickSort(current, pivot)) {
            current->next = larger;
            larger = current;
        }
        else if (comparePropertiesQuickSort(pivot, current)) {
            current->next = smaller;
            smaller = current;
        }
        else {
            current->next = equal;
            equal = current;
        }
        current = next;
    }

    smallerHead = smaller;
    equalHead = equal;
    largerHead = larger;
}

// Function to concatenate the properties for quicksort
Property* concatenatePropertiesQuickSort(Property* smallerHead, Property* equalHead, Property* largerHead) {
    Property* head = nullptr;
    Property* tail = nullptr;

    if (smallerHead != nullptr) {
        head = smallerHead;
        tail = smallerHead;
        while (tail->next != nullptr) {
            tail = tail->next;
        }
    }

    if (equalHead != nullptr) {
        if (head == nullptr) {
            head = equalHead;
        }
        else {
            tail->next = equalHead;
        }
        tail = equalHead;
        while (tail->next != nullptr) {
            tail = tail->next;
        }
    }

    if (largerHead != nullptr) {
        if (head == nullptr) {
            head = largerHead;
        }
        else {
            tail->next = largerHead;
        }
    }

    return head;
}

// Function to display properties after sorting based on multiple criteria
void displayPropertiesByMultipleCriteriaQuickSort() {
    cout << endl;
    cout << "======== Display Properties by Multiple Criteria ========" << endl;

    // Perform quicksort on the properties based on multiple criteria
    pHead = quickSortProperties(pHead);

    // Traverse and display the sorted properties
    Property* currentProperty = pHead;
    int pageNum = 1;
    int batchSize = 1;

    while (currentProperty != nullptr) {
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
        currentProperty = currentProperty->next;
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
        cout << "4. Sort by Multiple Criteria (Merge Sort)" << endl;
        cout << "5. Sort by Multiple Criteria (Quick Sort)" << endl;
        cout << "6. Go Back to Tenant Menu" << endl;
        cout << "=======================================" << endl;
        cout << "Enter your choice (1-6): ";
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
            displayPropertiesByMultipleCriteriaMergeSort();
            break;
        case 5:
            displayPropertiesByMultipleCriteriaQuickSort();
            break;
        case 6:
            cout << endl;
            displayTenantMenu();
            break;
        default:
            cout << "Invalid choice. Please select again." << endl;
            displayTenantMenu();
        }

        cout << endl;
    } while (choice != 6);

}