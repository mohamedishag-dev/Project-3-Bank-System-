#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen :protected clsScreen
{
private:

	static clsBankClient _ReadClientInfo(clsBankClient& Client)
	{

		cout << "\nEnter First Name? ";
		Client.FirstName = clsInputValidate<string>::ReadString();

		cout << "\nEnter Last Name? ";
		Client.LastName = clsInputValidate<string>::ReadString();

		cout << "\nEnter Email? ";
		Client.Email = clsInputValidate<string>::ReadString();

		cout << "\nEnter Phone? ";
		Client.Phone = clsInputValidate<string>::ReadString();

		cout << "\nEnter PinCode? ";
		Client.PinCode = clsInputValidate<string>::ReadString();

		cout << "\nEnter AccountBalance? ";
		Client.AccountBalance = clsInputValidate<float>::ReadNumber();

		return Client;
	}

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

	static void ShowUpdateClientScreen()
	{

		clsScreen::_DrawScreenHeader("\t Update Client Screen");

		string AccountNumber = "";

		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputValidate<string>::ReadString();

		while (!clsBankClient::IsClientExist(AccountNumber))

		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate<string>::ReadString();
		}

		clsBankClient UpdateClient = clsBankClient::Find(AccountNumber);
		_PrintClient(UpdateClient);


		cout << "\nUpdate Client:";
		cout << "\n___________________";
		_ReadClientInfo(UpdateClient);

		clsBankClient::enSaveResults SaveResult;
		SaveResult = UpdateClient.Save();

		switch (SaveResult)
		{
		case clsBankClient::enSaveResults::svSucceeded:
		{

			cout << "\nAccount Update Successfully :-)\n";
			_PrintClient(UpdateClient);
			break;
		}
		case clsBankClient::enSaveResults::svFaildEmptyObject:
		{

			cout << "\nError account was not saved because is's Empty.\n";
			break;
		}
		}


	}

};