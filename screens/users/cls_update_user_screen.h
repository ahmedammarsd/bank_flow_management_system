#include <iostream>
#include "../../core/cls_user.h"
#include "../common/cls_screen.h"
#include "../../libs/cls_util.h"
#include "../../libs/cls_input_validate.h"

class ClsUpdateUserScreen : protected ClsScreen
{
private:
    static void _readUserInfo(ClsUser &user)
    {
        if (clsInputValidate::readBoolValue("Do you want to Update the First Name ? [Y] = Yes | [N] = No ? "))
            user.setFirstName(clsInputValidate::readString("Enter The First Name ? \n"));

        if (clsInputValidate::readBoolValue("Do you want to Update the Last Name ? [Y] = Yes | [N] = No ? "))
            user.setLastName(clsInputValidate::readString("Enter the Last Name ? \n"));

        if (clsInputValidate::readBoolValue("Do you want to Update the Email ? [Y] = Yes | [N] = No ? "))
            user.setEmail(clsInputValidate::readString("Enter The Email ? \n"));

        if (clsInputValidate::readBoolValue("Do you want to Update the Phone ? [Y] = Yes | [N] = No ? "))
            user.setPhone(clsInputValidate::readString("Enter The Phone ? \n"));

        if (clsInputValidate::readBoolValue("Do you want to Update the Password ? [Y] = Yes | [N] = No ? "))
            user.setPassword(clsInputValidate::readString("Enter The Password ? \n"));

        if (clsInputValidate::readBoolValue("Do you want to Update the Permissions ? [Y] = Yes | [N] = No ? "))
            user.setPermissions(_readPermissionsToSet());
    }

    static int _readPermissionsToSet()
    {
        int permissions = 0;

        if (clsInputValidate::readBoolValue("Do you want to give full access ? [Y] = Yes | [N] = No ? "))
        {
            return -1;
        }
        cout << "\nDo you want to give access to : \n ";

        if (clsInputValidate::readBoolValue("Show Client List ? [Y] = Yes | [N] = No ? "))
        {
            permissions += ClsUser::enPermissions::pListClients;
        }
        if (clsInputValidate::readBoolValue("Add New Client ? ? [Y] = Yes | [N] = No ? "))
        {
            permissions += ClsUser::enPermissions::pAddNewClient;
            ;
        }
        if (clsInputValidate::readBoolValue("Delete Client ? [Y] = Yes | [N] = No ? "))
        {
            permissions += ClsUser::enPermissions::pDeleteClient;
        }
        if (clsInputValidate::readBoolValue("Update Client ? [Y] = Yes | [N] = No ? "))
        {
            permissions += ClsUser::enPermissions::pUpdateClient;
        }
        if (clsInputValidate::readBoolValue("Find Client ? [Y] = Yes | [N] = No ? "))
        {
            permissions += ClsUser::enPermissions::pFindClient;
        }
        if (clsInputValidate::readBoolValue("Transactions ? [Y] = Yes | [N] = No ? "))
        {
            permissions += ClsUser::enPermissions::pTransactions;
        }
        if (clsInputValidate::readBoolValue("Manage Users ? [Y] = Yes | [N] = No ? "))
        {
            permissions += ClsUser::enPermissions::pManageUsers;
        }
        if (clsInputValidate::readBoolValue("Login Registers Log ? [Y] = Yes | [N] = No ? "))
        {
            permissions += ClsUser::enPermissions::pLoginRegister;
        }
        return permissions;
    }
    static void _printUser(ClsUser &user)
    {
        cout << "\nUser Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << user.getFirstName();
        cout << "\nLastName    : " << user.getLastName();
        cout << "\nFull Name   : " << user.fullName();
        cout << "\nEmail       : " << user.getEmail();
        cout << "\nPhone       : " << user.getPhone();
        cout << "\nUser Name   : " << user.getUserName();
        cout << "\nPassword    : " << user.getPassword();
        cout << "\nPermissions : " << user.getPermissions();
        cout << "\n___________________\n";
    }

public:
    static void showUpdateUserScreen()
    {
        _drawScreenHeader("\t  Update User Screen");
        string username = clsInputValidate::readString("Please Enter Username ? \n");

        while (!ClsUser::isUserExist(username))
        {
            username = clsInputValidate::readString("Username isn't found, Please Enter Username Again ? \n");
        }

        ClsUser user = ClsUser::find(username);
        // client.print();
        _printUser(user);

        cout << "\nUpdate User\n";
        _readUserInfo(user);
        ClsUser::enSaveResults saveResult;
        saveResult = user.save();
        switch (saveResult)
        {
        case ClsUser::enSaveResults::svSucceeded:
            cout << "\n User Updated Successfully\n";
            // client.print();
            _printUser(user);
            break;

        case ClsUser::enSaveResults::svFaildEmptyObject:
            cout << "\nError, Username wasn't saved because is empty\n";
        default:
            break;
        }
    }
};
