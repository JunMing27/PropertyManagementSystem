#include <iostream>

using namespace std;


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

void addNewTenant(string tenantId, string tenantName, string tenantUserName, string tenantPassword, string tenantEmail, string propertyId, string paymentHistory, bool leaseRenewed, bool isActive);
void initializeTenant();
void signUpTenant();
void loginTenant();
void displayTenantMenu();
void displayTenantPropertyMenu();
void inputTenantMenu();
void inputTenantPropertyMenu();
bool searchTenant(Tenant* tHead, string username, string password);
void displayAllTenants();
void displayTenantDetails(Tenant* tenant);

