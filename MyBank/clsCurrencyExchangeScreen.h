#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsListCurrenciesScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeScreen : public clsScreen
{
private:
    enum class _enCurrencyExchangeMenu
    {
        ListCurrencies = 1, FindCurrency = 2, UpdateRate = 3, CurrencyCalculator = 4, MainMenu = 5
    };

    static _enCurrencyExchangeMenu ReadMenuOption()
    {
        int MenuOption = clsInputValidate::ReadNumberBetween("Choose what do you want to do [1 to 5] : ", 1, 5);

        return _enCurrencyExchangeMenu(MenuOption);

    }

	static void _PrintMenu()
	{
        cout << "\n";
        cout << "===========================================\n";
        cout << "               Currency Exchange\n";
        cout << "===========================================\n";
        cout << "\t[1] List Currencies.\n";
        cout << "\t[2] Find Currency.\n";
        cout << "\t[3] Update rate.\n";
        cout << "\t[4] Currency calculator.\n";
        cout << "\t[5] Main menu.\n";
        cout << "===========================================\n";

	}

    static void _ListCurrencies()
    {
        clsListCurrenciesScreen::ShowListCurrencies();
    }

    static void _FindCurrency()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static bool _UpdateRate()
    {
        return clsUpdateRateScreen::ShowUpdateRateScreen();
    }

    static void _CurrencyCalculator()
    {
        clsCurrencyCalculatorScreen::ShowCalculatorScreen();
    }


    static void _PerformCurrencyMenuOperation(_enCurrencyExchangeMenu Choice)
    {
        switch (Choice)
        {
        case clsCurrencyExchangeScreen::_enCurrencyExchangeMenu::ListCurrencies:
            _ListCurrencies();
            break;
        case clsCurrencyExchangeScreen::_enCurrencyExchangeMenu::FindCurrency:
            _FindCurrency();
            break;
        case clsCurrencyExchangeScreen::_enCurrencyExchangeMenu::UpdateRate:
            _UpdateRate();
            break;
        case clsCurrencyExchangeScreen::_enCurrencyExchangeMenu::CurrencyCalculator:
            _CurrencyCalculator();
            break;
        default:
            break;
        }
    }

public:
	static void StartCurrencyExchangeMenu()
	{

        while(true)
        {
            DrawScreenHeader("Currency Exchange");
            _PrintMenu();
            _enCurrencyExchangeMenu Choice = ReadMenuOption();

            system("cls");

            if (Choice == _enCurrencyExchangeMenu::MainMenu)
            {
                return;
            }
            _PerformCurrencyMenuOperation(Choice);

            system("pause=0");
            system("cls");

        }
	}
};

