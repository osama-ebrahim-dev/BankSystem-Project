#pragma once

#include "iostream"
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"
#include "clsSession.h"
#include "clsAuditLogger.h"


using namespace std;


class clsLoginScreen : public clsScreen
{
private:
public:

	static bool Login()
	{
			system("cls");
			DrawScreenHeader("Login screen");

			clsBankUser User = clsBankUser::GetEmptyUser();
			string Username = "";
			string Password = "";
			int Trials = 3;
			bool IsUserNotValid = true;
			do
			{

				Username = clsInputValidate::ReadString("Enter Username : ");

				Password = clsInputValidate::ReadString("Enter Password : ");
				

				User = clsBankUser::Find(Username, Password);

				IsUserNotValid = User.IsEmpty();

				if (IsUserNotValid)
				{
					Trials--;
					cout << "\n\nInvalid Username/Password . \n";
					cout << "\n\nYou have " << Trials << " Trial(s) to login .\n\n";
					if (Trials == 0)
					{
						cout << "\n\nYou are locked after 3 failed trials . \n\n";
						return false;
					}
				}

			} while (IsUserNotValid);

			clsAuditLogger::LogLoginSuccess(User);
			system("cls");
			clsSession::StartSession(User);
			return true;
	}


};

