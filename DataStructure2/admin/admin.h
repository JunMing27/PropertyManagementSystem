#pragma once
#include <iostream>
#include "../manager/manager.h"

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
