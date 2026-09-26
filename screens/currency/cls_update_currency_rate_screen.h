#include <iostream>
#include "../common/cls_screen.h"
#include "../../libs/cls_input_validate.h"
#include "cls_currency.h"

class ClsUpdateCurrencyRateScreen : protected ClsScreen
{

private:
    static void _printCurrency(ClsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.country();
        cout << "\nCode       : " << Currency.currencyCode();
        cout << "\nName       : " << Currency.currencyName();
        cout << "\nRate(1$) = : " << Currency.rate();

        cout << "\n_____________________________\n";
    }

    static string _readCurrencyCode()
    {
        string code = clsInputValidate::readString("Please Enter Currency Code : ");
        return code;
    }

public:
    static void showUpdateCurrencyRateScreen()
    {
        _drawScreenHeader("Update Currency Screen");

        string code = _readCurrencyCode();
        ClsCurrency currency = ClsCurrency::findByCode(code);

        if (currency.isEmpty())
        {
            cout << "\nCurrency was Not Found :-( \n";
            return;
        }

        _printCurrency(currency);

        bool isConfirmUpdate = clsInputValidate::readBoolValue("\nAre you sure you want to update the rate of this currency ? [Y] = Yes | [N] = No ? ");

        if (isConfirmUpdate)
        {
            cout << "\nCurrency Card:\n";
            cout << "_____________________________\n";
            float newRate = clsInputValidate::readFloatNumber("Please Enter the New Rate : ");
            currency.updateRate(newRate);
            cout << "\nCurrency Updated Successfully :)\n";
            _printCurrency(currency);
        }
    }
};
