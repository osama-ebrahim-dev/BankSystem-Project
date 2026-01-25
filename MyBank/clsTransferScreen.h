#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsAuditLogger.h"

using namespace std;


class clsTransferScreen : public clsScreen
{

private:
	static void _PrintMiniClientCard(clsBankClient Client)
	{
		cout << "\nFull Name   : " << Client.GetFirstName() + " " + Client.GetLastName();
		cout << "\nAcc. Number : " << Client.GetAccountNumber();
		cout << "\nBalance     : " << Client.GetBalance() << endl << endl;

	}

public:

	static bool Transfer()
	{

		DrawScreenHeader("Transfer screen");



		string SourceAccount = clsInputValidate::ReadString("Enter account number to transfer from : ");

		clsBankClient SourceClient = clsBankClient::Find(SourceAccount);

		while (!SourceClient.IsActive())
		{
			SourceAccount = clsInputValidate::ReadString("Enter valid account number to transfer from : ");
			SourceClient = clsBankClient::Find(SourceAccount);
		}
		_PrintMiniClientCard(SourceClient);




		string DestinationAccount = clsInputValidate::ReadString("Enter account number to transfer to : ");

		clsBankClient DestinationClient = clsBankClient::Find(DestinationAccount);

		while (!DestinationClient.IsActive())
		{
			DestinationAccount = clsInputValidate::ReadString("Enter valid account number to transfer to : ");
			DestinationClient = clsBankClient::Find(DestinationAccount);
		}
		_PrintMiniClientCard(DestinationClient);



		double TransferAmount = clsInputValidate::ReadDoubleNumber("Enter tranfer amount : ");

		while (TransferAmount > SourceClient.GetBalance())
		{
			TransferAmount = clsInputValidate::ReadDoubleNumber("Amount exceeds the balance, Enter another amount : ");
		}

		char Confirm = clsInputValidate::ReadChar("Are you sure you want to perform this operation (y/n) : ");

		if (Confirm == 'n' || Confirm == 'N')
		{
			cout << "Operation has been cancelled .\n";
			return false;
		}
		else
		{
			if (SourceClient.TransferTo(TransferAmount, DestinationClient))
			{
				clsAuditLogger::LogTransfer(SourceClient, TransferAmount, DestinationClient);
				cout << "Transfer done successfully .\n";
			}
			else
			{
				cout << "Operation failed .\n";
				return false;
			}
		}

		cout << "Source client : \n";
		_PrintMiniClientCard(SourceClient);

		cout << "Destination client : \n";
		_PrintMiniClientCard(DestinationClient);

		return true;
	}

};

