#pragma once
#include <iostream>
#include <string>
#include "cls_date.h"
using namespace std;

class clsInputValidate
{
public:
    static bool IsNumber(string strInput)
    {
        for (char c : strInput)
        {
            if (!isdigit(c))
                return false;
        }
        return true;
    }

    static bool isNumberBetween(int number, int from, int to)
    {
        return number >= from && number <= to;
    }

    static bool isNumberBetween(float number, float from, float to)
    {
        return number >= from && number <= to;
    }
    static bool isNumberBetween(double number, double from, double to)
    {
        return number >= from && number <= to;
    }

    static bool isDateBetween(ClsDate date, ClsDate startDate, ClsDate endDate)
    {
        return date.isDateAfterDate2(startDate) && date.isDateBeforeDate2(endDate);
    }

    static bool isValidDate(ClsDate date)
    {
        return ClsDate::isValidDate(date);
    }

    // Read Int Number
    static int readIntNumber(string errMessage = "Invalid Number, Enter Again ?\n")
    {
        int number;
        cin >> number;
        while (cin.fail())
        {
            // User didn't enter a number

            // resets the error state
            cin.clear();
            /*
            important to add [ std::numeric_limits<std::streamsize>::max(),'\n' ]
            inside the ignore,
            becaue if I didn't add it will loop depend of length that enter from user,
            and this to ignore the text that enterd by the user.

            cin.clear() // resets the error state
            عشان تقبل يكون عندنا عملية ادخال جديدة ثم بقا عشان امنع ان ميتمش
             ادخال البيانات الخاطئة اللي لسة في الذاكرة المؤقتة او البافر لازم نعمل
            cin.ignore() // عشان تمسح الحروف اللي متخزنة في البافر
            لكن هي لوحدها كدا بتمسح حرف واحد
             انما طريقة الدكتور بتخليها تمسح كل البيانات المدخلة في البافر تمامًا
             عشان حتى لو كان مكتوب اكثر من الف حرف يتشالوا" وبالتالي تمنع الــ
            cin
            */
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << errMessage;
            cin >> number;
        }
        return number;
    }
    static int readIntNumberBetween(int from, int to, string errMessage = "Number isn't within range, Enter Again ?\n")
    {
        int number;
        bool isValidNumber;
        do
        {
            number = readIntNumber();
            isValidNumber = isNumberBetween(number, from, to);
            if (!isValidNumber)
                cout << errMessage;
        } while (!isValidNumber);

        return number;
    }

    static int readShortNumber(string errMessage = "Invalid Number, Enter Again ?\n")
    {
        short number;
        cin >> number;
        while (cin.fail())
        {
            // User didn't enter a number

            // resets the error state
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << errMessage;
            cin >> number;
        }
        return number;
    }
    static int readShortNumberBetween(short from, short to, string errMessage = "Number isn't within range, Enter Again ?\n")
    {
        int number;
        bool isValidNumber;
        do
        {
            number = readIntNumber();
            isValidNumber = isNumberBetween(number, from, to);
            if (!isValidNumber)
                cout << errMessage;
        } while (!isValidNumber);

        return number;
    }

    static double readDoubleNumber(string errMessage = "Invalid Double Number, Enter Again ?\n")
    {
        double number;
        while (!(cin >> number))
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << errMessage;
            cin >> number;
        }
        return number;
    }

    static double readDoubleNumberBetween(double from, double to, string errMessage = "Double Number isn't within range, Enter Again ?\n")
    {
        double number;
        bool isValidNumber;
        do
        {
            number = readDoubleNumber();
            isValidNumber = isNumberBetween(number, from, to);
            if (!isValidNumber)
                cout << errMessage;
        } while (!isValidNumber);

        return number;
    }

    static float readFloatNumber(string message = "Please Enter a Number ?\n")
    {
        float number;
        cout << message;
        cin >> number;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid Number, Try to enter a number \n";
            cin >> number;
        }
        return number;
    }

    // Read String
    static string readString(string message)
    {
        string text;
        cout << message;
        // Usage of std::ws will extract allthe whitespace character
        getline(cin >> ws, text);

        // If you have control over the inputs class, modify readString() to handle the newline:
        //  If the input is empty (due to leftover newline), read again
        if (text.empty() && std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, text);
        }
        return text;
    }

    static bool readBoolValue(string message = "Enter ? [Y] = Yes | [N] = No \n")
    {
        char val = 'Y';
        bool isValAccepted;
        do
        {
            cout << message;
            cin >> val;
            isValAccepted = toupper(val) == 'Y' || toupper(val) == 'N';
            if (!isValAccepted)
            {
                cout << "Invalid answer\n";
            }
        } while (!isValAccepted);
        return toupper(val) == 'Y';
    }
};