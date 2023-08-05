#pragma once
#include <iostream>

using namespace std;


struct Property {
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
    Property* prev;
    Property* next;
};

extern Property* pHead; // Declare pHead as extern
extern Property* pTail; // Declare pTail as extern

void addNewProperty(string ads_id, string prop_name, string completion_year, string monthly_rent, string location, string propertyType, string rooms, string parking, string bathroom, string size, string furnished, string facilities, string additional_facilities, string region);
void initializeProperty();
void displayPropertyBy1();
void displayProperty();
