#pragma once

#include "iostream"
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"

using namespace std;


class clsUpdateUserScreen : public clsScreen
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

        Confirm = clsInputValidate::ReadChar("\nLogin logger (y/n) : ");
        if (Confirm == 'Y' || Confirm == 'y')
        {
            Permission += int(clsBankUser::enPermissions::LoginLogger);
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

    static bool UpdateClient()
    {
        DrawScreenHeader("Updating User");

        string UserName = clsInputValidate::ReadString("Enter Username : ");

        while (!clsBankUser::IsUserFound(UserName))
        {
            UserName = clsInputValidate::ReadString("invalid Username ,Enter a valid Username : ");
        }

        clsBankUser User = clsBankUser::Find(UserName);

        cout << User.ToString() << endl;

        char Confirm = clsInputValidate::ReadChar("\nAre you sure to update this User (y/n) : ");

        if (Confirm == 'Y' || Confirm == 'y')
        {

            _ReadUserInfo(User);

            clsBankUser::enSaveResult SaveResult = User.Save();

            switch (SaveResult)
            {
            case clsBankUser::enSaveResult::svSucceeded:
                cout << "\n\nUser Updated successfully.\n";
                cout << User.ToString() << '\n';
                return true;
            case clsBankUser::enSaveResult::svFailed_EmptyUser:
                cout << "Failed to update User (its an empty User).";
                return false;
            case clsBankUser::enSaveResult::svFailed_UserNotExists:
                cout << "Failed to update User (User not exists).";
                return false;
            default:
                cout << "Failed to update User .";
                return false;
            }
        }
        else
        {
            cout << "Update operation has been cancelled.\n";
            return false;
        }
    }

};

