#include <iostream>
#include <string>
#include "../property/property.h"
#include "../tenant/tenant.h"
#include "rentProp.h"
#include <unordered_map>
#include <unordered_set>

using namespace std;

RentProperty* rentHead = nullptr;
RentProperty* rentTail = nullptr;

void addNewRentProp(string propId, string propName)
{
	RentProperty* newRentProperty = new RentProperty;
	newRentProperty->propId = propId;
	newRentProperty->propName = propName;
	newRentProperty->prev = nullptr;
	newRentProperty->next = nullptr;

	if (rentHead == nullptr) {
		rentHead = newRentProperty;
		rentTail = newRentProperty;
	}
	else {
		rentTail->next = newRentProperty;
		newRentProperty->prev = rentTail;
		rentTail = newRentProperty;
	}
}


void initializeRentProp()
{
	addNewRentProp("100239196", "Greenview Apartments");
	addNewRentProp("100267049", "Sri Penara");
	addNewRentProp("100239196", "Greenview Apartments");
	addNewRentProp("100239196", "Greenview Apartments");
}

void displayRentPropTenant()
{
	int batchSize = 1;
	int pageNum = 1;
	RentProperty* currentFavProperty = rentHead;

	if (currentFavProperty == nullptr) {
		cout << "No favorite properties found." << endl << endl;
		displayTenantMenu();
	}

	while (currentFavProperty != nullptr) {
		cout << "============== Favourite Property List ===============" << endl;
		cout << "Property ID: " << currentFavProperty->propId << endl;
		cout << "Property Name: " << currentFavProperty->propName << endl;
		cout << "============== PAGE " << pageNum << " ===============" << endl << endl;

		// Ask for user input to continue or go back
		int choice;
		displayTenantRentPropMenu();
		cin >> choice;

		if (choice == 2 && currentFavProperty == rentHead) {
			cout << "You are already at the beginning of the list." << endl << endl;
		}
		else if (choice == 1) {
			// Move to the next property
			if (currentFavProperty->next != nullptr) {
				currentFavProperty = currentFavProperty->next;
				pageNum = pageNum + 1;
			}
			else {
				cout << "Reached the end of the list." << endl << endl;
			}
		}
		else if (choice == 2) {
			// Move to the previous property
			currentFavProperty = currentFavProperty->prev;
			pageNum = pageNum - 1;
		}
		else if (choice == 3) {
			//Back to TenantMenu
			cout << endl;
			displayTenantMenu();
		}
		else {
			cout << "Invalid Input..... Redirecting to Tenant Menu......" << endl << endl;
			// Back to TenantMenu if any other number is entered
			displayTenantMenu();
		}
	}
}


bool verifyRentProp(string propertyId) //to check if property is already favourite, if its favourite then user cant add again 
{
	RentProperty* currentFavProperty = rentHead;
	if (rentHead == nullptr) {
		cout << "No favorite properties found." << endl;
		return false;
	}
	else {
		do {
			if (currentFavProperty->propId == propertyId) {
				return true;
				break;
			}
			currentFavProperty = currentFavProperty->next;
		} while (currentFavProperty != nullptr);
		return false;
	}
}

