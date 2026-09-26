#include <iostream>
#include "../../core/cls_bank_client.h"
#include "../common/cls_screen.h"
#include "../../libs/cls_util.h"
#include "../../libs/cls_input_validate.h"

class ClsUpdateClientScreen : protected ClsScreen
{
private:
    static void _readClientInfo(ClsBankClient &client)
    {
        if (clsInputValidate::readBoolValue("Do you want to Update the First Name ? [Y] = Yes | [N] = No ? "))
            client.setFirstName(clsInputValidate::readString("Enter The First Name ? \n"));

        if (clsInputValidate::readBoolValue("Do you want to Update the Last Name ? [Y] = Yes | [N] = No ? "))
            client.setLastName(clsInputValidate::readString("Enter the Last Name ? \n"));

        if (clsInputValidate::readBoolValue("Do you want to Update the Email ? [Y] = Yes | [N] = No ? "))
            client.setEmail(clsInputValidate::readString("Enter The Email ? \n"));

        if (clsInputValidate::readBoolValue("Do you want to Update the Phone ? [Y] = Yes | [N] = No ? "))
            client.setPhone(clsInputValidate::readString("Enter The Phone ? \n"));

        if (clsInputValidate::readBoolValue("Do you want to Update the PinCode ? [Y] = Yes | [N] = No ? "))
            client.setPhone(clsInputValidate::readString("Enter The PinCode ? \n"));

        if (clsInputValidate::readBoolValue("Do you want to Update the AccountBalance ? [Y] = Yes | [N] = No ? "))
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
    static void showUpdateClientScreen()
    {
        _drawScreenHeader("\t  Update Client Screen");
        string accountNumber = clsInputValidate::readString("Please Enter Client Account Number ? \n");

        while (!ClsBankClient::isClientExist(accountNumber))
        {
            accountNumber = clsInputValidate::readString("Account Number isn't found, Please Enter Client Account Number Again ? \n");
        }

        ClsBankClient client = ClsBankClient::find(accountNumber);
        // client.print();
        _printClient(client);

        cout << "\nUpdate Client\n";
        _readClientInfo(client);
        ClsBankClient::enSaveResult saveResult;
        saveResult = client.save();
        switch (saveResult)
        {
        case ClsBankClient::enSaveResult::Succeeded:
            cout << "\nAccount Updated Successfully\n";
            // client.print();
            _printClient(client);
            break;

        case ClsBankClient::enSaveResult::FailedEmptyObject:
            cout << "\nError, Account wasn't saved because is empty\n";
        default:
            break;
        }
    }
};
