#include <iostream>
#include <vector>
using namespace std;

struct tempUser
{
    string userId;
    tempUser* prev;
    tempUser* next;
};

void addNewTempUser(string userId);
void displayMenuList();
void displayMenu();



//to store temporary userid that has logged in
void addNewTempUser(string userId);
string getTempUser();
void cleanTempUser();
