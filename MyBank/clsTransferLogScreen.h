#pragma once

#include <iostream>
#include <string>
#include "clsScreen.h"
#include "clsAuditLogger.h"

using namespace std;

class clsTransferLogScreen : public clsScreen
{
private:

	static void _DrawTableHeader()
	{
		cout << string(100, '_') << "\n\n";

		cout << "|" << setw(30) << left << "Date/Time of transfer"
			<< "|" << setw(10) << left << "S.Account"
			<< "|" << setw(10) << left << "D.Account"
			<< "|" << setw(10) << left << "Amount"
			<< "|" << setw(10) << left << "S.Balance"
			<< "|" << setw(10) << left << "D.Balance"
			<< "|" << setw(15) << left << "Username"
			<< '\n';

		cout << string(100, '_') << '\n';

	}

	static void _PrintOneTransfer(clsAuditLogger::stTransferRecord Record)
	{
		cout << "|" << setw(30) << left << Record.Date_Time
			<< "|" << setw(10) << left << Record.SourceAccount
			<< "|" << setw(10) << left << Record.DestinationAccount
			<< "|" << setw(10) << left << Record.TransferAmount
			<< "|" << setw(10) << left << Record.SourceBalance
			<< "|" << setw(10) << left << Record.DestinationBalance
			<< "|" << setw(15) << left << Record.UserName
			<< '\n';

	}

public:

	static void ShowTransferLog()
	{
		vector <clsAuditLogger::stTransferRecord> vTransfers = clsAuditLogger::GetAllTransfers();
		
		string title = "transfer log screen";
		string Subtitle = to_string(vTransfers.size()) + " record(s).";


		DrawScreenHeader(title, Subtitle);

		_DrawTableHeader();

		if (vTransfers.size() == 0)
		{
			cout << "\t\t\t\t\tNo Transfers Yet .";
			cout << string(100, '_') << '\n';
			return;
		}

		for (clsAuditLogger::stTransferRecord& Transfer : vTransfers)
		{
			_PrintOneTransfer(Transfer);
		}
		cout << string(100, '_') << '\n';


	}
};

