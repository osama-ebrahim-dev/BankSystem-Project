#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"


using namespace std;

class clsUpdateRateScreen : public clsScreen
{
private:

	static void _DisplayCurrencyCard(clsCurrency Currency)
	{
		cout << "-----------------------------------------------\n";
		cout << "Country : " << Currency.GetCountry() << "\n";
		cout << "Code : " << Currency.GetCountryCode() << "\n";
		cout << "Name : " << Currency.GetCurrencyName() << "\n";
		cout << "Rate (1$) : " << Currency.GetRate() << "\n";
		cout << "-----------------------------------------------\n";

	}


public:
	static bool ShowUpdateRateScreen()
	{
		DrawScreenHeader("Update rate screen");

		string CountryCode = clsInputValidate::ReadString("Please enter country code : ");

		clsCurrency Currency = clsCurrency::FindByCountryCode(CountryCode);

		if (Currency.IsActive())
		{
			cout << "Currency found \n\n";
			_DisplayCurrencyCard(Currency);
		}
		else
		{
			cout << "\n\nCurrency NOT found \n\n";
			return false;
		}

		char Confirm = clsInputValidate::ReadChar("Update the currency rate (y/n) ? : ");

		if (Confirm == 'y' || Confirm == 'Y')
		{
			double NewRate = clsInputValidate::ReadNumber<double>("Enter new rate : ");

			while (NewRate <= 0)
			{
				NewRate = clsInputValidate::ReadNumber<double>("Enter a valid rate : ");
			}
			Currency.SetRate(NewRate);
			if (Currency.Save())
			{
				cout << "Operation finished successfully . \n\n";
				_DisplayCurrencyCard(Currency);
				return true;
			}
			else
			{
				cout << "Operation failed . \n\n";
				return false;
			}
		}
		else
		{
			cout << "Operation has been cancelled \n";
			return false;
		}

	}
};

