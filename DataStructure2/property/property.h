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
void inputTenantPropertyMenu();
void displayTenantTenancyPropInfo(string PropId);
bool compareAttributeDesc(const string& attribute1, const string& attribute2);
void mergeSortForBinarySearch(Property* pHead, string searchCriteria);
void mergeForBinarySearch(Property*& pHead, Property* left, Property* mid, Property* right, string searchCriteria);
Property* getMidNode(Property* head, int size);
Property* getTailNode(Property* head);
Property* binarySearchOnSortedList(Property* head, string searchCriteria, string searchInput);
Property* getMidNode(Property* low, Property* high);
void linearOrBinary(string searchCriteria, string searchMethod, string searchInput);
void displaySearchResult(Property* result);
