#pragma once
#include <iostream>

using namespace std;


struct Admin {
    string adminId;
    string adminUserName;
    string adminPassword;
    Admin* prev;
    Admin* next;
};

void addNewAdmin(string adminId, string adminUserName, string adminPassword);
void initializeAdmin();
void loginAdmin();
void displayAdminMenu();
bool searchAdmin(Admin* tHead, string username, string password);
void addNewManager();
void modifyManagerStatus();
void displayPropertyByType(const string& propertyType);
void choosePropertyType();
void displayPropertiesByMonthlyRent();
int extractMonthlyRentValue(const string& rentString);
void chooseTenantStatus();
void displayTenantsByIsActive(bool isActive);