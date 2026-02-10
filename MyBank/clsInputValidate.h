#pragma once

#include <iostream>
#include <string>


using namespace std;


class clsInputValidate
{
public:

	template <typename T>
	static bool IsNumberBetween(T Number, T From, T To)
	{
		return (Number >= From && Number <= To);
	}

	template <typename T>
	static T ReadNumber(string Message, string MessageIfInvalid = "Invalid input , enter another number : ")
	{
		T Number = 0;
		cout << Message;
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << MessageIfInvalid;
			cin >> Number;
		}
		return Number;
	}

	template <typename T>
	static T ReadNumberBetween(string Message, T From, T To, string MessageIfOutOfRange = "Number out of range ,")
	{
		T Number = ReadNumber<T>(Message);

		while (!IsNumberBetween(Number, From, To))
		{
			cout << MessageIfOutOfRange;
			Number = ReadNumber<T>(Message);
		}
		return Number;
	}


	static string ReadString(string Message)
	{

		string Text = "";

		cout << Message;
		getline(cin >> ws, Text);

		return Text;

	}

	static char ReadChar(string Message)
	{
		char Char;

		cout << Message;
		cin >> Char;

		return Char;
	}

};

