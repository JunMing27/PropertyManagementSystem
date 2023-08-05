#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

struct RentProperty
{
    string propId;
    string propName;
    RentProperty* prev;
    RentProperty* next;
};

void addNewRentProp(string propId, string propName);
void initializeRentProp(); //for sample only
void displayRentProp();
bool verifyRentProp(string propertyId);