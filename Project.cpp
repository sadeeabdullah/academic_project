
#include <iostream>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>

#define nl '\n'
using namespace std;

// declaring the file where we are going to save the information or the credentials for patients;
const string USER_DB = "users.txt";
const string APP_DB = "appointments.txt";
const string REC_DB = "records.txt";


//tracking the user here
string loggedInPhone = "";
string loggedInName = "";
string loggedInDob = "";
string loggedInEmail = "";

//saving user details
bool getUserDetails(string &phone, string &name, string &dob, string &email, string &password);


// declaring functions for the operations;
void showDashBoard();
void registerUser();
bool loginUser();
void consultation();
void openUrl(string rxLink);
void records();

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
        cout << "\n========== MediTrack Main Menu ==========\n";
        cout << "1. Registration\n2. Login\n3. Exit\nChoice: ";
        cin >> choice;

        if (choice == 1) registerUser();
        else if (choice == 2) {
            if (loginUser()) {
                showDashBoard();
            }
        }
    } while(choice != 3); // the loop will go untill you choose 3 as an option

}


// defining the pages


// Dashboard
void showDashBoard()
{
    int choice;
    do{
        cout << "\n======================================\n";
        cout << "         USER DASHBOARD\n";
        cout << "======================================\n";

        cout << " Name  : " << loggedInName << "\n";
        cout << " Phone : " << loggedInPhone << "\n";
        cout << " Email : " << loggedInEmail << "\n";
        cout << " DOB   : " << loggedInDob << "\n";
        cout << "======================================\n";


        cout << "1. Consultation (Book & Generate Rx)\n";
        cout << "2. Medical Records (View Links)\n";
        cout << "3. Logout\n";
        cout << "Enter choice: "; cin >> choice;

        if (choice == 1) consultation();
        else if (choice == 2) records();
        else if (choice == 3) {
            cout << "Logging out...\n";
            loggedInPhone = "";
            loggedInName = "";
            loggedInEmail = "";
            loggedInDob = "";
        }
        else cout << "Invalid choice.\n";
    } while (choice != 3);

}

// Registration Page
void registerUser()
{
    cout << "========== Registration ==========" << nl << nl;

    //variables for registration information
    string name, dob, phone, email, password;
    string tName, tDob, tEmail, tPass;

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


    while (true) {
        cout << "Phone (11 digits, start 01): ";
        cin >> phone;
        if (validPhone(phone)) {
            if (getUserDetails(phone, tName, tDob, tEmail, tPass)) {
                cout << "Error: User with this phone already exists.\n";
                return;
            }
            break;
        }
        cout << "Error: Invalid Phone! Must be 11 digits & start with 01.\n";
    }


    // checking if the number is already registered or not


cin.ignore(numeric_limits<streamsize> :: max(), '\n');

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


    // saving these information on file
    ofstream fout(USER_DB, ios::app);
    fout << phone << "," << name << "," << dob << "," << email << "," << password << nl;

    cout << "Registered Succesfully. You can login now." << nl;
}


//login page
bool loginUser()
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


    string dbName, dbDob, dbEmail, dbPass;

    // now check the credentials for login
    if(getUserDetails(phone, dbName, dbDob, dbEmail,dbPass) && dbPass == password)
    {
        loggedInPhone = phone;
        loggedInName = dbName;
        loggedInDob = dbDob;
        loggedInEmail = dbEmail;

        cout << nl << "Login Successfull! Welcome " << loggedInName << nl;
        return true;
    }

    cout << "Invalid Credentials." << nl;
    return false;
}



//adding consultation
void consultation(){

    string docs[6] = {
        "Dr. Khabib (General) - 500tk",
        "Dr. Leonardo (Dentist) - 800tk",
        "Dr. Joshim (Cardio) - 1000tk",
        "Dr. Sadio (Neuro) - 1200tk",
        "Dr. Messi (Ortho) - 900tk",
        "Dr. Ronaldo (Pediatrics) - 600tk"
    };
    cout << nl << "===== Doctor Consultation =====" << nl;

    // showing the doctor list
    for(int i = 0; i < 6; i++)
    {
        cout << (i + 1) << ". " << docs[i] << nl;
    }

    int choice;
    cout << "Select Doctor (1 - 6): ";
    cin >> choice;

    if(choice <1 || choice > 6)
    {
        cout << "Invalid Choice" << nl;
        return ;
    }

    string docName = docs[choice - 1];


    // adding the informaton to the file now
    ofstream fout (APP_DB, ios:: app);
    fout << loggedInPhone << "," << docName << ",confirmed" << nl;

    cout << nl << "You have successfully Booked an appoinment with " << docName << nl;
    cout << "Prescription will be provided automatically after your appointment." << nl;

    string rxLink = "https://drive.google.com/file/d/18SCrzNjVU4nr3q_rac1IK81xAETQurrr/view?usp=sharing";       // it is an demo prescription

    cout << ">> Opening Prescription in Browser...\n";

    openUrl(rxLink); // opening the url on your computer based on the OS

    string labLink= "N/A";
    char needTest;

    cout << "Did the doctor prescribe medical tests? (y/n): ";
    cin >> needTest;

    string recordEntry = "visit: " + docName + " | Rx Link: " + rxLink;


    //if test need?
    if(needTest == 'y' || needTest == 'Y')
    {
        labLink = "https://drive.google.com/file/d/1TxMVKsccrtor7WUZjSAM8LRtjnqnRQS0/view?usp=sharing";
        recordEntry += " | Lab Report Link: " + labLink;

        cout << ">> Lab Test Added. Opening Report Link...\n";
        openUrl(labLink);
    }else{
        recordEntry += " | No lab test has been prescribed";
    }

    ofstream recOut (REC_DB, ios::app);
    recOut << loggedInPhone << "," << recordEntry << "\n";

    cout << ">> Digital Record saved successfully.\n";
}


// showing the records
void records(){
    int choice;
    cout << nl <<"--- Medical Records ---" << nl;
    cout << "1. View My Online Records\nChoice: ";
    cin >> choice;

    if(choice == 1){
        ifstream fin(REC_DB);
        string line, ph, rec;

        bool found = false;

        cout << nl << "[Your Digital Health Records]" << nl;

        while(getline(fin, line))
        {
            stringstream ss(line);
            if(line.size() == 0)
                continue;
            getline(ss, ph,',');
            getline(ss, rec, ',');
            if(ph == loggedInPhone)
            {
                cout << " - " << rec << nl;
                found = true;
            }
        }
        if(!found)
            cout << "No records found." << nl;
    }
    else
    {
        showDashBoard();
    }
}

// opening drive  link onbrowser
void openUrl(string rxLink)
{
    #ifdef _WIN32
        string command = "start " + rxLink;
    #elif __APPLE__
        string command = "open " + rxLink;
    #else
        string command = "xdg-open " + rxLink;
    #endif

    // Execute command
    system(command.c_str());
}

//get user details
bool getUserDetails(string &phone, string &name, string &dob, string &email, string &password)
{





    ifstream fin (USER_DB); // OPEN FILE
    if(!fin.is_open())
        return false;   // if file is not opened or didnto create untill now then return false

    // using temporary variable to read the file information line by line
    string line, p, n,d,e,pass;

    while(getline(fin, line)) // it will run as long as we get line from the user_db
    {
        if(line.empty())
            continue; // if the line is empty or by any chance there a enter in the text file we will skip this line

        stringstream ss(line);      //using string stream we will get the words in the line divided by the ',';
        getline(ss, p, ',');
        getline(ss, n, ',');
        getline(ss, d, ',');
        getline(ss, e, ',');
        getline(ss, pass, ',');



        if(p == phone)
        {
            name = n;
            dob = d;
            email = e;
            password = pass;
            return true;
        }
    }

    return false;
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

    if(p[0] != '0' || p[1] != '1')      // checking the phone number starting two index to make sure that it starts with 01
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


