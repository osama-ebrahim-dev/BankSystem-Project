#include <iostream>
#include "clsLoginScreen.h"
#include "clsMainScreen.h"

using namespace std;


int main()
{
    while (true)
    {

        clsLoginScreen::Login();
        clsMainScreen::StartBankSystem();

    }

    return 0;
}
