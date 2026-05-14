#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "clsUtil.h"
#include "clsDate.h"
#include "clsPerson.h"
#include "clsString.h"

using namespace std;

class clsUser : public clsPerson
{
private:

    enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permissions;
    bool _MarkForDelete = false;


    string _PrepareLogInRecord(string Seperator = "#//#")
    {

        string LoginRecord = "";
        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += _UserName + Seperator;
        LoginRecord += clsUtil::EncryptText(_Password) + Seperator;
        LoginRecord += to_string(_Permissions);

        return LoginRecord;
    }

    static clsUser _ConvertLinetoUserObject(string Line, string Seperator = "#//#")
    {
        vector <string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsUser(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
            vClientData[3], vClientData[4], clsUtil::DecryptText(vClientData[5]), stoi(vClientData[6]));

    }

    static string _ConverUserObjectToLine(clsUser User, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += User.FirstName + Seperator;
        stClientRecord += User.LastName + Seperator;
        stClientRecord += User.Email + Seperator;
        stClientRecord += User.Phone + Seperator;
        stClientRecord += User.UserName + Seperator;
        stClientRecord += clsUtil::EncryptText(User.Password) + Seperator;
        stClientRecord += to_string(User.Permissions);

        return stClientRecord;
    }

    static  vector <clsUser> _LoadUsersDataFromFile()
    {

        vector <clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                clsUser User = _ConvertLinetoUserObject(Line);

                vUsers.push_back(User);
            }

            MyFile.close();

        }

        return vUsers;

    }

    static void _SaveUsersDataToFile(vector <clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);//overwrite

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsUser U : vUsers)
            {
                if (U.MarkedForDeleted() == false)
                {
                    //we only write records that are not marked for delete.  
                    DataLine = _ConverUserObjectToLine(U);
                    MyFile << DataLine << endl;

                }

            }

            MyFile.close();

        }

    }

    void _Update()
    {
        vector <clsUser> vUsers;
        vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }

        }

        _SaveUsersDataToFile(vUsers);

    }

    void _AddNew()
    {

        _AddDataLineToFile(_ConverUserObjectToLine(*this));
    }

    void _AddDataLineToFile(string stDataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

public:

    enum enPermissions {
        eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
        pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64, pShowLoginRegister = 128
        , pShowCurrencyExchange = 256
    };

    clsUser(enMode Mode, string FirstName, string LastName,
        string Email, string Phone, string UserName, string Password,
        int Permissions) :
        clsPerson(FirstName, LastName, Email, Phone)

    {
      
        _Mode = Mode;
        _UserName = UserName;
        _Password = Password;
        _Permissions = Permissions;

    }

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    bool MarkedForDeleted()
    {
        return _MarkForDelete;
    }

    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }

    string GetUserName()
    {
        return _UserName;
    }
    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

   
    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int GetPermissions()
    {
        return _Permissions;
    }
    __declspec(property(get = GetPermissions, put = SetPermissions)) int Permissions;


    static clsUser Find(string UserName)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser Client = _ConvertLinetoUserObject(Line);
                if (Client.UserName == UserName)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string UserName, string Password)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser Client = _ConvertLinetoUserObject(Line);
                if (Client.UserName == UserName && Client.Password == Password)
                {
                    MyFile.close();
                    return Client;
                }

            }

            MyFile.close();

        }
        return _GetEmptyUserObject();
    }

    enum enSaveResults { svFaildEmptyObject = 0, svSucceeded = 1, svFaildAccountNumberExists = 2 };
    enSaveResults Save()
    {

        switch (_Mode)
        {
        case enMode::EmptyMode:
        {
            if (IsEmpty())
            {

                return enSaveResults::svFaildEmptyObject;

            }

        }

        case enMode::UpdateMode:
        {


            _Update();

            return enSaveResults::svSucceeded;

            break;
        }

        case enMode::AddNewMode:
        {
            //This will add new record to file or database
            if (clsUser::IsUserExist(UserName))
            {
                return enSaveResults::svFaildAccountNumberExists;
            }
            else
            {
                _AddNew();

                //We need to set the mode to update after add new
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceeded;
            }

            break;
        }
        }



    }

    static bool IsUserExist(string UserName)
    {

        clsUser Client1 = clsUser::Find(UserName);
        return (!Client1.IsEmpty());
    }

    bool Delete()
    {
        vector <clsUser> vUsers;
        vUsers = _LoadUsersDataFromFile();

        for (clsUser& U : vUsers)
        {
            if (U.UserName == UserName)
            {
                U._MarkForDelete = true;
                break;
            }

        }

        _SaveUsersDataToFile(vUsers);

        *this = _GetEmptyUserObject();

        return true;

    }

    static clsUser GetAddNewUserObject(string UserName)
    {
        return clsUser(enMode::AddNewMode, "", "", "", "", UserName, "", 0);
    }

    static vector <clsUser> GetUsersList()
    {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermission(enPermissions Permission)
    {
        if (this->Permissions == enPermissions::eAll)
            return true;

        if ((Permission & this->Permissions) == Permission)
            return true;
        else
            return false;

    }

    void RegisterLogIn()
    {
        string stDataLine = _PrepareLogInRecord();

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {

            MyFile << stDataLine << endl;

            MyFile.close();
        }

    }

    struct stLoginRegisterRecord
    {
        string Date_Time;
        string UserName;
        string Password;
        int Permissions;
    };

    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {

        stLoginRegisterRecord LoginRegisterRecord;

        vector <string> LoginRegisterDateLine = clsString::Split(Line, Seperator);
        LoginRegisterRecord.Date_Time = LoginRegisterDateLine[0];
        LoginRegisterRecord.UserName = LoginRegisterDateLine[1];
        LoginRegisterRecord.Password = clsUtil::DecryptText(LoginRegisterDateLine[2]);
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDateLine[3]);

        return LoginRegisterRecord;
    }

    static  vector <stLoginRegisterRecord> GetLoginRegisterRecord()
    {

        vector <stLoginRegisterRecord> vLoginRegisterRecord;

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in);//read Mode

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {

                stLoginRegisterRecord LoginRegisterRecord = _ConvertLoginRegisterLineToRecord(Line);

                vLoginRegisterRecord.push_back(LoginRegisterRecord);
            }

            MyFile.close();

        }

        return vLoginRegisterRecord;

    }

};