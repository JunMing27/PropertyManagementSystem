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
    string propertyId;
    string paymentHistory;
    bool leaseRenewed;
    bool isActive;
    Tenant* prev;
    Tenant* next;
};

extern Tenant* tHead; // Declare tHead as extern
extern Tenant* tTail; // Declare tTail as extern

void addNewTenant(string tenantId, string tenantName, string tenantUserName, string tenantPassword, string tenantEmail, string propertyId, string paymentHistory, bool leaseRenewed, bool isActive);
void initializeTenant();
void signUpTenant();
void loginTenant();
void displayTenantMenu();
bool searchTenant(Tenant* tHead, string username, string password);
void displayAllTenants();
void displayTenantDetails(Tenant* tenant);
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