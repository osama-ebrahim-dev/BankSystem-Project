#pragma once

#include "iostream"
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsDeleteClientScreen : public clsScreen
{

public:
    static bool DeleteClient()
    {

        DrawScreenHeader("Deleting client");

        string AccountNumber = clsInputValidate::ReadString("Enter account number : ");


        while (!clsBankClient::IsFound(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadString("Client does not exist ! ,Enter account number : ");
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        cout << Client.ToString();

        char Confirm = clsInputValidate::ReadChar("\nAre you sure to delete this client (y/n) : ");

        if (Confirm == 'Y' || Confirm == 'y')
        {
            if (clsBankClient::Delete(AccountNumber))
            {
                cout << "Client has been deleted successfully.\n";
                return true;
            }
            else
            {
                cout << "error occurred . Client Was not Deleted\n";
                return false;
            }
        }
        else
        {
            cout << "Delete operation has been cancelled.\n";
            return false;
        }



    }


};

