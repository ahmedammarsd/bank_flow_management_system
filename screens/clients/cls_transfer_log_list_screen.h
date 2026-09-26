#pragma once
#include <iostream>
#include <iomanip>
#include "../../core/cls_bank_client.h"
#include "../common/cls_screen.h"
#include "../../libs/cls_util.h"

class ClsTransferLogListScreen : protected ClsScreen
{
private:
    static void _header()
    {
        _showLine();
        cout << setw(2) << left << "" << "| " << left << setw(22) << "Date/Time";
        cout << "| " << left << setw(15) << "s.Account";
        cout << "| " << left << setw(15) << "d.Account";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(15) << "s.Balance";
        cout << "| " << left << setw(15) << "d.Balance";
        cout << "| " << left << setw(15) << "User";

        _showLine();
    }
    static void _printLogLine(ClsBankClient::stTransferLog log)
    {
        cout << setw(2) << left << "" << "| " << left << setw(22) << log.dateAndTime;
        cout << "| " << left << setw(15) << log.sourceAccountNumber;
        cout << "| " << left << setw(15) << log.destinationAccountNumber;
        cout << "| " << left << setw(10) << log.amount;
        cout << "| " << left << setw(15) << log.sourceBalance;
        cout << "| " << left << setw(15) << log.destinationBalance;
        cout << "| " << left << setw(15) << log.userName;
    }

public:
    static void showTransferLogListScreen()
    {
        vector<ClsBankClient::stTransferLog> logs = ClsBankClient::getTransferLogsList();
        string title = "\t Transfer Log List Screen";
        string subTitle = "\t (" + to_string(logs.size()) + ") Record(s)";
        _drawScreenHeader(title, subTitle);

        if (logs.size() == 0)
        {
            cout << ClsUtil::tabs(7) << " No Transfer Log Records in the system \n";
            _showLine();
            return;
        }

        _header();
        for (ClsBankClient::stTransferLog &log : logs)
        {
            _printLogLine(log);
            cout << "\n";
        }
        _showLine();
    }
};
