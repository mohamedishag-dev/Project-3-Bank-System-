#pragma once
#include <iomanip>
#include <iostream>
#include "clsUtil.h"
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsTotalBalances :protected clsScreen
{
private:

	static void PrintClientRecordBalanceLine(clsBankClient& Client)
	{
		cout << setw(20) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(40) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.AccountBalance;
	}

public:

	static void ShowTotalBalances()
	{

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "\t Total Balances Screen";

		string SubTitle = "\t  (" + to_string(vClients.size()) + ") Client(s).";

		clsScreen::_DrawScreenHeader(Title, SubTitle);

		cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
		cout << setw(8) << left << "" << "\n\t______________________________________________________________";
		cout << "___________________________________________\n\n";

		cout << setw(20) << left << "" << "| " << setw(15) << left << "AccountNumber";
		cout << "| " << setw(40) << left << "Client Name";
		cout << "| " << setw(12) << left << "AccountBalance";
		cout << setw(8) << left << "\n\t______________________________________________________________";
		cout << "___________________________________________\n\n";

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else

		{
			for (clsBankClient Client : vClients)
			{
				PrintClientRecordBalanceLine(Client);
				cout << endl;
			}
		}

		cout << setw(8) << left << "\n\t______________________________________________________________";
		cout << "___________________________________________\n\n";

		double TotalBalances = clsBankClient::GetTotalBalances();

		cout << "\t\t\t\t\tTotal Balances = " << TotalBalances;
		cout << "\n\t\t\t\t\t( " << clsUtil::NumberToText(TotalBalances) << ")\n";
	}

};