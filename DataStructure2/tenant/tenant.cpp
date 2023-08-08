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
    int tenantOption;
    bool tenantLogIn = true;

    while (tenantLogIn)
    {
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

    cin >> tenantOption;
    switch (tenantOption)
    {
    case 1:
        
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
        tenantLogIn = false;
        cout << "Logged out successfully." << endl;
        break;
    default:
        cout << "Invalid Option. Please Try Again." << endl;
        break;
    }
    }
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
    cout << "=======================================" << endl;
    cout << "Tenant ID: " << tenant->tenantId << endl;
    cout << "Tenant Name: " << tenant->tenantName << endl;
    cout << "Tenant UserName: " << tenant->tenantUserName << endl;
    cout << "Tenant Password: " << tenant->tenantPassword << endl;
    cout << "Tenant Email: " << tenant->tenantEmail << endl;
    cout << "Tenant Property ID: " << tenant->propertyId << endl;
    cout << "Tenant Payment History: " << tenant->paymentHistory << endl;
    cout << "Tenant Lease Renewed: " << tenant->leaseRenewed << endl;
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
void deleteInactive(Tenant* tHead, string tenantId)
{
    //if want to delete is the first one
    if (tHead->tenantId == tenantId)
    {
        Tenant* temp = tHead;
        tHead = tHead->next;
        delete temp;
        cout << "Tenant with ID : " << tenantId << " deleted successfully." << endl;
        return;
    }

    Tenant* current = tHead;
    //loop through list, stop when found
    while (current->next != nullptr && current->next->tenantId != tenantId)
    {
        current = current->next;
    }

    //if found
    if (current->next != nullptr)
    {
        Tenant* temp = current->next;
        current->next = current->next->next;
        delete temp;
        cout << "Tenant with ID: " << tenantId << " deleted successfully." << endl;
    }
    else
    {
        cout << "Tenant not found with ID: " << tenantId << endl;
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
            deleteInactive(tHead, tenantID);
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
        cout << "6. Exit" << endl;
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
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please select again." << endl;
        }

        cout << endl;
    } while (choice != 6);

}

