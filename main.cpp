#include <iostream>
#include "account.h"
using namespace std;

account a;

int main() {
    string ID; int pass;
    cout << "Enter ID: ";
    cin >> ID;
    cout << "Enter Password: ";
    cin >> pass;

    a.account_login(&ID, &pass);
    return 0;
}