#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

class account{
    private: //Methods
        void file_truncate();
        void methods_options();
        void menu(const string*, const int*);
        bool validation(const string*, const int*);
        int clearence_check(const string*, const int*);

    private: //Variables, etc.
        bool valid; map<string, int> account_d;
        string ID; int password, clearence_lvl;
        string ufile="accounts.dat", lfile="logs.dat", mfile= "methods.dat";
    
    enum clearences{
        Guest,
        Regular,
        Moderator,
        Admin,
    };


    public: //Public functions
        void account_login(const string*, const int*);
        void account_logout(const string*, const int*);
        void account_create(const string*, const int*, const int*);
};

void account::file_truncate(){
    ofstream file, fileb;
    file.open(ufile, ios::trunc);
    fileb.open(lfile, ios::trunc);
    file.close();
    fileb.close();
}

//STORING FUNCTIONS IN VECTOR LINK
//https://forum.openframeworks.cc/t/std-vector-of-void-function-pointers/17043/2

void account::menu(const string* ID, const int* pass){
    clearence_lvl = clearence_check(ID, pass);
    switch(clearence_lvl){
        case Guest:
            cout << "\nGuest\n";
            break;
        case Regular:
            cout << "\nRegular\n";
            break;
        case Moderator:
            cout << "\nModerator\n";
            break;
        case Admin:
            cout << "\nAdmin\n";
            break;
        default:
            /*
            GETTING 'YOU FUCKED UP' B/C clearence_check()
            is returning password instead of clearence;
            HUGE ERROR: FIX IN TIME!
            */
            cout << "\nYOU FUCKED UP\n";
            break;
    }
}

void account::account_logout(const string* user, const int* pass){
    valid = validation(user, pass);
    if(valid){
        
    }
}

void account::account_login(const string* user, const int* pass){
    ifstream file;
    file.open(ufile, ios::in);
    valid = validation(user, pass);
    map<string, int> clearence_only;

    if(valid){
        if(file.is_open()){
            while(!file.eof()){
                file >> ID >> password >> clearence_lvl;
                account_d.insert(pair(ID, password));
            }
            file.close();
            for(auto& x: account_d){
                if(*user == x.first){
                    if(*pass == x.second){
                        cout << "\nLogged IN\n";
                        menu(user, pass);
                        break;
                    }else if(*pass != x.second){
                        cout << "\nERROR: Incorrect password; @account_login()\n";
                        break;
                    }else{
                        cout << "\nISSUE: could not process password; @account_login()\n";
                        break;                       
                    }
                }else if(*user != x.first){
                    //uncomment for debugging 
                    // cout << "\nERROR: Invalid ID; @account_login()\n";
                }else{
                    cout << "\nISSUE: could not process ID; @account_login()\n";
                }
            }
        }
    }else if(!valid){
        cout << "\nERROR: Account not found; @account_login()\n";
    }else{
        cout << "\nISSUE: could not validate account; @account_login()\n";
    }
}


//Returns users clearence level
int account::clearence_check(const string* user, const int* pass){
    ifstream file; int clearence;
    file.open(ufile, ios::in);

    //ERROR WITH VALIDATION IN THIS FUNCTION;
    //FUNCTION RETURNS PASSWORD INSTEAD OF CLEARENCE!
    // valid = validation(user, pass);
    valid = true;

    if(valid){
        if(file.is_open()){
            while(!file.eof()){
                file >> ID >> password >> clearence;
                account_d.insert(pair(ID, clearence));
            }
            file.close();
            for(auto& x: account_d){
                if(*user == x.first){
                        clearence_lvl = x.second;
                        // cout << clearence_lvl;
                        break;
                }else if(*user != x.first){
                    //uncomment for debugging 
                    // cout << "\nERROR: Invalid ID; @clearence_check()\n";
                }else{
                    cout << "\nISSUE: could not process ID; @clearence_check()\n";
                }
            }
        }else{
        cout << "\nERROR: file != open; @clearence_check()\n";
        }
    }else if(!valid){
        cout << "\nERROR: Account not found; @clearence_check()\n";
    }else{
        cout << "\nISSUE: could not determine clearence level; @clearence_check()\n";
    }
    return clearence_lvl;
}

//function creates account;
void account::account_create(const string* ID, const int* pass, const int* clearence){
    ofstream file, fileb;
    file.open(ufile, ios::app);
    fileb.open(lfile, ios::app);

    valid = validation(ID, pass);

    if(!valid){
        if(file.is_open()){
            file << *ID << " " << *pass << " " << *clearence;
            fileb << *ID << "::" << *pass << "::" << *clearence << endl;
            valid = validation(ID, pass);
            file.close(); fileb.close();
            if(valid){
                cout << "\nACCOUNT CREATED\n";
            }else if(!valid){
                cout << "\nACCOUNT != CREATED\n";
            }else{
                cout << "\nISSUE: COULDN'T create account; @account_create()\n";
            }
        }else{
            cout << "\nERROR: file != open; @account_create()\n";
        }
    }else if(valid){
        cout << "\nERROR: Duplicate Accounts\n";
    }else{
        cout << "\nISSUE: could not create Account, @@account_create()\n";
    }
}

//function validates if user is in system
bool account::validation(const string* user, const int* pass){
    ifstream file;
    file.open(ufile, ios::in);

    if(file.is_open()){
        while(!file.eof()){
            file >> ID >> password >> clearence_lvl;
            account_d.insert(pair(ID, password));
        }
        file.close();
        for(auto& x: account_d){
            if(*user == x.first){
                if(*pass == x.second){
                    valid = true;
                    // cout << "True";
                    break;
                }else if(*pass != x.second){
                    valid = true;
                    cout << "\nERROR: Incorrect password; @validation();\n";
                    break;
                }else{
                    cout << "ISSUE: could not validate passaword; @validation";
                    break;
                }
            }else if(*user != x.first){
                valid = false;
                // cout << "False";
            }else{
                cout << "\nISSUE: could not determine validity, @validation()\n";
            }
        }
    }else{
        cout << "\nERROR: file != open; @validation()\n";
    }
    return valid;
}