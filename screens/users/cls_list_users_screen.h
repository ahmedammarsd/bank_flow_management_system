#pragma once
#include <iostream>
#include <iomanip>
#include "../../core/cls_user.h"
#include "../common/cls_screen.h"
#include "../../libs/cls_util.h"

class ClsListUserssScreen : protected ClsScreen
{
private:
    static void _header()
    {
        _showLine();
        cout << setw(8) << left << "" << "| " << left << setw(12) << "UserName";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";

        _showLine();
    }
    static void _printUserLine(ClsUser user)
    {
        cout << setw(8) << left << "" << "| " << setw(12) << left << user.getUserName();
        cout << "| " << setw(25) << left << user.fullName();
        cout << "| " << setw(12) << left << user.getPhone();
        cout << "| " << setw(20) << left << user.getEmail();
        cout << "| " << setw(10) << left << user.getPassword();
        cout << "| " << setw(12) << left << user.getPermissions();
    }

public:
    static void showUsersList()
    {
        vector<ClsUser> users = ClsUser::getUsersList();
        string title = "\t Users List Screen";
        string subTitle = "\t (" + to_string(users.size()) + ") User(s)";
        _drawScreenHeader(title, subTitle);

        if (users.size() == 0)
        {
            cout << ClsUtil::tabs(7) << " No Users in the system \n";
            _showLine();
            return;
        }

        _header();
        for (ClsUser &user : users)
        {
            _printUserLine(user);
            cout << "\n";
        }
        _showLine();
    }
};
