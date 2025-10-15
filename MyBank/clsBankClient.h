#pragma once

#include <iostream>
#include <string>
#include "clsPerson.h"
#include <fstream>
#include "clsString.h"
#include "vector"
#include "clsInputValidate.h"


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
	string _ConvertToLine()
	{
		string Delimiter = "#//#";

		return GetFirstName() + Delimiter + GetLastName() + Delimiter + GetEmail() + Delimiter
			+ GetPhone() + Delimiter + _AccountNumber + Delimiter + _PinCode + Delimiter + to_string(_Balance);
	}
	static clsBankClient _EmptyClient()
	{
		return clsBankClient(enState::Empty, "", "", "", "", "", "", 0);
	}
	static vector <clsBankClient> _LoadDataFromFileToVector()
	{
		fstream File;
		vector <clsBankClient> vClients;
		string Line = "";

		File.open(FileName, ios::in);

		if (File.is_open())
		{
			while (getline(File, Line))
			{
				vClients.push_back(_ConvertLineToClient(Line));
			}
			File.close();
		}
		return vClients;
	}
	static void _SaveVectorToFile(vector <clsBankClient> vClients)
	{

		fstream File;
		File.open(FileName, ios::out);

		if (File.is_open())
		{
			for (clsBankClient& Client : vClients)
			{
				File << Client._ConvertToLine() << endl;
			}
			File.close();
		}
		
	}
	void _UpdateInVector(vector <clsBankClient> & vClients)
	{
		for (clsBankClient& Client : vClients)
		{
			if (Client._AccountNumber == _AccountNumber)
			{
				Client = (*this);
				break;
			}
		}
	}
	void _Update()
	{
		vector <clsBankClient> vClients = _LoadDataFromFileToVector();

		_UpdateInVector(vClients);

		_SaveVectorToFile(vClients);

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


	string ToString()
	{
		string ClientCard = "";

		ClientCard += "\nFirstName   : " + GetFirstName();
		ClientCard += "\nLastName    : " + GetLastName();
		ClientCard += "\nFull Name   : " + GetFirstName() + " " + GetLastName();
		ClientCard += "\nEmail       : " + GetEmail();
		ClientCard += "\nPhone       : " + GetPhone();
		ClientCard += "\nAcc. Number : " + _AccountNumber;
		ClientCard += "\nPassword    : " + _PinCode;
		ClientCard += "\nBalance     : " + to_string(_Balance);

		return ClientCard;
	}


	bool Save()
	{
		if (IsFound())
		{
			_Update();
			return true;
		}
		else
		{
			return false;
		}
				 
	}


};

