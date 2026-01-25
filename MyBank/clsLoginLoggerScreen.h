#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsAuditLogger.h"
#include "clsMessages.h"

using namespace std;


class clsLoginLoggerScreen : public clsScreen
{
private:

	static void _DrawTableHeader()
	{
		cout << string(75, '_') << "\n\n";

		cout << "|" << setw(30) << left << "Date/Time of login"
			<< "|" << setw(15) << left << "Username"
			<< "|" << setw(10) << left << "Password"
			<< "|" << setw(12) << left << "Permissions"
			<< '\n';

		cout << string(75, '_') << '\n';

	}
	static void _PrintOneLogin(clsAuditLogger::stLoginRecord LoginRecord)
	{
		cout << "|" << setw(30) << left << LoginRecord.Date_Time
			<< "|" << setw(15) << left << LoginRecord.Username
			<< "|" << setw(10) << left << LoginRecord.Password
			<< "|" << setw(12) << left << LoginRecord.Permission
			<< '\n';

	}

public:

	static void ShowLoginLoggerScreen()
	{

		if (!clsSession::DoesCurrentUserHavePermission(clsBankUser::enPermissions::LoginLogger))
		{
			clsMessages::ShowAccessDeniedMessage();
			return;
		}

		vector<clsAuditLogger::stLoginRecord> vLogins = clsAuditLogger::GetAllSuccessLogins();
		int NumberOfLogins = vLogins.size();

		string title = "Login logger";
		string Subtitle = to_string(NumberOfLogins) + " record(s).";

		DrawScreenHeader(title, Subtitle);
		_DrawTableHeader();

		if (NumberOfLogins == 0)
		{
			cout << "\t\t\t\t\tNo logins Yet .";
			cout << string(75, '_') << '\n';
			return;

		}

		for (clsAuditLogger::stLoginRecord& Login : vLogins)
		{
			_PrintOneLogin(Login);
		}
		cout << string(75, '_') << "\n\n";

	}
};

