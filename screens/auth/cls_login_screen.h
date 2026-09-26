#include <iostream>
#include "../../libs/cls_input_validate.h"
#include "../common/cls_screen.h"
#include "cls_main_screen.h"
#include "../../core/cls_user.h"
#include "../../global/global.h"
#include "../../core/cls_login_logger.h"
using namespace std;

class ClsLoginScreen : protected ClsScreen
{

    static void _login()
    {
        bool isLoginFailed = false;
        string username, password;
        int trials = 3;

        do
        {
            if (isLoginFailed)
            {
                cout << "\nLogin Failed, Invalid Username or Password\n\n";
                cout << "You have " << --trials << " trials to login\n\n";
                if (trials == 0)
                {
                    cout << "You are locked out of the system \n\n\n";
                    std::exit(0);
                }
            }
            username = clsInputValidate::readString("Enter Username ? ");
            password = clsInputValidate::readString("Enter Password ? ");

            currentUser = ClsUser::find(username, password);
            isLoginFailed = currentUser.isEmpty();
        } while (isLoginFailed);
        // ClsLoginLogger::addToLoginLogFile(currentUser);
        currentUser.registerLogIn();
        ClsMainScreen::showMainMenue();
    }

public:
    static void showLoginScreen()
    {
        _clearScreen();
        _drawScreenHeader("\t  Login Screen");
        _login();
    };
};
