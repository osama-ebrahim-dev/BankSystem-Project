#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

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

    clsBankClient Client = clsBankClient::GetNewClient(AccountNumber);

    
    ReadNewClientInfo(Client);


    clsBankClient::enSaveState SaveResult = Client.Save();


    switch (SaveResult)
    {
    case clsBankClient::Added:
        cout << "\n\nClient Added successfully.\n";
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

bool DeleteClient()
{
    cout << "Deleting client.\n\n";

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
        if(clsBankClient::Delete(AccountNumber))
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

void PrintOneClient(clsBankClient Client)
{
    cout << "|" << setw(15) << left << Client.GetAccountNumber()
        << "|" << setw(22) << left << Client.GetFirstName() + " " + Client.GetLastName()
        << "|" << setw(14) << left << Client.GetPhone()
        << "|" << setw(25) << left << Client.GetEmail()
        << "|" << setw(10) << left << Client.GetPinCode()
        << "|" << setw(10) << left << Client.GetBalance()
        << '\n';
}

void DisplayClientsList()
{
    vector <clsBankClient> vClients = clsBankClient::GetClients();

    cout << "\t\t\t\t\tclient list (" << vClients.size() << ") client(s).\n";

    cout << string(110, '_') << "\n\n";

    cout << "|" << setw(15) << left << "Account Number"
        << "|" << setw(22) << left << "Client Name"
        << "|" << setw(14) << left << "Phone"
        << "|" << setw(25) << left << "email"
        << "|" << setw(10) << left << "pin code"
        << "|" << setw(10) << left << "Balance"
        << '\n';
        
    cout << string(110, '_') << '\n';

    if (vClients.size() == 0)
    {
        cout << "\t\t\t\t\tNo clients Found .";
        cout << string(110, '_') << '\n';
        return;
    }

    for (clsBankClient& Client : vClients)
    {
        PrintOneClient(Client);
    }
    cout << string(110, '_') << '\n';

}

void PrintOneClientBalance(clsBankClient Client)
{
    cout << "|" << setw(15) << left << Client.GetAccountNumber()
        << "|" << setw(22) << left << Client.GetFirstName() + " " + Client.GetLastName()
        << "|" << setw(10) << left << Client.GetBalance()
        << '\n';

}

void DisplayBalancesList()
{
    vector <clsBankClient> vClients = clsBankClient::GetClients();

    cout << "\t\tclient list (" << vClients.size() << ") client(s).\n";

    cout << string(60, '_') << "\n\n";

    cout << "|" << setw(15) << left << "Account Number"
        << "|" << setw(22) << left << "Client Name"
        << "|" << setw(10) << left << "Balance"
        << '\n';

    cout << string(60, '_') << '\n';

    if (vClients.size() == 0)
    {
        cout << "\t\t\t\t\tNo clients Found .";
        cout << string(60, '_') << '\n';
        return;
    }

    for (clsBankClient& Client : vClients)
    {
        PrintOneClientBalance(Client);
    }
    cout << string(60, '_') << '\n';

    double TotalBalances = clsBankClient::GetTotalBalances();

    cout << "\t\tTotal balances = " << TotalBalances << '\n';
    cout << "\t\t" << clsUtil::numberToWords(TotalBalances) << '\n';


}

int main()
{
    DisplayBalancesList();

    return 0;
}
