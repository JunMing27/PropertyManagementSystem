#include <iostream>
#include <fstream>
#include <string>
#include "property.h"
using namespace std;

Property* head = nullptr;
Property* tail = nullptr;
void initializeProperty()
{
    ifstream ip("../mudah-apartment-kl-selangor.csv");

    if (!ip.is_open()) cout << "ERROR: File Open" << '\n';

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
    displayPropertyBy5();
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

void displayPropertyBy5() {
    Property* temp = head;
    if (head == nullptr) {
        cout << "No property in the list." << endl;
        return;
    }
    while (temp != NULL) {
        cout << "================================" << endl;
        cout << "Property ID: " << temp->ads_id << endl;
        cout << "Property Name: " << temp->prop_name << endl;
        cout << "Completion Year: " << temp->completion_year << endl;
        cout << "Monthly Rent: " << temp->monthly_rent << endl;
        cout << "Location: " << temp->location << endl;
        cout << "Property Type: " << temp->propertyType << endl;
        cout << "Number of Rooms: " << temp->rooms << endl;
        cout << "Parking: " << temp->parking << endl;
        cout << "Number of Bathrooms: " << temp->bathroom << endl;
        cout << "Size: " << temp->size << endl;
        cout << "Furnished: " << temp->furnished << endl;
        cout << "Facilities: " << temp->facilities << endl;
        cout << "Additional Facilities: " << temp->additional_facilities << endl;
        cout << "Region: " << temp->region << endl;
        cout << "================================" << endl;
        temp = temp->next;
    }
}
