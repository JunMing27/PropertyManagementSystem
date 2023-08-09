#include <iostream>

using namespace std;

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
void tenantDisplayTenancy(string tenantId);
void tenantDisplayTenancyMenu();
void inputTenantPropertySearch();
void displayTenantPropertySearchMenu();
string returnTenantNameWithID(string id);

