#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

class Student
{
    int AdmissionNumber;
    char Name[50];
    int LanguagesMarks, MathematicsMarks, HumanitiesMarks, ScienceMarks, PhysicalEdMarks;
    double per;
    char Grade;
    void Calculate();
    int ValidateMarks(const string &subject);

public:
    void GetData();
    void ShowData() const;
    void ShowTabular() const;
    int Retrolino() const;
};

// Function to validate marks input
int Student::ValidateMarks(const string &subject)
{
    int marks;
    do
    {
        cout << "\nEnter Student's " << subject << " Marks out of 100 (0-100): ";
        cin >> marks;
        if (marks < 0 || marks > 100)
        {
            cout << "Invalid marks! Please enter marks between 0 and 100.";
        }
    } while (marks < 0 || marks > 100);
    return marks;
}

void Student::Calculate()
{
    per = (LanguagesMarks + MathematicsMarks + HumanitiesMarks + ScienceMarks + PhysicalEdMarks) / 5.0;
    if (per >= 60)
        Grade = 'A';
    else if (per >= 50)
        Grade = 'B';
    else if (per >= 33)
        Grade = 'C';
    else
        Grade = 'F';
}

void Student::GetData()
{
    cout << "\nEnter Student's Admission Number: ";
    cin >> AdmissionNumber;
    cout << "\nEnter Student's Name: ";
    cin.ignore();
    cin.getline(Name, 50);

    // Input validation for all marks
    LanguagesMarks = ValidateMarks("Languages");
    MathematicsMarks = ValidateMarks("Mathematics");
    HumanitiesMarks = ValidateMarks("Humanities");
    ScienceMarks = ValidateMarks("Science");
    PhysicalEdMarks = ValidateMarks("Physical Education(P.E)");

    Calculate();
}

void Student::ShowData() const
{
    cout << "\nStudent's Admission Number: " << AdmissionNumber;
    cout << "\nStudent's Name: " << Name;
    cout << "\nLanguages Score: " << LanguagesMarks;
    cout << "\nMathematics Score: " << MathematicsMarks;
    cout << "\nHumanities Score: " << HumanitiesMarks;
    cout << "\nScience Score: " << ScienceMarks;
    cout << "\nPhysical Education Score: " << PhysicalEdMarks;
    cout << "\nPercentage of Students is: " << per;
    cout << "\nStudent's Grade: " << Grade;
}

void Student::ShowTabular() const
{
    cout << setw(8) << AdmissionNumber << setw(15) << Name << setw(12) << LanguagesMarks
         << setw(12) << MathematicsMarks << setw(12) << HumanitiesMarks << setw(10) << ScienceMarks
         << setw(15) << PhysicalEdMarks << setw(12) << fixed << setprecision(2) << per
         << setw(8) << Grade << endl;
}

int Student::Retrolino() const
{
    return AdmissionNumber;
}

void WriteStudent();
void DisplayAll();
void DisplaySp(int);
void ModifyStudent(int);
void DeleteStudent(int);
void ClassResult();
void Result();
void Intro();
void EntryMenu();

int main()
{
    char ch;
    cout.setf(ios::fixed | ios::showpoint);
    cout << setprecision(2);
    Intro();
    do
    {
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t1.RESULTS";
        cout << "\n\n\t2.ENTRY/EDIT";
        cout << "\n\n\t3.EXIT";
        cout << "\n\n\tPlease Select a Valid Option(1-3): ";
        cin >> ch;
        switch (ch)
        {
        case '1':
            Result();
            break;
        case '2':
            EntryMenu();
            break;
        case '3':
            break;
        default:
            cout << "\a";
        }
    } while (ch != '3');
    return 0;
}

void WriteStudent()
{
    Student St;
    ofstream outFile;
    outFile.open("Student.dat", ios::binary | ios::app);
    if (!outFile)
    {
        cout << "Error: Cannot create file!";
        cin.ignore();
        cin.get();
        return;
    }
    St.GetData();
    outFile.write(reinterpret_cast<char *>(&St), sizeof(Student));
    outFile.close();
    cout << "\n\nStudent's Record Created Successfully!!";
    cin.ignore();
    cin.get();
}

void DisplayAll()
{
    Student St;
    ifstream inFile;
    inFile.open("Student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could Not be Open!!Press any Key to Continue";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\n\tDISPLAYING ALL RECORDS!!!\n\n";
    while (inFile.read(reinterpret_cast<char *>(&St), sizeof(Student)))
    {
        St.ShowData();
        cout << "\n\n====================\n";
    }
    inFile.close();
    cin.ignore();
    cin.get();
}

void DisplaySp(int n)
{
    Student St;
    ifstream inFile;
    inFile.open("Student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File Cannot be opened!!Press any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }
    bool flag = false;
    while (inFile.read(reinterpret_cast<char *>(&St), sizeof(Student)))
    {
        if (St.Retrolino() == n)
        {
            St.ShowData();
            flag = true;
        }
    }
    inFile.close();
    if (!flag)
        cout << "\nRecord Doesn't Exist";
    cin.ignore();
    cin.get();
}

void ModifyStudent(int n)
{
    bool Found = false;
    Student St;
    fstream File;
    File.open("Student.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File Cannot be opened!!Press any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }
    while (File.read(reinterpret_cast<char *>(&St), sizeof(Student)) && !Found)
    {
        if (St.Retrolino() == n)
        {
            St.ShowData();
            cout << "\nEnter New Details of Student: ";
            St.GetData();
            int pos = (-1) * static_cast<int>(sizeof(Student));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&St), sizeof(Student));
            cout << "\n\n\tRecords Successfully Updated!";
            Found = true;
        }
    }
    File.close();
    if (!Found)
        cout << "\n\n\tRecord Not Found";
    cin.ignore();
    cin.get();
}

void DeleteStudent(int n)
{
    Student St;
    ifstream inFile;
    inFile.open("Student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File Cannot be opened!!Press any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }
    ofstream outFile;
    outFile.open("Temp.dat", ios::binary);
    bool found = false;
    while (inFile.read(reinterpret_cast<char *>(&St), sizeof(Student)))
    {
        if (St.Retrolino() != n)
        {
            outFile.write(reinterpret_cast<char *>(&St), sizeof(Student));
        }
        else
        {
            found = true;
        }
    }
    outFile.close();
    inFile.close();
    remove("Student.dat");
    rename("Temp.dat", "Student.dat");

    if (found)
        cout << "\n\n\tRecord Deleted!!";
    else
        cout << "\n\n\tRecord Not Found!!";
    cin.ignore();
    cin.get();
}

void ClassResult()
{
    Student St;
    ifstream inFile;
    inFile.open("Student.dat", ios::binary);
    if (!inFile)
    {
        cout << "File Cannot be opened!!Press any key to continue...";
        cin.ignore();
        cin.get();
        return;
    }
    cout << "\n\n\tALL STUDENTS RESULTS\n\n";
    cout << "=====================================================================================\n";
    cout << setw(8) << "ADM.NO" << setw(15) << "NAME" << setw(12) << "LANGUAGES"
         << setw(12) << "MATHEMATICS" << setw(12) << "HUMANITIES" << setw(10) << "SCIENCE"
         << setw(15) << "PHYSICAL ED" << setw(12) << "PERCENTAGE" << setw(8) << "GRADE" << endl;
    cout << "=====================================================================================\n";
    while (inFile.read(reinterpret_cast<char *>(&St), sizeof(Student)))
    {
        St.ShowTabular();
    }
    inFile.close();
    cin.ignore();
    cin.get();
}

void Result()
{
    char Ch;
    int AdmissionNumber;
    system("cls");
    cout << "\n\n\n\tRESULTS MENU";
    cout << "\n\n\n\t1.Class Result";
    cout << "\n\n\n\t2.Students Report Card";
    cout << "\n\n\n\t3.Back to Main Menu";
    cout << "\n\n\n\tEnter valid choice: ";
    cin >> Ch;
    system("cls");
    switch (Ch)
    {
    case '1':
        ClassResult();
        break;
    case '2':
        cout << "\n\n\n\tEnter Student's Admission Number: ";
        cin >> AdmissionNumber;
        DisplaySp(AdmissionNumber);
        break;
    case '3':
        break;
    default:
        cout << "\a";
        break;
    }
}

void Intro()
{
    cout << "\n\n\n\t\tSTUDENT";
    cout << "\n\n\n\tREPORT CARD";
    cout << "\n\n\n\tPress Enter to Continue...";
    cin.get();
}

void EntryMenu()
{
    char Ch;
    int AdmissionNumber;
    system("cls");
    cout << "\n\n\n\tENTRY MENU";
    cout << "\n\n\t1.CREATE STUDENT RECORD";
    cout << "\n\n\t2.DISPLAY ALL STUDENTS RECORD";
    cout << "\n\n\t3.SEARCH STUDENT'S RECORD";
    cout << "\n\n\t4.MODIFY STUDENT'S RECORD";
    cout << "\n\n\t5.DELETE STUDENT'S RECORD";
    cout << "\n\n\t6.BACK TO MAIN MENU";
    cout << "\n\n\tPlease Enter a Valid Choice: ";
    cin >> Ch;
    system("cls");
    switch (Ch)
    {
    case '1':
        WriteStudent();
        break;
    case '2':
        DisplayAll();
        break;
    case '3':
        cout << "\n\n\tPlease Enter Student's Admission Number: ";
        cin >> AdmissionNumber;
        DisplaySp(AdmissionNumber);
        break;
    case '4':
        cout << "\n\n\tPlease Enter Student's Admission Number: ";
        cin >> AdmissionNumber;
        ModifyStudent(AdmissionNumber);
        break;
    case '5':
        cout << "\n\n\tPlease Enter Student's Admission Number: ";
        cin >> AdmissionNumber;
        DeleteStudent(AdmissionNumber);
        break;
    case '6':
        break;
    default:
        cout << "\a";
        EntryMenu();
        break;
    }
}
