#include <iostream>
#include <iomanip>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsMainScreen.h"

using namespace std;


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

    clsMainScreen::StartBankSystem();

    return 0;
}
