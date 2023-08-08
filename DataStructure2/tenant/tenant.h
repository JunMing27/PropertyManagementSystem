#include <iostream>

using namespace std;

struct Tenant {
    string tenantId;
    string tenantName;
    string tenantUserName;
    string tenantPassword;
    string tenantEmail;
    string propertyId;
    bool isRent;
    string paymentHistory;
    bool leaseRenewed;
    bool isActive;
    Tenant* prev;
    Tenant* next;
};

void addNewTenant(string tenantId, string tenantName, string tenantUserName, string tenantPassword, string tenantEmail, string propertyId, bool isRent, string paymentHistory, bool leaseRenewed, bool isActive);
void initializeTenant();
void signUpTenant();
void loginTenant();
void displayTenantMenu();
void displayTenantPropertyMenu();
void displayTenantFavPropMenu();
void displayTenantRentPropMenu();
void inputTenantMenu();
bool searchTenant(Tenant* tHead, string username, string password);
void tenantRentProperty(string tenantId, string newPropertyId);
void tenantDisplayTenancy(string tenantId);
void tenantDisplayTenancyMenu();
void inputTenantPropertySearch();
void displayTenantPropertySearchMenu();
string returnTenantNameWithID(string id);

