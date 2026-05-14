#pragma once

#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
using namespace std;

class clsClientListScreen :protected clsScreen
{

private:

	static void _PrintClientRecordLine(clsBankClient& Client)
	{

		cout << setw(8) << left << "" << "| " << setw(15) << left << Client.AccountNumber();
		cout << "| " << setw(20) << left << Client.FullName();
		cout << "| " << setw(12) << left << Client.Phone;
		cout << "| " << setw(20) << left << Client.Email;
		cout << "| " << setw(10) << left << Client.PinCode;
		cout << "| " << setw(12) << left << Client.AccountBalance;

	}

public:

	static void ShowClientsList()
	{

		vector <clsBankClient> vClients = clsBankClient::GetClientsList();

		string Title = "\tClients List Screen";
		string SubTitle = "\t  (" + to_string(vClients.size()) + ") Client(s).";

		clsScreen::_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t______________________________________________________________";
		cout << "___________________________________________\n\n";

		cout << setw(8) << left << "" << "| " << setw(15) << left << "AccountNumber";
		cout << "| " << setw(20) << left << "Client Name";
		cout << "| " << setw(12) << left << "Phone";
		cout << "| " << setw(20) << left << "Email";
		cout << "| " << setw(10) << left << "PinCode";
		cout << "| " << setw(12) << left << "AccountBalance";
		cout << setw(8) << left << "\n\t______________________________________________________________";
		cout << "___________________________________________\n\n";

		if (vClients.size() == 0)
			cout << "\t\t\t\tNo Clients Available In the System!";
		else

		{
			for (clsBankClient Client : vClients)
			{
				_PrintClientRecordLine(Client);
				cout << endl;
			}
		}

		cout << setw(8) << left << "\n\t______________________________________________________________";
		cout << "___________________________________________\n\n";

	}

};