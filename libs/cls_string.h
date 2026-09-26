#pragma once
#include <iostream>
#include <vector>
using namespace std;

class ClsString
{
private:
    string _value;

protected:
    static char _toUpper(char letter)
    {
        int ascii_value = static_cast<int>(letter);
        if (ascii_value >= 97)
        {
            return char(ascii_value - 32);
        }
        return letter;
    }
    static char _toLower(char letter)
    {
        int ascii_value = static_cast<int>(letter);
        if (ascii_value >= 65 && ascii_value <= 90)
        {
            return char(ascii_value + 32);
        }
        return letter;
    }
    static char _invertCharacter(char character)
    {
        int ascii_value = (char)character;
        if (ascii_value >= 97 && ascii_value <= 122)
        {
            return _toUpper(character);
        }
        else
        {
            return _toLower(character);
        }
    }

    static bool _isUpper(char letter)
    {
        int ascii_value = static_cast<int>(letter);
        return ascii_value >= 65 && ascii_value <= 90;
    }
    static bool _isLower(char letter)
    {
        int ascii_value = static_cast<int>(letter);
        return ascii_value >= 97 && ascii_value <= 122;
    }
    static bool _isVowel(char character)
    {
        character = _toUpper(character);
        switch (character)
        {
        case 'A':
        case 'E':
        case 'O':
        case 'I':
        case 'U':
            return true;
        default:
            return false;
        }
    }

public:
    ClsString();
    ClsString(string value)
    {
        _value = value;
    }

    void setValue(string value)
    {
        _value = value;
    }
    string getValue()
    {
        return _value;
    }

    void print()
    {
        cout << "\n"
             << _value << "\n";
    }
    // In Below the code of problems from 23 to 44 in Course 7. Algorigthms level 3.
    // Problem 23
    static void printFirstLettersOfEachWord(string text)
    {
        cout << "\nFirst letters of this string: \n";
        if (text[0] != ' ')
            cout << text[0] << endl;

        bool isViewSpace = false;
        for (int i = 1; i < text.length(); i++)
        {
            if (text[i] == ' ')
                isViewSpace = true;

            if (isViewSpace && text[i] != ' ')
            {
                cout << text[i] << endl;
                isViewSpace = false;
            }
        }
    }
    void printFirstLettersOfEachWord()
    {
        printFirstLettersOfEachWord(_value);
    }
    // ======================

    // Problem 24
    // Upper first letter of each word
    static void convertUpperFirstLettersOfEachWord(string &text)
    {
        // Same logic of last problem just change a little in code
        bool isViewSpace = true;
        for (int i = 0; i < text.length(); i++)
        {
            if (isViewSpace && text[i] != ' ')
                text[i] = _toUpper(text[i]);

            isViewSpace = (text[i] == ' ');
        }
    }
    void convertUpperFirstLettersOfEachWord()
    {
        convertUpperFirstLettersOfEachWord(_value);
    }
    // ======================

    // Problem 25
    // Lower first letter of each word
    static void convertLowerFirstLettersOfEachWord(string &text)
    {
        // Same logic of last problem just change a little in code
        bool isViewSpace = true;
        for (int i = 0; i < text.length(); i++)
        {
            if (isViewSpace && text[i] != ' ')
                text[i] = _toLower(text[i]);

            isViewSpace = (text[i] == ' ');
        }
    }
    void convertLowerFirstLettersOfEachWord()
    {
        convertLowerFirstLettersOfEachWord(_value);
    }
    // ======================

    // Problem 26
    // Upper Lower all Letters of String.
    static void toUpper(string &text)
    {

        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ')
                text[i] = _toUpper(text[i]);
        }
    }
    static string upperAllString(string text)
    {
        toUpper(text);
        return text;
    }
    void toUpper()
    {
        toUpper(_value);
    }
    static void toLower(string &text)
    {

        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ')
                text[i] = _toLower(text[i]);
        }
    }
    void toLower()
    {
        toLower(_value);
    }
    // ======================

    // Problem 28
    // Invert All Letters Case.
    static void invertLettersCase(string &text)
    {
        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ')
                text[i] = _invertCharacter(text[i]);
        }
    }
    void invertLettersCase()
    {
        invertLettersCase(_value);
    }
    // ======================

    // Problem 29
    // Count Small/Capital Letters
    static int upperLength(string text)
    {
        int counter = 0;

        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] == ' ')
                continue;
            if (_isUpper(text[i]))
                counter++;
        }

        return counter;
    }
    int upperLength()
    {
        return upperLength(_value);
    }
    static int lowerLength(string text)
    {
        int counter = 0;

        for (int i = 0; i < text.length(); i++)
        {
            if (text[i] == ' ')
                continue;
            if (_isLower(text[i]))
                counter++;
        }

        return counter;
    }
    int lowerLength()
    {
        return lowerLength(_value);
    }
    // ======================
    // problem countChracter 30 && 31
    static short countCharacter(string text, char character, bool isMatchCase = false)
    {
        short counter = 0;

        for (short i = 0; i < text.length(); i++)
        {
            if (isMatchCase)
            {
                if (text[i] == character)
                    counter++;
            }
            else
            {
                if (_toLower(text[i]) == _toLower(character))
                    counter++;
            }
        }
        return counter;
    }

    short countCharacter(char character, bool isMatchCase = false)
    {
        return countCharacter(_value, character, isMatchCase);
    }

    // ======================

    // problem countVowel 32 && 33
    static short countVowelCharacters(string text)
    {
        short counter = 0;

        for (short i = 0; i < text.length(); i++)
        {
            if (_isVowel(text[i]))
                counter++;
        }
        return counter;
    }

    short countVowelCharacters()
    {
        return countVowelCharacters(_value);
    }
    // ======================

    // problem Count Each Word In String.  36
    static short countWords(string text)
    {
        string delim = " "; // delimiter
        short Counter = 0;
        short pos = 0;
        // string sWord; // define a string variable
        // use find() function to get the position of the delimiters
        while ((pos = text.find(delim)) != std::string::npos)
        {
            //  sWord = text.substr(0, pos); // store the word
            if (text.substr(0, pos) != "")
            {
                Counter++;
            }
            // erase() until positon and move to next word.
            text.erase(0, pos + delim.length());
        }
        if (text != "")
        {
            Counter++; // it counts the last word of the string.
        }
        return Counter;
    }
    short countWords()
    {
        return countWords(_value);
    }
    // ======================

    // problem Split String  37
    static vector<string> split(string text, string delim)
    {
        vector<string> vText;
        short pos;
        string word;
        while ((pos = text.find(delim)) != string::npos)
        {

            word = text.substr(0, pos);

            vText.push_back(word);

            text.erase(0, word.length() + delim.length());
        }
        if (text != "")
            vText.push_back(text);
        return vText;
    }

    // ======================

    // problem TrimLeft, TrimRight, Trim.   39
    // Trim Right
    static void trimRight(string &text)
    {
        short lastLength = text.length() - 1;

        while (text[lastLength] == ' ')
        {
            text.erase(lastLength, 1);
            lastLength--;
        }
    }
    void trimRight()
    {
        trimRight(_value);
    }
    // Trim Left
    static void trimLeft(string &text)
    {
        int endOfSpace = 0;

        while (text[endOfSpace] == ' ')
        {
            endOfSpace++;
        }

        text.erase(0, endOfSpace);
    }
    void trimLeft()
    {
        trimLeft(_value);
    }
    void static trim(string &text)
    {
        trimLeft(text);
        trimRight(text);
    }
    void trim()
    {
        trim(_value);
    }
    // ======================

    // problem Join   40
    static string join(vector<string> vText, string delim)
    {
        string text = "";
        for (short i = 0; i < vText.size(); i++)
        {
            text += vText[i];
            if (i != vText.size() - 1)
                text += delim;
        }
        return text;
    }

    // ======================

    // problem Reverse String.   41
    static string reverseString(string text)
    {
        string reversedString = "";

        for (int i = text.length() - 1; i >= 0; i--)
        {
            reversedString += text[i];
        }
        return reversedString;
    }
    static void reverse(string &text)
    {
        text = reverseString(text);
    }
    void reverse()
    {
        _value = reverseString(_value);
    }
    // ======================

    // problem Replace 42
    static string replaceString(string text, string toReplace, string replaceTo)
    {
        int pos;

        while ((pos = text.find(toReplace)) != string::npos)
        {
            text.erase(pos, toReplace.length());
            text.insert(pos, replaceTo);
        }
        return text;
    }
    static void replace(string &text, string toReplace, string replaceTo)
    {
        text = replaceString(text, toReplace, replaceTo);
    }
    void replace(string toReplace, string replaceTo)
    {
        _value = replaceString(_value, toReplace, replaceTo);
    }

    // ======================

    // problem Length
    static short length(string text)
    {
        return text.length();
    }
    short length()
    {
        return _value.length();
    }
    // ======================

    // problem Remove Punctuations
    static string removePunctuations(string text)
    {
        string result = "";

        for (short i = 0; i < text.length(); i++)
        {
            if (!ispunct(text[i]))
            {
                result += text[i];
            }
        }
        return result;
    }
    void removePunctuations()
    {
        _value = removePunctuations(_value);
    }
    // ======================

    // problem Reverse Words In String
    static string reverseWordsInString(string text)
    {
        vector<string> vWords = split(text, " ");
        string reversedWords = "";

        vector<string>::iterator iter = vWords.end();

        while (iter != vWords.begin())
        {
            --iter;
            reversedWords += *iter + " ";
        }

        reversedWords = reversedWords.substr(0, reversedWords.length() - 1);
        return reversedWords;
    }
    void reverseWordsInString()
    {
        _value = reverseWordsInString(_value);
    }
    // ======================
};
