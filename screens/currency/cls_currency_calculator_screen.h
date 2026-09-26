#include <iostream>
#include "../common/cls_screen.h"
#include "../../libs/cls_input_validate.h"
#include "cls_currency.h"
using namespace std;

class ClsCurrencyCalculatorScreen : protected ClsScreen
{
private:
    static void _printCurrency(ClsCurrency Currency, string title = "Convert From")
    {
        cout << "\n"
             << title << " :\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.country();
        cout << "\nCode       : " << Currency.currencyCode();
        cout << "\nName       : " << Currency.currencyName();
        cout << "\nRate(1$) = : " << Currency.rate();
        cout << "\n_____________________________\n";
    }

    static ClsCurrency _readCurrency(string message = "Please Enter Currency 1 Code : ")
    {
        bool isCurrencyExist = false;
        do
        {
            if (isCurrencyExist)
            {
                cout << "\nCurrency was Not Found :-( \n";
            }
            string code = clsInputValidate::readString(message);
            ClsCurrency currency = ClsCurrency::findByCode(code);
            isCurrencyExist = !currency.isEmpty();
            if (isCurrencyExist)
            {
                return currency;
            }
        } while (true);
    }

    static float _readAmount(string message = "Please Enter Amount to Exchange : ")
    {
        return clsInputValidate::readFloatNumber(message);
    }

    static void _printCalculationResults(float amount, ClsCurrency currencyFrom, ClsCurrency currencyTo)
    {
        _printCurrency(currencyFrom, "Convert From");
        float amountExchangeToDollar = currencyFrom.exchangeToUSD(amount);

        cout << amount << " " << currencyFrom.currencyCode() << " = " << amountExchangeToDollar << " USD \n";

        if (currencyTo.currencyCode() != "USD")
        {
            cout << "Converting From USD to " << currencyTo.currencyCode() << "\n";
            _printCurrency(currencyTo, "Convert To");

            float amountInCurrency2 = currencyFrom.exchangeToCurrency(amount, currencyTo);
            cout << amount << " " << currencyFrom.currencyCode() << " = " << amountInCurrency2 << " " << currencyTo.currencyCode() << "\n";
        }
    }

public:
    static void showCurrencyCalculatorScreen()
    {
        bool isReCalculate = false;
        do
        {
            if (isReCalculate)
                _clearScreen();

            _drawScreenHeader("Currency Calculator Screen");
            ClsCurrency currencyFrom = _readCurrency("Please Enter Currency 1 Code : ");
            ClsCurrency currencyTo = _readCurrency("Please Enter Currency 2 Code : ");
            float amount = _readAmount();

            _printCalculationResults(amount, currencyFrom, currencyTo);

            isReCalculate = clsInputValidate::readBoolValue("\nDo you want to perform another calculation ? [Y] = Yes | [N] = No ? ");
        } while (isReCalculate);
    }
};
