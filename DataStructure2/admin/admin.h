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
void addNewManager(string managerId, string managerUserName, string managerPassword, bool managerStatus);
void modifyManagerStatus();
void displayPropertyByType(const string& propertyType);
void choosePropertyType();
void displayPropertiesByMonthlyRent();
int extractMonthlyRentValue(const string& rentString);
void displayPropertiesByMonthlyRent();
