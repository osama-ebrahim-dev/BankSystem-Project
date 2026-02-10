#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"

using namespace std;

class clsFindCurrencyScreen : public clsScreen
{
private: 
	enum class _enChoice { Code = 1, Country = 2 };

	static _enChoice _ReadUserChoice()
	{
		int Choice = clsInputValidate::ReadNumberBetween("Find by => [1] Code or [2] Country : ", 1, 2);

		return _enChoice(Choice);
	}

	static void _DisplayCurrencyCard(clsCurrency Currency)
	{
		cout << "-----------------------------------------------\n";
		cout << "Country : " << Currency.GetCountry() << "\n";
		cout << "Code : " << Currency.GetCountryCode() << "\n";
		cout << "Name : " << Currency.GetCurrencyName() << "\n";
		cout << "Rate (1$) : " << Currency.GetRate() << "\n";
		cout << "-----------------------------------------------\n";

	}

	static bool _FindByCode()
	{
		string CountryCode = clsInputValidate::ReadString("Please enter country code : ");

		clsCurrency Currency = clsCurrency::FindByCountryCode(CountryCode);

		if (Currency.IsActive())
		{
			cout << "Currency found \n\n";
			_DisplayCurrencyCard(Currency);
			return true;
		}
		
		cout << "\n\nCurrency NOT found \n\n";
		return false;

	}

	static bool _FindByCountry()
	{
		string CountryName = clsInputValidate::ReadString("Please enter country name : ");

		clsCurrency Currency = clsCurrency::FindByCountryName(CountryName);

		if (Currency.IsActive())
		{
			cout << "Currency found \n\n";
			_DisplayCurrencyCard(Currency);
			return true;
		}

		cout << "\n\nCurrency NOT found \n\n";
		return false;

	}


	static void _PerformChoice(_enChoice Choice)
	{
		switch (Choice)
		{
		case clsFindCurrencyScreen::_enChoice::Code:
			_FindByCode();
			break;
		case clsFindCurrencyScreen::_enChoice::Country:
			_FindByCountry();
			break;
		default:
			_FindByCode();
			break;
		}
	}

public:
	static void ShowFindCurrencyScreen()
	{
		DrawScreenHeader("Find currency screen");

		_enChoice Choice = _ReadUserChoice();

		_PerformChoice(Choice);

	}
};

