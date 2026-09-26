#include <iostream>
#include "../../core/cls_user.h"
#include "../common/cls_screen.h"
#include "../../libs/cls_util.h"
#include "../../libs/cls_input_validate.h"

class ClsFindUserScreen : protected ClsScreen
{
private:
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

    static void _printPermissions(int permissions)
    {
        switch (permissions)
        {
        case -1:
            cout << "\n\t - Full Access  \n";
            break;
        case 0:
            cout << "\n\t - No Access  \n";
            break;
        default:
            if (permissions & ClsUser::enPermissions::pListClients)
                cout << "\n\t - View Clients  \n";
            if (permissions & ClsUser::enPermissions::pAddNewClient)
                cout << "\n\t - Add New Client  \n";
            if (permissions & ClsUser::enPermissions::pUpdateClient)
                cout << "\n\t - Edit Client  \n";
            if (permissions & ClsUser::enPermissions::pDeleteClient)
                cout << "\n\t - Delete Client  \n";
            if (permissions & ClsUser::enPermissions::pFindClient)
                cout << "\n\t - Find Client  \n";
            if (permissions & ClsUser::enPermissions::pTransactions)
                cout << "\n\t - Transaction  \n";
            if (permissions & ClsUser::enPermissions::pManageUsers)
                cout << "\n\t - Manage Users  \n";
        }
    };

public:
    static void showFindUserScreen()
    {
        _drawScreenHeader("\t  Find User Screen");
        string user = clsInputValidate::readString("Please Enter Username ? \n");

        while (!ClsUser::isUserExist(user))
        {
            user = clsInputValidate::readString("Username isn't found, Please Enter Username Again ? \n");
        }

        ClsUser client = ClsUser::find(user);
        // client.print();
        if (!client.isEmpty())
        {
            cout << "\n User Found :-)\n";
        }
        else
        {
            cout << "\n User Was not Found :-(\n";
        }

        _printUser(client);
        cout << "\nPermissions:";
        _printPermissions(client.getPermissions());
    }
};
