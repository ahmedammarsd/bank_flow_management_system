#include <iostream>
#include "../../core/cls_user.h"
#include "../common/cls_screen.h"
#include "../../libs/cls_util.h"
#include "../../libs/cls_input_validate.h"

class ClsDeleteUserScreen : protected ClsScreen
{

private:
    static void _printUser(ClsUser &user)
    {
        cout << "\n User Card:";
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
    static void showDeleteClientScreen()
    {
        _drawScreenHeader("\t  Delete User Screen");
        string username = clsInputValidate::readString("Please Enter Username ? \n");

        while (!ClsUser::isUserExist(username))
        {
            username = clsInputValidate::readString("Username is not exists, Please Enter Username Again ? \n");
        }

        ClsUser user = ClsUser::find(username);
        // client.print();
        _printUser(user);

        bool isDelete = clsInputValidate::readBoolValue("Are you sure you want to delete this user ? [Y] = Yes | [N] = No ? ");
        if (!isDelete)
            return;

        if (user.Delete())
        {
            cout << "\n User Deleted Successfully\n";
            // client.print();
            _printUser(user);
        }
        else
            cout << "\nError, User wasn't deleted\n";
    }
};
