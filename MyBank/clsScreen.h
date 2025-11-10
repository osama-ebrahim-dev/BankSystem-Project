#pragma once

#include <iostream>
using namespace std;

class clsScreen
{
protected:

	static void DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << "-------------------------------------------\n";
		cout << "               " << Title << '\n';
		if (SubTitle != "")
		{
			cout << "               " << SubTitle << '\n';
		}
		cout << "-------------------------------------------\n";

	}

};

