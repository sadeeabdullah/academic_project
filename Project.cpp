
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>

#define nl '\n'
using namespace std;

// declaring the file where we are going to save the information or the credentials for patients;
const string USER_DB = "users.txt";

// declaring functions for the operations;
void showDashBoard();
void registerUser();
void loginUser();

// here is the validity checking funciton
bool validDOB(string dob);
bool validPhone(string p);
bool validEmail(string e);
bool validPassWord(string p);


//get days of the month
int getDays(int n, int year)
{

    if(n == 1 || n == 3 || n == 5 || n == 7 || n == 8 || n == 10 || n == 12)
        return 31;
    if(n == 4 || n == 6 || n == 9 || n == 11)
        return 30;

    // for february
    bool leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    return (leap ? 29 : 28);
}

int main()
{

    int choice;     // choose the operation you want to do

    do{
        cout << "========== Welcome To MediTrack ==========" << nl<<nl << nl;
        showDashBoard(); // no matter it will show the dashboard after running the function

        cin >> choice;      // enter your choice

        cout << nl << nl;
        if(choice == 1)
        {
            // if the choice is 1 then go to register page;
            registerUser();
        }
        else if(choice == 2)
        {
            // if the choice is 2 ten go to the login page
            loginUser();
        }
        else if(choice == 3)
        {
            // 3 is for exiting the program
            cout << "Exiting MediTrack ... \n Have a nice day." << nl;
        }
        else
        {
            // if you  don't choose any of the given choice
            cout << nl << "Invalid Choice. Please try again." << nl;
        }
    } while(choice != 3); // the loop will go untill you choose 3 as an option

}


// defining the pages


// Dashboard
void showDashBoard()
{

    cout << nl << "========== Dashboard ==========" << nl << nl;
    cout << "1. Registration" << nl;
    cout << "2. Login" << nl;
    cout << "3. Exit" << nl<<nl;

    cout << "Enter your choice (1 - 3) : " ;
}

// Registration Page
void registerUser()
{
    cout << "========== Registration ==========" << nl << nl;

    //variables for registration information
    string name, dob, phone, email, password;

    cin.ignore(numeric_limits<streamsize> :: max(), '\n');      // it will remove all the buffer of the input

    cout <<"Enter your Full Name : ";
    getline(cin, name);


    do{
        cout << "Enter your Date of Birth (dd/mm/yyyy): ";
        getline(cin, dob);      // taking input of the date of birth

        // checking the validity of the birth date that has been taken as input if the format is wrong then print a warning message that the format is not correct
        if(!validDOB(dob))
        {
            cout << "Invalid Date of Birth. Please follow the format and valid date." << nl;
        }
    } while(!validDOB(dob)); // we will run this loop until the birthdate is valid


    do{
        cout << "Enter your phone number (start with 01 and total 11 digit): ";
        getline(cin, phone);
        if (!validPhone(phone)){
            cout << "Invalid Phone number. Input a valid phone number" << nl;
        }
    }while(!validPhone(phone)); // it will work same as the birthdate checking


    // checking if the number is already registered or not














    do{
        cout << "Enter your email: ";
        getline(cin, email);

        if(!validEmail(email))
            cout << "Invalid email. Must contain '@' and end with '.com' " << nl;
    }while(!validEmail(email));


    do{
        cout << "Enter your password (min 4 characters, must include uppercase, lowercase and a special character): ";
        getline(cin, password);
        if(!validPassWord(password))
            cout << "Invalid password\nPassword should be minimum 4 characters, must include uppercase, lowercase and a special character" << nl;
    }while(!validPassWord(password));
}


//login page
void loginUser()
{

    cout << nl << "========== Login ==========" << nl << nl;

    string phone, password;
    cin.ignore(numeric_limits<streamsize> :: max(), '\n');

    do{
        cout << "Enter your phone number : ";
        getline(cin, phone);
        if (!validPhone(phone)){
            cout << "Invalid Phone number. Input a valid phone number" << nl;
        }
    }while(!validPhone(phone));


    do{
        cout << "Enter your password: ";
        getline(cin, password);
        if(!validPassWord(password))
            cout << "Invalid password\nPassword should be minimum 4 characters, must include uppercase, lowercase and a special character" << nl;
    }while(!validPassWord(password));

}



// validation of the input

// validation for the date of birth
bool validDOB(string dob)
{

    // we will check the date of birth size if it is not equal to 10 or if not  the third and 6th index is '/' then return false;
    if (dob.size() != 10 || dob[2] != '/' || dob[5] != '/')
        return false;

    // extracting day, month and year from the dob
    int day = stoi(dob.substr(0, 2));
    int month = stoi(dob.substr(3,2));
    int year = stoi(dob.substr(6,4));

    if (month < 1 || month > 12)
        return false;
    if (year > 2025)
        return false;
    if (day < 1 || day > getDays(month,year))
        return false;

    return true;
}

// validation for phone number
bool validPhone(string p)
{

    if(p.size() != 11)      // checking the phone number size
        return false;

    if(p[0] != '0' && p[1] != '1')      // checking the phone number starting two index to make sure that it starts with 01
        return false;

    for(char c : p)             // checking if any input is not number
        if(!isdigit(c))
            return false;

    return true;
}


//validation for the email
bool validEmail(string e)
{
    size_t atPos = e.find('@');
    size_t dotPos = e.rfind(".com");

    return (atPos != string :: npos && dotPos != string :: npos && atPos+ 2 < dotPos);

}

// validation for password
bool validPassWord(string p)
{
    if(p.size() < 4)
        return false;

    bool hasupper = false, hasLower = false, hasSpecial = false;

    for(char c : p)
    {
        if(isupper(c))
            hasupper = true;
        else if(islower(c))
            hasLower = true;
        else if(!isalnum(c))
            hasSpecial = true;
    }

    return hasupper && hasLower && hasSpecial;
}


