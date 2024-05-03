/*

Program under MIT License
Learn more @ https://github.com/nsoliven/passmanager
Created in 2023 by NSOLIVEN

*/

/*

    Full layout of how passmanager will work:
    1. User opens program then will check if a DB file exists or not
    (a) If it does not exist, it will create a new DB file
    (b) If it does exist, it will open the DB file

    2. User will be prompted to enter a password
    (a) If the password is correct, the user will be able to access the DB file
    (b) If the password is incorrect, the user will be prompted to enter the password again
    * note password will be hashed and salted stored in a txt file.

    3. Password will be used to generate a key for the AES encryption algorithm


*/





#include "userInterface.h"
#include "encryptionAlgorithm.h"
#include "passwordmanagement.h"

const string dbName = "lockSmithDB.db3";
const string masterFile = "master_password";
const int keyLength = 16;
const unsigned int maxLoginAttempts = 5;

int main(){
    //create our objects for use of functions
    SystemPasswordManagement systemPass;
    UserInterface ui;
    Database dbManager;

    //check if we are setting up a new database
    if(!dbManager.checkIfDatabaseExists(dbName)){
        ui.openNewInstanceMenu();
        if(!systemPass.masterPasswordSetup(masterFile)){
            std::cout<< "PASSWORD SETUP FAILED! DO YOU HAVE READ/WRITE PERMISSIONS?\n";
            return -1;
        }

        if(!dbManager.declareDatabase(dbName)){
            std::cout<< "DATABASE SETUP FAILED! DO YOU HAVE READ/WRITE PERMISSIONS?\n";
            return -1;
        }
        cout << "New Database has been created!\n";
    }else{ui.openLoginMenu();}

    //logging in 
    for(int i = 0; i <= maxLoginAttempts; i++){
        if(systemPass.masterPasswordLogin(masterFile)){break;}
        std::cout<< "Wrong Password! Attempts Left = [" <<
        (maxLoginAttempts-i) << " of " << maxLoginAttempts << "]\n";

        if(i==maxLoginAttempts){cout<< "MAX ATTEMPTS REACHED, EXITING PROGRAM\n"; return 1;}
    }


    return 0;
}