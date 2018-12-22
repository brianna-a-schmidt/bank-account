/*------------------------------------------------------------------------------ 
 NAME:         bankacct.cpp
 DESCRIPTION:       A program that allows manipulation of a bank account database
 USAGE:             ./bankacct
 COMPILER:          GNU g++ compiler on Linux
 NOTES:
 
 MODIFICATION HISTORY:
 Author             Date               Version
 ---------------    ----------         --------------
 Brianna Schmidt    2018-02-15         1.0 - made create() and display() to test working with structures
 Brianna Schmidt	2018-02-16		   1.1 - switched cout with ostream object
 Brianna Schmidt    2018-02-20		   2.0 - added if else to main for command line and interactive mode as well as main menu
 Brianna Schmidt	2018-02-20		   3.0 - began work with command line arguments
 Brianna Schmidt    2018-02-23		   3.1 - worked with array of structures
 Brianna Schmidt    2018-03-02		   3.2 - got check arg to work in combo with I/O from Lab 4
 Brianna Schmidt    2018-03-04		   4.0 - COMMAND LINE WORKS!!!!!! for one function, that is...
 Brianna Schmidt	2018-03-05		   5.0 - working on more command line stuff
 Brianna Schmidt	2018-03-05		   6.0 - working on even more command line stuff with any order
 Brianna Schmidt	2018-03-06		   7.0 - got some functions working in any order, but others not
 Brianna Schmidt	2018-03-07		   8.0 - did even further work on commands in any order
 Brianna Schmidt	2018-03-08		   9.0 - COMMAND LINE ANY ORDER! REPORT FILE! INTERACTIVE MODE NOT BROKEN! HALLELJUJAH
 										   - Leftovers: Transfer, error messages in wrong place, some final clean up, close acct
 Brianna Schmidt	2018-03-08		   10.0 - wrapped up some left overs, other just broke it more 
 									   (interactive mode transfer and displays errors when there isn't one are still broken)
----------------------------------------------------------------------------- */

#include "bankacct.h"

//NEED TO FIX HEADER FILE 
/* -----------------------------------------------------------------------------
 FUNCTION:          main()
 DESCRIPTION:       controller for the code I guess ADD MORE LATER
 RETURNS:           0
 NOTES:				if statement to switch between command line and interactive
 					int argc                //number of parameters on command line
                    char *argv[]            //an array of pointers to C-strings
 ------------------------------------------------------------------------------- */
int main(int argc, char * argv[])
{
	bool flag = true;
	int num_acct = 0;	//This is what you will access with output so you don't print a bajillion blank accounts
    account* user = new account[100];
    char opt;
    char* value;
	char* file_cl;
	char file_i[20+1];
	int temp = 99;
	bool success = false;
	bool over = false;
	
	if (argc > 1)
	{
		file_cl = file_scan(argc, argv, user, num_acct, opt, value, temp, success);
		output(user, num_acct, file_cl);
	}
	else
		{
			cout << "Please enter input file: ";
			cin >> file_i;
			read_file(file_i, user, num_acct);
			while (flag)
		{

			switch (MainMenu())
			{
				case 'a':
					create(user, cout, cin, 1, num_acct);
					break;
				case 'b':
					login(user, temp, 1, value);
					verify_account(user, temp, num_acct, success);
					if (success) display(user, cout, temp, 1);
					break;
				case 'c':
					login(user, temp, 1, value);
					verify_account(user, temp, num_acct, success);
					if (success) deposit(user, temp);
					break;
				case 'd':
					login(user, temp, 1, value);
					verify_account(user, temp, num_acct, success);
					if (success) withdraw(user, temp);
					break;
				case 'e':
					//withdraws first account, but not second account
					login(user, temp, 1, value);
					verify_account(user, temp, num_acct, success);
					if (success) transfer(user, temp, 1, over);
					if(!over)
					{
						temp = 99;
						login(user, temp, 1, value);
						verify_account(user, temp, num_acct, success);
						if (success) 
							transfer(user, temp, 0, over);
					}
					break;
				case 'f':
					login(user, temp, 1, value);
					verify_account(user, temp, num_acct, success);
					if (success)
						close_account(user, num_acct, temp);
					break;
				case 'g':
					report(user, num_acct, value);
					break;
				case 'q':
					if (num_acct)
					{ 
					output(user, num_acct, file_i);
					cout << "Data saved to " << file_i << endl;
					}
					flag = false;
					cout << "Goodbye!" << endl << endl;
			}
		}
		cout << endl;
    	cout << "Programmed by: " << PROGRAMMER_NAME << " -- ";
    	cout << __DATE__ << "  " __TIME__ << endl;
    	cout << endl;
	}

	delete[] user;
	
   
    
    return 0;
}
/*-----------------------------------------------------------------------------

FUNCTION NAME:     void read_file
PURPOSE:           read in file as designated by command line
RETURNS:           nothing
NOTES:             
----------------------------------------------------------------------------- */
/* 
void read_file(char* file, account* user, int &num_acct, bool io)
{
	fstream dbfile;
	dbfile.open(file, fstream::in | fstream::out);
	if (io)
	{
	if (!dbfile)
		cout << "\nError opening file: " << file << "\n\n";
	else
	{
		cout << "Input file: " << file << endl;
		while(dbfile)	//won't proceed if end of file WHY DOES THIS WORK
		{
		create(user, cout, dbfile, 0, num_acct); 
		}
		--num_acct;
		cout << "Accounts read: " << num_acct << endl;
	}
	}
	else
	{
		for (int i = 0; i < num_acct; i++)
 		{
 			display(user, dbfile, i, 0);
 		}
	}
	dbfile.close();

}
 */
 void read_file(char* file, account* user, int &num_acct)
{
	ifstream infile(file);

	if (!infile)
		cout << "\nError opening file: " << file << "\n\n";
	else
	{
		cout << "Input file: " << file << endl;
		while(infile)	//won't proceed if end of file WHY DOES THIS WORK
		{
		create(user, cout, infile, 0, num_acct); 
		}
		infile.close();
		--num_acct;
		cout << "Accounts read: " << num_acct << endl;
	}

}
/* -----------------------------------------------------------------------------
FUNCTION:          MainMenu()
DESCRIPTION:       interactive mode home base
RETURNS:           char choice
NOTES:
----------------------------------------------------------------------------- */
char MainMenu()
{
	char choice;

	cout << endl << endl;
	cout << "-----------------------------------------------\n";
	cout << "	Welcome to the Bank of Free Puppies!\n		MAIN MENU	\n";
	cout << "----------------------------------------------- " << endl;
	cout << endl << endl;
	cout << "	a. Create Account                               " << endl;
	cout << "	b. Display Account                            " << endl;
	cout << "	c. Deposit                          " << endl;
	cout << "	d. Withdraw                               " << endl;
	cout << "	e. Transfer                               " << endl;
	cout << "	f. Close Account (Coming Soon)                              " << endl;
	cout << "	g. Generate Report (Coming Soon)                              " << endl;
	cout << "	q. Quit the program " << endl;
	cout << endl << endl;
	cout << "-----------------------------------------------\n";
	cout << "	Enter your choice [ a - g, q ]:";
	cin >> choice;
	cout << "----------------------------------------------- " << endl << endl;
	cout << endl << endl;

	if (choice >= 'a' && choice <= 'g')
	{
		cout << "You entered: '" << choice << "'." << endl;
	}
	else if (choice == 'q')
		cout << "You entered: '" << choice << "', to quit program." << endl;
	else
	{
		cout << "You did not enter 'a', 'b', 'c', 'd', 'e', 'f', 'g', or 'q'." << endl;
		cout << "Please try again." << endl;
	}
	cout << endl;

	return choice;
}
/* -----------------------------------------------------------------------------
FUNCTION:          check_arg()
DESCRIPTION:       checks command line args
RETURNS:           Nothing
NOTES:				char* arg
----------------------------------------------------------------------------- */
char* check_arg(char arg[], int argc, account* user, int &num_acct, char &opt)
{	
	char buf[100];
	const char SLASH = '/';
	char valid_options[] = "?ACDFILMNOPRSTW";
	char* p = valid_options;
	char* value;
	
	bool first_char = arg[0] == SLASH; 	//Test 1st argument's first character

	bool second_char = false;

	for (; *p != 0; ++p) 				//Test 1st arg's 2nd character
	{
		second_char = arg[1] == *p;
		if (second_char == true) 
			break;
	}

	if (!first_char || !second_char)
		cout << "Invalid argument" << endl;

	else
	{
	opt = *p;

	if (arg[2] != 0)
	{
	strcpy(buf, arg+2);
	value = (arg+2);		//= arg+2?
	}
	}
	return value;
}

/* -----------------------------------------------------------------------------
 FUNCTION:          void create()
 DESCRIPTION:       creates a bank account
 RETURNS:           Nothing
 NOTES:             Use ostream object instead of cout/cin
 					Can I use a loop instead of asking for each individual input?
 					Array of structures
 ------------------------------------------------------------------------------- */

void create(account* user, ostream &out, istream &in, bool mode, int &num_acct)
{
    if (mode) 
    	out << "Last Name? ";
    in >> user[num_acct].lname;	
    if (mode) 
    	out << "First Name? ";
    in >> user[num_acct].fname;
    if (mode) 
    	out << "Middle Initial? ";
    in >> user[num_acct].mi;
    if (mode) 
    	out << "Social Security Number? ";
    in >> user[num_acct].ssn;
    if (mode) 
    	out << "Phone Number? ";
    in >> user[num_acct].phone;
    if (mode) 
    	out << "Balance? ";
    in >> user[num_acct].bal;
    if (mode) 
    	out << "Account Number? ";
    in >> user[num_acct].acctnum;
    if (mode) 
    	out << "Password? ";
    in >> user[num_acct].acctpass;
    num_acct++;
}
/* -----------------------------------------------------------------------------
 FUNCTION:          void display()
 DESCRIPTION:       displays account info
 RETURNS:           Nothing
 NOTES:             Use ostream object instead of cout/cin
 					Does this one really need pass by ref? Copy should be fine.
 					//ident
 ------------------------------------------------------------------------------- */

void display(account* user, ostream &out, int num_acct, bool mode)
{
	out << setprecision(2) << fixed;
	if (mode) 
		cout << endl;
    if (mode) 
    	cout << "Last Name: ";
    out << user[num_acct].lname << endl;
    if (mode) 
    	cout << "First Name: ";
    out << user[num_acct].fname << endl;
    if (mode) 
    	cout << "Middle Initial: ";
    out << user[num_acct].mi << endl;
    if (mode) 
    	cout << "Social Security Number: ";
    out << user[num_acct].ssn << endl;
    if (mode) 
    	cout << "Phone Number: ";
    out << user[num_acct].phone << endl;
    if (mode) 
    	cout << "Balance: ";
    out << user[num_acct].bal << endl;
    if (mode) 
    	cout << "Account Number: ";
    out << user[num_acct].acctnum << endl;
    if (mode) 
    	cout << "Password: ";
    out << user[num_acct].acctpass << endl;
    out << endl;
}
/* -----------------------------------------------------------------------------
 FUNCTION:          void output()
 DESCRIPTION:       puts array of structures to output file
 RETURNS:           Nothing
 NOTES:             
 ------------------------------------------------------------------------------- */
 void output(account* user, int num_acct, char* file)
 {
 	ofstream outfile;
 	outfile.open(file);
 	for (int i = 0; i < num_acct; i++)
 	{
 		display(user, outfile, i, 0);
 	}
 	outfile.close();
 }
/*-----------------------------------------------------------------------------
FUNCTION NAME:     void file_scan()
PURPOSE:           parses command line for file to open
RETURNS:           Nothing (void function)
NOTES:             Need to write to file but OMG IT KINDA HECKA WORKS
----------------------------------------------------------------------------- */
 char* file_scan(int argc, char* argv[], account* user, int &num_acct, char &opt, char* value, int &temp, bool success)
 {
 char* file;
 int count_a = 0;
 int count_p = 0;
 for (int i = 0; i < argc; ++i)
	{
		if (i) 
		{
			value = check_arg(argv[i], argc, user, num_acct, opt);
 
			if (opt == 'O')	//argv[i] = "/OTestDB.txt *p = "O"
			{
					file = value;
					read_file(value, user, num_acct);	//call from commands???
				if (count_a == 1 || count_p == 1)	//or do we just store separate?
					{
						--temp;
					}
			}
			
			if (opt =='?')		//run nothing else
				helpmenu();
		}
	}
for (int i = 0; i < argc; ++i)
	{
		if (i) 
		{
			value = check_arg(argv[i], argc, user, num_acct, opt);
 			{
				switch(opt)
				{	
					case 'A':
						if(count_a == 0)
						{
						strcpy(user[temp].acctnum, value);
						count_a++;
						}
						else
						{
						strcpy(user[temp-1].acctnum, value);
						}
						break;
					case 'P':
						if(count_p == 0)
						{
						strcpy(user[temp].acctpass, value);
						count_p++;
						}
						else
						{
						strcpy(user[temp-1].acctpass, value);
						}
						break;
					case 'R':
						report(user, num_acct, value);
				}
			}
		}
	}
verify_account(user, temp, num_acct, success);
if (!success) 
	cout << "No match found in database. Please try again, or type /? for help menu." << endl;
else
{
	
	for (int i = 0; i < argc; ++i)
	{
		if (i) 
		{
			value = check_arg(argv[i], argc, user, num_acct, opt);
 
			switch(opt)
			{
			
				case 'L':
					strcpy(user[temp].lname, value);
					break;
				case 'F':
					strcpy(user[temp].fname, value);
					break;
				case 'M':
					user[temp].mi = *value;
					break;
				case 'S':
					strcpy(user[temp].ssn, value);
					break;
				case 'N':
					strcpy(user[temp].phone, value);
					break;
				case 'D':
					user[temp].bal += atof(value);
					break;
				case 'W':
					user[temp].bal -= atof(value);
					break;
				case 'C':
					strcpy(user[temp].acctpass, value);
					break;
				case 'T':
					user[temp].bal -= atof(value);
					user[temp-1].bal += atof(value);
				case 'I':
					display(user, cout, temp, 0);
			}
		}
	}
}
return file;
}
/*-----------------------------------------------------------------------------
FUNCTION NAME:     void helpmenu()
PURPOSE:           displays help for batch mode
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
 void helpmenu()
 {
 	cout << endl << endl;
	cout << " -------------------------------------------------------------------------------------------------\n";
	cout << "					HELP MENU													   \n";
	cout << " -------------------------------------------------------------------------------------------------" << endl;
	cout << endl << endl;
	cout << "/? - display help menu						" << "        " << "/L - set last name (/LSmith)    			" << endl;
	cout << "/W - withdraw (/W1245.67)					" << "        " << "/F - set first name (/FJohn)	  			" << endl;
	cout << "/D - Deposit (/D200.00)					" << "        " << "/M - set middle initial (/MJ)   			" << endl;
	cout << "/C - create password (/Cabc123)			" << "        " << "/S - set social security number (/S12345 " << endl;
	cout << "/T - transfer (/T345.60 - need 2 accts		" << "        " << "/N - set phone number (/N(775)777-6666)  " << endl;
	cout << "/I - show account info (/I)				" << "        " << "/A - account number (/Ac123a)*   		" << endl;
	cout << "/R - generate report file					" << "        " << "/P - account password (/Pz52c42)*		" << endl;
	cout << "/O - open database file			   		" << "        												" << endl;
	cout << " ------------------------------------------------------------------------------------------------ " << endl;
 }
/*-----------------------------------------------------------------------------
FUNCTION NAME:     void login()
PURPOSE:           asks for account number and password
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
 void login(account* user, int temp, bool mode, char* value)
 {
 	if (mode) 
 	{
 	cout << "Account number? ";
 	cin >> user[temp].acctnum;
 	cout << "Account password?";
 	cin >> user[temp].acctpass;
 	}
 	else
 	{
 	strcpy(user[temp].acctnum, value);
 	strcpy(user[temp].acctpass, value);
 	}
 }
/*-----------------------------------------------------------------------------
FUNCTION NAME:     void verify_account()
PURPOSE:           verifies account number and password
RETURNS:           Nothing (void function)
NOTES:             success doesn't actually work for some reason???
----------------------------------------------------------------------------- */
 void verify_account(account* user, int &temp, int num_acct, bool &success)
 {	
 	for (int i = 0; i < num_acct; i++)
 	{
 		if (!strcmp(user[i].acctnum, user[temp].acctnum) && !strcmp(user[i].acctpass, user[temp].acctpass))
 		{
 			cout << user[i].acctnum << " " << user[i].acctpass << endl;
 			success = true;
 			temp = i;
 			break;
 		}
	}
	cout << success << endl;
/* 
	if (!success)
	{
		cout << "ARE WE IN HERE??? " << endl;
		error('A');
 	}
 */
 }
/*-----------------------------------------------------------------------------
FUNCTION NAME:     void deposit()
PURPOSE:           makes a deposit
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void deposit(account* user, int temp)
{
	float deposit;
	cout << "How much would you like to deposit?" << endl;
	cin >> deposit;
	user[temp].bal += deposit;
	cout << "New balance: " << user[temp].bal << endl;
}
/*-----------------------------------------------------------------------------
FUNCTION NAME:     withdraw()
PURPOSE:           makes a withdrawal
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void withdraw(account* user, int temp)
{
	float withdraw;
	cout << "How much would you like to withdraw?" << endl;
	cin >> withdraw;
	if (withdraw < user[temp].bal)
		{
		user[temp].bal -= withdraw;
		cout << "New balance: " << user[temp].bal << endl;
		}
	else
			error('O');
}
/*-----------------------------------------------------------------------------
FUNCTION NAME:     transfer()
PURPOSE:           makes a transfer
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void transfer(account* user, int temp, bool mode, bool &over)
{
	float transfer;
	cout << setprecision(2) << fixed;
	if (mode)
	{
		cout << "How much would you like to transfer?" << endl;
		cin >> transfer;
		if (user[temp].bal - transfer > 0)
		{
		cout << temp << endl;
		user[temp].bal -= transfer;
		cout << "New balance: " << user[temp].bal << endl;
		cout << temp << endl;
		}
		else
		{
			cout << temp << endl;
			over = true;
			error('O');
		}
	}
	else if (!mode)
	{
		cout << temp << endl;
		user[temp].bal += transfer;
		cout << "New balance: " << user[temp].bal << endl;
	}
}
/* 
void transfer(account* user, int temp, char fromto)
{
	float transfer;
	if (fromto == 'F')
	{
		cout << "How much would you like to transfer from " << user[temp].fname << "'s account?" << endl;
		cin >> transfer;
		if(transfer > user[temp].bal)
			error('O');
		else
		{
			user[temp].bal -= transfer;
			cout << "New balance: " << user[temp].bal << endl;
		}
	}
	if (fromto == 'T')
	{
		user[temp].bal += transfer;
		cout << "New balance: " << user[temp].bal << endl;
	}
}
 */
/*-----------------------------------------------------------------------------
FUNCTION NAME:     void report()
PURPOSE:           generates report file
RETURNS:           Nothing (void function)
NOTES:             formatting not perfect
----------------------------------------------------------------------------- */
void report(account* user, int num_acct, char* file)
{
	ofstream outfile;
 	if (file) outfile.open(file);
 	else outfile.open("BankAcct.Rpt");
 	outfile << "-------" << setw(4) << " " << "----" << setw(4) << " " << "-----" << setw(4) << " " << "--" << setw(4) << " " << "-----------" << setw(4) << " " << "-------------" << setw(4) << " " << "---------" << endl;
 	outfile << "Account" << setw(4) << " " << "Last" << setw(4) << " " << "First" << setw(4) << " " << "MI" << setw(4) << " " << "SS         " << setw(4) << " " << "Phone        " << setw(4) << " " << "Account  " << endl;
 	outfile << "Number " << setw(4) << " " << "Name" << setw(4) << " " << "Name " << setw(4) << " " << "  " << setw(4) << " " << "Number     " << setw(4) << " " << "Number       " << setw(4) << " " << "Balance  " << endl;
 	outfile << "-------" << setw(4) << " " << "----" << setw(4) << " " << "-----" << setw(4) << " " << "--" << setw(4) << " " << "-----------" << setw(4) << " " << "-------------" << setw(4) << " " << "---------" << endl;
	for (int i = 0; i < num_acct; i++)
	{
		outfile << left << setprecision(2) << fixed;
		outfile << setw(8) << user[i].acctnum << setw(4) << " " << user[i].lname << setw(4) << " " << user[i].fname <<  setw(4) << " " << user[i].mi << setw(4) << " " << user[i].ssn <<  setw(4) << " "  << user[i].phone <<  setw(4) << " "  << user[i].bal << endl;
	}
	outfile.close();
}
/*-----------------------------------------------------------------------------
FUNCTION NAME:     void error()
PURPOSE:           spits out error messages
RETURNS:           Nothing (void function)
NOTES:             
----------------------------------------------------------------------------- */
void error(char code)
{
	cout << "ERROR CODE VALUE: " << code << endl;
	switch(code)
	{
		case 'F':
			cout << "Error opening file, please try again." << endl;
			break;
		case 'A':
			cout << "Error accessing account, please try again." << endl;
			break;
		case 'O':
			cout << "Not enough funds in account. Procedure cancelled." << endl;
			break;
	}
}
/*-----------------------------------------------------------------------------
FUNCTION NAME:     void close_account()
PURPOSE:           close an account
RETURNS:           Nothing (void function)
NOTES:             OMG IT WORKS WHAT
----------------------------------------------------------------------------- */
void close_account(account* user, int &num_acct, int temp)
{
	//delete user[temp];
	// strcpy(user[temp].lname, NULL);	
//     strcpy(user[temp].fname, NULL);
//     user[temp].mi = NULL;
//     strcpy(user[temp].ssn, NULL);
//     strcpy(user[temp].phone, NULL);
//     strcpy(user[temp].acctnum, NULL);					
//     strcpy(user[temp].acctpass, NULL);
	
	for (int i = temp; i < num_acct; i++)
	{
		strcpy(user[i].lname, user[i+1].lname);	
    	strcpy(user[i].fname, user[i+1].fname);
    	user[i].mi = user[i+1].mi;
    	strcpy(user[i].ssn, user[i+1].ssn);
    	strcpy(user[i].phone, user[i+1].phone);
    	strcpy(user[i].acctnum, user[i+1].acctnum);					
    	strcpy(user[i].acctpass, user[i+1].acctpass);	
	}
	--num_acct;
}
