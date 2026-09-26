#include <iostream>
#include "../common/cls_screen.h"
#include "../../libs/cls_input_validate.h"
#include "cls_currency.h"
using namespace std;

class ClsFindCurrencyScreen : public ClsScreen
{
private:
    enum FindCurrencyOptions
    {
        FindCurrencyByCode = 1,
        FindCurrencyByName = 2,
    };

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
    static FindCurrencyOptions _readFindCurrencyOption()
    {
        cout << "Find by: [1] Code  or [2] Name ? ";
        short choice = clsInputValidate::readShortNumberBetween(1, 2, "Enter Number between 1 to 2 ? ");

        return (FindCurrencyOptions)choice;
    }

    static string _readCurrencyCode()
    {
        string code = clsInputValidate::readString("Please Enter Currency Code : ");
        return code;
    }

    static ClsCurrency _getCurrencyByCode(string code)
    {
        return ClsCurrency::findByCode(code);
    }

    static string _readCountryName()
    {
        string countryName = clsInputValidate::readString("Please Enter Country Name : ");

        return countryName;
    }

    static ClsCurrency _getCurrencyByContry(string countryName)
    {
        return ClsCurrency::findByCountry(countryName);
    }

    static ClsCurrency _getCurrency(FindCurrencyOptions option)
    {
        if (option == FindCurrencyOptions::FindCurrencyByCode)
        {
            return _getCurrencyByCode(_readCurrencyCode());
        }

        return _getCurrencyByContry(_readCountryName());
    }

public:
    static void showFindCurrencyScreen()
    {

        _drawScreenHeader("Find Currency Screen");

        FindCurrencyOptions option = _readFindCurrencyOption();
        ClsCurrency currency = _getCurrency(option);

        if (currency.isEmpty())
        {
            cout << "\nCurrency was Not Found :-( \n";
            return;
        }

        cout << "\n Currency Found :-) \n";
        _printCurrency(currency);
    }
};
