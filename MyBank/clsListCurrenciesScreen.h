#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsListCurrenciesScreen : public clsScreen
{
private:
	static void _DrawTableHeader()
	{
		cout << string(110, '_') << "\n\n";

		cout << "|" << setw(35) << left << "Country"
			<< "|" << setw(10) << left << "Code"
			<< "|" << setw(31) << left << "Name"
			<< "|" << setw(15) << left << "Rate/(1$)"
			<< '\n';

		cout << string(110, '_') << '\n';

	}

	static void _PrintOneCurrency(clsCurrency & Currency)
	{
		cout << "|" << setw(35) << left << Currency.GetCountry()
			<< "|" << setw(10) << left << Currency.GetCountryCode()
			<< "|" << setw(31) << left << Currency.GetCurrencyName()
			<< "|" << setw(15) << left << Currency.GetRate()
			<< '\n';

	}

public:
	static void ShowListCurrencies()
	{
		vector <clsCurrency> vCurrencies = clsCurrency::GetCurrencies();

		string Title = "Currencies list";
		string SubTitle = "(" + to_string(vCurrencies.size()) + ") Currency.";

		DrawScreenHeader(Title, SubTitle);

		_DrawTableHeader();

		for (clsCurrency& Currency : vCurrencies)
		{
			_PrintOneCurrency(Currency);
		}

		cout << string(110, '_') << '\n';


	}
};

