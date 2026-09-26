#pragma once
#include <iostream>
#include <iomanip>
#include "../../core/cls_bank_client.h"
#include "../common/cls_screen.h"
#include "../../libs/cls_util.h"

class ClsListClientsScreen : protected ClsScreen
{
private:
    static void _header()
    {
        _showLine();
        cout << "| " << left << setw(15) << "Account Number"
             << "| " << left << setw(35) << "Client Name"
             << "| " << left << setw(20) << "Email"
             << "| " << left << setw(15) << "Phone"
             << "| " << left << setw(15) << "Pin Code"
             << "| " << left << setw(20) << "Balance";
        _showLine();
    }
    static void _printClientLine(ClsBankClient client)
    {
        cout << "| " << left << setw(15) << client.accountNumber()
             << "| " << left << setw(35) << client.fullName()
             << "| " << left << setw(20) << client.getEmail()
             << "| " << left << setw(15) << client.getPhone()
             << "| " << left << setw(15) << client.getPinCode()
             << "| " << left << setw(20) << client.getAccountBalance() << "\n";
    }

public:
    static void showClientList()
    {
        vector<ClsBankClient> clients = ClsBankClient::getClientsList();
        string title = "\t Clients List Screen";
        string subTitle = "\t (" + to_string(clients.size()) + ") Clients(s)";
        _drawScreenHeader(title, subTitle);

        if (clients.size() == 0)
        {
            cout << ClsUtil::tabs(7) << " No Clients in the system \n";
            _showLine();
            return;
        }

        _header();
        for (ClsBankClient &client : clients)
        {
            _printClientLine(client);
            cout << "\n";
        }
        _showLine();
    }
};
