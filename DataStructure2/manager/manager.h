#include <string>

using namespace std;

struct Manager {
    string managerId;
    string managerUsername;
    string managerPassword;
    bool managerStatus;
    Manager* prev;
    Manager* next;
};

//Add all
void initializeManager();
void addNewManager(string managerId, string managerUsername, string managerPassword, bool managerStatus);

//Login
void loginManager();
bool searchManager(string username, string password);
void logout();
void displayManagerMenu();

//Functionality
void managePayment();



