#include <iostream>
#include "../common/cls_screen.h"
#include "../../libs/cls_input_validate.h"

// Screens
#include "cls_currency_list_screen.h"
#include "cls_find_currency_screen.h"
#include "cls_update_currency_rate_screen.h"
#include "cls_currency_calculator_screen.h"
// =========================
class ClsCurrencyExchangeScreen : protected ClsScreen
{

private:
    enum eCurrencyMenueOptions
    {
        ListCurrencies = 1,
        FindCurrency = 2,
        UpdateRate = 3,
        CurrencyCalculator = 4,
        MainMenue = 5
    };

    static void _showListCurrenciesScreen()
    {
        // cout << "List Currencies Screen Will be here...\n";
        ClsCurrencyListScreen::showCurrenciesList();
    }

    static void _showFindCurrencyScreen()
    {
        // cout << "Find Currency Screen Will be here...\n";
        ClsFindCurrencyScreen::showFindCurrencyScreen();
    }

    static void _showUpdateRateScreen()
    {
        // cout << "Update Rate Screen Will be here...\n";
        ClsUpdateCurrencyRateScreen::showUpdateCurrencyRateScreen();
    }
    static void _showCurrencyCalculatorScreen()
    {
        // cout << "Currency Calculator Screen Will be here...\n";
        ClsCurrencyCalculatorScreen::showCurrencyCalculatorScreen();
    }

    static void _goBackToMainMenue()
    {
        cout << "\n\nPress any key to go back to Currency Menue...";
        _pauseSystem();
        showCurrencyMainMenue();
    }
    static short readTransactionsMenueOption()
    {

        short Choice = clsInputValidate::readShortNumberBetween(1, 5, "Enter Number between 1 to 5 ? ");
        return Choice;
    }
    static void _performTransactionsMenueOption(eCurrencyMenueOptions TransactionsMenueOption)
    {
        switch (TransactionsMenueOption)
        {
        case eCurrencyMenueOptions::ListCurrencies:
        {
            _clearScreen();
            _showListCurrenciesScreen();
            _goBackToMainMenue();
            break;
        }

        case eCurrencyMenueOptions::FindCurrency:
        {
            _clearScreen();
            _showFindCurrencyScreen();
            _goBackToMainMenue();
            break;
        }

        case eCurrencyMenueOptions::UpdateRate:
        {
            _clearScreen();
            _showUpdateRateScreen();
            _goBackToMainMenue();
            break;
        }

        case eCurrencyMenueOptions::CurrencyCalculator:
        {
            _clearScreen();
            _showCurrencyCalculatorScreen();
            _goBackToMainMenue();
            break;
        }

        case eCurrencyMenueOptions::MainMenue:
        {
            // do nothing here the main screen will handle it :-) ;
        }
        }
    }

public:
    static void showCurrencyMainMenue()
    {
        _clearScreen();
        _drawScreenHeader("Currency Exchange Main Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t  Currency Exchange Main Menu\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] List Currencies.\n";
        cout << setw(37) << left << "" << "\t[2] Find Currency.\n";
        cout << setw(37) << left << "" << "\t[3] Update Rate.\n";
        cout << setw(37) << left << "" << "\t[4] Currency Calculator \n";
        cout << setw(37) << left << "" << "\t[5] Main Menue.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 5]? ";

        _performTransactionsMenueOption((eCurrencyMenueOptions)readTransactionsMenueOption());
    }
};
