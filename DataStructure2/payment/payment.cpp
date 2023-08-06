#include <iostream>
#include <string>
#include <sstream>
#include "payment.h"

using namespace std;

Payment* pHead = nullptr;
Payment* pTail = nullptr;

void addPayment(string startDate, string endDate, double totalAmount, double paidAmount)
{
    // Generate the next payment ID with the counter
    int paymentCounter = 1;
    stringstream ss;
    ss << "P" << paymentCounter;
    string paymentId = ss.str();
    paymentCounter++;

    Payment* newPayment = new Payment;
    newPayment->paymentId = paymentId;
    newPayment->startDate = startDate;
    newPayment->endDate = endDate;
    newPayment->totalAmount = totalAmount;
    newPayment->paidAmount = paidAmount;
    newPayment->next = nullptr;
    newPayment->prev = nullptr;

    if (pHead == nullptr) {
        pHead = newPayment;
    }
    else {
        Payment* temp = pHead;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newPayment;
        newPayment->prev = temp;
    }
}

void displayAllPayments()
{
    Payment* current = pHead;

    if (current == nullptr)
    {
        cout << "No payment found." << endl;
        return;
    }

    while (current != nullptr) {
        cout << "============= Payment =============" << endl;
        cout << "Payment ID: " << current->paymentId << endl;
        cout << "Start Date: " << current->startDate << endl;
        cout << "End Date: " << current->endDate << endl;
        cout << "Total Amount: " << current->totalAmount << endl;
        cout << "Paid Amount: " << current->paidAmount << endl;

        current = current->next;
    }
}

void displaySinglePayment()
{
    Payment* current = pHead;
    if (current == nullptr)
    {
        cout << "No payment found." << endl;
        return;
    }

    double payAmount;
    string choice;
    char endChoice;

    while (true) //only false when q
    {
        cout << "============= Payment =============" << endl;
        cout << "Payment ID: " << current->paymentId << endl;
        cout << "Start Date: " << current->startDate << endl;
        cout << "End Date: " << current->endDate << endl;
        cout << "Total Amount: " << current->totalAmount << endl;
        cout << "Paid Amount: " << current->paidAmount << endl;

        cout << "Do you want to update this payment ? "
            << "Type 'yes' to update, 'n' for next, 'p' for previous, or 'q' to quit: ";
        cin >> choice;

        if (choice == "yes" || choice == "Yes")
        {
            while (true) {
                cout << "Enter Paid amount: ";
                cin >> payAmount;

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
            current->paidAmount = payAmount;
            cout << "Paid amount updated successfully." << endl << endl;
        }
        else if (choice == "N" || choice == "n")
        {
            if (current->next != nullptr) {
                current = current->next;
            }
            else {
                cout << "End of payment list reached. Do you want to move to previous payment ? (Y/N)" << endl;
                cin >> endChoice;

                if (endChoice == 'Y' || endChoice == 'y')
                {
                    if (current->prev != nullptr) {
                        current = current->prev;
                    }
                    else {
                        cout << "Start of payment list reached." << endl;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        else if (choice == "P" || choice == "p")
        {
            if (current->prev != nullptr) {
                current = current->prev;
            }
            else {
                cout << "Start of payment list reached." << endl;
            }
        }
        else if (choice == "Q" || choice == "q")
        {
            cout << "Exiting updating payment." << endl;
            break;
        }
        else
        {
            cout << "Invalid input. Please enter 'yes', 'n', 'p', or 'q'." << endl;
        }
    }

}

void managePayment()
{
    char choice;
    while (true)
    {
        cout << "Do you want to see all payments or update payments?" << endl;
        cout << "1. See all payments" << endl;
        cout << "2. Update payments" << endl;
        cout << "Enter your choice : ";
        cin >> choice;

        if (choice == '1')
        {
            displayAllPayments();
            break;
        }
        else if (choice == '2')
        {
            displaySinglePayment();
            break;
        }
        else
        {
            cout << "Invalid input. Please enter '1' or '2'." << endl;
        }
    }
}