#pragma once

#include "iostream"
#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;


class clsUpdateClientScreen : public clsScreen
{

private:
    static void _ReadUpdatedClientInfo(clsBankClient& Client)
    {

        Client.SetFirstName(clsInputValidate::ReadString("\nEnter FirstName : "));

        Client.SetLastName(clsInputValidate::ReadString("\nEnter LastName: "));

        Client.SetEmail(clsInputValidate::ReadString("\nEnter Email: "));

        Client.SetPhone(clsInputValidate::ReadString("\nEnter Phone: "));

        Client.SetPinCode(clsInputValidate::ReadString("\nEnter PinCode : "));

    }


public:
    static bool UpdateClient()
    {
        if (!clsSession::DoesCurrentUserHavePermission(clsBankUser::enPermissions::UpdateClient))
        {
            clsMessages::ShowAccessDeniedMessage();
            return false;
        }


        DrawScreenHeader("Updating client");

        string AccountNumber = clsInputValidate::ReadString("Enter account number : ");

        while (!clsBankClient::IsClientFound(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadString("invalid acc. number ,Enter a valid account number : ");
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);

        cout << Client.ToString() << endl;

        char Confirm = clsInputValidate::ReadChar("\nAre you sure to update this client (y/n) : ");

        if (Confirm == 'Y' || Confirm == 'y')
        {

            _ReadUpdatedClientInfo(Client);

            clsBankClient::enSaveState SaveResult = Client.Save();

            switch (SaveResult)
            {
            case clsBankClient::Updated:
                cout << "\n\nClient Updated successfully.\n";
                cout << Client.ToString() << '\n';
                return true;
            case clsBankClient::svFailed_EmptyClient:
                cout << "Failed to update client (its an empty client).";
                return false;
            case clsBankClient::svFailed_ClientNotExists:
                cout << "Failed to update client (client not exists).";
                return false;
            default:
                cout << "Failed to update client .";
                return false;
            }
        }
        else
        {
            cout << "Update operation has been cancelled.\n";
            return false;
        }
    }


};

