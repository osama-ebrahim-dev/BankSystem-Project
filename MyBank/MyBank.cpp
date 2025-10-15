#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

// here
void ReadUpdatedClientInfo(clsBankClient & Client)
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


int main()
{

    UpdateClient();

    return 0;
}
