#pragma once
#include "iostream"
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsWithdrawScreen : public clsScreen
{

public :

	static bool WithDraw()
	{
        DrawScreenHeader("Withdraw screen");

        string AccountNumber = clsInputValidate::ReadString("Enter account number : ");

        while (!clsBankClient::IsFound(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadString("invalid acc. number ,Enter a valid account number : ");
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        cout << Client.ToString() << endl;

        double Amount = clsInputValidate::ReadDoubleNumber("Enter Withdraw amount : ");

        char Confirm = clsInputValidate::ReadChar("\nAre you sure you want to perform this transaction (y/n) : ");

        if (Confirm == 'Y' || Confirm == 'y')
        {
            if (Client.WithDraw(Amount))
            {
                cout << "The transaction was completed successfully.\n";
                cout << "New balance is : " << Client.GetBalance() << '\n';
                Client.Save();
                return true;
            }
            else
            {
                cout << "Transaction Failed . \n";
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

