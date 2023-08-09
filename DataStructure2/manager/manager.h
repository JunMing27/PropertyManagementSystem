#pragma once
#include <iostream>

using namespace std;

struct Manager {
    string managerId;
    string managerUsername;
    string managerPassword;
    bool managerStatus;
    Manager* prev;
    Manager* next;
};

extern Manager* mHead; // Declare mHead as extern
extern Manager* mTail; // Declare mTail as extern

//Add all
void initializeManager();
void addInManager(string managerUsername, string managerPassword, bool managerStatus);

//Login
void loginManager();
Manager* searchManager(string username, string password);
void logout();
void displayManagerMenu();
