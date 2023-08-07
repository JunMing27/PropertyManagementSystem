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

void addNewProperty(string ads_id, string prop_name, string completion_year, string monthly_rent, string location, string propertyType, string rooms, string parking, string bathroom, string size, string furnished, string facilities, string additional_facilities, string region);
void initializeProperty();
void inputTenantPropertyMenu();
void displayPropertyDetails(Property* property);
void displayTenantTenancyPropInfo(string PropId);
void inputTenantPropertySearch();
void displayTenantPropertySearchMenu();
Property* merge(Property* left, Property* right, string searchCriteria, Property*& prev);
Property* splitListIterative(Property* head, int blockSize);
void mergeSortIterative(Property** headRef, string searchCriteria);
Property* getLastNode(Property* head);
Property* binarySearch(Property* head,string searchCriteria,string searchValue);
Property* getLastNode(Property* head);
void displaySearchResult(string searchCriteria, string searchMethod, string searchInput);