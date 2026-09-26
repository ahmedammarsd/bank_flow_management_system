#include <iostream>
#include "../../libs/cls_input_validate.h"
#include "../../core/cls_bank_client.h"
#include "../common/cls_screen.h"
#include <iomanip>

// Screens
#include "cls_deposit_screen.h"
#include "cls_withdraw_screen.h"
#include "cls_total_balances_screen.h"
#include "cls_transfer_screen.h"
#include "cls_transfer_log_list_screen.h"
// ====================
using namespace std;

class ClsTransactionsScreen : protected ClsScreen
{

private:
    enum enTransactionsMenueOptions
    {
        eDeposit = 1,
        eWithdraw = 2,
        eShowTotalBalance = 3,
        eTransfer = 4,
        eTransferLog = 5,
        eShowMainMenue = 6
    };

    static short readTransactionsMenueOption()
    {

        short Choice = clsInputValidate::readShortNumberBetween(1, 6, "Enter Number between 1 to 6 ? ");
        return Choice;
    }

    static void _showDepositScreen()
    {
        // cout << "\n Deposit Screen will be here.\n";
        ClsDepositScreen::showDepositScreen();
    }

    static void _showWithdrawScreen()
    {
        // cout << "\n Withdraw Screen will be here.\n";
        ClsWithdrawScreen::showWithdrawScreen();
    }

    static void _showTotalBalancesScreen()
    {
        // cout << "\n Balances Screen will be here.\n";
        ClsTotalBalancesScreen::showTotalBalancesScreen();
    }

    static void _showTransferScreen()
    {
        // cout << "\n Transfer Screen will be here.\n";
        ClsTransferScreen::showTransferScreen();
    }

    static void _showTransferLogScreen()
    {
        // cout << "\n Transfer Log Screen will be here.\n";
        ClsTransferLogListScreen::showTransferLogListScreen();
    }

    static void _goBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        _pauseSystem();
        showTransactionsMenu();
    }

    static void _performTransactionsMenueOption(enTransactionsMenueOptions TransactionsMenueOption)
    {
        switch (TransactionsMenueOption)
        {
        case enTransactionsMenueOptions::eDeposit:
        {
            _clearScreen();
            _showDepositScreen();
            _goBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eWithdraw:
        {
            _clearScreen();
            _showWithdrawScreen();
            _goBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eShowTotalBalance:
        {
            _clearScreen();
            _showTotalBalancesScreen();
            _goBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eTransfer:
        {
            _clearScreen();
            _showTransferScreen();
            _goBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eTransferLog:
        {
            _clearScreen();
            _showTransferLogScreen();
            _goBackToTransactionsMenue();
            break;
        }

        case enTransactionsMenueOptions::eShowMainMenue:
        {
            // do nothing here the main screen will handle it :-) ;
        }
        }
    }

public:
    static void showTransactionsMenu()
    {
        _clearScreen();
        _drawScreenHeader("Transactions Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Transactions Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Deposit.\n";
        cout << setw(37) << left << "" << "\t[2] Withdraw.\n";
        cout << setw(37) << left << "" << "\t[3] Total Balances.\n";
        cout << setw(37) << left << "" << "\t[4] Transfer \n";
        cout << setw(37) << left << "" << "\t[5] Transfer Log \n";
        cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 6]? ";

        _performTransactionsMenueOption((enTransactionsMenueOptions)readTransactionsMenueOption());
    }
};
