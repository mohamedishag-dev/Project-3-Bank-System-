#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <iomanip> 

using namespace std;
const string ClientsFileName = "Clients.txt";
void ShowMainMenue();

struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarkForDelete = false;
};

vector <string> SplitString(string S1, string Seperator = "#//#")
{
	vector <string> vString;
	short pos = 0;
	string sWord; // define a string variable

	do
	{
		pos = S1.find(Seperator);
		sWord = S1.substr(0, pos); // store the word
		if (sWord != Seperator)
		{
			vString.push_back(sWord);
		}
		//erase() until positon and move to next word.
		S1.erase(0, pos + Seperator.length());

	} while (pos != std::string::npos);

	return vString;
}

sClient ConverLineDataToRecord(string stLine, string Seperator = "#//#")
{
	vector <string> vClientData = SplitString(stLine, Seperator);
	sClient Client;

	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

vector <sClient> LoadClientsDataFromFile(string FileName)
{
	vector <sClient> vClient;
	fstream MyFile;

	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;

		while (getline(MyFile, Line))
		{
			Client = ConverLineDataToRecord(Line);
			vClient.push_back(Client);
		}
		MyFile.close();
	}
	return vClient;
}

string ReadClientAccountNumber()
{
	string AccountNumber = "";
	cout << "Please enter AccountNumber? ";
	cin >> AccountNumber;
	return AccountNumber;
}

void PrintClientRecord(sClient Client)
{
	cout << "\n\nThe following is the extracted client record:\n";
	cout << "\nAccountNumber: " << Client.AccountNumber;
	cout << "\nPinCode      : " << Client.PinCode;
	cout << "\nName         : " << Client.Name;
	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccountBalance: " << Client.AccountBalance;
}

string ConverRecordToLine(sClient Client, string Seperator = "#//#")
{
	string stClientRecord = "";

	stClientRecord = Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);

	return stClientRecord;
}

void PrintAllClientsRecord(sClient& Client)
{
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}

void PrintAllClientsData(vector <sClient> vClients)
{
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n\n";

	for (sClient Client : vClients)
	{
		PrintAllClientsRecord(Client);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector <sClient>& vClients, sClient& Client)
{
	for (sClient& C : vClients)
	{
		if (C.AccountNumber == AccountNumber)
		{
			Client = C;
			return true;
		}

	}

	return false;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConverLineDataToRecord(Line);
			if (Client.AccountNumber == AccountNumber)
			{
				MyFile.close();
				return true;
			}
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return false;
}

sClient ReadNewClient()
{
	sClient Client;
	cout << "Enter Account Number? ";
	// Usage of std::ws will extract allthe whitespace character
	getline(cin >> ws, Client.AccountNumber);

	while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName));
	{

		cout << "\nClient with [" << Client.AccountNumber << "] already exists,Enter Account Number ? ";
		getline(cin >> ws, Client.AccountNumber);

	}

	cout << "Enter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out | ios::app);

	if (MyFile.is_open())
	{
		MyFile << stDataLine << endl;

		MyFile.close();
	}
}

void AddNewClients()
{
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	sClient Client;

	Client = ReadNewClient();
	AddDataLineToFile(ClientsFileName, ConverRecordToLine(Client));
}

void SaveClientsDataToFile(string FileName, vector <sClient> vClient)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	if (MyFile.is_open())
	{
		for (sClient& C : vClient)
		{
			if (C.MarkForDelete == false)
			{
				MyFile << ConverRecordToLine(C) << endl;
			}
		}
		MyFile.close();
	}
}

bool UpdateClient(string AccountNumber, vector <sClient>& vClient)
{
	for (sClient& C : vClient)
	{
		if (C.AccountNumber == AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

bool DeleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientRecord(Client);
		cout << "\nAre you sure you want delete this client? y/n ? ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			UpdateClient(AccountNumber, vClients);
			SaveClientsDataToFile(ClientsFileName, vClients);

			vClients = LoadClientsDataFromFile(ClientsFileName);
			cout << "\nClient Deleted Successfully.";
		}
		return true;
	}

	else
	{
		cout << "\n\nClient with Account Number (" << AccountNumber << ") Not Found!";

		string AccountNumber = ReadClientAccountNumber();
		DeleteClientByAccountNumber(AccountNumber, vClients);

		return false;
	}
}

sClient ChangeClientRecord(string AccountNumber)
{
	sClient Client;

	Client.AccountNumber = AccountNumber;

	cout << "\n\nEnter PinCode? ";
	getline(cin >> ws, Client.PinCode);

	cout << "Enter Name? ";
	getline(cin, Client.Name);

	cout << "Enter Phone? ";
	getline(cin, Client.Phone);

	cout << "Enter AccountBalance? ";
	cin >> Client.AccountBalance;

	return Client;
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
	sClient Client;
	char Answer = 'n';

	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientRecord(Client);
		cout << "\nAre you sure you want update this client? y/n ? ";
		cin >> Answer;
		if (tolower(Answer) == 'y')
		{
			for (sClient& C : vClients)
			{
				if (C.AccountNumber == AccountNumber)
				{
					C = ChangeClientRecord(AccountNumber);
				}
			}

			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "\nClient updated Successfully.";
		}
		return true;
	}

	else
	{
		cout << "\n\nClient with Account Number (" << AccountNumber << ") Not Found!";
		return false;
	}
}

void FindClient(string AccountNumber, vector <sClient>& vClients, sClient& Client)
{
	if (FindClientByAccountNumber(AccountNumber, vClients, Client))
	{
		PrintClientRecord(Client);
	}

	else
	{
		cout << "\n\nClient with Account Number (" << AccountNumber << ") Not Found!";
	}
}

enum enMainMenueOptions
{
	eShowClientList = 1, eAddNewClient = 2, eDeleteClient = 3,
	eUpdateClient = 4, eFindClient = 5, eExit = 6
};

void ShowEndScreen()
{
	cout << "----------------------------------------\n";
	cout << "\tProgram Ends :-)\n";
	cout << "----------------------------------------\n";
}

void ShowFindClient()
{
	cout << "----------------------------------------\n";
	cout << "\tFind Clients Screen\n";
	cout << "----------------------------------------\n\n";

	sClient Client;
	string AccountNumber = ReadClientAccountNumber();
	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	FindClient(AccountNumber, vClients, Client);

}

void ShowUpdateClientInfo()
{
	cout << "----------------------------------------\n";
	cout << "\tUpdate Clients Screen\n";
	cout << "----------------------------------------\n\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	UpdateClientByAccountNumber(AccountNumber, vClients);

}

void ShowDeleteClientScreen()
{
	cout << "----------------------------------------\n";
	cout << "\tDelete Clients Screen\n";
	cout << "----------------------------------------\n\n";

	vector <sClient> vClients = LoadClientsDataFromFile(ClientsFileName);
	string AccountNumber = ReadClientAccountNumber();
	DeleteClientByAccountNumber(AccountNumber, vClients);

}

void ShowAddNewClients()
{

	cout << "----------------------------------------\n";
	cout << "\tAdd New Clients Screen\n";
	cout << "----------------------------------------\n";
	cout << "Adding New Client:\n\n";

	char AddAgen = 'Y';
	do {


		AddNewClients();

		cout << ("\n\nClient added Successfully, do you want to add more clients? [ Y/N ]: ");
		cin >> AddAgen;

	} while (toupper(AddAgen) == 'Y');

}

void ShowClientList()
{
	vector <sClient> Client = LoadClientsDataFromFile(ClientsFileName);
	PrintAllClientsData(Client);

}

void GoBackToMainMenue()
{
	cout << "\n\nPress any key to back Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOptions)
{
	switch (MainMenueOptions) {

	case enMainMenueOptions::eShowClientList:
	{
		system("cls");
		ShowClientList();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eAddNewClient:
	{
		system("cls");
		ShowAddNewClients();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eDeleteClient:
	{
		system("cls");
		ShowDeleteClientScreen();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eUpdateClient:
	{
		system("cls");
		ShowUpdateClientInfo();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eFindClient:
	{
		system("cls");
		ShowFindClient();
		GoBackToMainMenue();
		break;
	}
	case enMainMenueOptions::eExit:
	{
		system("cls");
		ShowEndScreen();
		break;
	}

	}

}

short ReadGoMainMenueOptions()
{
	short Chose;
	cout << "Chose what do you want to do? [1 to 6]? ";
	cin >> Chose;
	return Chose;
}

void ShowMainMenue()
{
	system("cls");
	cout << "========================================================\n";
	cout << "\t\tMain Menue Screen\n";
	cout << "========================================================\n";
	cout << "\t[1] Show Client List.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Updare Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Exit.\n";
	cout << "========================================================\n";
	PerfromMainMenueOption((enMainMenueOptions)ReadGoMainMenueOptions());
}

int main()
{
	ShowMainMenue();

	system("pause>0");
	return 0;
}