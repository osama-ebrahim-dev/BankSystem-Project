#pragma once

#include <iostream>
#include <string>
#include "clsPerson.h"
#include <fstream>
#include "clsString.h"
#include "vector"


using namespace std;

const string FileName = "BankClients.txt";


class clsBankClient : public clsPerson
{
public:
	enum enState { Empty, Loaded };
private:

	string _AccountNumber;
	string _PinCode;
	double _Balance;
	enState _State;

private:
	static clsBankClient _ConvertLineToClient(string Line)
	{
		vector<string>vFields = clsString::vSplit(Line, "#//#");
		return clsBankClient(enState::Loaded, vFields[0], vFields[1], vFields[2], vFields[3], vFields[4], vFields[5], stod(vFields[6]));
	}
	static clsBankClient _EmptyClient()
	{
		return clsBankClient(enState::Empty, "", "", "", "", "", "", 0);
	}
public:

	clsBankClient(enState State, string FirstName, string LastName, string Email, string Phone ,string AccountNumber , string PinCode, double Balance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_State = State;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_Balance = Balance;
	}

	void SetState(enState State)
	{
		_State = State;
	}
	enState GetState()
	{
		return _State;
	}

	string GetAccountNumber()
	{
		return _AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}

	double GetBalance()
	{
		return _Balance;
	}


public:

	static clsBankClient Find(string AccountNumber)
	{
		fstream File;

		File.open(FileName, ios::in);

		if (File.is_open())
		{
			string Line = "";
			
			while (getline(File, Line))
			{
				clsBankClient Client = _ConvertLineToClient(Line);

				if (Client._AccountNumber == AccountNumber)
				{
					File.close();
					return Client;
				}
			}

		}
		File.close();
		return _EmptyClient();

	}


	bool IsFound()
	{
		return (_State != enState::Empty);
	}


	static bool IsFound(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);
		return Client.IsFound();
	}


	void Print()
	{
		cout << "\nClient Card : ";
		cout << "\n________________________________";
		cout << "\nFirstName   : " << GetFirstName();
		cout << "\nLastName    : " << GetLastName();
		cout << "\nFull Name   : " << GetFirstName() + " " + GetLastName();
		cout << "\nEmail       : " << GetEmail();
		cout << "\nPhone       : " << GetPhone();
		cout << "\nAcc. Number : " << _AccountNumber;
		cout << "\nPassword    : " << _PinCode;
		cout << "\nBalance     : " << _Balance;
		cout << "\n________________________________\n";
	}


};

