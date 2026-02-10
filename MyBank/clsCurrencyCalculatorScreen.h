#pragma once

#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrency.h"


using namespace std;


class clsCurrencyCalculatorScreen : public clsScreen
{
private:

	static clsCurrency _GetCurrency(string Message)
	{
		string Code = "";
		clsCurrency Currency = clsCurrency::GetEmptyObj();
		do
		{
			Code = clsInputValidate::ReadString(Message);
			Currency = clsCurrency::FindByCountryCode(Code);
		} while (!Currency.IsActive());

		return Currency;

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


public:
	static void ShowCalculatorScreen()
	{
		char Confirm = 'y';
		while(Confirm == 'y' || Confirm == 'Y')
		{
			DrawScreenHeader("Calculator Screen");

			clsCurrency Currency_From = _GetCurrency("Enter country code (from) : ");

			clsCurrency Currency_To = _GetCurrency("Enter country code (To) : ");

			double Amount = 0;
			do
			{
				Amount = clsInputValidate::ReadNumber<double>("Enter amount to exchange : ");

			} while (Amount <= 0);

			cout << "\n\nConvert from : \n\n";
			_DisplayCurrencyCard(Currency_From);

			cout << "\n\n\n";

			cout << "Convert to : \n\n";
			_DisplayCurrencyCard(Currency_To);

			cout << "\n\n";

			double Result = clsCurrency::CurrencyExchange(Amount, Currency_From.GetRate(), Currency_To.GetRate());

			cout << Amount << " " << Currency_From.GetCurrencyName() << " = " << Result << " " << Currency_To.GetCurrencyName() << "\n\n";
			
			Confirm = clsInputValidate::ReadChar("Do you want to perform another exchange (y/n) ? : ");
		
			system("cls");
		}




	}
};

