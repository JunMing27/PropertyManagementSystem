#include <string>

using namespace std;

struct Payment
{
	string paymentId;
	string startDate;
	string endDate;
	double totalAmount;
	double paidAmount;
	Payment* prev;
	Payment* next;
};

void addPayment(string startDate, string endDate, double totalAmount, double paidAmount);
void displayAllPayments();
void displaySinglePayment();
void managePayment();