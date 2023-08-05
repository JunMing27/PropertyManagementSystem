#include <iostream>
#include <fstream>
#include <string>
#include "property.h"
#include "../tenant/tenant.h"
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
                addNewFavProp(currentProperty->ads_id, currentProperty->prop_name, "T1");
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

