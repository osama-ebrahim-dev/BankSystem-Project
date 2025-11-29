#pragma once
#include "iostream"
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsDepositScreen : public clsScreen
{


public :

	static bool Deposit()
	{
        DrawScreenHeader("Deposit screen");

        string AccountNumber = clsInputValidate::ReadString("Enter account number : ");

        while (!clsBankClient::IsClientFound(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadString("invalid acc. number ,Enter a valid account number : ");
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        cout << Client.ToString() << endl;

        double Amount = clsInputValidate::ReadDoubleNumber("Enter deposit amount : ");

        char Confirm = clsInputValidate::ReadChar("\nAre you sure you want to perform this transaction (y/n) : ");

        if (Confirm == 'Y' || Confirm == 'y')
        {
            if (Client.Deposit(Amount))
            {
                cout << "Amount deposited successfully .\n";
                cout << "New balance is : " << Client.GetBalance() << '\n';
                Client.Save();
                return true;
            }
            else
            {
                cout << "Deposit Failed . \n";
                return false;
            }
        }
        else
        {
            cout << "Transaction has been cancelled.\n";
            return false;
        }


	}
};

