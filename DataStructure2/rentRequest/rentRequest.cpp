#include <iostream>
#include <string>
#include <sstream>
#include "rentRequest.h"

using namespace std;

RentRequest* rHead;
RentRequest* rTail;

void addRent(string propId, string propName, string tenantId, string tenantName, int durationMonths, double rentalAmount, bool rentingApproval)
{
    // Generate the next rent ID with the counter
    int rentCounter = 1;
    stringstream ss;
    ss << "R" << rentCounter;
    string rentId = ss.str();
    rentCounter++;

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

void displayAllRequests()
{
    RentRequest* current = rHead;
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

void displayPendingRequest(RentRequest* rHead)
{
    RentRequest* current = rHead;
    string approvalChoice;
    
    while (true) //only false when q
    {
        if (current->isProcessed)
        {
            if (current->next != nullptr) {
                current = current->next;
                continue;
            }
            else {
                cout << "End of rent request list reached." << endl;
                break;
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
                cout << "End of rent request list reached." << endl;
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
    displayAllRequests();
    char choice;
    cout << "Do you want to review the rent requests? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y')
    {
        displayPendingRequest(rHead);
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
        cout << "Rent request ID " << current->rentRequestId << " has been approved." << endl;
    }
    else {
        cout << "Rent request ID " << current->rentRequestId << " has been rejected." << endl;
    }

}

