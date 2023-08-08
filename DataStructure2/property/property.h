#pragma once
#include <iostream>
#include <vector>

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
bool compareLocationDesc(const string& location1, const string& location2);
bool isSubstring(const string& str, const string& sub);
void merge(vector<Property>& properties, int left, int mid, int right);
void mergeSort(vector<Property>& properties, int left, int right);
vector<int> binarySearch(const vector<Property>& properties, int left, int right, string target, string searchCriteria);
void displayAfterSearch(const Property& property);
void linearOrBinary(string searchCriteria, string searchMethod, string searchInput);
void displaySearchResult(Property* result);
string returnPropertyPriceWithID(string id);