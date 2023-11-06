//? A basic project in C++

//HEADER FILE USED IN PROJECT
#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include<conio.h>
using namespace std;

// CLASS USED IN PROJECT

class account
{
	int Account_No;
	char Account_Holder_Name[44];
	char type;
	int Deposit_Amount;
public:
	void Open_account();	//function to get data from user
	void Display_account() const;	//function to show data on screen
	void Update();	//function to add new data
	void dep(int);	//function to accept amount and add to balance amount
	void Withdraw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int Return_Account_Number() const;	//function to return account number
	int Return_Deposit_Amount() const;	//function to return balance amount
	char Return_type() const;	//function to return type of account
};         //class ends here


void account::Display_account() const
{
	cout << " Please! Enter the account No. : " << Account_No << endl;
	cout << " Account Holder Name : ";
	cout << Account_Holder_Name << endl;
	cout << " Type of Account : " << type << endl;
	cout << " Balance amount : " << Deposit_Amount << endl;
}
void account::Open_account()
{
	cout <<"Account Number should be of 9 digits only"<<endl;
	cout<<" Please! Enter the account No. :";
	cin>>Account_No;
	cout<<" Please! Enter the name of the account Holder : ";
	cin.ignore();
	cin.getline(Account_Holder_Name,44);
	cout<<" Please! Enter type of the account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<" Please! Enter the initial amount you want to add (Can't be less than Rs.2000) : ";
	cin>>Deposit_Amount;
	cout<<"  Account Created..";
}



	
void account::dep(int x)

{
	Deposit_Amount += x;
}
	
void account::Withdraw(int x)
{
	Deposit_Amount-=x;
}
	
void account::report() const
{
	cout<<Account_No<<setw(10)<<" "<<Account_Holder_Name<<setw(10)<<" "<<type<<setw(6)<<Deposit_Amount<<endl;
}

void account::Update()
{
	cout << " Please! Enter the account No. : " << Account_No << endl;
	cout<<" Update Account Holder Name : ";
	cin.ignore();
	cin.getline(Account_Holder_Name,44);
	cout<<" Update Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<" Update Balance amount : ";
	cin>>Deposit_Amount;
}
	
int account::Return_Account_Number() const
{
	return Account_No;
}


char account::Return_type() const
{
	return type;
}
int account::Return_Deposit_Amount() const
{
	return Deposit_Amount;
}

//function declaration

void delete_account(int);	//function to delete record of file
void display_all();		//function to display all account details
void write_account();	//function to write record in binary file
void display_sp(int);	//function to display account details given by user
void Deposit_Amount_withWithdraw(int, int); // function to deposit/withWithdraw amount for given account
void intro();	//introductory screen function
void Update_account(int);	//function to Update record of file
//THE MAIN FUNCTION OF PROGRAM

int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"  \t\t---MAIN MENU---"<<endl;
		cout<<" \t\t01. NEW ACCOUNT"<<endl;
		cout<<" \t\t02. DEPOSIT AMOUNT"<<endl;
		cout<<" \t\t03. WITHDRAW AMOUNT"<<endl;
		cout<<" \t\t04. BALANCE ENQUIRY"<<endl;
		cout<<" \t\t05. ALL ACCOUNT HOLDER LIST"<<endl;
		cout<<" \t\t06. CLOSE AN ACCOUNT"<<endl;
		cout<<" \t\t07. UPDATE AN ACCOUNT"<<endl;
		cout << " \t\t08. EXIT" << endl << endl;
		cout << " \t\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<" \t\tPlease! Enter the account No. : "; cin>>num;
			Deposit_Amount_withWithdraw(num, 1);
			break;
		case '3':
			cout<<" \t\tPlease! Enter the account No. : "; cin>>num;
			Deposit_Amount_withWithdraw(num, 2);
			break;
		case '4': 
			cout<<" \t\tPlease! Enter the account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<" \t\tPlease! Enter the account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<" \t\tPlease! Enter the account No. : "; cin>>num;
			Update_account(num);
			break;
		 case '8':
			cout<<" \t\t** Thanks for using Our Banking System **";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}
//function to write in file

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.Open_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//function to read specific record from file

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<" BALANCE DETAILS ";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.Return_Account_Number()==n)
		{
			ac.Display_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<" Account number does not exist";
}


//function to Update record of file

void Update_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.Return_Account_Number()==n)
		{
			ac.Display_account();
			cout<<" Please! Enter The New Details of account: "<<endl;
			ac.Update();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<" \t\t Record Updated";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"  Record Not Found ";
}

//function to delete record of file

void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.Return_Account_Number()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<" \t\tRecord Deleted ..";
}

//function to display all accounts Deposit_Amount list

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h> // for getch()
using namespace std;

void display_all()
{
    const string PASSWORD = "admin";  // define the password constant
    string input_password;
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\nEnter password to view account holder list: ";
    
    // Loop until the user hits the Enter key
    char ch;
    while ((ch = getch()) != '\r') { // \r is the Enter key
        input_password.push_back(ch); // add the character to the password
        cout << "*"; // display an asterisk instead of the character
    }
    
    if (input_password != PASSWORD) {
        cout << "\nIncorrect password. Access denied.\n";
        return;
    }
    cout << "\n\n\t\t\t\tACCOUNT HOLDER LIST\n";
    cout << "*********************************************************\n";
    cout << "A/c no.      NAME           Type  Balance\n";
    cout << "*********************************************************\n";
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(account)))
    {
        ac.report();
    }
    inFile.close();
}



//  	function to Deposit_Amount and withWithdraw amounts


void Deposit_Amount_withWithdraw(int n, int option)
{
	int Amount;
	bool found=false;
	account ac;
	fstream File;
	File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.Return_Account_Number()==n)
		{
			ac.Display_account();
			if(option==1)
			{
				cout<<"\n\t\tTO DEPOSIT AMOUNT ";
				cout<<"\nPlease! Enter the amount to deposit: ";
				cin>>Amount;
				ac.dep(Amount);
			}
			if(option==2)
			{
				cout<<"\n\t\tTO WITHDRAW AMOUNT ";
				cout<<"\nPlease! Enter The amount to withdraw: ";
				cin>>Amount;
				int bal=ac.Return_Deposit_Amount()-Amount;
				if((bal<440 && ac.Return_type()=='S') || (bal<1000 && ac.Return_type()=='C'))
					cout<<"Insufficience balance";
				else
					ac.Withdraw(Amount);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\t\t Record Updated";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n Record Not Found ";
}



//INTRODUCTION FUNCTION

void intro()
{
	cout<<"****************************************************************************"<<endl;
	cout<<"  \t\t*  BANK";
	cout<<"\tMANAGEMENT";
	cout << " SYSTEM *" << endl;
	cout<<"****************************************************************************"<<endl;


	cout<<" DEV :      Upendra Raj Joshi and Aagaman KC"<<endl;
	cout<<" COLLEGE :  Pashchimanchal Campus (IOE),Lamachaur,Pokhara,Nepal"<<endl;
	cin.get();
}