#include <iostream>
#include "../../core/cls_bank_client.h"
#include "../common/cls_screen.h"
#include "../../libs/cls_util.h"
#include "../../libs/cls_input_validate.h"
using namespace std;

class ClsDepositScreen : protected ClsScreen
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
    static void showDepositScreen()
    {
        _drawScreenHeader("\t\tDeposit Screen");
        string accountNumber = clsInputValidate::readString("Please Enter Client Account Number ? \n");
        while (!ClsBankClient::isClientExist(accountNumber))
        {
            accountNumber = clsInputValidate::readString("Client isn't found, Please Enter Client Account Number Again ? \n");
        }
        ClsBankClient client = ClsBankClient::find(accountNumber);
        _printClient(client);

        double amount = 0;
        cout << "Please enter double deposit amount? ";
        amount = clsInputValidate::readDoubleNumber("Please enter double deposit amount? ");

        bool answer = clsInputValidate::readBoolValue("Are you sure you want to perform this transaction? [Y] = Yes | [N] = No ? ");

        if (answer)
        {
            client.deposit(amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance Is: " << client.getAccountBalance() << endl;
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};
