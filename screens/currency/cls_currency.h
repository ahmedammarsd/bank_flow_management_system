#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include "../../libs/cls_string.h"
class ClsCurrency
{

private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1
    };
    enMode _Mode;

    string _Country;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;

    static string _getFilePathOfCurrencies()
    {
        std::filesystem::path projectRoot = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path();
        return (projectRoot / "data" / "currencies.txt").string();
    }

    static ClsCurrency _convertLinetoCurrencyObject(string Line, string Seperator = "#//#")
    {
        vector<string> vCurrencyData;
        vCurrencyData = ClsString::split(Line, Seperator);

        return ClsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
                           stod(vCurrencyData[3]));
    }

    static string _converCurrencyObjectToLine(ClsCurrency Currency, string Seperator = "#//#")
    {

        string stCurrencyRecord = "";
        stCurrencyRecord += Currency.country() + Seperator;
        stCurrencyRecord += Currency.currencyCode() + Seperator;
        stCurrencyRecord += Currency.currencyName() + Seperator;
        stCurrencyRecord += to_string(Currency.rate());

        return stCurrencyRecord;
    }

    static vector<ClsCurrency> _loadCurrencysDataFromFile()
    {

        vector<ClsCurrency> vCurrencys;

        fstream MyFile;
        MyFile.open(_getFilePathOfCurrencies(), ios::in); // read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                ClsCurrency Currency = _convertLinetoCurrencyObject(Line);

                vCurrencys.push_back(Currency);
            }

            MyFile.close();
        }

        return vCurrencys;
    }

    static void _saveCurrencyDataToFile(vector<ClsCurrency> vCurrencys)
    {

        fstream MyFile;
        MyFile.open(_getFilePathOfCurrencies(), ios::out); // overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (ClsCurrency C : vCurrencys)
            {
                DataLine = _converCurrencyObjectToLine(C);
                MyFile << DataLine << endl;
            }

            MyFile.close();
        }
    }

    void _update()
    {
        vector<ClsCurrency> _vCurrencys;
        _vCurrencys = _loadCurrencysDataFromFile();

        for (ClsCurrency &C : _vCurrencys)
        {
            if (C.currencyCode() == currencyCode())
            {
                C = *this;
                break;
            }
        }

        _saveCurrencyDataToFile(_vCurrencys);
    }

    static ClsCurrency _getEmptyCurrencyObject()
    {
        return ClsCurrency(enMode::EmptyMode, "", "", "", 0);
    }

public:
    ClsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }

    static vector<ClsCurrency> getAllUSDRates()
    {

        return _loadCurrencysDataFromFile();
    }

    bool isEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string country()
    {
        return _Country;
    }

    string currencyCode()
    {
        return _CurrencyCode;
    }

    string currencyName()
    {
        return _CurrencyName;
    }

    void updateRate(float NewRate)
    {
        _Rate = NewRate;
        _update();
    }

    float rate()
    {
        return _Rate;
    }

    static ClsCurrency findByCode(string CurrencyCode)
    {

        CurrencyCode = ClsString::upperAllString(CurrencyCode);

        fstream MyFile;
        MyFile.open(_getFilePathOfCurrencies(), ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                ClsCurrency Currency = _convertLinetoCurrencyObject(Line);
                if (Currency.currencyCode() == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }
            }

            MyFile.close();
        }

        return _getEmptyCurrencyObject();
    }

    static ClsCurrency findByCountry(string Country)
    {
        Country = ClsString::upperAllString(Country);

        fstream MyFile;
        MyFile.open(_getFilePathOfCurrencies(), ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                ClsCurrency Currency = _convertLinetoCurrencyObject(Line);
                if (ClsString::upperAllString(Currency.country()) == Country)
                {
                    MyFile.close();
                    return Currency;
                }
            }

            MyFile.close();
        }

        return _getEmptyCurrencyObject();
    }

    static bool isCurrencyExist(string CurrencyCode)
    {
        ClsCurrency C1 = ClsCurrency::findByCode(CurrencyCode);
        return (!C1.isEmpty());
    }

    static vector<ClsCurrency> getCurrenciesList()
    {
        return _loadCurrencysDataFromFile();
    }
    float exchangeToUSD(float Amount)
    {
        return (float)(Amount / _Rate);
    }

    float exchangeToCurrency(float amount, ClsCurrency Currency2)
    {
        float amountExchangeToUSD = exchangeToUSD(amount);
        if (Currency2.currencyCode() == "USD")
            return amountExchangeToUSD;
        return (float)(amountExchangeToUSD * Currency2.rate());
    }
};
