#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

struct FavProperty
{
    string propId;
    string propName;
    string favTenantId;
    FavProperty* prev;
    FavProperty* next;
};

void addNewFavProp(string propId, string propName, string favTenantId);
void initializeFavProp(); //for sample only

void summarizeTop10FavProp();