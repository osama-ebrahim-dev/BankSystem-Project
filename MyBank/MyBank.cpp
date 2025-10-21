#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

void ReadUpdatedClientInfo(clsBankClient& Client)
{

    Client.SetFirstName(clsInputValidate::ReadString("\nEnter FirstName : "));

    Client.SetLastName(clsInputValidate::ReadString("\nEnter LastName: "));

    Client.SetEmail(clsInputValidate::ReadString("\nEnter Email: "));

    Client.SetPhone(clsInputValidate::ReadString("\nEnter Phone: "));

    Client.SetPinCode(clsInputValidate::ReadString("\nEnter PinCode : "));

}

void UpdateClient()
{
	string AccountNumber = clsInputValidate::ReadString("Enter account number : ");

	while (!clsBankClient::IsFound(AccountNumber))
	{
		AccountNumber = clsInputValidate::ReadString("invalid acc. number ,Enter a valid account number : ");
	}

    clsBankClient Client = clsBankClient::Find(AccountNumber);

    cout << Client.ToString() << endl;

    ReadUpdatedClientInfo(Client);

    Client.Save();

    cout << Client.ToString() << endl;
}

void ReadNewClientInfo(clsBankClient& Client)
{
    Client.SetFirstName(clsInputValidate::ReadString("\nEnter FirstName : "));

    Client.SetLastName(clsInputValidate::ReadString("\nEnter LastName: "));

    Client.SetEmail(clsInputValidate::ReadString("\nEnter Email: "));

    Client.SetPhone(clsInputValidate::ReadString("\nEnter Phone: "));

    Client.SetPinCode(clsInputValidate::ReadString("\nEnter PinCode : "));

    Client.SetBalance(clsInputValidate::ReadDoubleNumber("\nEnter Balance : "));

}

void AddClient()
{
    cout << "Adding new client.\n\n";

    string AccountNumber = clsInputValidate::ReadString("Enter account number : ");


    while (clsBankClient::IsFound(AccountNumber))
    {
        AccountNumber = clsInputValidate::ReadString("Enter a non-exist account number : ");
    }


    clsBankClient Client(clsBankClient::enState::Add, "", "", "", "", AccountNumber, "", 0);

    
    ReadNewClientInfo(Client);


    clsBankClient::enSaveState SaveResult = Client.Save();

    
    switch (SaveResult)
    {
    case clsBankClient::Added:
        cout << "Client Added successfully.\n";
        cout << Client.ToString();
        break;
    case clsBankClient::svFailed_EmptyClient:
        cout << "Failed to add client (its an empty client).";
        break;
    case clsBankClient::svFailed_ClientExists:
        cout << "Failed to add client (client already exists).";
        break;
    default:
        cout << "Failed to add client .";
        break;
    }



}


int main()
{

    AddClient();

    return 0;
}
