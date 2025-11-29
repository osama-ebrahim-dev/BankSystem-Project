#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankUser.h"
#include "iomanip"


using namespace std;


class clsListUsersScreen : public clsScreen
{
private:
	static void _PrintOneUser(clsBankUser User)
	{
		cout << "|" << setw(15) << left << User.GetUserName()
			<< "|" << setw(22) << left << User.GetFirstName() + " " + User.GetLastName()
			<< "|" << setw(14) << left << User.GetPhone()
			<< "|" << setw(25) << left << User.GetEmail()
			<< "|" << setw(10) << left << User.GetPassword()
			<< "|" << setw(14) << left << User.GetPermission()
			<< '\n';
	}

public:
	static void DisplayUsersList()
	{
		vector <clsBankUser> vUsers = clsBankUser::GetUsers();

		string Title = "Users list";
		string SubTitle = "User list (" + to_string(vUsers.size()) + ") User(s).";

		DrawScreenHeader(Title, SubTitle);

		cout << string(110, '_') << "\n\n";

		cout<< "|" << setw(15) << left << "UserName"
			<< "|" << setw(22) << left << "Full Name"
			<< "|" << setw(14) << left << "Phone"
			<< "|" << setw(25) << left << "email"
			<< "|" << setw(10) << left << "Password"
			<< "|" << setw(14) << left << "Permission"
			<< '\n';

		cout << string(110, '_') << '\n';

		if (vUsers.size() == 0)
		{
			cout << "\t\t\t\t\tNo Users Found .";
			cout << string(110, '_') << '\n';
			return;
		}

		for (clsBankUser& User : vUsers)
		{
			_PrintOneUser(User);
		}
		cout << string(110, '_') << '\n';


	}
};

