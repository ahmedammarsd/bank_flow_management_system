#include <iostream>
#include "../../core/cls_bank_client.h"
#include "../common/cls_screen.h"
#include "../../libs/cls_util.h"

class ClsAddNewClientScreen : protected ClsScreen
{

private:
    static void _readClientInfo(ClsBankClient &client)
    {

        client.setFirstName(clsInputValidate::readString("Enter The First Name ? \n"));

        client.setLastName(clsInputValidate::readString("Enter the Last Name ? \n"));

        client.setEmail(clsInputValidate::readString("Enter The Email ? \n"));

        client.setPhone(clsInputValidate::readString("Enter The Phone ? \n"));

        client.setPinCode(clsInputValidate::readString("Enter The PinCode ? \n"));

        client.setAccountBalance(clsInputValidate::readFloatNumber("Enter The Account Balance ? \n"));
    }

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
    static void showAddNewClientScreen()
    {
        _drawScreenHeader("\t  Add New Client Screen");
        string accountNumber = clsInputValidate::readString("Please Enter Client Account Number ? \n");

        while (ClsBankClient::isClientExist(accountNumber))
        {
            accountNumber = clsInputValidate::readString("Account Number is already exists, Please Enter Client Account Number Again ? \n");
        }

        ClsBankClient client = ClsBankClient::getAddNewClientObject(accountNumber);

        _readClientInfo(client);

        ClsBankClient::enSaveResult saveResult;
        saveResult = client.save();
        switch (saveResult)
        {
        case ClsBankClient::enSaveResult::Succeeded:
            cout << "\nAccount Added Successfully\n";
            // client.print();
            _printClient(client);
            break;

        case ClsBankClient::enSaveResult::FailedEmptyObject:
            cout << "\nError, Account wasn't saved because is empty\n";
            break;
        case ClsBankClient::enSaveResult::FailedAccountNumberExist:
            cout << "\nError, Account wasn't saved because Account Number is already exists\n";
            break;
        default:
            break;
        }
    }
};
