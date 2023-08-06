//This file is the main file to run propertyManagement system

#include <iostream>
#include <chrono>
#include "tenant/tenant.h"
#include "admin/admin.h"
#include "manager/manager.h"
#include "property/property.h"
#include "main.h"
using namespace std;

void displayMenuList() {
    cout << "======== Main Menu ========" << endl;
    cout << "1. Login as Tenant" << endl;
    cout << "2. Login as Manager" << endl;
    cout << "3. Login as Admin" << endl;
    cout << "4. Register as Tenant" << endl;
    cout << "5. Exit" << endl;
    cout << "===========================" << endl;
    cout << "Enter your choice: ";
}

void displayMenu() {
    int choice;

    initializeTenant(); //initialize the current tenant into linkedlist first
    initializeAdmin(); //initialize the current admin into linkedlist first
    initializeProperty();
    
    do {
        displayMenuList();
        cin >> choice;
        if (cin.fail()) //validate the input, ensure it is integer only continue with loop
        {
            // clear error flags
            cin.clear();
            // Wrong input remains on the stream, so you need to get rid of it
            cin.ignore();
            cout << "Invalid choice. Please try again." << endl;
            displayMenu();
        }
        else
        {
            switch (choice) {
            case 1:
                cout << endl;
                loginTenant();
                do {
                    displayTenantMenu();
                    cin >> choice;
                    switch (choice) {
                    case 1:
                        
                        break;
                    case 2:
                        
                        break;
                    case 3:
                        choosePropertySort();
                        break;
                    case 4:
                        
                        break;
                    case 5:
                        
                        break;
                    case 6:
                        
                        break;
                    case 7:
                        
                        break;
                    case 8:
                        cout << endl;
                        displayMenu();
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl << endl;
                    }
                } while (choice != 8);
                break;
            case 2:
                cout << endl;
                break;
            case 3:
                    cout << endl;
                    loginAdmin();
                    do {
                    displayAdminMenu();
                    cin >> choice;
                    switch (choice) {
                    case 1:
                        addNewManager();
                        break;
                    case 2:
                        modifyManagerStatus();
                        break;
                    case 3:
                        chooseTenantStatus();
                        break;
                    case 4:
                        displayPropertiesByMonthlyRent();
                        break;
                    case 5:
                        cout << endl;
                        choosePropertyType();
                        break;
                    case 6:
                        cout << endl;
                        displayMenu();
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl << endl;
                    }
                } while (choice != 6);
                break;
            case 4:
                cout << endl;
                signUpTenant();
                break;
            case 5:
                cout << "Exiting..." << endl;
                exit(0);
                break;
            default:
                cout << "Invalid choice. Please try again." << endl << endl;
                displayMenu();
            }
        }

        cout << endl;
    } while (choice != 5);
    
}


int main()
{
    displayMenu();
    return 0;
}

// Comparison execution time - by Alan
// Monthly Rent
// 
// Measure the execution time of displayPropertyMonthlyRent with quick sort
//auto startQuickSort = chrono::high_resolution_clock::now();
//displayPropertyMonthlyRent();
//auto endQuickSort = chrono::high_resolution_clock::now();
//chrono::duration<double> timeQuickSort = endQuickSort - startQuickSort;
//cout << "Execution time with quick sort: " << timeQuickSort.count() << " seconds." << endl;
//
// Measure the execution time of displayPropertyMonthlyRent with merge sort
//auto startMergeSort = chrono::high_resolution_clock::now();
//displayPropertyMonthlyRent();
//auto endMergeSort = chrono::high_resolution_clock::now();
//chrono::duration<double> timeMergeSort = endMergeSort - startMergeSort;
//cout << "Execution time with merge sort: " << timeMergeSort.count() << " seconds." << endl;
// 
// Size
// 
// Measure the execution time of displayPropertySize with quick sort
//auto startQuickSort = chrono::high_resolution_clock::now();
//displayPropertySize();
//auto endQuickSort = chrono::high_resolution_clock::now();
//chrono::duration<double> timeQuickSort = endQuickSort - startQuickSort;
//cout << "Execution time with quick sort: " << timeQuickSort.count() << " seconds." << endl;
//
// Measure the execution time of displayPropertySize with merge sort
//auto startMergeSort = chrono::high_resolution_clock::now();
//displayPropertySize();
//auto endMergeSort = chrono::high_resolution_clock::now();
//chrono::duration<double> timeMergeSort = endMergeSort - startMergeSort;
//cout << "Execution time with merge sort: " << timeMergeSort.count() << " seconds." << endl;
// 
// Location
// 
// Measure the execution time of displayPropertyLocation with quick sort
//auto startQuickSort = chrono::high_resolution_clock::now();
//displayPropertyLocation();
//auto endQuickSort = chrono::high_resolution_clock::now();
//chrono::duration<double> timeQuickSort = endQuickSort - startQuickSort;
//cout << "Execution time with quick sort: " << timeQuickSort.count() << " seconds." << endl;
//
// Measure the execution time of displayPropertyLocation with merge sort
//auto startMergeSort = chrono::high_resolution_clock::now();
//displayPropertyLocation();
//auto endMergeSort = chrono::high_resolution_clock::now();
//chrono::duration<double> timeMergeSort = endMergeSort - startMergeSort;
//cout << "Execution time with merge sort: " << timeMergeSort.count() << " seconds." << endl;


