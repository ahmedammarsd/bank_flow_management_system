/**
 *
 * I wrote this code, but I'm not used it I updated it with same way
 * that teacher solve it,
 * This code also same way but in the user class,
 * The different that only I separate this class
 */

#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include "../libs/cls_string.h"
#include "../libs/cls_date.h"
#include "cls_user.h"
using namespace std;

class ClsLoginLogger
{
private:
    static string _getFilePath()
    {
        std::filesystem::path projectRoot = std::filesystem::path(__FILE__).parent_path().parent_path();
        return (projectRoot / "data" / "login_register.txt").string();
    }

    static string _convertUserToLine(ClsUser user, string separator = "#//#")
    {
        string userLine = "";
        ClsDate date;
        userLine += date.getDateTime() + separator;
        userLine += user.getUserName() + separator;
        userLine += user.getPassword() + separator;
        userLine += to_string(user.getPermissions());
        return userLine;
    }

public:
    static void addToLoginLogFile(ClsUser user)
    {
        fstream file;
        file.open(_getFilePath(), ios::app);

        if (file.is_open())
        {
            file << _convertUserToLine(user) << endl;
        }
        file.close();
    }
};
