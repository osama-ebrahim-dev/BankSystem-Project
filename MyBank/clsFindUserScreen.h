#pragma once

#include "iostream"
#include "clsScreen.h"
#include "clsBankUser.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindUserScreen : public clsScreen
{
public:

    static bool FindClient()
    {
        DrawScreenHeader("Find user");

        string UserName = clsInputValidate::ReadString("Enter username : ");

        while (!clsBankUser::IsUserFound(UserName))
        {
            UserName = clsInputValidate::ReadString("invalid Username ,Enter a valid Username : ");
        }

        clsBankUser User = clsBankUser::Find(UserName);

        if (User.IsActive())
        {
            cout << "\n\nUser is found .\n\n";
            cout << User.ToString();
            return true;
        }
        else
        {
            cout << "\n\nUser is empty . \n\n";
            return false;
        }

    }

};

