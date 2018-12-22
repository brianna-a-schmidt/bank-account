#----------------------------------------------------------------------------
#
#FILE NAME:         Makefile
#DESCRIPTION:       Compiles and makes C++ file with executable desginated by the CPP file
#PURPOSE:	    Build a program executable on Linux

#MODIFICATION HISTORY:

#Author             Date           Modification(s)
#----------------   -----------    ---------------
#Brianna Schmidt    2018-01-30     Version 1.0
#Brianna Schmidt    2018-02-20     Version 2.0 - added makefile dependencies
#-----------------------------------------------------------------------------

#	This generic makefile command builds any stand alone ".cpp" source file.
#	e.g make bankacct
.cpp :
	g++ -o $* $*.cpp -std=c++11

#	This will build the files that have dependencies on .h files
#	make -f Makefile bankacct

bankacct : bankacct.h
bankacct_v1 : bankacct_v1.h
bankacct_v2 : bankacct_v2.h
bankacct_v3 : bankacct_v3.h
bankacct_v4 : bankacct_v4.h
bankacct_v5 : bankacct_v5.h
bankacct_v6 : bankacct_v6.h
bankacct_v7 : bankacct_v7.h
bankacct_v8 : bankacct_v8.h
bankacct_v9 : bankacct_v9.h
bankacct_v10 : bankacct_v10.h
