#include <iostream>
#include "account.h"
using namespace std;

account a;

int main() {
    string ID; int pass;
    cout << "\nEnter ID and password seperated by a ' '.\n";
    cout << "Enter, here!: ";
    cin >> ID >> pass;

    a.account_login(&ID, &pass);
    return 0;
}
