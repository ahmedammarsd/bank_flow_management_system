#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include "cls_person.h"
#include "../libs/cls_string.h"
#include "../libs/cls_util.h"

using namespace std;

class ClsUser : public ClsPerson
{
public:
    struct stUserLog; // Declaration
private:
    static short encryptionKey;
    enum enMode
    {
        EmptyMode = 0,
        UpdateMode = 1,
        AddNewMode = 2
    };
    enMode _mode;
    string _userName;
    string _password;
    int _permissions;

    bool _markedForDelete = false;
    static string _getfilePath()
    {
        std::filesystem::path projectRoot = std::filesystem::path(__FILE__).parent_path().parent_path();
        return (projectRoot / "data" / "users.txt").string();
    }
    static string _getFilePathOfLoginLog()
    {
        std::filesystem::path projectRoot = std::filesystem::path(__FILE__).parent_path().parent_path();
        return (projectRoot / "data" / "login_register.txt").string();
    }
    string _prepareLogInRecord(string separator = "#//#")
    {
        string userLine = "";
        ClsDate date;
        userLine += date.getDateTime() + separator;
        userLine += getUserName() + separator;
        userLine += ClsUtil::encryptText(getPassword(), encryptionKey) + separator; // getPassword() + separator;
        userLine += to_string(getPermissions());
        return userLine;
    }

    static ClsUser _convertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = ClsString::split(Line, Seperator);

        return ClsUser(enMode::UpdateMode, vUserData[0], vUserData[1], vUserData[2],
                       vUserData[3], vUserData[4],
                       // vUserData[5]
                       ClsUtil::decryptText(vUserData[5], encryptionKey),
                       stoi(vUserData[6]));
    }

    static string _converUserObjectToLine(ClsUser User, string Seperator = "#//#")
    {

        string UserRecord = "";
        UserRecord += User.getFirstName() + Seperator;
        UserRecord += User.getLastName() + Seperator;
        UserRecord += User.getEmail() + Seperator;
        UserRecord += User.getPhone() + Seperator;
        UserRecord += User.getUserName() + Seperator;
        UserRecord += ClsUtil::encryptText(User.getPassword(), encryptionKey) + Seperator; // User.getPassword() + Seperator;
        UserRecord += to_string(User.getPermissions());

        return UserRecord;
    }

    static vector<ClsUser> _loadUsersDataFromFile()
    {

        vector<ClsUser> vUsers;

        fstream MyFile;
        MyFile.open(_getfilePath(), ios::in); // read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                ClsUser User = _convertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();
        }

        return vUsers;
    }

    static stUserLog _convertLineToUserStruct(string line, string separator = "#//#")
    {
        vector<string> vUser;
        vUser = ClsString::split(line, separator);

        stUserLog userLog;
        userLog.dateTime = vUser[0];
        userLog.userName = vUser[1];
        userLog.password = ClsUtil::decryptText(vUser[2], encryptionKey); // vUser[2];
        userLog.permission = vUser[3];
        return userLog;
    }
    static vector<stUserLog> _loadLoginRegisterLogFile()
    {
        vector<stUserLog> vUsers;

        fstream MyFile;
        MyFile.open(_getFilePathOfLoginLog(), ios::in); // read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                stUserLog User = _convertLineToUserStruct(Line);

                vUsers.push_back(User);
            }

            MyFile.close();
        }

        return vUsers;
    }

    static void _saveUsersDataToFile(vector<ClsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open(_getfilePath(), ios::out); // overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (ClsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    // we only write records that are not marked for delete.
                    DataLine = _converUserObjectToLine(U);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();
        }
    }

    void _update()
    {
        vector<ClsUser> _vUsers;
        _vUsers = _loadUsersDataFromFile();

        for (ClsUser &U : _vUsers)
        {
            if (U.getUserName() == _userName)
            {
                U = *this;
                break;
            }
        }

        _saveUsersDataToFile(_vUsers);
    }

    void _addNew()
    {

        _addDataLineToFile(_converUserObjectToLine(*this));
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

    static ClsUser _getEmptyUserObject()
    {
        return ClsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:
    enum enSaveResults
    {
        svFaildEmptyObject = 0,
        svSucceeded = 1,
        svFaildUserExists = 2
    };
    enum enPermissions
    {
        pAll = -1,
        pListClients = 1,
        pAddNewClient = 2,
        pDeleteClient = 4,
        pUpdateClient = 8,
        pFindClient = 16,
        pTransactions = 32,
        pManageUsers = 64,
        pLoginRegister = 128
    };
    struct stUserLog
    {
        string dateTime;
        string userName;
        string password;
        string permission;
    };
    ClsUser(enMode Mode, string FirstName, string LastName,
            string Email, string Phone, string UserName, string Password,
            int Permissions) : ClsPerson(FirstName, LastName, Email, Phone)

    {
        _mode = Mode;
        _userName = UserName;
        _password = Password;
        _permissions = Permissions;
    }

    bool isEmpty()
    {
        return (_mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _markedForDelete;
    }

    string getUserName()
    {
        return _userName;
    }

    void setUserName(string UserName)
    {
        _userName = UserName;
    }

    void setPassword(string Password)
    {
        _password = Password;
    }

    string getPassword()
    {
        return _password;
    }

    void setPermissions(int Permissions)
    {
        _permissions = Permissions;
    }

    int getPermissions()
    {
        return _permissions;
    }

    static ClsUser find(string UserName)
    {
        fstream MyFile;
        MyFile.open(_getfilePath(), ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                ClsUser User = _convertLinetoUserObject(Line);
                if (User.getUserName() == UserName)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }

        return _getEmptyUserObject();
    }

    static ClsUser find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open(_getfilePath(), ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                ClsUser User = _convertLinetoUserObject(Line);
                if (User.getUserName() == UserName && User.getPassword() == Password)
                {
                    MyFile.close();
                    return User;
                }
            }

            MyFile.close();
        }
        return _getEmptyUserObject();
    }

    enSaveResults save()
    {

        switch (_mode)
        {
        case enMode::EmptyMode:
        {
            if (isEmpty())
            {
                return enSaveResults::svFaildEmptyObject;
            }
        }

        case enMode::UpdateMode:
        {
            _update();
            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            // This will add new record to file or database
            if (ClsUser::isUserExist(_userName))
            {
                return enSaveResults::svFaildUserExists;
            }
            else
            {
                _addNew();
                // We need to set the mode to update after add new
                _mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }

        return enSaveResults::svFaildEmptyObject;
    }

    static bool isUserExist(string UserName)
    {

        ClsUser User = ClsUser::find(UserName);
        return (!User.isEmpty());
    }

    bool Delete()
    {
        vector<ClsUser> _vUsers;
        _vUsers = _loadUsersDataFromFile();

        for (ClsUser &U : _vUsers)
        {
            if (U.getUserName() == _userName)
            {
                U._markedForDelete = true;
                break;
            }
        }

        _saveUsersDataToFile(_vUsers);

        *this = _getEmptyUserObject();

        return true;
    }

    static ClsUser getAddNewUserObject(string UserName)
    {
        return ClsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector<ClsUser> getUsersList()
    {
        return _loadUsersDataFromFile();
    }

    bool hasPermission(enPermissions permission)
    {
        // if (_permissions == enPermissions::pAll || _permissions & permission)
        //     return true;
        // else
        //     return false;
        // }

        if (this->getPermissions() == enPermissions::pAll)
            return true;

        if ((this->getPermissions() & permission) == permission)
            return true;
        else
            return false;
    }

    void registerLogIn()
    {

        string stDataLine = _prepareLogInRecord();

        fstream MyFile;
        MyFile.open(_getFilePathOfLoginLog(), ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }
    }

    static vector<stUserLog> getLoginLogList()
    {
        return _loadLoginRegisterLogFile();
    }

    // static void encriptPasswordInUserFileAndSave()
    // {
    //     fstream MyFile;
    //     vector<ClsUser> vUsers = _loadUsersDataFromFile();
    //     MyFile.open(_getfilePath(), ios::app); // write Mode
    //     if (MyFile.is_open())
    //     {
    //         for (ClsUser User : vUsers)
    //         {
    //             MyFile << _converUserObjectToLine(User, "#//#") << endl;
    //         }
    //         MyFile.close();
    //     }
    // }
};

short ClsUser::encryptionKey = 10;
