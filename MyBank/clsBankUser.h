#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsPerson.h"
#include "clsString.h"
#include "clsUtil.h"



using namespace std;


const string UsersFile = "BankUsers.txt";


class clsBankUser : public clsPerson
{
public:
    enum class enState { Empty, Update, Add };

    enum class enPermissions
    {
        All = -1, ListClients = 1, AddNewClient = 2, DeleteClient = 4,
        UpdateClient = 8, FindClient = 16, Tranactions = 32, ManageUsers = 64
        , LoginLogger = 128
        , None = 0, Total = 255
    };
private:

    enState _State = enState::Empty;
    string _UserName = "";
    string _Password = "";
    int _Permission = 0;
    bool _MarkForDelete = false;

private:
    static clsBankUser _ConvertLineToUser(string Line)
    {
        vector<string>vFields = clsString::vSplit(Line, "#//#");
        return clsBankUser(enState::Update, vFields[0], vFields[1], vFields[2], vFields[3], vFields[4], vFields[5], stoi(vFields[6]));
    }
    static vector <clsBankUser> _LoadUsersFromFileToVector()
    {
        fstream File;
        vector <clsBankUser> vUsers;
        string Line = "";

        File.open(UsersFile, ios::in);

        if (File.is_open())
        {
            while (getline(File, Line))
            {
                vUsers.push_back(_ConvertLineToUser(Line));
            }
            File.close();
        }
        return vUsers;

    }
    bool _UpdateUserInVector(vector <clsBankUser>& vUsers)
    {
        for (clsBankUser& User : vUsers)
        {
            if (User.GetUserName() == _UserName)
            {
                User = (*this);
                return true;
            }
        }
        return false;
    }
    string _ConvertToLine()
    {
        string Delimiter = "#//#";

        return GetFirstName() + Delimiter + GetLastName() + Delimiter + GetEmail() + Delimiter
            + GetPhone() + Delimiter + _UserName + Delimiter + _Password + Delimiter + to_string(_Permission);
    }
    static bool _SaveVectorToFile(vector <clsBankUser>& vUsers)
    {
        fstream File;
        File.open(UsersFile, ios::out);

        if (File.is_open())
        {
            for (clsBankUser& User : vUsers)
            {
                if (User._MarkForDelete == false)
                {
                    File << User._ConvertToLine() << endl;
                }
            }
            File.close();
            return true;
        }
        return false;
    }
    bool _Update()
    {
        vector <clsBankUser> vUsers = _LoadUsersFromFileToVector();

        if (_UpdateUserInVector(vUsers))
        {
            _SaveVectorToFile(vUsers);
            return true;
        }
        return false;
        
    }
    bool _AddNew()
    {
        string UserAsLine = (*this)._ConvertToLine();

        if (clsUtil::AddLineToFile(UserAsLine, UsersFile))
        {
            _State = enState::Update;
            return true;
        }

        return false;
        
    }
    static bool _MarkForDeleteInVector(vector <clsBankUser>& vUsers, string UserName)
    {
        for (clsBankUser& User : vUsers)
        {
            if (User.GetUserName() == UserName)
            {
                User._MarkForDelete = true;
                return true;
            }
        }
        return false;
    }
public:

	clsBankUser(enState State ,string FirstName, string LastName, string Email, string Phone,
		string UserName, string Password, int Permission)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
        _State = State;
		_UserName = UserName;
		_Password = Password;
		_Permission = Permission;
	}


    void SetState(enState State)
    {
        _State = State;
    }
    enState GetState()
    {
        return _State;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }
    string GetUserName()
    {
        return _UserName;
    }

    void SetPassword(string Password)
    {
        _Password = Password;
    }
    string GetPassword()
    {
        return _Password;
    }

    void SetPermission(int Permission)
    {
        _Permission = Permission;
    }
    int GetPermission()
    {
        return _Permission;
    }


public:

    bool IsActive()
    {
        return (_State == enState::Update);
    }

    bool IsEmpty()
    {
        return (_State == enState::Empty);
    }

    static clsBankUser Find(string UserName)
    {
        fstream File;

        File.open(UsersFile, ios::in);

        if (File.is_open())
        {
            string Line = "";

            while (getline(File, Line))
            {
                clsBankUser User = _ConvertLineToUser(Line);

                if (User._UserName == UserName)
                {
                    File.close();
                    return User;
                }
            }

        }
        File.close();
        return GetEmptyUser();

    }

    static clsBankUser Find(string UserName ,string Password)
    {
        fstream File;

        File.open(UsersFile, ios::in);

        if (File.is_open())
        {
            string Line = "";

            while (getline(File, Line))
            {
                clsBankUser User = _ConvertLineToUser(Line);

                if (User._UserName == UserName && User._Password == Password)
                {
                    File.close();
                    return User;
                }
            }
            File.close();
        }
        
        return GetEmptyUser();

    }

    static bool IsUserFound(string UserName)
    {
        clsBankUser User = Find(UserName);
        return User.IsActive();
    }

    enum class enSaveResult { svSucceeded, svFailed_EmptyUser, svFailed_UserExists, svFailed_UserNotExists };

    enSaveResult Save()
    {
        switch (_State)
        {
        case clsBankUser::enState::Empty:
            return enSaveResult::svFailed_EmptyUser;
        case clsBankUser::enState::Update:
            if (IsUserFound(_UserName))
            {
                _Update();
                return enSaveResult::svSucceeded;
            }
            else
            {
                return enSaveResult::svFailed_UserNotExists;
            }
        case clsBankUser::enState::Add:
            if (!IsUserFound(_UserName))
            {
                _AddNew();
                return enSaveResult::svSucceeded;
            }
            else
            {
                return enSaveResult::svFailed_UserExists;
            }
        default:
            return enSaveResult::svFailed_EmptyUser;;
        }
    }

    static bool Delete(string UserName)
    {
        vector <clsBankUser> vUsers = _LoadUsersFromFileToVector();

        if (_MarkForDeleteInVector(vUsers, UserName))
        {
            _SaveVectorToFile(vUsers);
            return true;
        }
        return false;
    }

    static vector <clsBankUser> GetUsers()
    {
        return _LoadUsersFromFileToVector();
    }

    static clsBankUser GetNewUser(string UserName)
    {
        return clsBankUser(clsBankUser::enState::Add, "", "", "", "", UserName, "", 0);
    }

    string ToString()
    {

        string UserCard = "";

        UserCard += "\n---------------------------";
        UserCard += "\nFirstName   : " + GetFirstName();
        UserCard += "\nLastName    : " + GetLastName();
        UserCard += "\nFull Name   : " + GetFirstName() + " " + GetLastName();
        UserCard += "\nEmail       : " + GetEmail();
        UserCard += "\nPhone       : " + GetPhone();
        UserCard += "\nUser name   : " + _UserName;
        UserCard += "\nPassword    : " + _Password;
        UserCard += "\nPermission  : " + to_string(_Permission);
        UserCard += "\n---------------------------\n";

        return UserCard;

    }

    static clsBankUser GetEmptyUser()
    {
        return clsBankUser(enState::Empty, "", "", "", "", "", "", 0);
    }

    static bool DoesUserHavePermission(enPermissions OperationPermission, int UserPermission)
    {
        return (int(OperationPermission) & UserPermission);
    }

};

