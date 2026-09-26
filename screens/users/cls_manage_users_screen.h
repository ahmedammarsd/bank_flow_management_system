#pragma once
#include <iostream>
#include <iomanip>
#include "../../libs/cls_input_validate.h"
#include "../../core/cls_bank_client.h"
#include "../common/cls_screen.h"
using namespace std;

// Screens
#include "cls_list_users_screen.h"
#include "cls_add_new_user_screen.h"
#include "cls_delete_user.h"
#include "cls_update_user_screen.h"
#include "cls_find_user_screen.h"
// =====================

class ClsManageUsersScreen : protected ClsScreen
{
private:
    enum enManageUsersMenueOptions
    {
        eListUsers = 1,
        eAddNewUser = 2,
        eDeleteUser = 3,
        eUpdateUser = 4,
        eFindUser = 5,
        eMainMenue = 6
    };

    static short ReadManageUsersMenueOption()
    {
        short Choice = clsInputValidate::readShortNumberBetween(1, 6, "Enter Number between 1 to 6 ? ");
        return Choice;
    }

    static void _goBackToManageUsersMenue()
    {
        // cout << "\n\tPress any key to go back to Manage Users Menue...\n";
        _pauseSystem();
        showManageUsersMenu();
    }

    static void _showListUsersScreen()
    {
        // cout << "\nList Users Screen Will Be Here.\n";
        ClsListUserssScreen::showUsersList();
    }

    static void _showAddNewUserScreen()
    {
        // cout << "\nAdd New User Screen Will Be Here.\n";
        ClsAddNewUserScreen::showAddNewUserScreen();
    }

    static void _showDeleteUserScreen()
    {
        // cout << "\nDelete User Screen Will Be Here.\n";
        ClsDeleteUserScreen::showDeleteClientScreen();
    }

    static void _showUpdateUserScreen()
    {
        // cout << "\nUpdate User Screen Will Be Here.\n";
        ClsUpdateUserScreen::showUpdateUserScreen();
    }

    static void _showFindUserScreen()
    {
        // cout << "\nFind User Screen Will Be Here.\n";
        ClsFindUserScreen::showFindUserScreen();
    }

    static void _PerformManageUsersMenueOption(enManageUsersMenueOptions ManageUsersMenueOption)
    {

        switch (ManageUsersMenueOption)
        {
        case enManageUsersMenueOptions::eListUsers:
        {
            _clearScreen();
            _showListUsersScreen();
            _goBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eAddNewUser:
        {
            _clearScreen();
            _showAddNewUserScreen();
            _goBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eDeleteUser:
        {
            _clearScreen();
            _showDeleteUserScreen();
            _goBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eUpdateUser:
        {
            _clearScreen();
            _showUpdateUserScreen();
            _goBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eFindUser:
        {
            _clearScreen();

            _showFindUserScreen();
            _goBackToManageUsersMenue();
            break;
        }

        case enManageUsersMenueOptions::eMainMenue:
        {
            // do nothing here the main screen will handle it :-) ;
        }
        }
    }

public:
    static void showManageUsersMenu()
    {
        _clearScreen();
        _drawScreenHeader("Manage Users Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Manage Users Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Users.\n";
        cout << setw(37) << left << "" << "\t[2] Add New User.\n";
        cout << setw(37) << left << "" << "\t[3] Delete User.\n";
        cout << setw(37) << left << "" << "\t[4] Update User.\n";
        cout << setw(37) << left << "" << "\t[5] Find User.\n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";
        _PerformManageUsersMenueOption((enManageUsersMenueOptions)ReadManageUsersMenueOption());
    }
};
