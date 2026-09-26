#include <iostream>
#include "../common/cls_screen.h"
#include "../../core/cls_bank_client.h"
#include "../../libs/cls_input_validate.h"

class ClsTransferScreen : protected ClsScreen
{

private:
    static void _printClient(ClsBankClient &client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << client.fullName();
        cout << "\nAcc. Number : " << client.accountNumber();
        cout << "\nBalance     : " << client.getAccountBalance();
        cout << "\n___________________\n";
    }

    static string _readAccountNumber()
    {
        string accountNumberFrom = clsInputValidate::readString("Please Enter Client Account Number to Transfer from ? ");
        while (!ClsBankClient::isClientExist(accountNumberFrom))
        {
            accountNumberFrom = clsInputValidate::readString("Account Number isn't found, Please Enter Client Account Number to Transfer from ? Again ? \n");
        }

        return accountNumberFrom;
    }

    static float readAmount(ClsBankClient sourceClient)
    {
        double amount = 0;
        bool isBalanceExceeded = false;
        cout << "Please enter amount to transfer ? ";
        do
        {
            if (isBalanceExceeded)
                cout << "Amount exceeded the avaliable balance, please enter amount again ? ";
            amount = clsInputValidate::readDoubleNumber("Please enter double amount ? ");
            isBalanceExceeded = amount > sourceClient.getAccountBalance();
        } while (isBalanceExceeded);

        return amount;
    }

public:
    static void showTransferScreen()
    {
        _drawScreenHeader("Transfer Screen");

        // From
        ClsBankClient clientTransferFrom = ClsBankClient::find(_readAccountNumber());
        _printClient(clientTransferFrom);

        // To
        ClsBankClient clientTransferTo = ClsBankClient::find(_readAccountNumber());
        _printClient(clientTransferTo);

        // Amount
        double amount = readAmount(clientTransferFrom);

        bool answer = clsInputValidate::readBoolValue("Are you sure you want to perform this transaction? [Y] = Yes | [N] = No ? ");

        if (answer)
        {
            ClsBankClient::enTransferResult transferResult = clientTransferFrom.transfer(amount, clientTransferTo);
            if (transferResult == ClsBankClient::enTransferResult::transferSucceeded)
            {
                cout << "\nTransfer Done Successfully\n";
                _printClient(clientTransferFrom);
                _printClient(clientTransferTo);
            }
            else if (transferResult == ClsBankClient::enTransferResult::FailedInsufficientBalance)
                cout << "\nTransfer Failed, Insufficient Balance\n";
            else if (transferResult == ClsBankClient::enTransferResult::FailedSameAccountNumber)
                cout << "\nTransfer Failed, Same Account Number\n";
            else if (transferResult == ClsBankClient::enTransferResult::FailedAmountLessThanZero)
                cout << "\nTransfer Failed, Amount is less than zero\n";
        }
    }
};
