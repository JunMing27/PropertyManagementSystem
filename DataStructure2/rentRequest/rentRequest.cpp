#include <iostream>
#include <string>
#include <sstream>
#include "rentRequest.h"
#include "../payment/payment.h"
#include "../tenant/tenant.h"

using namespace std;

RentRequest* rHead;
RentRequest* rTail;

void addRent(string propId, string propName, string tenantId, string tenantName, int durationMonths, string rentalAmount, bool rentingApproval)
{
    // Generate the next rent ID with the counter
    int rentCounter = 0;
    RentRequest* current = rHead;
    while (current != nullptr) {
        rentCounter++;
        current = current->next;
    }

    stringstream ss;
    ss << "R" << (rentCounter + 1);
    string rentId = ss.str();

    RentRequest* newRequest = new RentRequest;
    newRequest->rentRequestId = rentId;
    newRequest->propId = propId;
    newRequest->propName = propName;
    newRequest->tenantId = tenantId;
    newRequest->tenantName = tenantName;
    newRequest->durationMonths = durationMonths;
    newRequest->rentalAmount = rentalAmount;
    newRequest->rentingApproval = rentingApproval;
    newRequest->isProcessed = false;
    newRequest->next = nullptr;
    newRequest->prev = nullptr;

    if (rHead == nullptr) {
        rHead = newRequest;
    }
    else {
        RentRequest* temp = rHead;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newRequest;
        newRequest->prev = temp;
    }
}

void initializeRentRequest()
{
    addRent("P1", "Under Bridge", "T1", "JunMing", 2, "200 per month", "Pending");
}

void displayAllRequests()
{
    RentRequest* current = rHead;
    if (current == nullptr)
    {
        cout << "No rent requests found." << endl;
        return;
    }

    while (current != nullptr) {
        cout << "=======================================" << endl;
        cout << "Rent Request ID: " << current->rentRequestId << endl;
        cout << "Property Id: " << current->propId << endl;
        cout << "Property Name: " << current->propName << endl;
        cout << "Tenant Id: " << current->tenantId << endl;
        cout << "Tenant Name: " << current->tenantName << endl;
        cout << "Duration (months): " << current->durationMonths << endl;
        cout << "Rental Amount: " << current->rentalAmount << endl;
        if (current->isProcessed)
        {
            cout << "Renting Approval: " << (current->rentingApproval ? "Approved" : "Rejected") << endl;
        }
        else
        {
            cout << "Renting Approval: " << (current->rentingApproval ? "Approved" : "Pending") << endl;
        }
        cout << "Processed: " << (current->isProcessed ? "Yes" : "No") << endl;

        current = current->next;
    }
}

void displayTenantTenancyPropInfo(string tenantId)
{
    RentRequest* current = rHead;
    while (current != NULL) {
        if (current->tenantId == tenantId) {
            cout << "============== TENANCY INFORMATION ===============" << endl;
            cout << "Rent Request ID: " << current->rentRequestId << endl;
            cout << "Property Id: " << current->propId << endl;
            cout << "Property Name: " << current->propName << endl;
            cout << "Tenant Id: " << current->tenantId << endl;
            cout << "Tenant Name: " << current->tenantName << endl;
            cout << "Duration (months): " << current->durationMonths << endl;
            cout << "Rental Amount: " << current->rentalAmount << endl;
            cout << "============== TENANCY INFORMATION ===============" << endl << endl;
            break;
        }
        current = current->next;
    }
}

void displayPendingRequest(RentRequest* rHead)
{
    RentRequest* current = rHead;
    string approvalChoice;
    char endChoice;

    if (current == nullptr)
    {
        cout << "No rent requests found." << endl;
        return;
    }

    while (true) //only false when q
    {
        if (current->isProcessed)
        {
            if (current->next != nullptr) {
                current = current->next;
            }
            else {
                cout << "End of rent request list reached. Do you want to move to previous rent request ? (Y/N)" << endl;
                cin >> endChoice;

                if (endChoice == 'Y' || endChoice == 'y')
                {
                    if (current->prev != nullptr) {
                        current = current->prev;
                    }
                    else {
                        cout << "Start of rent request list reached." << endl;
                    }
                }
                else
                {
                    break;
                }
            }
        }

        cout << "=======================================" << endl;
        cout << "Rent Request ID: " << current->rentRequestId << endl;
        cout << "Property Id: " << current->propId << endl;
        cout << "Property Name: " << current->propName << endl;
        cout << "Tenant Id: " << current->tenantId << endl;
        cout << "Tenant Name: " << current->tenantName << endl;
        cout << "Duration (months): " << current->durationMonths << endl;
        cout << "Rental Amount: " << current->rentalAmount << endl;
        cout << "Renting Approval: " << (current->rentingApproval ? "Approved" : "Pending") << endl;

        cout << "Do you approve this request ? "
            << "Type 'yes' to approve, 'no' to reject, 'n' for next, 'p' for previous, or 'q' to quit: ";
        cin >> approvalChoice;

        if (approvalChoice == "yes" || approvalChoice == "Yes")
        {
            updateRentRequest(current, true);
            current->isProcessed = true;
        }
        else if (approvalChoice == "no" || approvalChoice == "No")
        {
            updateRentRequest(current, false);
            current->isProcessed = true;
        }
        else if (approvalChoice == "N" || approvalChoice == "n")
        {
            if (current->next != nullptr) {
                current = current->next;
            }
            else {
                cout << "End of rent request list reached. Do you want to move to previous rent request ? (Y/N)" << endl;
                cin >> endChoice;

                if (endChoice == 'Y' || endChoice == 'y')
                {
                    if (current->prev != nullptr) {
                        current = current->prev;
                    }
                    else {
                        cout << "Start of rent request list reached." << endl;
                    }
                }
                else
                {
                    break;
                }

            }
        }
        else if (approvalChoice == "P" || approvalChoice == "p")
        {
            if (current->prev != nullptr) {
                current = current->prev;
            }
            else {
                cout << "Start of rent request list reached." << endl;
            }
        }
        else if (approvalChoice == "Q" || approvalChoice == "q")
        {
            cout << "Exiting review." << endl;
            break;
        }
        else
        {
            cout << "Invalid input. Please enter 'yes', 'no', 'n', 'p', or 'q'." << endl;
        }
    }
}

void manageTenancyProcess()
{
    char choice;
    while (true)
    {
        cout << "Do you want to see all requests or only review the rent requests?" << endl;
        cout << "1. See all requests" << endl;
        cout << "2. Review pending rent requests" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        if (choice == '1')
        {
            displayAllRequests();
            break;
        }
        else if (choice == '2')
        {
            displayPendingRequest(rHead);
            break;
        }
        else
        {
            cout << "Invalid input. Please enter '1' or '2'." << endl;
        }
    }
}

void updateRentRequest(RentRequest* rHead, bool approval)
{
    RentRequest* current = rHead;
    current->rentingApproval = approval;

    if (current == nullptr)
    {
        cout << "Invalid rent request." << endl;
        return;
    }

    if (approval) {
        // Update payment details
        string startDate, endDate;
        double totalAmount;
        cout << "Enter start date (DD-MM-YYYY): ";
        cin >> startDate;
        cout << "Enter end date (DD-MM-YYYY): ";
        cin >> endDate;
        while (true) {
            cout << "Enter total amount: ";
            cin >> totalAmount;

            if (cin.fail()) {
                // Clear error flags
                cin.clear();
                // Discard invalid input
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid number for total amount." << endl;
            }
            else {
                break; // Input is a valid double, exit the loop
            }
        }
        cout << "Enter total amount: ";
        cin >> totalAmount;
        addPayment(startDate, endDate, totalAmount, 0);
        cout << "Rent request ID " << current->rentRequestId << " has been approved." << endl;
    }
    else {
        cout << "Rent request ID " << current->rentRequestId << " has been rejected." << endl;
    }

}

void tenantDisplayRentRequest(string tenantId) {
    RentRequest* current = rHead;
    while (current != NULL) {
        if (current->tenantId == tenantId) {
            displayTenantTenancyPropInfo(current->tenantId);
            tenantDisplayTenancyMenu();
            break;
        }
        else {
            cout << "You have not rented any Property yet" << endl << endl;
            displayTenantMenu();
        }
        current = current->next;
    }
}