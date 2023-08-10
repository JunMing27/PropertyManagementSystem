#include <iostream>
#include <vector>

using namespace std;

struct Property;

struct Tenant {
    string tenantId;
    string tenantName;
    string tenantUserName;
    string tenantPassword;
    string tenantEmail;
    bool isActive;
    Tenant* prev;
    Tenant* next;
};

extern Tenant* tHead; // Declare tHead as extern
extern Tenant* tTail; // Declare tTail as extern

//by jun ming (tenant)
void addNewTenant(string tenantName, string tenantUserName, string tenantPassword, string tenantEmail, bool isActive);
void initializeTenant();
void signUpTenant();
string incrementTenantId(Tenant* tHead);
void loginTenant();
void displayTenantMenu();
void displayTenantPropertyMenu();
void displayTenantFavPropMenu();
void displayTenantRentPropMenu();
void inputTenantMenu();
bool searchTenant(Tenant* tHead, string username, string password);
void tenantDisplayTenancyMenu();
void inputTenantPropertySearch();
void displayTenantPropertySearchMenu();
string returnTenantNameWithID(string id);
//by hoiyi (manager)
//for display
void showAllTenants();

//for search
void searchTenantDetails();
Tenant* searchTenantById(Tenant* tHead, string tenantId);
void displaySingleTenant(Tenant* tenant);

//for delete due to inactive
void displayDeleteInactiveTenants();
void deleteInactive(Tenant* tHead, string tenantId);

//by alan tenant sort
int partitionMonthlyRent(vector<Property*>& properties, int low, int high);
void quickSortMonthlyRent(vector<Property*>& properties, int low, int high);
void displayPropertyMonthlyRent();
int extractSizeValue(const string& sizeString);
int partitionSize(vector<Property*>& properties, int low, int high);
void quickSortSize(vector<Property*>& properties, int low, int high);
void displayPropertySize();
bool compareLocationDesc(const string& location1, const string& location2);
void mergeLocation(vector<Property*>& properties, int left, int mid, int right);
void mergeSortLocation(vector<Property*>& properties, int left, int right);
void displayPropertyLocation();
bool comparePropertiesMergeSort(Property* prop1, Property* prop2);
Property* mergeSortProperties(Property* head);
Property* findMiddleMergeSort(Property* head);
Property* mergeProperties(Property* left, Property* right);
void displayPropertiesByMultipleCriteriaMergeSort();
bool comparePropertiesQuickSort(Property* prop1, Property* prop2);
Property* quickSortProperties(Property* head);
Property* findPivotQuickSort(Property* head);
void partitionPropertiesQuickSort(Property* head, Property* pivot, Property*& smallerHead, Property*& equalHead, Property*& largerHead);
Property* concatenatePropertiesQuickSort(Property* smallerHead, Property* equalHead, Property* largerHead);
void displayPropertiesByMultipleCriteriaQuickSort();
void choosePropertySort();

