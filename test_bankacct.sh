#!/bin/sh

set -v

./bankacct /?
./bankacct /OBankDB.txt
./bankacct /OBankDB.txt /A1234L /P12345L /LCool
./bankacct /OBankDB.txt /A1234L /P12345L /FJoe
./bankacct /OBankDB.txt /A1234L /P12345L /MQ
./bankacct /OBankDB.txt /A1234L /P12345L /S999-99-9999
./bankacct /OBankDB.txt /A1234L /P12345L /N777-333-3333
./bankacct /OBankDB.txt /A1234L /P12345L /I
./bankacct /OBankDB.txt /A9876L /P98765L /I
./bankacct /OBankDB.txt /A9876L /P98765L /D200.00
./bankacct /OBankDB.txt /A9876L /P98765L /I
./bankacct /OBankDB.txt /A9876L /P98765L /W50.00
./bankacct /OBankDB.txt /A9876L /P98765L /I
./bankacct /OBankDB.txt /A9876L /P98765L /A1234L /P12345L /T500.00
./bankacct /OBankDB.txt /A9876L /P98765L /I
./bankacct /OBankDB.txt /A1234L /P12345L /I
./bankacct /OBankDB.txt /A1234L /P12345L /CZZST0P
./bankacct /OBankDB.txt /A1234L /P12345L /I
./bankacct /OBankDB.txt /A1234L /PZZST0P /I
./bankacct /OBankDB.txt /RBank_Rpt.txt
cat Bank_Rpt.txt

