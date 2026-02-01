#pragma once
#include <iostream>
#include "clsBankUser.h"
#include "clsBankClient.h"
#include "clsSession.h"

using namespace std;


class clsAuditLogger
{
private:
	inline static string _LogLoginFile = "LogLoginFile.txt";
	inline static string _LogTransferFile = "LogTransferFile.txt";
	static string _GetSuccessLoginLine(clsBankUser& User)
	{
		string delimiter = "#//#";
		string CurrentTime = clsUtil::GetCurrentTime();
		string TodayDate = clsUtil::GetTodayDate();

		return CurrentTime + " - " + TodayDate + delimiter + User.GetUserName() + delimiter
			+ clsUtil::Encrypt(User.GetPassword()) + delimiter + to_string(User.GetPermission());
	}
	static string _GetTransferLine(clsBankClient& SourceClient, double Amount, clsBankClient& DestinationClient)
	{
		string delimiter = "#//#";
		string CurrentTime = clsUtil::GetCurrentTime();
		string TodayDate = clsUtil::GetTodayDate();
		string Line = "";

		Line += CurrentTime + " - " + TodayDate + delimiter;
		Line += SourceClient.GetAccountNumber() + delimiter;
		Line += DestinationClient.GetAccountNumber() + delimiter;
		Line += to_string(Amount)+delimiter;
		Line += to_string(SourceClient.GetBalance()) + delimiter;
		Line += to_string(DestinationClient.GetBalance()) + delimiter;
		Line += clsSession::GetSessionUser().GetUserName();

		return Line;
	}

public:

	struct stTransferRecord
	{
		string Date_Time = "";
		string SourceAccount = "";
		string DestinationAccount = "";
		double TransferAmount = 0;
		double SourceBalance = 0;
		double DestinationBalance = 0;
		string UserName = "";

		static stTransferRecord ConvertLineToRecord(string Line)
		{
			stTransferRecord Record;
			vector<string> FieldsOfRecord = clsString::vSplit(Line, "#//#");

			Record.Date_Time = FieldsOfRecord[0];
			Record.SourceAccount = FieldsOfRecord[1];
			Record.DestinationAccount = FieldsOfRecord[2];
			Record.TransferAmount = stod(FieldsOfRecord[3]);
			Record.SourceBalance = stod(FieldsOfRecord[4]);
			Record.DestinationBalance = stod(FieldsOfRecord[5]);
			Record.UserName = FieldsOfRecord[6];

			return Record;

		}

	};


	struct stLoginRecord
	{
		string Date_Time = "";
		string Username = "";
		string Password = "";
		int Permission;



		static stLoginRecord ConvertLineToRecord(string Line)
		{
			stLoginRecord Record;
			vector<string> FieldsOfRecord = clsString::vSplit(Line, "#//#");

			Record.Date_Time = FieldsOfRecord[0];
			Record.Username = FieldsOfRecord[1];
			Record.Password = FieldsOfRecord[2];
			Record.Permission = stoi(FieldsOfRecord[3]);

			return Record;
		}

	};

	static bool LogLoginSuccess(clsBankUser& User)
	{
		string LoginLine = _GetSuccessLoginLine(User);
		return clsUtil::AddLineToFile(LoginLine, _LogLoginFile);
	}
	static vector<stLoginRecord> GetAllSuccessLogins()
	{
		vector<stLoginRecord> vLogins;
		fstream LoginFile;
		LoginFile.open(_LogLoginFile, ios::in);

		if (LoginFile.is_open())
		{
			string Line;
			while (getline(LoginFile, Line))
			{
				vLogins.push_back(stLoginRecord::ConvertLineToRecord(Line));
			}
			LoginFile.close();
		}
		return vLogins;
	}

	static bool LogTransfer(clsBankClient& SourceClient ,double Amount, clsBankClient& DestinationClient)
	{
		string TransferLine = _GetTransferLine(SourceClient, Amount, DestinationClient);
		return clsUtil::AddLineToFile(TransferLine, _LogTransferFile);
	}

	static vector<stTransferRecord> GetAllTransfers()
	{
		vector<stTransferRecord> vTransfers;
		fstream TransferFile;
		TransferFile.open(_LogTransferFile, ios::in);

		if (TransferFile.is_open())
		{
			string Line;
			while (getline(TransferFile, Line))
			{
				vTransfers.push_back(stTransferRecord::ConvertLineToRecord(Line));
			}
			TransferFile.close();
		}
		return vTransfers;

	}
};

