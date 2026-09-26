#include <iostream>
#include "../../core/cls_bank_client.h"
#include "../common/cls_screen.h"
#include "../../libs/cls_util.h"
#include "../../libs/cls_input_validate.h"

class ClsFindClientScreen : protected ClsScreen
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
    static void showFindClientScreen()
    {
        _drawScreenHeader("\t  Find Client Screen");
        string accountNumber = clsInputValidate::readString("Please Enter Client Account Number ? \n");

        while (!ClsBankClient::isClientExist(accountNumber))
        {
            accountNumber = clsInputValidate::readString("Account Number isn't found, Please Enter Client Account Number Again ? \n");
        }

        ClsBankClient client = ClsBankClient::find(accountNumber);
        // client.print();
        if (!client.isEmpty())
        {
            cout << "\nClient Found :-)\n";
        }
        else
        {
            cout << "\nClient Was not Found :-(\n";
        }

        _printClient(client);
    }
};
