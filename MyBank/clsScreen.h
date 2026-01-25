#pragma once

#include <iostream>
#include "clsSession.h"


using namespace std;

class clsScreen
{
protected:

	static void DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << "-------------------------------------------\n";
		cout << "               " << Title << '\n';
		if (SubTitle != "")
		{
			cout << "               " << SubTitle << '\n';
		}
		cout << "-------------------------------------------\n";
		cout << "User : " << clsSession::GetSessionUser().GetUserName() << endl;
		cout << "Date : " << clsUtil::GetTodayDate() << endl << endl;
	}

};

