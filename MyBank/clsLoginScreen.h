#pragma once

#include "iostream"
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"
#include "clsSession.h"


using namespace std;


class clsLoginScreen : public clsScreen
{
private :

public:

	static void Login()
	{
			system("cls");
			DrawScreenHeader("Login screen");

			clsBankUser User = clsBankUser::GetEmptyUser();
			string Username = "";
			string Password = "";
			bool IsUserNotValid = true;
			do
			{

				Username = clsInputValidate::ReadString("Enter Username : ");

				Password = clsInputValidate::ReadString("Enter Password : ");

				User = clsBankUser::Find(Username, Password);

				IsUserNotValid = User.IsEmpty();

				if (IsUserNotValid)
				{
					cout << "Invalid Username/Password . \n\n";
				}

			} while (IsUserNotValid);

			system("cls");
			clsSession::StartSession(User);

	}


};

