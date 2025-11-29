#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"


using namespace std;


class clsManageUsersScreen : public clsScreen
{
private:

	enum class _enManageUsersMenuOptions {
		ListUsers = 1, AddNewUser = 2, DeleteUser = 3,
		UpdateUser = 4, FindUser = 5, MainMenu = 6
	};

private:
	static void _DrawManageUsersMenu()
	{
		DrawScreenHeader("Manage Users Screen");

		cout << "===========================================\n";
		cout << "\t\t  Manage Users Menu\n";
		cout << "===========================================\n";
		cout << "\t[1] List Users.\n";
		cout << "\t[2] Add New User.\n";
		cout << "\t[3] Delete User.\n";
		cout << "\t[4] Update User.\n";
		cout << "\t[5] Find User.\n";
		cout << "\t[6] Main Menu.\n";
		cout << "===========================================\n";
	}

	static _enManageUsersMenuOptions _ReadManageUsersMenuOption()
	{

		int choice = clsInputValidate::ReadIntNumberBetween("Choose what do you want to do [1 to 6] : ", 1, 6);

		return _enManageUsersMenuOptions(choice);

	}

	static void _ListUsers()
	{
		clsListUsersScreen::DisplayUsersList();
	}

	static bool _AddNewUser()
	{
		return clsAddNewUserScreen::AddUser();
	}

	static bool _DeleteUser()
	{
		return clsDeleteUserScreen::DeleteUser();
	}

	static bool _UpdateUser()
	{
		return clsUpdateUserScreen::UpdateClient();
	}

	static bool _FindUser()
	{
		return clsFindUserScreen::FindClient();
	}

	static void _PerformManageUsersMenuOperation(_enManageUsersMenuOptions Choice)
	{
		switch (Choice)
		{
		case clsManageUsersScreen::_enManageUsersMenuOptions::ListUsers:
			_ListUsers();
			break;
		case clsManageUsersScreen::_enManageUsersMenuOptions::AddNewUser:
			_AddNewUser();
			break;
		case clsManageUsersScreen::_enManageUsersMenuOptions::DeleteUser:
			_DeleteUser();
			break;
		case clsManageUsersScreen::_enManageUsersMenuOptions::UpdateUser:
			_UpdateUser();
			break;
		case clsManageUsersScreen::_enManageUsersMenuOptions::FindUser:
			_FindUser();
			break;
		default:
			return;
			break;
		}
	}
public:

	static void StartManageUsersMenu()
	{
		while (true)
		{
			_DrawManageUsersMenu();

			_enManageUsersMenuOptions Choice = _ReadManageUsersMenuOption();

			if (Choice == _enManageUsersMenuOptions::MainMenu)
			{
				return;
			}

			system("cls");

			_PerformManageUsersMenuOperation(Choice);

			system("pause=0");

			system("cls");


		}
	}

};

