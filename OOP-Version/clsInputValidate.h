#pragma once
#include <iostream>
#include <string>     
#include "clsDate.h"     

using namespace std;
template <class T>
class clsInputValidate
{
public:


	static bool IsNumberBetween(T Number, T From, T To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;

	}

	static T ReadNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		T Number;
		while (!(cin >> Number)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static T ReadNumberBetween(T From, T To, string ErrorMessage = "Number is not within range, Enter again:\n")
	{
		T Number = ReadNumber();

		while (!IsNumberBetween(Number, From, To)) {
			cout << ErrorMessage;
			Number = ReadNumber();
		}
		return Number;
	}

	static bool IsDateBetween(clsDate Date, clsDate DateFrom, clsDate DateTo)
	{

		if (clsDate::CompareDate(DateFrom, DateTo) == clsDate::eDateCompare::After)
		{
			clsDate::SwapDate(DateFrom, DateTo);
		}

		return !(clsDate::CompareDate(Date, DateFrom) == clsDate::eDateCompare::Before
			||
			clsDate::CompareDate(Date, DateTo) == clsDate::eDateCompare::After);

	}

	static string ReadString()
	{
		string  S1 = "";
		// Usage of std::ws will extract allthe whitespace character
		getline(cin >> ws, S1);
		return S1;
	}

};