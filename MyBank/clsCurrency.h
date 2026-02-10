#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:
	enum class _enState { Empty, Update };
private:

	_enState _State = _enState::Empty;
	string _Country = "";
	string _CountryCode = "";
	string _CurrencyName = "";
	double _Rate = 0;
	inline static string _CurrenciesFile = "Currencies.txt";

private:

	static clsCurrency _ConvertLineToObj(string Line)
	{
		vector<string>vFields = clsString::vSplit(Line, "#//#");

		return clsCurrency(_enState::Update, vFields[0], vFields[1], vFields[2], stod(vFields[3]));
	}

	static vector <clsCurrency> _vLoadCurrencies()
	{
		vector <clsCurrency> vCurrencies;

		fstream File;

		File.open(_CurrenciesFile, ios::in);

		if (File.is_open())
		{
			string Line = "";

			while (getline(File, Line))
			{
				vCurrencies.push_back(_ConvertLineToObj(Line));
			}
			File.close();
		}
		return vCurrencies;
	}

	bool _UpdateCurrencyInVector(vector <clsCurrency>& vCurrencies)
	{
		for (clsCurrency& Currency : vCurrencies)
		{
			if (Currency.GetCountryCode() == _CountryCode)
			{
				Currency = *this;
				return true;
			}
		}
		return false;
	}

	string _ConvertToLine()
	{
		string Delimiter = "#//#";
		string Line = "";

		Line += _Country + Delimiter;
		Line += _CountryCode + Delimiter;
		Line += _CurrencyName + Delimiter;
		Line += to_string(_Rate);

		return Line;
	}

	static bool _SaveVectorToFile(vector <clsCurrency>& vCurrencies)
	{
		fstream File;
		File.open(_CurrenciesFile, ios::out);

		if (File.is_open())
		{
			for (clsCurrency& Currency : vCurrencies)
			{
				File << Currency._ConvertToLine() << endl;
			}
			File.close();
			return true;
		}
		return false;

	}

	bool _Update()
	{
		vector <clsCurrency> vCurrencies = _vLoadCurrencies();

		if (_UpdateCurrencyInVector(vCurrencies))
		{
			_SaveVectorToFile(vCurrencies);
			return true;
		}
		return false;
	}

public:
	clsCurrency(_enState State, string Country, string CountryCode, string CurrencyName, double Rate)
	{
		_State = State;
		_Country = Country;
		_CountryCode = CountryCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	void SetState(_enState State)
	{
		_State = State;
	}
	_enState GetState()
	{
		return _State;
	}

	string GetCountry()
	{
		return _Country;
	}
	string GetCountryCode()
	{
		return _CountryCode;
	}
	string GetCurrencyName()
	{
		return _CurrencyName;
	}

	void SetRate(double Rate)
	{
		if (Rate > 0)
		{
			_Rate = Rate;
		}
	}
	double GetRate()
	{
		return _Rate;
	}

	bool IsActive()
	{
		return (_State == _enState::Update);
	}

	static clsCurrency GetEmptyObj()
	{
		return clsCurrency(_enState::Empty, "", "", "", 0);
	}

	static vector <clsCurrency> GetCurrencies()
	{
		return _vLoadCurrencies();
	}

	static clsCurrency FindByCountryCode(string CountryCode)
	{
		fstream File;
		
		File.open(_CurrenciesFile, ios::in);

		if (File.is_open())
		{
			string Line = "";
			string Code = "";
			clsCurrency Currency = GetEmptyObj();
			while (getline(File, Line))
			{
				Currency = _ConvertLineToObj(Line);
				Code = Currency.GetCountryCode();
				if (clsString::UpperOrLowerAllLetters(Code, true) == clsString::UpperOrLowerAllLetters(CountryCode, true))
				{
					File.close();
					return Currency;
				}
			}
			File.close();
		}
		return GetEmptyObj();
	}

	static clsCurrency FindByCountryName(string CountryName)
	{
		fstream File;
		string Name = "";
		File.open(_CurrenciesFile, ios::in);

		if (File.is_open())
		{
			string Line = "";
			
			clsCurrency Currency = GetEmptyObj();
			while (getline(File, Line))
			{
				Currency = _ConvertLineToObj(Line);
				Name = Currency.GetCountry();
				if (clsString::UpperOrLowerAllLetters(Name, true) == clsString::UpperOrLowerAllLetters(CountryName, true))
				{
					File.close();
					return Currency;
				}
			}
			File.close();
		}
		return GetEmptyObj();
	}

	bool Save()
	{
		if (IsActive())
		{
			_Update();
			return true;
		}
		return false;
	}

	static double CurrencyExchange(double Amount, double Rate_From, double Rate_To)
	{
		return Amount * (Rate_To / Rate_From);
	}


};

