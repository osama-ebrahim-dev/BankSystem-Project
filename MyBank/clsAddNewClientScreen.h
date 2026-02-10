#pragma once
#include "iostream"
#include"clsScreen.h"
#include "clsBankClient.h"
#include "clsSession.h"

using namespace std;

class clsAddNewClientScreen :public clsScreen
{
private:
    static void _ReadNewClientInfo(clsBankClient& Client)
    {
        Client.SetFirstName(clsInputValidate::ReadString("\nEnter FirstName : "));

        Client.SetLastName(clsInputValidate::ReadString("\nEnter LastName: "));

        Client.SetEmail(clsInputValidate::ReadString("\nEnter Email: "));

        Client.SetPhone(clsInputValidate::ReadString("\nEnter Phone: "));

        Client.SetPinCode(clsInputValidate::ReadString("\nEnter PinCode : "));

        Client.SetBalance(clsInputValidate::ReadNumber<double>("\nEnter Balance : "));

    }

public:

    static bool AddClient()
    {
        if (!clsSession::DoesCurrentUserHavePermission(clsBankUser::enPermissions::AddNewClient))
        {
            clsMessages::ShowAccessDeniedMessage();
            return false;
        }


        DrawScreenHeader("Adding new client");

        string AccountNumber = clsInputValidate::ReadString("Enter account number : ");


        while (clsBankClient::IsClientFound(AccountNumber))
        {
            AccountNumber = clsInputValidate::ReadString("Enter a non-exist account number : ");
        }

        clsBankClient Client = clsBankClient::GetNewClient(AccountNumber);


        _ReadNewClientInfo(Client);


        clsBankClient::enSaveState SaveResult = Client.Save();


        switch (SaveResult)
        {
        case clsBankClient::Added:
            cout << "\n\nClient Added successfully.\n";
            cout << Client.ToString() << '\n';
            return true;
        case clsBankClient::svFailed_EmptyClient:
            cout << "Failed to add client (its an empty client).";
            return false;
        case clsBankClient::svFailed_ClientExists:
            cout << "Failed to add client (client already exists).";
            return false;
        default:
            cout << "Failed to add client .";
            return false;
        }



    }


};

