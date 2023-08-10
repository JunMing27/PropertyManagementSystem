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

extern Property* pHead; // Declare pHead as extern
extern Property* pTail; // Declare pTail as extern

void addNewProperty(string ads_id, string prop_name, string completion_year, string monthly_rent, string location, string propertyType, string rooms, string parking, string bathroom, string size, string furnished, string facilities, string additional_facilities, string region);
void initializeProperty();
void displayPropertyBy1();
void displayProperty();
void inputTenantPropertyMenu();
bool compareLocationDescForMergeSort(const string& location1, const string& location2);
void merge(vector<Property>& properties, int left, int mid, int right);
void mergeSort(vector<Property>& properties, int left, int right);
vector<int> binarySearchProperty(const vector<Property>& properties, int left, int right, string target, string searchCriteria);
vector<int> linearSearchProperty(const vector<Property>& properties, int vectorSize, string target, string searchCriteria);
void linearOrBinary(string searchCriteria, string searchMethod, string searchInput);
void displayLinearBinarySearchResult(vector<Property>& properties, vector <int> resultIndexes);
string returnPropertyPriceWithID(string id);