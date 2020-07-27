#include<iostream>
#include<fstream>
#include<string>

using namespace std;


struct Subject
{
    string name;
	string subcode;
}sublist[7];


struct session
{
    string date;
    char presence;
};


class Attendance
{
    session record[100];
    int pos;
    int attended;

    public:
        Attendance()
        {
            pos=0;
            attended=0;
        }

        int Position()
        {
            return pos;
        }

        int Attended()
        {
            return attended;
        }

        void mark(string d, char p)
        {
            record[pos].date = d;
            record[pos].presence = p;
            pos++;
            if(p=='P')
                attended++;
        }

        void display()
        {
            cout<<"Date | Presence"<<endl;
            for(int i=0;i<pos;i++)
            {
                cout<<record[i].date;
                cout<<" | ";
                cout<<record[i].presence<<endl;
            }
        }
};

class Person
{
    protected:
    string name, uname, password;

    public:
        string Uname()
        {
            return uname;
        }
        string Password()
        {
            return password;
        }
        string Name()
	    {
	        return name;
	    }
};


class Student: public Person
{
	int admno;
	Attendance subjects[7];

	public:
	    int Admno()
	    {
	        return admno;
	    }
		void enterData(int a, string n, string u, string p)
		{
            admno = a;
            name = n;
            uname = u;
            password = p;
		}
		void showData()
		{
		    cout<<"\n\n.......Student Details......\n";
            cout<<"Admission No.     : "<<admno<<endl;
            cout<<"Full Name         : "<<name<<endl;
            cout<<"Username          : "<<uname<<endl;
            cout<<endl;
		}
		void askData()
        {
            cout<<"\n\nEnter Student Details......\n";
            cout<<"Enter Admission No.     : "; cin>>admno;
            cout<<"Enter Full Name         : "; cin.ignore(); getline(cin,name);
            cout<<"Enter Username          : "; cin>>uname;
            cout<<"Enter Password          : "; cin>>password;
            cout<<endl;
        }
        void markAttendance(int code, string date, char presence)
        {
            subjects[code].mark(date, presence);
        }
        void displayAttendance(int code)
        {
            subjects[code].display();
        }
        void report()
        {
            cout<<".......Attendance Report...........\n";
            for (int j=0; j<7; j++)
            {
                cout<<sublist[j].name<<":-"<<endl;
                cout<<"No of Classes: "<<subjects[j].Position()<<endl;
                cout<<"Classes attended: "<<subjects[j].Attended()<<endl<<endl;
            }
        }

}S,loggedS;



class Faculty:public Person
{
    int id;
    int code;

    public:
        int Id()
	    {
	        return id;
	    }
	    int Code()
	    {
	        return code;
	    }
		void enterData(int i, string n, string u, string p, int c)
		{
            id = i;
            name = n;
            uname = u;
            password = p;
            code = c;
		}
		void showData()
		{
		    cout<<"\n\n.......Faculty Details......\n";
            cout<<"ID                : "<<id<<endl;
            cout<<"Full Name         : "<<name<<endl;
            cout<<"Username          : "<<uname<<endl;
            cout<<"Assigned Subject  : "<<sublist[code].name<<endl;
            cout<<"Code              : "<<sublist[code].subcode<<endl;

            cout<<endl;
		}
		void askData()
        {
            cout<<"\n\nEnter Faculty Details......\n";
            cout<<"Enter ID                : "; cin>>id;
            cout<<"Enter Full Name         : "; cin.ignore(); getline(cin, name);
            cout<<"Enter Username          : "; cin>>uname;
            cout<<"Enter Password          : "; cin>>password;
            cout<<"Enter Subject Code      : "; cin>>code;
            cout<<endl;
        }
}F,loggedF;


class Admin:public Person
{
    public:
		void enterData(string n, string u, string p)
		{
            name = n;
            uname = u;
            password = p;
		}

		void askData()
        {
            cout<<"\n\nEnter Admin Details......\n";
            cout<<"Enter Full Name         : "; getline(cin, name);
            cout<<"Enter Username          : "; cin>>uname;
            cout<<"Enter Password          : "; cin>>password;
            cout<<endl;
        }
}A,loggedA;


void writeSData()
{
    S.askData();
    int flag = 0;
    Student S1;
	ifstream fin;
	fin.open("Students.dat",ios::in|ios::binary);
	while(fin.read((char*)&S1,sizeof(S1)))
	{
		if(S.Admno() == S1.Admno() || S.Uname() == S1.Uname())
		    flag++;
	}
    if(flag==0)
    {
        ofstream fout;
        fout.open("Students.dat",ios::binary|ios::out|ios::app);
        fout.write((char*)&S,sizeof(S));
        fout.close();
	}
	else
        cout<<"Admssion number and Username should be unique.\n";

	fin.close();
}

void writeFData()
{
    F.askData();
    int flag=0;
    Faculty F1;

	ifstream fin;
	fin.open("Faculty.dat",ios::in|ios::binary);
	while(fin.read((char*)&F1,sizeof(F1)))
	{
		if(F.Id() == F1.Id() || F.Uname() == F1.Uname())
		    flag++;
	}
    if(flag==0)
    {
        ofstream fout;
        fout.open("Faculty.dat",ios::binary|ios::out|ios::app);
        fout.write((char*)&F,sizeof(F));
        fout.close();
	}
	else
        cout<<"ID and Username should be unique.\n";

	fin.close();
}

void displaySData()
{
	ifstream fin;
	fin.open("Students.dat",ios::in|ios::binary);
	while(fin.read((char*)&S,sizeof(S)))
	{
		S.showData();
	}
	fin.close();
	cout<<"\n\nData Reading from File Successfully Done....\n";
}

void displayFData()
{
	ifstream fin;
	fin.open("Faculty.dat",ios::in|ios::binary);
	while(fin.read((char*)&F,sizeof(F)))
	{
		F.showData();
	}
	fin.close();
	cout<<"\n\nData Reading from File Successfully Done....\n";
}

void searchSData()
{
	int n, flag=0;
	ifstream fin;
	fin.open("Students.dat",ios::in|ios::binary);
	cout<<"Enter Admission Number you want to search : ";
	cin>>n;

	while(fin.read((char*)&S,sizeof(S)))
	{
		if(n==S.Admno())
		{
			cout<<"The Details of Admission No. "<<n<<" shown herewith:\n";
			S.showData();
			flag++;
		}
	}
	fin.close();
	if(flag==0)
		cout<<"The Admission No. "<<n<<" not found....\n\n";
	cout<<"\n\nData Reading from File Successfully Done....\n";
}

void searchFData()
{
	int n, flag=0;
	ifstream fin;
	fin.open("Faculty.dat",ios::in|ios::binary);
	cout<<"Enter ID you want to search : ";
	cin>>n;

	while(fin.read((char*)&F,sizeof(F)))
	{
		if(n==F.Id())
		{
			cout<<"The Details of ID "<<n<<" shown herewith:\n";
			F.showData();
			flag++;
		}
	}
	fin.close();
	if(flag==0)
		cout<<"ID "<<n<<" not found....\n\n";
	cout<<"\n\nData Reading from File Successfully Done....\n";
}

void deleteSData()
{
	int n, flag=0;
	ifstream fin;
	ofstream fout,tout;

	fin.open("Students.dat",ios::in|ios::binary);
	fout.open("TempStud.dat",ios::out|ios::app|ios::binary);
	tout.open("TrashStud.dat",ios::out|ios::app|ios::binary);

	cout<<"Enter Admission Number you want to delete : ";
	cin>>n;

	while(fin.read((char*)&S,sizeof(S)))
	{
		if(n==S.Admno())
		{
			cout<<"The Following Admission No. "<<n<<" has been deleted:\n";
			S.showData();
			tout.write((char*)&S,sizeof(S));
			flag++;
		}
		else
		{
			fout.write((char*)&S,sizeof(S));
		}
	}
	fout.close();
	tout.close();
	fin.close();
	if(flag==0)
		cout<<"The Admission No. "<<n<<" not found....\n\n";
	remove("Students.dat");
	rename("tempStud.dat","Students.dat");
}

void deleteFData()
{
	int n, flag=0;
	ifstream fin;
	ofstream fout,tout;

	fin.open("Faculty.dat",ios::in|ios::binary);
	fout.open("TempFac.dat",ios::out|ios::app|ios::binary);
	tout.open("TrashFac.dat",ios::out|ios::app|ios::binary);

	cout<<"Enter ID you want to delete : ";
	cin>>n;

	while(fin.read((char*)&F,sizeof(F)))
	{
		if(n==F.Id())
		{
			cout<<"The Following ID "<<n<<" has been deleted:\n";
			F.showData();
			tout.write((char*)&F,sizeof(F));
			flag++;
		}
		else
		{
			fout.write((char*)&F,sizeof(F));
		}
	}
	fout.close();
	tout.close();
	fin.close();
	if(flag==0)
		cout<<"ID "<<n<<" not found....\n\n";
	remove("Faculty.dat");
	rename("TempFac.dat","Faculty.dat");
}

void takeAttendance()
{
    int code = loggedF.Code();
    string date;
    cout<<"Enter date (DD-MM-YYYY):";
    cin>>date;
    system("cls");

    fstream fio;
	fio.open("Students.dat",ios::in|ios::out|ios::binary);
    char presence;
    cout<<"Name | Presence"<<endl;
	while(fio.read((char*)&S,sizeof(S)))
	{
		int posi=fio.tellg();
        cout<<S.Name();
		cout<<" | ";
		cin>>presence;
		S.markAttendance(code, date, presence);
		fio.seekg(posi-sizeof(S));
		fio.write((char*)&S,sizeof(S));
	}
	fio.close();
}

void showAttendance(int a = 0)
{
	int flag=0;
	ifstream fin;
	fin.open("Students.dat",ios::in|ios::binary);

    if(a==0)
    {
		cout<<"Enter Admission Number : ";
		cin>>a;
    }

    int code;
	system("cls");
	cout<<"Subjects\n";
	cout<<"0. Web Technology\n";
	cout<<"1. Discreet Math\n";
	cout<<"2. Computer Organization and Architecture\n";
	cout<<"3. Operating System\n";
	cout<<"4. Object Oriented Programming\n";
	cout<<"5. Environmental Science\n";
	cout<<"6. Organizational Behaviour\n";
	cout<<"Enter your choice  : ";
	cin>>code;
	system("cls");


	while(fin.read((char*)&S,sizeof(S)))
	{
		if(a==S.Admno())
		{
			cout<<"The Attendance of Admission No. "<<a<<" :\n";
			S.displayAttendance(code);
			flag++;
		}
	}
	fin.close();
	if(flag==0)
		cout<<"The Admission No. "<<a<<" not found....\n\n";
	cout<<"\n\nData Reading from File Successfully Done....\n";
}

void generateReport()
{
	int a, flag=0;
	ifstream fin;
	fin.open("Students.dat",ios::in|ios::binary);
	cout<<"Enter Admission Number : ";
	cin>>a;

	system("cls");
	while(fin.read((char*)&S,sizeof(S)))
	{
		if(a==S.Admno())
		{
			cout<<"The Attendance Report of Admission No. "<<a<<" :\n";
			S.report();
			flag++;
		}
	}
	fin.close();
	if(flag==0)
		cout<<"The Admission No. "<<a<<" not found....\n\n";
	cout<<"\n\nData Reading from File Successfully Done....\n";
}

void adminMenu()
{
	int ch;
	do
	{
		system("cls");
		cout<<"======================================================\n";
		cout<<"..............ATTENDANCE MANAGEMENT SYSTEM............\n";
		cout<<"======================================================\n";
		cout<<"Logged in as "<<loggedA.Name()<<"."<<endl;
		cout<<endl;
		cout<<"1. Read Student File\n";
		cout<<"2. Read Faculty File\n";
		cout<<"3. Search Student Data\n";
		cout<<"4. Search Faculty Data\n";
		cout<<endl;
		cout<<"5. Read Attendance\n";
		cout<<"6. Generate Attendance Report\n";
		cout<<endl;
        cout<<"7. Register New Student\n";
        cout<<"8. Register New Faculty\n";
        cout<<"9. Delete A Student\n";
        cout<<"10. Delete A Faculty\n";
        cout<<endl;
        cout<<"0. Log Out\n"<<endl;
		cout<<"Enter your choice  : ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
			case 1: displaySData(); break;
			case 2: displayFData(); break;
			case 3: searchSData(); break;
			case 4: searchFData(); break;
			case 5: showAttendance(); break;
			case 6: generateReport(); break;
			case 7: writeSData(); break;
			case 8: writeFData(); break;
			case 9: deleteSData(); break;
			case 10: deleteFData(); break;
		}
		if(ch)
            system("pause");

	}while(ch);
}

void facultyMenu()
{
	int ch;
	do
	{
		system("cls");
		cout<<"======================================================\n";
		cout<<"..............ATTENDANCE MANAGEMENT SYSTEM............\n";
		cout<<"======================================================\n";
		cout<<"Logged in as "<<loggedF.Name()<<"."<<endl;
		cout<<endl;
		cout<<"1. Read Student File\n";
		cout<<"2. Read Faculty File\n";
		cout<<"3. Search Student Data\n";
		cout<<"4. Search Faculty Data\n";
		cout<<endl;
		cout<<"5. Take Attendance\n";
		cout<<"6. Read Attendance\n";
		cout<<"7. Generate Attendance Report\n";
		cout<<endl;
		cout<<"0. Log Out\n"<<endl;
		cout<<"Enter your choice  : ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
			case 1: displaySData(); break;
			case 2: displayFData(); break;
			case 3: searchSData(); break;
			case 4: searchFData(); break;
			case 5: takeAttendance(); break;
			case 6: showAttendance(); break;
			case 7: generateReport(); break;
		}
		if(ch)
            system("pause");

	}while(ch);
}

void studentMenu()
{
	int ch;
	do
	{
		system("cls");
		cout<<"======================================================\n";
		cout<<"..............ATTENDANCE MANAGEMENT SYSTEM............\n";
		cout<<"======================================================\n";
		cout<<"Logged in as "<<loggedS.Name()<<"."<<endl;
		cout<<endl;
		cout<<"1. Read Student File\n";
		cout<<"2. Read Faculty File\n";
		cout<<"2. Search Student Data\n";
		cout<<"4. Search Faculty Data\n";
		cout<<endl;
		cout<<"5. Read Attendance\n";
		cout<<endl;
		cout<<"0. Log Out\n"<<endl;
		cout<<"Enter your choice  : ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
			case 1: displaySData(); break;
			case 2: displayFData(); break;
			case 3: searchSData(); break;
			case 4: searchFData(); break;
			case 5: showAttendance(loggedS.Admno()); break;
		}
		if(ch)
            system("pause");

	}while(ch);
}

void reset()
{
    string uname, password;
    system("cls");
    cout<<"======================================================\n";
    cout<<"..............ATTENDANCE MANAGEMENT SYSTEM............\n";
    cout<<"======================================================\n";

    cout<<"Enter Admin Username:";
    cin>>uname;
    cout<<"Enter password:";
    cin>>password;

    ifstream fin;
    fin.open("Admin.dat",ios::in|ios::binary);
    fin.read((char*)&A,sizeof(A));
    fin.close();
    if(uname == A.Uname() && password == A.Password())
    {
        remove("Admin.dat");
        remove("Faculty.dat");
        remove("Students.dat");
        remove("TrashStud.dat");
        remove("TrashFac.dat");
        cout<<"\nFactory Reset successful. You may now exit the program.\n\n";
    }
    else
		cout<<"\nInvalid Credentials!\n\n";
    system("pause");
}

void auth()
{
    string uname, password;
	char AFS;

    system("cls");
    cout<<"======================================================\n";
    cout<<"..............ATTENDANCE MANAGEMENT SYSTEM............\n";
    cout<<"======================================================\n";

    cout<<"Enter Username:";
    cin>>uname;
    cout<<"Enter password:";
    cin>>password;
    cout<<"Admin, Faculty or Student?(a/f/s):";
    cin>>AFS;

    int flag=0;
    ifstream fin;

    if(AFS == 'a')
    {
        fin.open("Admin.dat",ios::in|ios::binary);

        while(fin.read((char*)&A,sizeof(A)))
        {
            if(uname == A.Uname() && password == A.Password())
            {
                loggedA.enterData(A.Name(),A.Uname(),A.Password());
                flag++;
                adminMenu();
            }
        }

    }

    else if(AFS=='f')
    {
        fin.open("Faculty.dat",ios::in|ios::binary);

        while(fin.read((char*)&F,sizeof(F)))
        {
            if(uname == F.Uname() && password == F.Password())
            {
                loggedF.enterData(F.Id(),F.Name(),F.Uname(),F.Password(),F.Code());
                flag++;
                facultyMenu();
            }
        }

    }

    else if(AFS=='s')
    {
        fin.open("Students.dat",ios::in|ios::binary);

        while(fin.read((char*)&S,sizeof(S)))
        {
            if(uname == S.Uname() && password == S.Password())
            {
                loggedS.enterData(S.Admno(),S.Name(),S.Uname(),S.Password());
                flag++;
                studentMenu();
            }
        }

    }
    else
        cout<<"Wrong Choice!\n";

    fin.close();
	if(flag==0)
		cout<<"Log in Failed!\n";
    system("pause");
}

void logout()
{
    string dummy = "dummy";
    loggedF.enterData(-1,dummy,dummy,dummy,-1);
    loggedS.enterData(-1,dummy,dummy,dummy);
    loggedA.enterData(dummy,dummy,dummy);
}

void main_menu()
{
    int ch;
    do
    {
        system("cls");
        cout<<"======================================================\n";
        cout<<"..............ATTENDANCE MANAGEMENT SYSTEM............\n";
        cout<<"======================================================\n";
        cout<<"1. Login\n";
        cout<<"2. Factory Reset\n";
        cout<<"0. Exit\n"<<endl;
        cout<<"Enter your choice  : ";

        while(!(cin>>ch))
        {
            cout<<"Bad Value!\n";
            cout<<"Enter your choice  : ";
            cin.clear();
            cin.ignore();
        }

        switch(ch)
        {
            case 1:
                auth();
                logout();
                break;
            case 2:
                reset();
                break;
        }

    }while(ch);
}


void admin()
{
    ifstream file;
    file.open("Admin.dat");
    if (file.fail())
    {
        cout<<"This is the first time this program has been opened.\n";
        A.askData();

        ofstream fout;
        fout.open("Admin.dat",ios::binary|ios::out|ios::app);
        fout.write((char*)&A,sizeof(A));
        fout.close();
    }
    else
        file.close();
}

void createSubjects()
{
    sublist[0].name = "Web Technology";
    sublist[0].subcode = "PCC-CSE-201G";

    sublist[1].name = "Discreet Math";
    sublist[1].subcode = "PCC-CSE-202G";

    sublist[2].name = "Computer Organization and Architecture";
    sublist[2].subcode = "PCC-CSE-204G";

    sublist[3].name = "Operating Systems";
    sublist[3].subcode = "PCC-CSE-206G";

    sublist[4].name = "Object Oriented Programming";
    sublist[4].subcode = "PCC-CSE-208G";

    sublist[5].name = "Environmental Science";
    sublist[5].subcode = "MC-106G";

    sublist[6].name = "Organizational behaviour";
    sublist[6].subcode = "HSMC-02G";
}


int main()
{
    admin();
    createSubjects();
    main_menu();
    return 0;
}
