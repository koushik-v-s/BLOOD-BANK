#include <iostream>
#include <conio.h> 
#include <windows.h> 
#include <fstream> 
#include <chrono>
using namespace std;
const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 24;
const string OPTIONS[] = {"A D D   D O N O R      ", "S E A R C H   D O N O R", "D E L E T E   D O N O R", "E X I T                "};
const int NUM_OPTIONS = 4; 
class Animation 
{
    protected:
    void delay(int milliseconds) 
    {
        auto start = chrono::high_resolution_clock::now();
        while (true) 
        {
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
            if (duration >= milliseconds / 4) 
                break;
        }
    }
    void intro()
    {
        for(int i=0;i<10;i++)
        {
            system("CLS");
            cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            if(i%2==0)
            {
                cout<<string(60, ' ')<<"     ----    ----    ----    ----"<<endl;
                cout<<string(60, ' ')<<"|"<<endl;
                cout<<string(60, ' ')<<"|     B L O O D    U N I T Y     |"<<endl;
                cout<<string(60, ' ')<<"                                 |"<<endl;
                cout<<string(60, ' ')<<" ----    ----    ----    ----"<<endl;
            }
            else
            {
                cout<<string(60, ' ')<<" ----    ----    ----    ----"<<endl;
                cout<<string(60, ' ')<<"                                 |"<<endl;
                cout<<string(60, ' ')<<"|     B L O O D    U N I T Y     |"<<endl;
                cout<<string(60, ' ')<<"|"<<endl;
                cout<<string(60, ' ')<<"     ----    ----    ----    ----"<<endl;
            }
            delay(1000);
        }
    }
    void show(const string loadingText)
    {
        const int barWidth = 24; 
        const char symbols[4] = { '|', '/', '-', '\\' }; 
        int symbolIndex = 0; 
        system("CLS");
        cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        for (int i = 0; i <= barWidth; ++i) 
        {
            cout << "\r";
            cout << string(60, ' '); 
            cout << loadingText << " [";
            for (int j = 0; j < barWidth; ++j) 
            {
                if (j < i)
                    cout << "=";
                else if (j == i)
                    cout << symbols[symbolIndex++ % 4]; 
                else
                    cout << " ";
            }
            cout << "] " << (i * 100) / barWidth << "%";
            cout.flush();
            delay(350);
        }
        cout << endl;
        system("CLS");
    }
};
class Person 
{
    protected:
    string name, fatherName, dob, bloodGroup, address, phoneNumber;
    int age;
    void getDetails() 
    {
        cout << "ENTER NAME                       : ";
        getline(cin, name);
        cout << "ENTER FATHER'S NAME              : ";
        getline(cin, fatherName);
        cout << "ENTER DATE OF BIRTH (YYYY-MM-DD) : ";
        getline(cin, dob);
        cout << "ENTER BLOOD GROUP                : ";
        getline(cin, bloodGroup);
        cout << "ENTER AGE                        : ";
        cin >> age;
        cin.ignore(); 
        cout << "ENTER ADDRESS                    : ";
        getline(cin, address);
        cout << "ENTER PHONE NUMBER               : ";
        cin >> phoneNumber;
    }
    void displayScreen(int mouseY) 
    {
        system("CLS");
        cout<<string(60,' ')<<"---------------------------\n";
        cout<<string(60,' ')<<"|| B L O O D   U N I T Y ||\n";
        cout<<string(60,' ')<<"---------------------------";
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n"; 
        for (int i = 0; i < NUM_OPTIONS; ++i) 
        {
            int optionX = (SCREEN_WIDTH - OPTIONS[i].length()) / 2; 
            if (i == mouseY)
                cout <<"                                                   "<<char(272)<<"\t"; 
            else 
                cout << "                                                  ";
            cout <<"  "<<OPTIONS[i];
            if (i == mouseY) 
                cout << "\t"<<char(273); 
            cout << endl;
        }
    }
};
class Donor : protected Person, protected Animation
{
    void writeToFile() 
    {
        ofstream file("DONOR_DETAILS.txt", ios::app); 
        if (file.is_open()) 
        {
            file << "-------------------------------------------" << endl;
            file << "BLOOD GROUP   : " << bloodGroup << endl;
            file << "NAME          : " << name << endl;
            file << "FATHER'S NAME : " << fatherName << endl;
            file << "DATE OF BIRTH : " << dob << endl;
            file << "AGE           : " << age << endl;
            file << "ADDRESS       : " << address << endl;
            file << "PHONE NUMBER  : " << phoneNumber << endl;
            file << "-------------------------------------------" << endl;
            file.close();
            cout << "\nDONOR DETAILS ARE ADDED SUCCESSFULLY!!!" << endl;
            system("pause");
        } 
        else
            cout << string(60, ' ') << "\nSORRY, SERVER IS BUSY!!!" << endl;
    }
    public:
    void intro()
    {
        Animation::intro();
    }
    void displayScreen(int mouseY)
    {
        Person::displayScreen(mouseY);
    }
    void show(const string loadingtext)
    {
        Animation::show(loadingtext);
    }
    void getDetails()
    {
        Person::getDetails();
        if (age < 18)
        {
            cout << "\nTHANKS FOR YOUR INTEREST BUT, UNFORTUNATELY YOU ARE NOT APPLICABLE TO DONATE BLOOD!!!" << endl;
            system("pause");
        }
        else
            writeToFile();
    }
    void searchDonor(const string& bloodGroup) 
    {
        ifstream file("DONOR_DETAILS.txt"); 
        string line;
        bool found = false;
        if (file.is_open()) 
        {
            while (getline(file, line)) 
            {
                if (line.find("BLOOD GROUP   : " + bloodGroup) == 0) 
                {
                    if (!found)
                        cout << "\nMATCHING DONORS FOUND :" << endl;
                    found = true;
                    cout << "-------------------------------------------" << endl;
                    cout << line << endl; 
                    for (int i = 0; i < 7; ++i) 
                    { 
                        getline(file, line);
                        cout << line << endl;
                    }
                }
            }
            file.close();
            if (!found) 
                cout << "\nNO DONORS WITH BLOOD GROUP " << bloodGroup << " FOUND." << endl;
        } 
        else 
            cout << "\nSORRY, SERVER IS BUSY!!!" << endl;
    }
    void deleteFromFile(const string& name, const string& phoneNumber) 
    {
        ifstream inFile("DONOR_DETAILS.txt");
        ofstream outFile("TEMP.txt");
        if (!inFile || !outFile) 
        {
            cout << "\nSORRY, SERVER IS BUSY!!!" << endl;
            return;
        }
        bool found = false;
        string line;
        while (getline(inFile, line)) 
        {
            getline(inFile, line); 
            bloodGroup = line.substr(line.find("BLOOD GROUP   : ") + 16);
            getline(inFile, line);
            this->name = line.substr(line.find("NAME          : ") + 16);
            getline(inFile, line);
            fatherName = line.substr(line.find("FATHER'S NAME : ") + 16);
            getline(inFile, line);
            dob = line.substr(line.find("DATE OF BIRTH : ") + 16);
            getline(inFile, line);
            age = stoi(line.substr(line.find("AGE           : ") + 16));
            getline(inFile, line);
            address = line.substr(line.find("ADDRESS       : ") + 16);
            getline(inFile, line);
            this->phoneNumber = line.substr(line.find("PHONE NUMBER  : ") + 16);
            getline(inFile, line);
            if (this->name == name && this->phoneNumber == phoneNumber) 
                found = true;
            else 
            {
                outFile << "-------------------------------------------" << endl;
                outFile << "BLOOD GROUP   : "+bloodGroup << endl;
                outFile << "NAME          : "+this->name << endl;
                outFile << "FATHER'S NAME : "+fatherName << endl;
                outFile << "DATE OF BIRTH : "+dob << endl;
                outFile << "AGE           : "<<age << endl;
                outFile << "ADDRESS       : "+address << endl;
                outFile << "PHONE NUMBER  : "+this->phoneNumber << endl;
                outFile << "-------------------------------------------" << endl;
            }
        }
        inFile.close();
        outFile.close();
        if (found) 
        {
            remove("DONOR_DETAILS.txt");
            rename("TEMP.txt", "DONOR_DETAILS.txt");
            cout << "\nDONOR DETAILS DELETED SUCCESSFULLY!!!" << endl;
        } 
        else 
        {
            remove("TEMP.txt");
            cout << "\nSORRY, DONOR NOT FOUND!!!" << endl;
        }
    }
};
int main() 
{
    int mouseY = 0; 
    char input;
    Donor donor; 
    donor.intro();
    do 
    {
        donor.displayScreen(mouseY);
        input = _getch(); 
        switch (input) 
        { 
            case 72: 
                if (mouseY > 0) 
                    mouseY--;
                break;
            case 80: 
                if (mouseY < NUM_OPTIONS - 1) 
                    mouseY++;
                break;
        }
        if (input == '\r') 
        {
            system("CLS");
            if (OPTIONS[mouseY] == OPTIONS[3]) 
                break;
            if (OPTIONS[mouseY] == "A D D   D O N O R      ") 
            {
                donor.show("LOADING...");
                cout<<"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
                donor.getDetails(); 
            } 
            else if (OPTIONS[mouseY] == "S E A R C H   D O N O R") 
            {
                donor.show("LOADING...");
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nENTER BLOOD GROUP TO SEARCH : ";
                string bloodGroup;
                getline(cin, bloodGroup);
                donor.searchDonor(bloodGroup);
            }  
            else if (OPTIONS[mouseY] == "D E L E T E   D O N O R") 
            {
                donor.show("LOADING...");
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nENTER DONOR'S NAME         : ";
                string name, phoneNumber;
                getline(cin, name);
                cout << "ENTER DONOR'S PHONE NUMBER : ";
                getline(cin, phoneNumber);
                donor.deleteFromFile(name, phoneNumber); 
            } 
            cout << "\n\n" << "<  B A C K  >";
            cin.ignore();
        }
    } while (input != 'Q' && input!='q'); 
    donor.show("EXITING...");
    return 0;
}