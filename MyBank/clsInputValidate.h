#pragma once

#include <iostream>
#include <string>


using namespace std;


class clsInputValidate
{
public:


	static bool IsNumberBetween(int Number, int From, int To)
	{
		return (Number >= From && Number <= To);
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		return (Number >= From && Number <= To);
	}


	static int ReadIntNumber(string Message, string MessageIfInvalid = "Invalid input , enter another number : ")
	{
		int Number = 0;
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

	static double ReadDoubleNumber(string Message ,string MessageIfInvalid = "Invalid input , enter another number : ")
	{
		double Number = 0;
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


	static int ReadIntNumberBetween(string Message, int From, int To, string MessageIfOutOfRange = "Number out of range ,")
	{
		int Number = ReadIntNumber(Message);

		while (!IsNumberBetween(Number, From, To))
		{
			cout << MessageIfOutOfRange;
			Number = ReadIntNumber(Message);
		}
		return Number;
	}

	static double ReadDoubleNumberBetween(string Message, double From, double To, string MessageIfOutOfRange = "Number out of range ,")
	{
		double Number = ReadDoubleNumber(Message);

		while (!IsNumberBetween(Number, From, To))
		{
			cout << MessageIfOutOfRange;
			Number = ReadDoubleNumber(Message);
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

};

