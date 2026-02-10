#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListClientsScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsSession.h"
#include "clsLoginLoggerScreen.h"
#include "clsCurrencyExchangeScreen.h"


using namespace std;


class clsMainScreen : public clsScreen
{
private:
    enum class _enMainMenuOptions {
        ListClients = 1, AddNewClient = 2, DeleteClient = 3,
        UpdateClient = 4, FindClient = 5, ShowTransactionsMenu = 6,
        ManageUsers = 7, LoginLogger = 8, CurrencyExchange = 9, LogOut = 10
    };
private :
    static void _DrawMainMenuScreen()
    {
        DrawScreenHeader("Main screen");
        cout << "\n";
        cout << "===========================================\n";
        cout << "                Main Menu\n";
        cout << "===========================================\n";
        cout << "\t[1] Show Client List.\n";
        cout << "\t[2] Add New Client.\n";
        cout << "\t[3] Delete Client.\n";
        cout << "\t[4] Update Client Info.\n";
        cout << "\t[5] Find Client.\n";
        cout << "\t[6] Transactions.\n";
        cout << "\t[7] Manage Users.\n";
        cout << "\t[8] Login logger.\n";
        cout << "\t[9] Currency exchange.\n";
        cout << "\t[10] Logout.\n";
        cout << "===========================================\n";
    }

    static _enMainMenuOptions ReadMainMenuOption()
    {
        int MainMenuOption = clsInputValidate::ReadNumberBetween("Choose what do you want to do [1 to 10] : ", 1, 10);

        return _enMainMenuOptions(MainMenuOption);
    }


    static void _ListClients()
    {
        clsListClientsScreen::DisplayClientsList();
    }

    static bool _AddNewClient()
    {
        return clsAddNewClientScreen::AddClient();
    }

    static bool _DeleteClient()
    {
        return clsDeleteClientScreen::DeleteClient();
    }

    static bool _UpdateClient()
    {
        return clsUpdateClientScreen::UpdateClient();
    }

    static bool _FindClient()
    {
        return clsFindClientScreen::FindClient();
    }

    static void _ShowTransactionsMenu()
    {
        clsTransactionsScreen::StartTransactionsMenu();
    }

    static void _ManageUsers()
    {
        clsManageUsersScreen::StartManageUsersMenu();
    }

    static void _ShowLoginLogger()
    {
        clsLoginLoggerScreen::ShowLoginLoggerScreen();
    }

    static void _ShowCurrencyExchangeMenu()
    {
        clsCurrencyExchangeScreen::StartCurrencyExchangeMenu();
    }

    static void _PerformMainMenuOperation(_enMainMenuOptions Choice)
    {
        switch (Choice)
        {
        case clsMainScreen::_enMainMenuOptions::ListClients:
            _ListClients();
            system("pause=0");
            break;
        case clsMainScreen::_enMainMenuOptions::AddNewClient:
            _AddNewClient();
            system("pause=0");
            break;
        case clsMainScreen::_enMainMenuOptions::DeleteClient:
            _DeleteClient();
            system("pause=0");
            break;
        case clsMainScreen::_enMainMenuOptions::UpdateClient:
            _UpdateClient();
            system("pause=0");
            break;
        case clsMainScreen::_enMainMenuOptions::FindClient:
            _FindClient();
            system("pause=0");
            break;
        case clsMainScreen::_enMainMenuOptions::ShowTransactionsMenu:
            _ShowTransactionsMenu();
            break;
        case clsMainScreen::_enMainMenuOptions::ManageUsers:
            _ManageUsers();
            break;
        case clsMainScreen::_enMainMenuOptions::LoginLogger:
            _ShowLoginLogger();
            system("pause=0");
            break;
        case clsMainScreen::_enMainMenuOptions::CurrencyExchange:
            _ShowCurrencyExchangeMenu();
            break;
        case clsMainScreen::_enMainMenuOptions::LogOut:
            clsSession::EndSession();
            break;
        default:
            return;
        }
    }


public:


    static void StartBankSystem()
    {
        while (true)
        {
            _DrawMainMenuScreen();

            _enMainMenuOptions Choice = ReadMainMenuOption();

            system("cls");

            _PerformMainMenuOperation(Choice);

            if (Choice == _enMainMenuOptions::LogOut)
            {
                return;
            }


            system("cls");

        }

    }



};

