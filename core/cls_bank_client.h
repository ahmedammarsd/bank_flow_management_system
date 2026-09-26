#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include "cls_person.h"
#include "../libs/cls_string.h"
#include <vector>
#include <fstream>

using namespace std;

class ClsBankClient : public ClsPerson
{
public:
    struct stTransferLog
    {
        string dateAndTime;
        string sourceAccountNumber;
        string destinationAccountNumber;
        double amount;
        double sourceBalance;
        double destinationBalance;
        string userName;
    };

private:
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };

    enMode _mode;
    string _accountNumber;
    string _pinCode;
    float _accountBalance;
    bool _markedForDelete = false;

    static ClsBankClient _convertLinetoClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = ClsString::split(Line, Seperator);

        return ClsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
                             vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static string _converClientObjectToLine(ClsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.getFirstName() + Seperator;
        stClientRecord += Client.getLastName() + Seperator;
        stClientRecord += Client.getEmail() + Seperator;
        stClientRecord += Client.getPhone() + Seperator;
        stClientRecord += Client.accountNumber() + Seperator;
        stClientRecord += Client.getPinCode() + Seperator;
        stClientRecord += to_string(Client.getAccountBalance());

        return stClientRecord;
    }

    string _prepareLogInRecord(double amount, ClsBankClient destinationClient, string separator = "#//#")
    {
        string transferLogLine = "";
        ClsDate date;
        transferLogLine += date.getDateTime() + separator;
        transferLogLine += accountNumber() + separator;
        transferLogLine += destinationClient.accountNumber() + separator;
        transferLogLine += to_string(amount) + separator;
        transferLogLine += to_string(getAccountBalance()) + separator;
        transferLogLine += to_string(destinationClient.getAccountBalance()) + separator;
        transferLogLine += currentUser.getUserName();

        return transferLogLine;
    }
    static ClsBankClient _getEmptyClientObject()
    {
        return ClsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static string _getfilePath()
    {
        std::filesystem::path projectRoot = std::filesystem::path(__FILE__).parent_path().parent_path();
        return (projectRoot / "data" / "clients.txt").string();
    }
    static string _getfilePathOfTransferLog()
    {
        std::filesystem::path projectRoot = std::filesystem::path(__FILE__).parent_path().parent_path();
        return (projectRoot / "data" / "transfer_log.txt").string();
    }
    static vector<ClsBankClient> _loadClientsDataFromFile()
    {

        vector<ClsBankClient> vClients;

        fstream MyFile;
        MyFile.open(_getfilePath(), ios::in); // read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                ClsBankClient Client = _convertLinetoClientObject(Line);

                vClients.push_back(Client);
            }

            MyFile.close();
        }

        return vClients;
    }

    static void _saveCleintsDataToFile(vector<ClsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open(_getfilePath(), ios::out); // overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (ClsBankClient C : vClients)
            {
                if (C._markedForDelete)
                    continue;
                DataLine = _converClientObjectToLine(C);
                MyFile << DataLine << endl;
            }

            MyFile.close();
        }
    }

    void _update()
    {
        vector<ClsBankClient> _vClients;
        _vClients = _loadClientsDataFromFile();

        for (ClsBankClient &c : _vClients)
        {
            if (c.accountNumber() == _accountNumber)
            {
                c = *this;
                break;
            }
        }

        _saveCleintsDataToFile(_vClients);
    }

    void _addNew()
    {

        _addDataLineToFile(_converClientObjectToLine(*this));
    }

    void _addDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open(_getfilePath(), ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    void _registerRecordOfTransferLog(double amount, ClsBankClient destinationClient)
    {

        string stDataLine = _prepareLogInRecord(amount, destinationClient);

        fstream MyFile;
        MyFile.open(_getfilePathOfTransferLog(), ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    static stTransferLog _convertLineToTransferLogStruct(string line, string separator = "#//#")
    {
        vector<string> vTransferLog;
        vTransferLog = ClsString::split(line, separator);

        stTransferLog transferLog;
        transferLog.dateAndTime = vTransferLog[0];
        transferLog.sourceAccountNumber = vTransferLog[1];
        transferLog.destinationAccountNumber = vTransferLog[2];
        transferLog.amount = stod(vTransferLog[3]);
        transferLog.sourceBalance = stod(vTransferLog[4]);
        transferLog.destinationBalance = stod(vTransferLog[5]);
        transferLog.userName = vTransferLog[6];

        return transferLog;
    }
    static vector<stTransferLog> _loadTransferLogFile()
    {
        vector<stTransferLog> vTransferLogs;

        fstream MyFile;
        MyFile.open(_getfilePathOfTransferLog(), ios::in); // read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                stTransferLog transferLog = _convertLineToTransferLogStruct(Line);

                vTransferLogs.push_back(transferLog);
            }

            MyFile.close();
        }

        return vTransferLogs;
    }

public:
    ClsBankClient(enMode mode, string firstName, string lastName,
                  string email, string phone, string accountNumber, string pinCode,
                  float accountBalance) : ClsPerson(firstName, lastName, email, phone)

    {
        _mode = mode;
        _accountNumber = accountNumber;
        _pinCode = pinCode;
        _accountBalance = accountBalance;
    }

    bool isEmpty()
    {
        return (_mode == enMode::EmptyMode);
    }

    string accountNumber()
    {
        return _accountNumber;
    }

    void setPinCode(string pinCode)
    {
        _pinCode = pinCode;
    }

    string getPinCode()
    {
        return _pinCode;
    }

    void setAccountBalance(float accountBalance)
    {
        _accountBalance = accountBalance;
    }

    float getAccountBalance()
    {
        return _accountBalance;
    }
    void deposit(double amount)
    {
        _accountBalance += amount;
        save();
    }
    bool withdraw(double amount)
    {
        if (amount > _accountBalance)
            return false;
        _accountBalance -= amount;
        save();
        return true;
    }
    static ClsBankClient find(string AccountNumber)
    {

        fstream MyFile;
        MyFile.open(_getfilePath(), ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                ClsBankClient Client = _convertLinetoClientObject(Line);
                if (Client.accountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }

        return _getEmptyClientObject();
    }

    static ClsBankClient find(string accountNumber, string pinCode)
    {
        fstream MyFile;
        MyFile.open(_getfilePath(), ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                ClsBankClient Client = _convertLinetoClientObject(Line);
                if (Client.accountNumber() == accountNumber && Client.getPinCode() == pinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }

            MyFile.close();
        }
        return _getEmptyClientObject();
    }

    static bool isClientExist(string accountNumber)
    {
        ClsBankClient Client1 = ClsBankClient::find(accountNumber);
        return (!Client1.isEmpty());
    }

    // Why I commented it, because, No UI code Related inside object
    // void print()
    // {
    //     cout << "\nClient Card:";
    //     cout << "\n___________________";
    //     cout << "\nFirstName   : " << getFirstName();
    //     cout << "\nLastName    : " << getLastName();
    //     cout << "\nFull Name   : " << fullName();
    //     cout << "\nEmail       : " << getEmail();
    //     cout << "\nPhone       : " << getPhone();
    //     cout << "\nAcc. Number : " << _accountNumber;
    //     cout << "\nPassword    : " << _pinCode;
    //     cout << "\nBalance     : " << _accountBalance;
    //     cout << "\n___________________\n";
    // }

    /// Save
    enum enSaveResult
    {
        FailedEmptyObject = 0,
        Succeeded = 1,
        FailedAccountNumberExist = 2
    };
    enSaveResult save()
    {
        switch (_mode)
        {
        case enMode::EmptyMode:
            return enSaveResult::FailedEmptyObject;
        case enMode::UpdateMode:
            _update();
            return enSaveResult::Succeeded;
        case enMode::AddNewMode:
        {
            if (isClientExist(_accountNumber))
                return enSaveResult::FailedAccountNumberExist;
            else
            {
                _addNew();
                // We need to set the mode to update after add new
                _mode = enMode::UpdateMode;
                return enSaveResult::Succeeded;
            }
        }
        default:
            return enSaveResult::FailedEmptyObject;
        }
    }
    // =====================================

    // Get Add New Client Object
    static ClsBankClient getAddNewClientObject(string accountNumber)
    {
        return ClsBankClient(enMode::AddNewMode, "", "", "", "", accountNumber, "", 0);
    }

    // Delete Client
    bool deleteC()
    {
        vector<ClsBankClient> vClients;
        vClients = _loadClientsDataFromFile();
        bool isDeleted = false;

        for (ClsBankClient &c : vClients)
        {
            if (c.accountNumber() == _accountNumber)
            {
                // If not use _markedForDelete, we can use the below code to delete the client from the vector
                // vClients.erase(std::remove(vClients.begin(), vClients.end(), c), vClients.end());
                c._markedForDelete = true;
                isDeleted = true;
                break;
            }
        }
        *this = _getEmptyClientObject();

        _saveCleintsDataToFile(vClients);
        return isDeleted;
    }

    static vector<ClsBankClient> getClientsList()
    {
        return _loadClientsDataFromFile();
    }

    static double totalBalances()
    {
        vector<ClsBankClient> vClients = ClsBankClient::getClientsList();
        double total = 0;
        for (ClsBankClient &c : vClients)
        {
            total += c.getAccountBalance();
        }
        return total;
    }

    enum enTransferResult
    {

        FailedAmountLessThanZero = 2,
        FailedInsufficientBalance = 3,
        FailedSameAccountNumber = 4,
        transferSucceeded = 5,
    };

    enTransferResult transfer(double amount, ClsBankClient &destinationClient)
    {
        if (amount <= 0)
            return enTransferResult::FailedAmountLessThanZero;
        if (amount > _accountBalance)
            return enTransferResult::FailedInsufficientBalance;
        else if (destinationClient.accountNumber() == _accountNumber)
            return enTransferResult::FailedSameAccountNumber;
        else
        {
            withdraw(amount);
            destinationClient.deposit(amount);
            _registerRecordOfTransferLog(amount, destinationClient);
            return enTransferResult::transferSucceeded;
        }
    }

    static vector<stTransferLog> getTransferLogsList()
    {
        return _loadTransferLogFile();
    }
};

// Ø§ÙŠ Ø­Ø¯ Ø¨ÙŠØ³ØªØ®Ø¯Ù… vsc
// ctrl + k
// Ø¨Ø¹Ø¯ ÙƒØ¯Ù‡
// ctrl + j
// Ù„Ù„ÙØªØ­ Ø§Ù…Ø§ Ù„Ù„Ø§ØºÙ„Ø§Ù‚:
// ctrl + k
// Ø¨Ø¹Ø¯ ÙƒØ¯Ù‡
// ctrl + 0
// Ø§Ù†Øª Ù„Ø§Ø²Ù… ØªØ¶ØºØ· Ø§Ù„Ø§ØªÙ†ÙŠÙ† ÙƒÙˆÙ†ØªØ±ÙˆÙ„ ÙƒÙŠÙ‡ ÙˆØ§Ù„ Ø¨Ø¹Ø¯ÙŠÙ‡Ø§
