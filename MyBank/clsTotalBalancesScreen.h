#pragma once

#include "iostream"
#include "clsScreen.h"
#include "clsBankClient.h"
#include "iomanip"
#include "clsUtil.h"

using namespace std;

class clsTotalBalancesScreen :public clsScreen
{

private:
    static void PrintOneClientBalance(clsBankClient Client)
    {
        cout << "|" << setw(15) << left << Client.GetAccountNumber()
            << "|" << setw(22) << left << Client.GetFirstName() + " " + Client.GetLastName()
            << "|" << setw(10) << left << Client.GetBalance()
            << '\n';

    }


public:
                
	static void DisplayTotalBalancesScreen()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClients();

		string Title = "Balances list";
		string SubTitle = "client list (" + to_string(vClients.size()) + ") client(s).";

		DrawScreenHeader(Title, SubTitle);

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

};

