#pragma once

#include "iostream"
#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"


using namespace std;

class clsTransactionsScreen : public clsScreen
{
private:
    enum class _enTransactionsMenuOptions
    {
        Deposit = 1, Withdraw = 2, ShowTotalBalance = 3, ShowMainMenu = 4
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
        cout << "\t[4] Main Menu.\n";
        cout << "===========================================\n";
    }

    static _enTransactionsMenuOptions _ReadTransactionsMenuOption()
    {
        int TransactionsMenuOption = clsInputValidate::ReadIntNumberBetween("Choose what do you want to do [1 to 4] : ", 1, 4);

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
        default:
            return;
        }
    }

public:

	static void StartTransactionsMenu()
	{
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

