#pragma once
#include <iostream>
#include "../common/cls_screen.h"
#include "../../libs/cls_input_validate.h"
#include <iomanip>

// Screens
#include "../clients/cls_list_clients_screen.h"
#include "../clients/cls_add_new_client_screen.h"
#include "../clients/cls_delete_client_screen.h"
#include "../clients/cls_update_client_screen.h"
#include "../clients/cls_find_client_screen.h"
#include "../clients/cls_transactions_screen.h"
#include "../users/cls_manage_users_screen.h"
#include "../users/cls_login_register_list_screen.h"
#include "../currency/cls_currency_exchange_screen.h"
/// =================

#include "../../global/global.h"
using namespace std;

class ClsMainScreen : protected ClsScreen
{

private:
    enum enMainMenueOptions
    {
        eListClients = 1,
        eAddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClient = 4,
        eFindClient = 5,
        eShowTransactionsMenue = 6,
        eManageUsers = 7,
        eLoginRegister = 8,
        eCurrencyExchange = 9,
        eExit = 10
    };

    static short _readMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Choice = clsInputValidate::readShortNumberBetween(1, 10, "Enter Number between 1 to 10 ? ");
        return Choice;
    }

    static void _goBackToMainMenue()
    {
        // cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

        _pauseSystem();
        showMainMenue();
    }

    static void _showAllClientsScreen()
    {
        if (!checkAccessScreen(ClsUser::enPermissions::pListClients))
            return;

        // cout << "\nClient List Screen Will be here...\n";
        ClsListClientsScreen::showClientList();
    }

    static void _showAddNewClientsScreen()
    {
        if (!checkAccessScreen(ClsUser::enPermissions::pAddNewClient))
            return;

        // cout << "\nAdd New Client Screen Will be here...\n";
        ClsAddNewClientScreen::showAddNewClientScreen();
    }

    static void _showDeleteClientScreen()
    {

        if (!checkAccessScreen(ClsUser::enPermissions::pDeleteClient))
            return;

        // cout << "\nDelete Client Screen Will be here...\n";
        ClsDeleteClientScreen::showDeleteClientScreen();
    }

    static void _showUpdateClientScreen()
    {
        if (!checkAccessScreen(ClsUser::enPermissions::pUpdateClient))
            return;

        // cout << "\nUpdate Client Screen Will be here...\n";
        ClsUpdateClientScreen::showUpdateClientScreen();
    }

    static void _showFindClientScreen()
    {
        if (!checkAccessScreen(ClsUser::enPermissions::pFindClient))
            return;

        // cout << "\nFind Client Screen Will be here...\n";
        ClsFindClientScreen::showFindClientScreen();
    }

    static void _showTransactionsMenue()
    {
        if (!checkAccessScreen(ClsUser::enPermissions::pTransactions))
            return;
        // cout << "\nTransactions Menue Will be here...\n";
        ClsTransactionsScreen::showTransactionsMenu();
    }

    static void _showManageUsersMenue()
    {
        if (!checkAccessScreen(ClsUser::enPermissions::pManageUsers))
            return;
        // cout << "\nUsers Menue Will be here...\n";
        ClsManageUsersScreen::showManageUsersMenu();
    }
    static void _showLoginRegisterScreen()
    {
        if (!checkAccessScreen(ClsUser::enPermissions::pLoginRegister))
            return;
        // cout << "\n Login Register Will be here...\n";
        ClsLoginRegisterListScreen::showLoginRegisterListScreen();
    }

    static void _showCurrencyExchangeScreen()
    {
        // if (!checkAccessScreen(ClsUser::enPermissions::pCurrencyExchange))
        //     return;
        // cout << "\n Currency Exchange Will be here...\n";
        ClsCurrencyExchangeScreen::showCurrencyMainMenue();
    }

    // static void _showEndScreen()
    // {
    //     cout << "\nEnd Screen Will be here...\n";
    // }

    static void _logout()
    {
        currentUser = ClsUser::find("", "");
    }

    static void _perfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
        {
            _clearScreen();
            _showAllClientsScreen();
            _goBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            _clearScreen();
            _showAddNewClientsScreen();
            _goBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            _clearScreen();
            _showDeleteClientScreen();
            _goBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            _clearScreen();
            _showUpdateClientScreen();
            _goBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            _clearScreen();
            _showFindClientScreen();
            _goBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            _clearScreen();
            _showTransactionsMenue();
            _goBackToMainMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            _clearScreen();
            _showManageUsersMenue();
            _goBackToMainMenue();
            break;
        case enMainMenueOptions::eLoginRegister:
            _clearScreen();
            _showLoginRegisterScreen();
            _goBackToMainMenue();
            break;
        case enMainMenueOptions::eCurrencyExchange:
            _clearScreen();
            _showCurrencyExchangeScreen();
            _goBackToMainMenue();
            break;
        case enMainMenueOptions::eExit:
            _clearScreen();
            _logout();
            // ClsLoginScreen::showLoginScreen();
            //  Login();
            break;
        }
    }

public:
    static void showMainMenue()
    {

        _clearScreen();
        _drawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Register Log.\n";
        cout << setw(37) << left << "" << "\t[9] Currency Exchange.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _perfromMainMenueOption((enMainMenueOptions)_readMainMenueOption());
    }
};
