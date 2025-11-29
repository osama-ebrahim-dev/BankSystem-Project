#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"


using namespace std;


class clsAddNewUserScreen : public clsScreen
{

private:

    static int _ReadPermissions()
    {
        int Permission = 0;

        cout << "\n\n(Permissions.....)\n\n";

        char Confirm = clsInputValidate::ReadChar("\nDo you want to give full access (y/n) : ");
        if (Confirm == 'Y' || Confirm == 'y')
        {
            return int(clsBankUser::enPermissions::All);
        }

        Confirm = clsInputValidate::ReadChar("\nShow Client List (y/n) : ");
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permission += int(clsBankUser::enPermissions::ListClients);
        }

        Confirm = clsInputValidate::ReadChar("\nAdd new Client (y/n) : ");
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permission += int(clsBankUser::enPermissions::AddNewClient);
        }

        Confirm = clsInputValidate::ReadChar("\nDelete Client (y/n) : ");
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permission += int(clsBankUser::enPermissions::DeleteClient);
        }

        Confirm = clsInputValidate::ReadChar("\nUpdate Client (y/n) : ");
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permission += int(clsBankUser::enPermissions::UpdateClient);
        }

        Confirm = clsInputValidate::ReadChar("\nFind Client (y/n) : ");
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permission += int(clsBankUser::enPermissions::FindClient);
        }

        Confirm = clsInputValidate::ReadChar("\nTransactions (y/n) : ");
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permission += int(clsBankUser::enPermissions::Tranactions);
        }

        Confirm = clsInputValidate::ReadChar("\nManage Users (y/n) : ");
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permission += int(clsBankUser::enPermissions::ManageUsers);
        }

        if (Permission == int(clsBankUser::enPermissions::Total))
        {
            return int(clsBankUser::enPermissions::All);
        }

        return Permission;

    }

    static void _ReadUserInfo(clsBankUser& User)
    {
        User.SetFirstName(clsInputValidate::ReadString("\nEnter FirstName : "));

        User.SetLastName(clsInputValidate::ReadString("\nEnter LastName: "));

        User.SetEmail(clsInputValidate::ReadString("\nEnter Email: "));

        User.SetPhone(clsInputValidate::ReadString("\nEnter Phone: "));

        User.SetPassword(clsInputValidate::ReadString("\nEnter Password : "));

        User.SetPermission(_ReadPermissions());

    }

public:

	static bool AddUser()
	{
        DrawScreenHeader("Adding new User");

        string UserName = clsInputValidate::ReadString("Enter User Name : ");


        while (clsBankUser::IsUserFound(UserName))
        {
            UserName = clsInputValidate::ReadString("Enter a non-exist User name : ");
        }


        clsBankUser User = clsBankUser::GetNewUser(UserName);


        _ReadUserInfo(User);


        clsBankUser::enSaveResult SaveResult = User.Save();

        switch (SaveResult)
        {
        case clsBankUser::enSaveResult::svSucceeded:
            cout << "\n\nUser Added successfully.\n";
            cout << User.ToString() << '\n';
            return true;
        case clsBankUser::enSaveResult::svFailed_EmptyUser:
            cout << "Failed to add User (its an empty User).";
            return false;
        case clsBankUser::enSaveResult::svFailed_UserExists:
            cout << "Failed to add User (User already exists).";
            return false;
        default:
            cout << "Failed to add User .";
            return false;
        }

	}

};

