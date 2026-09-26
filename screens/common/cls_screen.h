#pragma once
#include <iostream>
#include <iomanip>
#include "../../libs/cls_util.h"
#include "../../global/global.h"
#include "../../core/cls_user.h"
#include "../../libs/cls_date.h"

using namespace std;

class ClsScreen
{
protected:
    static void _showCurrentUser()
    {
        cout << ClsUtil::tabs(5) << "Current User : ";
        cout << currentUser.fullName();
        cout << endl;
    }
    static void _showTodayDate()
    {

        cout << ClsUtil::tabs(5) << "Date : ";
        ClsDate date;
        date.print();
        cout << endl;
    }
    static void _drawScreenHeader(string Title, string SubTitle = "")
    {
        cout << ClsUtil::tabs(5) << "______________________________________";
        cout << "\n\n"
             << ClsUtil::tabs(5) << Title;
        if (SubTitle != "")
        {
            cout << "\n"
                 << ClsUtil::tabs(5) << SubTitle;
        }
        cout << "\n"
             << ClsUtil::tabs(5) << "______________________________________\n\n";

        _showCurrentUser();
        _showTodayDate();
    }

    static void _clearScreen()
    {
        std::cout << "\033[2J\033[H";
        std::cout.flush(); // Force output
    }
    static void _pauseSystem()
    {
        // system("pause")
        std::cin.clear(); // Clear any error flags
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // std::cout << "Press Enter to continue To Back Main Menu . . . ";
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";
        std::cin.get();
    }

    static void _showLine()
    {
        cout << setw(8) << left << "" << "\n__________________________________________________________"
             << "_______________________________________________________\n\n";
    }
    static void _showAccessDeniedScreen()
    {
        _drawScreenHeader("\t  Access Denied Screen Contact to Admin");
    }

    static bool checkAccessScreen(ClsUser::enPermissions permission)
    {
        if (currentUser.hasPermission(permission))
            return true;
        else
        {
            _showAccessDeniedScreen();
            return false;
        }
    }
};
