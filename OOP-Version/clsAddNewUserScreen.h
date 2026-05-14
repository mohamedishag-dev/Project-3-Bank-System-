#pragma once

#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidate.h"

using namespace std;
class clsAddNewUserScreen :protected clsScreen
{
private:

	static int ReadPermissionsToSet()
	{

		int Permissions = 0;
		char Answer = 'n';


		cout << "\nDo you want to give full access? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			return -1;
		}

		cout << "\nDo you want to give access to : \n ";

		cout << "\nShow Client List? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pListClients;
		}

		cout << "\nAdd New Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pUpdateClients;
		}

		cout << "\nFind Client? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pFindClient;
		}

		cout << "\nTransactions? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pTranactions;
		}

		cout << "\nManage Users? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pManageUsers;
		}
		
		cout << "\nShow Login Register? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pShowLoginRegister;
		}
	
		cout << "\nShow Currency Exchange? y/n? ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			Permissions += clsUser::enPermissions::pShowCurrencyExchange;
		}

		return Permissions;

	}

	static clsUser _ReadUserInfo(clsUser& User)
	{

		cout << "\nEnter First Name? ";
		User.FirstName = clsInputValidate<string>::ReadString();

		cout << "\nEnter Last Name? ";
		User.LastName = clsInputValidate<string>::ReadString();

		cout << "\nEnter Email? ";
		User.Email = clsInputValidate<string>::ReadString();

		cout << "\nEnter Phone? ";
		User.Phone = clsInputValidate<string>::ReadString();

		cout << "\nEnter Password? ";
		User.Password = clsInputValidate<string>::ReadString();

		cout << "\nEnter Permissions? ";
		User.Permissions = ReadPermissionsToSet();

		return User;
	}

	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName  : " << User.FirstName;
		cout << "\nLastName   : " << User.LastName;
		cout << "\nFull Name  : " << User.FullName();
		cout << "\nEmail      : " << User.Email;
		cout << "\nPhone      : " << User.Phone;
		cout << "\nUserName   : " << User.UserName;
		cout << "\nPassword   : " << User.Password;
		cout << "\nPermissions: " << User.Permissions;
		cout << "\n___________________\n";

	}

public:

	static void ShowAddNewUsersScreen()
	{

		clsScreen::_DrawScreenHeader("\t Add New User Screen");

		string Username = "";

		cout << "Enter Username? ";
		Username = clsInputValidate<string>::ReadString();

		while (clsUser::IsUserExist(Username))
		{
			cout << "\nUsername is Already Used, choose another one: ";
			Username = clsInputValidate<string>::ReadString();
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(Username);
		
		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResult;
		SaveResult = NewUser.Save();

		switch (SaveResult)
		{
		case clsUser::enSaveResults::svSucceeded:
		{

			cout << "\nAccount Added Successfully :-)\n";
			_PrintUser(NewUser);
			break;
		}
		case clsUser::enSaveResults::svFaildEmptyObject:
		{

			cout << "\nError account was not saved because is's Empty.\n";
			break;
		}
		case clsUser::enSaveResults::svFaildAccountNumberExists:
		{
			cout << "\nError account was not saved because account number is used!\n";
			break;

		}
		}
	}

};