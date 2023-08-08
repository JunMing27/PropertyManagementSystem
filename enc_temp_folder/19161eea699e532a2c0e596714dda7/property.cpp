#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "property.h"
#include "../tenant/tenant.h"
#include "../main.h"
#include "../favouriteProperty/favProp.h"
using namespace std;

Property* pHead = nullptr;
Property* pTail = nullptr;
void initializeProperty()
{
    ifstream ip;
    ip.open("../../mudah-apartment-kl-selangor.csv");
    if (!ip.is_open()) cout << "ERROR: File Not Open" << '\n';

    string ads_id;
    string prop_name;
    string completion_year;
    string monthly_rent;
    string location;
    string propertyType;
    string rooms;
    string parking;
    string bathroom;
    string size;
    string furnished;
    string facilities;
    string additional_facilities;
    string region;
    string ignore; // create to ignore the ,
        getline(ip, ignore, '\n');
    while (ip.good()) {
        // Get data from each line
        getline(ip, ads_id, ',');
        getline(ip, prop_name, ',');
        getline(ip, completion_year, ',');
        getline(ip, monthly_rent, ',');
        getline(ip, location, ',');
        getline(ip, propertyType, ',');
        getline(ip, rooms, ',');
        getline(ip, parking, ',');
        getline(ip, bathroom, ',');
        getline(ip, size, ',');
        getline(ip, furnished, ',');
        getline(ip, facilities, ',');
        getline(ip, additional_facilities, ',');
        getline(ip, region, '\n');

        // replace empty field with "NULL"
        ads_id = ads_id.empty() ? "NULL" : ads_id;
        prop_name = prop_name.empty() ? "NULL" : prop_name;
        completion_year = completion_year.empty() ? "NULL" : completion_year;
        monthly_rent = monthly_rent.empty() ? "NULL" : monthly_rent;
        location = location.empty() ? "NULL" : location;
        propertyType = propertyType.empty() ? "NULL" : propertyType;
        rooms = rooms.empty() ? "NULL" : rooms;
        parking = parking.empty() ? "NULL" : parking;
        bathroom = bathroom.empty() ? "NULL" : bathroom;
        size = size.empty() ? "NULL" : size;
        furnished = furnished.empty() ? "NULL" : furnished;
        facilities = facilities.empty() ? "NULL" : facilities;
        additional_facilities = additional_facilities.empty() ? "NULL" : additional_facilities;
        region = region.empty() ? "NULL" : region;

        //Assign property value into linkedlist
        addNewProperty(ads_id, prop_name, completion_year, monthly_rent, location, propertyType, rooms, parking, bathroom, size, furnished, facilities, additional_facilities, region);
    }
    ip.close();
}

void addNewProperty(string ads_id, string prop_name, string completion_year, string monthly_rent, string location, string propertyType, string rooms, string parking, string bathroom, string size, string furnished, string facilities, string additional_facilities, string region)
{
    Property* newProperty = new Property;
    newProperty->ads_id = ads_id;
    newProperty->prop_name = prop_name;
    newProperty->completion_year = completion_year;
    newProperty->monthly_rent = monthly_rent;
    newProperty->location = location;
    newProperty->propertyType = propertyType;
    newProperty->rooms = rooms;
    newProperty->parking = parking;
    newProperty->bathroom = bathroom;
    newProperty->size = size;
    newProperty->furnished = furnished;
    newProperty->facilities = facilities;
    newProperty->additional_facilities = additional_facilities;
    newProperty->region = region;
    newProperty->next = nullptr;
    newProperty->prev = nullptr;

    if (pHead == NULL) {
        pHead = newProperty;
    }
    else {
        Property* temp = pHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newProperty;
        newProperty->prev = temp; //doubly
    }
}



void inputTenantPropertyMenu() {
    int batchSize = 1;
    int pageNum = 1;
    Property* currentProperty = pHead;

    if (currentProperty == nullptr) {
        cout << "No property in the list." << endl;
        return;
    }

    while (currentProperty != nullptr) {
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

        // Ask for user input to continue or go back
        int choice;
        displayTenantPropertyMenu();
        cin >> choice;

        if (choice == 2 && currentProperty == pHead) {
            cout << "You are already at the beginning of the list." << endl << endl;
        }
        else if (choice == 1) {
            // Move to the next property
            currentProperty = currentProperty->next;
            pageNum = pageNum + 1;
        }
        else if (choice == 2) {
            // Move to the previous property
            currentProperty = currentProperty->prev;
            pageNum = pageNum - 1;
        }
        else if (choice == 3) {
            //Save property into favourite
            bool isPropertyFavorite = verifyFavProp(currentProperty->ads_id); //to check if property is already favourite, if its favourite then user cant add again 
            if (isPropertyFavorite) {
                cout << "This property has been added into the favourite list already. Please Select Another" << endl << endl;
            }
            else {
                addNewFavProp(currentProperty->ads_id, currentProperty->prop_name, getTempUser());
                cout << "Added into favourite property" << endl << endl;
            }
        }
        else if (choice == 4) {
            //Back to TenantMenu
            cout << endl;
            displayTenantMenu();
        }
        else {
            cout << "Invalid Input..... Redirecting to Tenant Menu......" << endl << endl;
            // Back to TenantMenu if any other number is entered
            displayTenantMenu();
        }
    }
}

void displayTenantTenancyPropInfo(string PropId) 
{
    Property* currentProperty = pHead;
    while (currentProperty != NULL) {
        if (currentProperty->ads_id == PropId) {
            cout << "============== TENANCY INFORMATION ===============" << endl;
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
            cout << "============== TENANCY INFORMATION ===============" << endl << endl;
            break;
        }
        currentProperty = currentProperty->next;
    }
}

vector<Property> convertLinkedListToVector(Property* head) {
    vector<Property> properties;
    while (head != nullptr) {
        properties.push_back(*head);
        head = head->next;
    }
    return properties;
}

// Helper function to compare two location strings for descending order sorting
bool compareLocationDesc(const string& location1, const string& location2) {
    return location1 > location2;
}

void merge(vector<Property>& properties, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Property> leftArr(n1);
    vector<Property> rightArr(n2);

    for (int i = 0; i < n1; i++) {
        leftArr[i] = properties[left + i];
    }
    for (int j = 0; j < n2; j++) {
        rightArr[j] = properties[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (compareLocationDesc(leftArr[i].prop_name, rightArr[j].prop_name)) {
            properties[k] = leftArr[i];
            i++;
        }
        else {
            properties[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        properties[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        properties[k] = rightArr[j];
        j++;
        k++;
    }
}

void mergeSort(vector<Property>& properties, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(properties, left, mid);
        mergeSort(properties, mid + 1, right);

        merge(properties, left, mid, right);
    }
}

void linearOrBinary(string searchCriteria, string searchMethod, string searchInput) {
    Property* currentProperty = pHead;
    if (searchMethod != "binary") {
        cout << "Invalid search method. Binary search is supported only." << endl;
        return;
    }

    // Convert linked list to vector
    vector<Property> properties = convertLinkedListToVector(currentProperty);
    // Sort the vector using merge sort
    mergeSort(properties, 0, properties.size() - 1);
    int vectorSize = size(properties);
    vector <int> resultIndex = binarySearch(properties, 0, vectorSize - 1, searchInput, searchCriteria);
    vector <int> resultIndexes = resultIndex;
    if (resultIndex.empty()) {
        cout << "Property not found" << endl;
    }
    else {
        // Display or process the matching properties
        cout << "Matching properties found at indices: ";
        for (int index : resultIndex) {
            cout << index << " ";
        }
        cout << endl;
    }
    displayTenantMenu();
}

vector<int> binarySearch(const vector<Property>& properties, int left, int right, string target, string searchCriteria) {
    vector<int> indexValues;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (searchCriteria == "ID") {
            if (properties[mid].ads_id == target) {
                indexValues.push_back(mid);

                int leftProperty = mid - 1;
                while (leftProperty >= left && (properties[leftProperty].ads_id == target)) {
                    indexValues.push_back(leftProperty);
                    leftProperty--;
                }
                int rightProperty = mid + 1;
                while (rightProperty >= right && (properties[rightProperty].ads_id == target)) {
                    indexValues.push_back(rightProperty);
                    rightProperty++;
                }
                return indexValues;
            }
            else if (properties[mid].ads_id == target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        if (searchCriteria == "propertyName") {
            if (properties[mid].prop_name == target) {
                indexValues.push_back(mid);

                int leftProperty = mid - 1;
                while (leftProperty >= left && (properties[leftProperty].prop_name == target)) {
                    indexValues.push_back(leftProperty);
                    leftProperty--;
                }
                int rightProperty = mid + 1;
                while (rightProperty >= right && (properties[rightProperty].prop_name == target)) {
                    indexValues.push_back(rightProperty);
                    rightProperty++;
                }
                return indexValues;
            }
            else if (properties[mid].prop_name == target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        if (searchCriteria == "location") {
            if (properties[mid].location==target) {
                indexValues.push_back(mid);

                int leftProperty = mid - 1;
                while (leftProperty >= left && (properties[leftProperty].location==target)) {
                    indexValues.push_back(leftProperty);
                    leftProperty--;
                }
                int rightProperty = mid + 1;
                while (rightProperty >= right && (properties[rightProperty].location== target)) {
                    indexValues.push_back(rightProperty);
                    rightProperty++;
                }
                return indexValues;
            }
            else if (properties[mid].location==target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        if (searchCriteria == "region") {
            if (properties[mid].region == target) {
                indexValues.push_back(mid);

                int leftProperty = mid - 1;
                while (leftProperty >= left && (properties[leftProperty].region == target)) {
                    indexValues.push_back(leftProperty);
                    leftProperty--;
                }
                int rightProperty = mid + 1;
                while (rightProperty >= right && (properties[rightProperty].region == target)) {
                    indexValues.push_back(rightProperty);
                    rightProperty++;
                }
                return indexValues;
            }
            else if (properties[mid].region == target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
    }
    return indexValues;
}


void displayAfterSearch(const Property& property) {
    // Modify this function to display the property information as desired
    cout << "Property Information:" << endl;
    cout << "Property Name: " << property.prop_name << endl;
    cout << "Location: " << property.location << endl;
    // Add other property information fields if needed
    cout << endl;
}

void displaySearchResult(Property* result) {
    if (result != NULL) {
        int pageNum = 1;
        while (result != NULL) { // Check if result is not NULL
            cout << "============== PAGE " << pageNum << " ===============" << endl;
            cout << "Property ID: " << result->ads_id << endl;
            cout << "Property Name: " << result->prop_name << endl;
            // Display other information...
            cout << "============== PAGE " << pageNum << " ===============" << endl << endl;

            // Ask for user input to continue or go back
            int choice;
            cout << "1. Next Property\n2. Previous Property\n3. Back to TenantMenu" << endl;
            cin >> choice;

            if (choice == 1) {
                // Move to the next property
                result = result->next;
                pageNum++;
            }
            else if (choice == 2) {
                // Move to the previous property
                result = result->prev;
                pageNum--;
            }
            else if (choice == 3) {
                // Back to TenantMenu
                cout << endl;
                displayTenantMenu();
                return; // Return from the function after going back to TenantMenu
            }
            else {
                cout << "Invalid Input..... Redirecting to Tenant Menu......" << endl << endl;
                // Back to TenantMenu if any other number is entered
                displayTenantMenu();
                return; // Return from the function after displaying the error message
            }
        }
    }
    else {
        cout << "Property not found." << endl;
        displayTenantMenu();
    }
}