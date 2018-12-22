#ifndef BANKACCT_H__
#define BANKACCT_H__

/*------------------------------------------------------------------------------
 NAME:        	   bankacct.h
 DESCRIPTION:       A program that allows manipulation of a bank account database
 USAGE:             ./bankacct
 COMPILER:          GNU g++ compiler on Linux
 NOTES:
 
 MODIFICATION HISTORY:
 Author             Date               Version
 ---------------    ----------         --------------
 Brianna Schmidt    2018-02-15         1.0
 Brianna Schmidt    2018-02-20         1.1 - modified for command line args
 Brianna Schmidt	2018-03-01		   1.2 - added functions for output file and modified arguments for create and display
 ----------------------------------------------------------------------------- */

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>

using namespace std;

const char PROGRAMMER_NAME[] = "Bri Schmidt";

#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])

//structure
struct account{
    char lname[20+1];
    char fname[20+1];
    char mi;
    char ssn[20+1];
    char phone[20+1];
    float bal;
    char acctnum[5+1];
    char acctpass[6+1];
};

//function prototypes go here
char MainMenu();
char* check_arg(char arg[], int argc, account* user, int &num_accts, char &opt);
void read_file(char* file, account* s, int &num_acct);
void create(account* user, ostream &out, istream &in, bool mode, int &num_acct);
void display(account* user, ostream &out, int num_acct, bool mode);
void output(account* user, int num_acct, char* file);
void commands(char opt, char* value, account* user, int temp);
char* file_scan(int argc, char* argv[], account* user, int &num_acct, char &opt, char* value, int &temp, bool success);
void helpmenu();
void login(account* user, int temp, bool mode, char* value);
void verify_account(account* user, int &temp, int num_acct, bool &success);
void deposit(account* user, int temp);
void withdraw(account* user, int temp);
void report(account* user, int num_acct, char* file);
void transfer(account* user, int temp, bool mode, bool &over);
void close_account(account* user, int &num_acct, int temp);
void error(char code);

#endif /* BANKACCT_H__ */
