#pragma once
#include <iomanip>
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;

class clsDepositScreen :protected clsScreen
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

    static void ShowDepositScreen()
    {
        clsScreen::_DrawScreenHeader("\t Deposit Screen");

        string AccountNumber = "";

        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate<string>::ReadString();

        while (!clsBankClient::IsClientExist(AccountNumber))

        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = clsInputValidate<string>::ReadString();
        }

        clsBankClient Client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(Client1);

        double Amount = 0;
        cout << "\nPlease enter deposit amount? ";
        cin >> Amount;

        char Answer = 'n';
        cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Client1.Deposit(Amount);

            cout << "\n\nDone Successfully.\n";
            cout << "New balance is: " << Client1.AccountBalance << "\n\n";
        }


    }

};