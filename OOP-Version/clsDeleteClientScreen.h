#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen :protected clsScreen
{
private:


	static void _PrintClient(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}

public:

	static void ShowDeleteClientScreen()
	{


		clsScreen::_DrawScreenHeader("\t Delete Client Screen");

		string AccountNumber = "";

		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputValidate<string>::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))

		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}

		clsBankClient DeleteClient = clsBankClient::Find(AccountNumber);
		_PrintClient(DeleteClient);

		char Answer = 'n';

		cout << "\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;

		if (Answer == 'y' || Answer == 'Y')
		{
			if (DeleteClient.Delete())
			{
				cout << "\nClient Deleted Successfully.";
				_PrintClient(DeleteClient);

			}
			else
			{
				cout << "\n\nError Client was not Deleted\n";
			}
		}
	}


};