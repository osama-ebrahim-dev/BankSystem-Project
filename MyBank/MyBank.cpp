#include <iostream>
#include "clsLoginScreen.h"
#include "clsMainScreen.h"

using namespace std;


int main()
{
    while (true)
    {

        if(!clsLoginScreen::Login())
        {
            break;
        }
        clsMainScreen::StartBankSystem();
    }

    return 0;
}
