#include <iostream>
#include "../../core/cls_bank_client.h"
#include "../common/cls_screen.h"
#include "../../libs/cls_util.h"
#include "../../libs/cls_input_validate.h"
using namespace std;

class ClsTotalBalancesScreen : protected ClsScreen
{
private:
    static void _header(int countOfClients)
    {

        _showLine();
        cout << "| " << left << setw(15) << "Account Number"
             << "| " << left << setw(50) << "Client Name"
             << "| " << left << setw(20) << "Balance";
        _showLine();
    }

    static void _printClientLine(ClsBankClient client)
    {
        cout << "| " << left << setw(15) << client.accountNumber()
             << "| " << left << setw(50) << client.fullName()
             << "| " << left << setw(20) << client.getAccountBalance();
    }

public:
    static void showTotalBalancesScreen()
    {
        vector<ClsBankClient> clients = ClsBankClient::getClientsList();
        string title = "\t Total Balances Screen";
        string subTitle = "\t (" + to_string(clients.size()) + ") Clients(s)";
        _drawScreenHeader(title, subTitle);

        _header(clients.size());

        if (clients.size() == 0)
        {
            cout << ClsUtil::tabs(7) << " No Clients in the system \n";
            _showLine();
            return;
        }

        for (ClsBankClient &client : clients)
        {
            _printClientLine(client);
            cout << "\n";
        }
        _showLine();

        double totalBalance = ClsBankClient::totalBalances();
        cout << "| " << left << setw(35) << "Total Balances"
             << "| " << left << setw(20) << totalBalance << "\n";

        cout << "| " << left << setw(35) << "Total Balances In Text"
             << "| " << ClsUtil::numberToText(totalBalance) << "\n\n\n";
    }
};
