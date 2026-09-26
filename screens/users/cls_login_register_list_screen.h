#pragma once
#include <iostream>
#include <iomanip>
#include "../../core/cls_user.h"
#include "../common/cls_screen.h"
#include "../../libs/cls_util.h"

class ClsLoginRegisterListScreen : protected ClsScreen
{
private:
    static void _header()
    {
        _showLine();
        cout << setw(8) << left << "" << "| " << left << setw(30) << "Date/Time";
        cout << "| " << left << setw(25) << "UserName";
        cout << "| " << left << setw(12) << "Password";
        cout << "| " << left << setw(20) << "Permissions";

        _showLine();
    }
    static void _printLogLine(ClsUser::stUserLog log)
    {
        cout << setw(8) << left << "" << "| " << setw(30) << left << log.dateTime;
        cout << "| " << setw(25) << left << log.userName;
        cout << "| " << setw(12) << left << log.password;
        cout << "| " << setw(20) << left << log.permission;
    }

public:
    static void showLoginRegisterListScreen()
    {
        vector<ClsUser::stUserLog> logs = ClsUser::getLoginLogList();
        string title = "\t Login Register List Screen";
        string subTitle = "\t (" + to_string(logs.size()) + ") Record(s)";
        _drawScreenHeader(title, subTitle);

        if (logs.size() == 0)
        {
            cout << ClsUtil::tabs(7) << " No Logins Records in the system \n";
            _showLine();
            return;
        }

        _header();
        for (ClsUser::stUserLog &log : logs)
        {
            _printLogLine(log);
            cout << "\n";
        }
        _showLine();
    }
};
