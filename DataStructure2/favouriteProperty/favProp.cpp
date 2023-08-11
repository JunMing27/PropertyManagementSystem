#include <iostream>
#include <string>
#include "../property/property.h"
#include "../tenant/tenant.h"
#include "../rentRequest/rentRequest.h"
#include "../main.h"
#include "favProp.h"
#include <unordered_map>
#include <unordered_set>

using namespace std;

FavProperty* favHead = nullptr;
FavProperty* favTail = nullptr;

void addNewFavProp(string propId, string propName, string favTenantId)
{
	FavProperty* newFavProperty = new FavProperty;
	newFavProperty->propId = propId;
	newFavProperty->propName = propName;
	newFavProperty->favTenantId = favTenantId;
	newFavProperty->prev = nullptr;
	newFavProperty->next = nullptr;

	if (favHead == nullptr) {
		favHead = newFavProperty;
		favTail = newFavProperty;
	}
	else {
		favTail->next = newFavProperty;
		newFavProperty->prev = favTail;
		favTail = newFavProperty;
	}
}


void initializeFavProp()
{
	addNewFavProp("100239196", "Greenview Apartments", "T1");
	addNewFavProp("100267049", "Sri Penara", "T2");
	addNewFavProp("100239196", "Greenview Apartments", "T2");
	addNewFavProp("100239196", "Greenview Apartments", "T3");
}

void showAllFavProp()
{
	FavProperty* current = favHead;
	if (current == nullptr)
	{
		cout << "Favourite Property List is Empty." << endl;
	}
	else
	{
		while (current != nullptr)
		{
			cout << "Favourite Property ID: " << current->propId << endl;
			cout << "Favourite Property Name: " << current->propName << endl;
			cout << "Favourite By Tenant ID: " << current->favTenantId << endl;
			cout << "================================" << endl;
			current = current->next;
		}
	}


}


//summarize
void summarizeTop10FavProp()
{
	if (favHead == nullptr) {
		cout << "No favorite properties found." << endl;
		return;
	}
	else
	{
		//show all first then ask want to summarize or not
		showAllFavProp();
		char choice;
		cout << "Do you want to summarize the top 10 favourite properties? (y/n): ";
		cin >> choice;
		if (choice == 'y' || choice == 'Y')
		{
			unordered_map<string, pair <int, string>> propertyCountMap;
			unordered_set<string> displayedProperties;

			FavProperty* current = favHead;

			//count total number of favourite property
			while (current != nullptr)
			{
				propertyCountMap[current->propId].first++; //to count
				propertyCountMap[current->propId].second = current->propName; //to store property name
				current = current->next;
			}

			//display top 10
			cout << "======== Top 10 Favourite Properties Report ======== " << endl;
			int count = 0;
			current = favHead;
			while (current != nullptr && count < 10)
			{
				if (displayedProperties.find(current->propId) == displayedProperties.end())
				{
					cout << "Property ID: " << current->propId
						<< ", Property Name: " << propertyCountMap[current->propId].second
						<< ", Favorites Count: " << propertyCountMap[current->propId].first << endl;
					displayedProperties.insert(current->propId);
					count++;
				}
				current = current->next;
			}
		}
		else //if choice is n or N
		{
			cout << "Top 10 favourite property summarization skipped." << endl;
		}

		/*char reportChoice;
		cout << "Do you want to generate a report? (y/n): ";
		cin >> reportChoice;
		if (reportChoice == 'y' || reportChoice == 'Y')
		{
			generateReport();
		}
		else
		{
			cout << "Report generation skipped." << endl;
		}*/


	}

}

void displayFavPropTenant()
{
	int batchSize = 1;
	int pageNum = 1;
	bool nextOrPrev = true;
	FavProperty* currentFavProperty = favHead;

	if (currentFavProperty == nullptr) {
		cout << "No favorite properties found." << endl << endl;
		displayTenantMenu();
	}

	while (currentFavProperty != nullptr) {
		if (currentFavProperty->favTenantId != getTempUser() && nextOrPrev == true) {
			currentFavProperty = currentFavProperty->next;
		}
		else if (currentFavProperty->favTenantId != getTempUser() && nextOrPrev == false) {
			currentFavProperty = currentFavProperty->prev;
		}
		else {
			cout << "============== Favourite Property List ===============" << endl;
			cout << "Property ID: " << currentFavProperty->propId << endl;
			cout << "Property Name: " << currentFavProperty->propName << endl;
			cout << "Tenant ID: " << currentFavProperty->favTenantId << endl;
			cout << "============== PAGE " << pageNum << " ===============" << endl << endl;

			// Ask for user input to continue or go back
			int choice;
			displayTenantFavPropMenu();
			cin >> choice;

			if (choice == 2 && currentFavProperty == favHead) {
				cout << "You are already at the beginning of the list." << endl << endl;
			}
			else if (choice == 1) {
				// Move to the next property
				if (currentFavProperty->next != nullptr) {
					nextOrPrev = true;
					currentFavProperty = currentFavProperty->next;
					pageNum = pageNum + 1;
				}
				else {
					cout << "Reached the end of the list." << endl << endl;
				}
			}
			else if (choice == 2) {
				// Move to the previous property
				nextOrPrev = false;
				currentFavProperty = currentFavProperty->prev;
				pageNum = pageNum - 1;
			}
			else if (choice == 3) {
				//Rent This Current Property
				int rentMonth;
				cout << "How many months do you want to rent this property? (e.g.: 3)" << endl;
				cin >> rentMonth;
				string tenantName = returnTenantNameWithID(currentFavProperty->favTenantId);
				string monthlyPrice = returnPropertyPriceWithID(currentFavProperty->propId);
				addRent(currentFavProperty->propId, currentFavProperty->propName, currentFavProperty->favTenantId, tenantName, rentMonth, monthlyPrice, "Pending");

			}
			else if (choice == 4) {
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
	cout << "Thats the end of menu" << endl << endl;
	displayTenantMenu();
}


bool verifyFavProp(string propertyId) //to check if property is already favourite, if its favourite then user cant add again 
{
	FavProperty* currentFavProperty = favHead;
	if (favHead == nullptr) {
		return false;
	}
	else {
		do {
			if (currentFavProperty->propId == propertyId && currentFavProperty->favTenantId == getTempUser()) {
				return true;
				break;
			}
			currentFavProperty = currentFavProperty->next;
		} while (currentFavProperty != nullptr);
		return false;
	}
}