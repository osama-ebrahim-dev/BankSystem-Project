#pragma once
#include <iostream>
#include <string>
using namespace std;

class clsMessages
{
public:

    static void ShowAccessDeniedMessage()
    {
        cout << "\n------------------------------------\n";
        cout << "Access Denied! Contact your Admin.";
        cout << "\n------------------------------------\n";
    }

    static void ShowSuccessMessage(string Message)
    {
        cout << "\n" << Message << " :-)\n";
    }

    static void ShowErrorMessage(string Message)
    {
        cout << "\nError: " << Message << " :-(\n";
    }

};