#pragma once

#include "iostream"
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteUserScreen : public clsScreen
{
public:
    static bool DeleteUser()
    {

        DrawScreenHeader("Deleting User");

        string UserName = clsInputValidate::ReadString("Enter User name : ");


        while (!clsBankUser::IsUserFound(UserName))
        {
            UserName = clsInputValidate::ReadString("User does not exist ! ,Enter User name : ");
        }

        clsBankUser User = clsBankUser::Find(UserName);

        cout << User.ToString();

        char Confirm = clsInputValidate::ReadChar("\nAre you sure to delete this User (y/n) : ");

        if (Confirm == 'Y' || Confirm == 'y')
        {
            if (clsBankUser::Delete(UserName))
            {
                cout << "User has been deleted successfully.\n";
                return true;
            }
            else
            {
                cout << "error occurred . User Was not Deleted\n";
                return false;
            }
        }
        else
        {
            cout << "Delete operation has been cancelled.\n";
            return false;
        }



    }

};

