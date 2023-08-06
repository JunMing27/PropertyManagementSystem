#include <iostream>
#include <fstream>
#include <string>
#include "property.h"
#include "../tenant/tenant.h"
#include "../main.h"
#include "../favouriteProperty/favProp.h"
using namespace std;

Property* head = nullptr;
Property* tail = nullptr;
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

    while (ip.good()) {
        getline(ip, ignore, '\n');
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
        getline(ip, ignore, '"');
        getline(ip, facilities, '"');
        getline(ip, ignore, ',');
        getline(ip, ignore, '"');
        getline(ip, additional_facilities, '"');
        getline(ip, ignore, ',');
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

    if (head == NULL) {
        head = newProperty;
    }
    else {
        Property* temp = head;
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
    Property* currentProperty = head;

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

        if (choice == 2 && currentProperty == head) {
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
    Property* currentProperty = head;
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
        cin >> searchInput;
        //Run search
        displaySearchResult(searchCriteria, searchMethod, searchInput);
    }
}

void displayTenantPropertySearchMenu() {
    cout << "======== Tenant Operation ========" << endl;
    cout << "1. Next" << endl;
    cout << "2. Previous" << endl;
    cout << "3. Back" << endl;
    cout << "==================================" << endl;
}

Property* binarySearch(Property* head, string searchCriteria, string searchInput) {
    Property* low = head;
    Property* high = NULL;

    // Find the last node in the linked list
    Property* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    high = temp;

    while (low != high && high->next != low) {
        Property* mid = low;
        int count = 0;
        while (mid != high && mid->next != high) {
            mid = mid->next;
            count++;
        }
        if (count % 2 != 0) {
            mid = mid->next;
        }

        // Here, you can specify different criteria to perform binary search
        if (searchCriteria == "propertyName") {
            if (mid->prop_name == searchInput) {
                return mid;
            }
            else if (mid->prop_name < searchInput) {
                low = mid->next;
            }
            else {
                high = mid;
            }
        }
        else if (searchCriteria == "location") {
            if (mid->location == searchInput) {
                return mid;
            }
            else if (mid->location < searchInput) {
                low = mid->next;
            }
            else {
                high = mid;
            }
        }
        else if (searchCriteria == "region") {
            if (mid->region == searchInput) {
                return mid;
            }
            else if (mid->region < searchInput) {
                low = mid->next;
            }
            else {
                high = mid;
            }
        }

    }

    return NULL; // Not found
}

void displaySearchResult(string searchCriteria, string searchMethod, string searchInput) {
    Property* result = NULL;
    if (searchMethod == "linear") {
        // Implement linear search here (not shown in the provided code)
    }
    else if (searchMethod == "binary") {
        result = binarySearch(head, searchCriteria, searchInput);
    }
    else {
        cout << "An error has occurred..... Redirecting to tenant Menu......" << endl << endl;
        displayTenantMenu();
        return; // Return from the function after displaying the error message
    }

    if (result != NULL) {
        int batchSize = 1;
        int pageNum = 1;
        while (result != NULL) { // Check if result is not NULL
            cout << "============== PAGE " << pageNum << " ===============" << endl;
            cout << "Property ID: " << result->ads_id << endl;
            cout << "Property Name: " << result->prop_name << endl;
            // Display other information...
            cout << "============== PAGE " << pageNum << " ===============" << endl << endl;

            // Ask for user input to continue or go back
            int choice;
            displayTenantPropertySearchMenu();
            cin >> choice;

            if (choice == 2 && result == head) {
                cout << "You are already at the beginning of the list." << endl << endl;
            }
            else if (choice == 1) {
                // Move to the next property
                result = result->next;
                pageNum = pageNum + 1;
            }
            else if (choice == 2) {
                // Move to the previous property
                result = result->prev;
                pageNum = pageNum - 1;
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