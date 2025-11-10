#pragma once

#include "iostream"
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;


class clsFindClientScreen : public clsScreen
{

public:

	static bool FindClient()
	{
        DrawScreenHeader("Find client");

        string AccountNumber = clsInputValidate::ReadString("Enter account number : ");

        while (!clsBankClient::IsFound(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadString("invalid acc. number ,Enter a valid account number : ");
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        if (!Client.IsEmpty())
        {
            cout << "\n\nClient is found .\n\n";
            cout << Client.ToString();
            return true;
        }
        else
        {
            cout << "\n\nClient is empty . \n\n";
            return false;
        }

	}

};

