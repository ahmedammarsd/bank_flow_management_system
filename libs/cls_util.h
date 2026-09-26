#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "cls_date.h"
using namespace std;
//  This Included Problems from fifth Course
class ClsUtil
{
public:
    static void sRand()
    {
        // Seed the random number generator with the current time.
        // This ensures that we get a different sequence of random numbers on each run.
        srand((unsigned)time(NULL));
    }

    // Problem 19
    static int randomNumber(int from, int to)
    {
        int random = rand();
        int range = to - from + 1;
        return random % range + from;
    }

    // Problem 20
    enum enCharType
    {
        smallLetter = 1,      // Represents lowercase letters (ASCII 97 to 122).
        capitalLetter = 2,    // Represents uppercase letters (ASCII 65 to 90).
        specialCharacter = 3, // Represents special characters (ASCII 33 to 47).
        digit = 4,            // Represents digits (ASCII 48 to 57).
        mixChars = 5,         // Represents a mix of all character types.
    };
    static char getRandomCharacter(enCharType CharType)
    {
        // For mixChars, randomly pick between small, capital, or digit
        if (CharType == mixChars)
        {
            CharType = (enCharType)randomNumber(1, 3);
        }

        // Use a switch-case to handle the different character types.
        switch (CharType)
        {
        case enCharType::smallLetter:
        {
            // Generate a random lowercase letter (ASCII codes 97 to 122).
            return char(randomNumber(97, 122));
            break;
        }
        case enCharType::capitalLetter:
        {
            // Generate a random uppercase letter (ASCII codes 65 to 90).
            return char(randomNumber(65, 90));
            break;
        }
        case enCharType::specialCharacter:
        {
            // Generate a random special character (ASCII codes 33 to 47).
            return char(randomNumber(33, 47));
            break;
        }
        case enCharType::digit:
        {
            // Generate a random digit (ASCII codes 48 to 57).
            return char(randomNumber(48, 57));
            break;
        }
        }
        // If an invalid type is passed, return a null character.
        return '\0';
    }
    static string generateWord(enCharType CharType, short Length)
    {
        string Word; // Initialize an empty string to build the word.

        // Loop for the number of characters specified by Length.
        for (int i = 1; i <= Length; i++)
        {
            // Append a random character of the specified type to the word.
            Word = Word + getRandomCharacter(CharType);
        }
        return Word;
    }
    static string generateKey(enCharType charType = enCharType::capitalLetter)
    {
        string Key = ""; // Initialize an empty key string.

        // Concatenate four groups of 4 random uppercase letters, separated by hyphens.
        Key = generateWord(charType, 4) + "-";
        Key = Key + generateWord(charType, 4) + "-";
        Key = Key + generateWord(charType, 4) + "-";
        Key = Key + generateWord(charType, 4);

        return Key;
    }
    static void generateKeys(short NumberOfKeys, enCharType charType = enCharType::capitalLetter)
    {
        // Loop from 1 to NumberOfKeys.
        for (int i = 1; i <= NumberOfKeys; i++)
        {
            // Print the current key number and the generated key.
            cout << "Key [" << i << "] : ";
            cout << generateKey(charType) << endl;
        }
    }

    // Problem 18
    static string encryptText(string Text, short EncryptionKey)
    {

        for (int i = 0; i <= Text.length(); i++)
        {
            // Convert the current character to its integer ASCII value,
            // add the encryption key, cast it back to char, and assign it back.
            Text[i] = char((int)Text[i] + EncryptionKey);
        }
        return Text; // Return the encrypted text.
    }

    static string decryptText(string Text, short EncryptionKey)
    {
        // Loop through each character of the text.
        // Note: Using "<= Text.length()" will process one extra character (the null terminator).
        for (int i = 0; i <= Text.length(); i++)
        {
            // Convert the current character to its ASCII integer value,
            // subtract the encryption key, cast back to char, and assign it back.
            Text[i] = char((int)Text[i] - EncryptionKey);
        }
        return Text; // Return the decrypted text.
    }

    // Swap Functions
    static void swap(int &a, int &b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    static void swap(float &a, float &b)
    {
        float temp = a;
        a = b;
        b = temp;
    }
    static void swap(double &a, double &b)
    {
        double temp = a;
        a = b;
        b = temp;
    }
    static void swap(string &a, string &b)
    {
        string temp = a;
        a = b;
        b = temp;
    }
    static void swap(char &a, char &b)
    {
        char temp = a;
        a = b;
        b = temp;
    }
    static void swap(bool &a, bool &b)
    {
        bool temp = a;
        a = b;
        b = temp;
    }
    static void swap(ClsDate &a, ClsDate &b)
    {
        ClsDate temp = a;
        a = b;
        b = temp;
    }
    // =========================

    // Fill Array with Random Numbers
    static void fillArrayWithRandomNumbers(int arr[100], int arrLength, int from, int to)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = randomNumber(from, to);
    }
    // =========================

    // Fill Array with Random Words
    static void fillArrayWithRandomWords(string arr[100], int arrLength, enCharType charType, short wordLength)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = generateWord(charType, wordLength);
    }
    // =========================

    // Fill Array with Random Keys
    static void fillArrayWithRandomKeys(string arr[100], int arrLength, enCharType charType = enCharType::capitalLetter)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = generateKey(charType);
    }
    // =========================

    // Shuffle Array - Int
    static void shuffleArray(int arr[100], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            swap(arr[randomNumber(1, arrLength) - 1], arr[randomNumber(1, arrLength) - 1]);
        }
    }
    // =========================

    // Shuffle Array - String
    static void shuffleArray(string arr[100], int arrLength)
    {
        for (int i = 0; i < arrLength; i++)
        {
            swap(arr[randomNumber(1, arrLength) - 1], arr[randomNumber(1, arrLength) - 1]);
        }
    }
    // =========================

    // Tabs - Generate Tab Characters
    static string tabs(short numberOfTabs)
    {
        string t = "";

        for (int i = 1; i < numberOfTabs; i++)
        {
            t = t + "\t";
        }
        return t;
    }
    // =========================

    // TODO: 100409 The number is not working, edge case, check it
    static string numberToText(int number)
    {
        string textNumber[19] = {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Eleven", "Twelve", "Therteen", "Fourteen", "Fivteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        string textNumber2[8] = {"Twenty", "Thirty", "Fourty", "fifty", "Sixty", "Seventy", "Eighty", "Ninty"};
        string bigNumbersDiscriptions[3] = {"Hundreds", "Thousands", "Millions"};
        if (number == 0)
            return " ";
        if (number >= 1 && number <= 19)
        {
            return textNumber[number - 1] + " ";
        }
        else if (number >= 20 && number <= 99)
        {
            return textNumber2[number / 10 - 2] + " " + numberToText(number % 10);
        }
        else if (number >= 100 && number <= 199)
        {
            return "One Hundred " + numberToText(number % 100);
        }
        else if (number >= 200 && number <= 999)
        {
            return numberToText(number / 100) + "Hundreds " + numberToText(number % 100);
        }
        else if (number >= 1000 && number <= 1999)
        {
            return "One Thousands" + numberToText(number / 1000);
        }
        else if (number >= 2000 && number <= 999999)
        {
            return numberToText(number / 1000) + "Thousands " + numberToText(number % 1000);
        }
        else if (number >= 1000000 && number <= 1999999)
        {
            return "One Million" + numberToText(number / 1000000);
        }
        else if (number >= 2000000 && number <= 999999999)
        {
            return numberToText(number / 1000000) + "Millions " + numberToText(number % 1000000);
        }
        return " ";
    }
};