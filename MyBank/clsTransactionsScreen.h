#pragma once

#include "iostream"
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"


using namespace std;

class clsTransactionsScreen : public clsScreen
{
private:
    enum class _enTransactionsMenuOptions
    {
        Deposit = 1, Withdraw = 2, ShowTotalBalance = 3, Transfer = 4, TransferLogger = 5, ShowMainMenu = 6
    };
private:
    static void _DrawTransactionsMenu()
    {
        DrawScreenHeader("Transactions Menu");

        cout << "===========================================\n";
        cout << "             Transactions Menu\n";
        cout << "===========================================\n";
        cout << "\t[1] Deposit.\n";
        cout << "\t[2] Withdraw.\n";
        cout << "\t[3] Total Balances.\n";
        cout << "\t[4] Transfer.\n";
        cout << "\t[5] Transfer logger.\n";
        cout << "\t[6] Main Menu.\n";
        cout << "===========================================\n";
    }

    static _enTransactionsMenuOptions _ReadTransactionsMenuOption()
    {
        int TransactionsMenuOption = clsInputValidate::ReadNumberBetween("Choose what do you want to do [1 to 6] : ", 1, 6);

        return _enTransactionsMenuOptions(TransactionsMenuOption);

    }



    static bool _Deposit()
    {
        return clsDepositScreen::Deposit();
    }

    static bool _Withdraw()
    {
        return clsWithdrawScreen::WithDraw();
    }

    static void _ShowTotalBalance()
    {
        clsTotalBalancesScreen::DisplayTotalBalancesScreen();
    }

    static bool _Transfer()
    {
        return clsTransferScreen::Transfer();
    }

    static void _TransferLogger()
    {
        clsTransferLogScreen::ShowTransferLog();
    }


    static void _PerformTransactionsMenuOperation(_enTransactionsMenuOptions Choice)
    {
        switch (Choice)
        {
        case clsTransactionsScreen::_enTransactionsMenuOptions::Deposit:
            _Deposit();
            break;
        case clsTransactionsScreen::_enTransactionsMenuOptions::Withdraw:
            _Withdraw();
            break;
        case clsTransactionsScreen::_enTransactionsMenuOptions::ShowTotalBalance:
            _ShowTotalBalance();
            break;
        case clsTransactionsScreen::_enTransactionsMenuOptions::Transfer:
            _Transfer();
            break;
        case clsTransactionsScreen::_enTransactionsMenuOptions::TransferLogger:
            _TransferLogger();
            break;
        default:
            return;
        }
    }

public:

	static void StartTransactionsMenu()
	{

        if (!clsSession::DoesCurrentUserHavePermission(clsBankUser::enPermissions::Tranactions))
        {
            clsMessages::ShowAccessDeniedMessage();
            system("pause=0");
            return;
        }


        while (true)
        {


            _DrawTransactionsMenu();

            _enTransactionsMenuOptions Choice = _ReadTransactionsMenuOption();

            if (Choice == _enTransactionsMenuOptions::ShowMainMenu)
            {
                return;
            }

            system("cls");

            _PerformTransactionsMenuOperation(Choice);

            system("pause=0");

            system("cls");
        }
	}


};

