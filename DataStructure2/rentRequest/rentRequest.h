#include <string>

using namespace std;

struct RentRequest
{
	string rentRequestId;
	string propId;
	string propName;
	string tenantId;
	string tenantName;
	int durationMonths;
	string rentalAmount;
	bool rentingApproval;
	bool isProcessed;
	RentRequest* prev;
	RentRequest* next;
};

//by hoiyi (manager)
void addRent(string propId, string propName, string tenantId, string tenantName, int durationMonths, string rentalAmount, bool rentingApproval);
void displayAllRequests();
void initializeRentRequest(); //for sample only

//for manage tenancy process
void displayPendingRequest(RentRequest* rHead);
void manageTenancyProcess();
void updateRentRequest(RentRequest* rHead, bool approval);
void displayTenantTenancyPropInfo(string tenantId);
void tenantDisplayRentRequest(string tenantId);
