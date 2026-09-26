#pragma once
#include <iostream>
#include <iomanip>
#include "../common/cls_screen.h"
#include "../../libs/cls_util.h"
#include "cls_currency.h"

class ClsCurrencyListScreen : protected ClsScreen
{
private:
    static void _header()
    {
        _showLine();
        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(30) << "Name";
        cout << "| " << left << setw(20) << "Rate(1$)";

        _showLine();
    }
    static void _printCurrencyLine(ClsCurrency currency)
    {
        cout << setw(8) << left << "" << "| " << left << setw(30) << currency.country();
        cout << "| " << left << setw(8) << currency.currencyCode();
        cout << "| " << left << setw(30) << currency.currencyName();
        cout << "| " << left << setw(20) << currency.rate();
    }

public:
    static void showCurrenciesList()
    {
        vector<ClsCurrency> currencies = ClsCurrency::getCurrenciesList();
        string title = "\t Currencies List Screen";
        string subTitle = "\t (" + to_string(currencies.size()) + ") Currency(s)";
        _drawScreenHeader(title, subTitle);

        if (currencies.size() == 0)
        {
            cout << ClsUtil::tabs(7) << " No Currencies in the system \n";
            _showLine();
            return;
        }

        _header();
        for (ClsCurrency &currency : currencies)
        {
            _printCurrencyLine(currency);
            cout << "\n";
        }
        _showLine();
    }
};
