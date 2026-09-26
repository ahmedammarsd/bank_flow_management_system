#include <iostream>
#include "../../core/cls_bank_client.h"
#include "../common/cls_screen.h"
#include "../../libs/cls_util.h"
#include "../../libs/cls_input_validate.h"

class ClsDeleteClientScreen : protected ClsScreen
{

private:
    static void _printClient(ClsBankClient &client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << client.getFirstName();
        cout << "\nLastName    : " << client.getLastName();
        cout << "\nFull Name   : " << client.fullName();
        cout << "\nEmail       : " << client.getEmail();
        cout << "\nPhone       : " << client.getPhone();
        cout << "\nAcc. Number : " << client.accountNumber();
        cout << "\nPassword    : " << client.getPinCode();
        cout << "\nBalance     : " << client.getAccountBalance();
        cout << "\n___________________\n";
    }

public:
    static void showDeleteClientScreen()
    {
        _drawScreenHeader("\t  Delete Client Screen");
        string accountNumber = clsInputValidate::readString("Please Enter Client Account Number ? \n");

        while (!ClsBankClient::isClientExist(accountNumber))
        {
            accountNumber = clsInputValidate::readString("Account Number is not exists, Please Enter Client Account Number Again ? \n");
        }

        ClsBankClient client = ClsBankClient::find(accountNumber);
        // client.print();
        _printClient(client);

        bool isDelete = clsInputValidate::readBoolValue("Are you sure you want to delete this client ? [Y] = Yes | [N] = No ? ");
        if (!isDelete)
            return;

        if (client.deleteC())
        {
            cout << "\nAccount Deleted Successfully\n";
            // client.print();
            _printClient(client);
        }
        else
            cout << "\nError, Account wasn't deleted\n";
    }
};
