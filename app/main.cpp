#include <iostream>
#include "../screens/auth/cls_login_screen.h"
#include "../core/cls_user.h"
using namespace std;

int main()
{

    while (true)
    {

        ClsLoginScreen::showLoginScreen();
    }

    return 0;
}
