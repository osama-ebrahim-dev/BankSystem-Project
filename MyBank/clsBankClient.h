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
	enum enState { Empty, Update, Add };
private:

	string _AccountNumber;
	string _PinCode;
	double _Balance;
	enState _State;

private:
	static clsBankClient _ConvertLineToClient(string Line)
	{
		vector<string>vFields = clsString::vSplit(Line, "#//#");
		return clsBankClient(enState::Update, vFields[0], vFields[1], vFields[2], vFields[3], vFields[4], vFields[5], stod(vFields[6]));
	}
	string _ConvertToLine()
	{
		string Delimiter = "#//#";

		return GetFirstName() + Delimiter + GetLastName() + Delimiter + GetEmail() + Delimiter
			+ GetPhone() + Delimiter + _AccountNumber + Delimiter + _PinCode + Delimiter + to_string(_Balance);
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
	static void _AddClientToFile(string ClientAsLine)
	{
		fstream File;
		File.open(FileName, ios::out | ios::app);
		if (File.is_open())
		{
			File << ClientAsLine << endl;
		}
		File.close();
	}
	void _Update()
	{
		vector <clsBankClient> vClients = _LoadDataFromFileToVector();

		_UpdateInVector(vClients);

		_SaveVectorToFile(vClients);

	}
	void _AddNew()
	{

		string ClientAsLine = (*this)._ConvertToLine();

		_AddClientToFile(ClientAsLine);

		_State = enState::Update;

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

	void SetBalance(double Balance)
	{
		_Balance = Balance;
	}
	double GetBalance()
	{
		return _Balance;
	}


public:
	
	static clsBankClient EmptyClient()
	{
		return clsBankClient(enState::Empty, "", "", "", "", "", "", 0);
	}


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
		return EmptyClient();

	}


	bool IsFound()
	{
		return (_State == enState::Update);
	}


	static bool IsFound(string AccountNumber)
	{
		clsBankClient Client = Find(AccountNumber);

		return Client.IsFound();
	}


	string ToString()
	{
		string ClientCard = "";

		ClientCard += "\n---------------------------";
		ClientCard += "\nFirstName   : " + GetFirstName();
		ClientCard += "\nLastName    : " + GetLastName();
		ClientCard += "\nFull Name   : " + GetFirstName() + " " + GetLastName();
		ClientCard += "\nEmail       : " + GetEmail();
		ClientCard += "\nPhone       : " + GetPhone();
		ClientCard += "\nAcc. Number : " + _AccountNumber;
		ClientCard += "\nPassword    : " + _PinCode;
		ClientCard += "\nBalance     : " + to_string(_Balance);
		ClientCard += "\n---------------------------";

		return ClientCard;
	}


	bool IsEmpty()
	{
		return (_State == enState::Empty);
	}



	enum enSaveState { Updated, Added, svFailed_EmptyClient , svFailed_ClientNotExists , svFailed_ClientExists};


	enSaveState Save()
	{

		switch (_State)
		{
		case clsBankClient::Empty:
			return svFailed_EmptyClient;
		case clsBankClient::Update:
			if(IsFound(_AccountNumber))
			{
				_Update();
				return enSaveState::Updated;
			}
			else
			{
				return enSaveState::svFailed_ClientNotExists;
			}
		case clsBankClient::Add:
			if (!IsFound(_AccountNumber))
			{
				_AddNew();
				return enSaveState::Added;
			}
			else
			{
				return enSaveState::svFailed_ClientExists;
			}
		default:
			return svFailed_EmptyClient;
		}
 
	}


};

