#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class clsDate
{
	short _Day = 1;
	short _Month = 1;
	short _Year = 1900;

public:


	clsDate()
	{

		time_t t = time(0); // get time now
		tm* now = localtime(&t);

		_Year = now->tm_year + 1900;
		_Month = now->tm_mon + 1;
		_Day = now->tm_mday;

	}

	clsDate(string stLine)
	{
		*this = StringToDate(stLine);
	}

	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}

	clsDate(short DateOrderInYear, short Year)
	{
		short RemainingDays = DateOrderInYear;
		short MonthDays = 0;

		_Year = Year;
		_Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(_Month, Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				_Month++;
			}
			else
			{
				_Day = RemainingDays;
				break;
			}
		}

	}

	void SetDay(short Day)
	{
		_Day = Day;
	}
	short GetDay()
	{
		return _Day;
	}

	void SetMonth(short Month)
	{
		_Month = Month;
	}
	short GetMonth()
	{
		return _Month;
	}

	void SetYear(short Year)
	{
		_Year = Year;
	}
	short GetYear()
	{
		return _Year;
	}

	void Print()
	{
		cout << DateToString(*this) << endl;
	}

	static bool IsVadideDate(clsDate Date)
	{

		if (Date.Day < 1 || Date.Day > 31)
			return false;

		if (Date.Month < 1 || Date.Month > 12)
			return false;

		if (Date.Month == 2)
		{
			if (IsLeapYear(Date.Year))
			{
				if (Date.Day > 29)
					return false;
			}

			else if (Date.Day > 28)
				return false;

		}
		short DaysInMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > DaysInMonth)
			return false;


		return true;
	}
	bool IsVadide()
	{
		IsVadideDate(*this);
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;
	__declspec(property(get = GetYear, put = SetYear)) short Year;

	static bool IsLeapYear(short Year)
	{
		return  (Year % 4 == 0 && Year % 100 != 0) || (Year % 400) == 0;
	}
	bool IsLeapYear()
	{
		return  IsLeapYear(_Year);
	}

	static int NumberOfDaysInYear(short Year)
	{
		return IsLeapYear(Year) ? 366 : 365;;
	}
	int NumberOfDaysInYear()
	{
		return NumberOfDaysInYear(_Year);
	}

	static int NumberOfHourInYear(short Year)
	{
		return NumberOfDaysInYear(Year) * 24;
	}
	int NumberOfHourInYear()
	{
		return NumberOfHourInYear(_Year);
	}

	static int NumberOfMinuteInYear(short Year)
	{
		return NumberOfHourInYear(Year) * 60;
	}
	int NumberOfMinuteInYear()
	{
		return NumberOfMinuteInYear(_Year);
	}

	static int NumberOfSecondInYear(short Year)
	{
		return NumberOfMinuteInYear(Year) * 60;
	}
	int NumberOfSecondInYear()
	{
		return NumberOfSecondInYear(_Year);
	}


	static short NumberOfDaysInMonth(short Month, short Year)
	{
		if (Month < 1 || Month > 12)
		{
			return 0;
		}

		short DaysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

		return (Month == 2) ? IsLeapYear(Year) ? 29 : 28 : DaysInMonth[Month - 1];

	}
	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_Month, _Year);
	}

	static short NumberOfHourInMonth(short Month, short Year)
	{
		return NumberOfDaysInMonth(Month, Year) * 24;
	}
	short NumberOfHourInMonth()
	{
		return NumberOfHourInMonth(_Month, _Year);
	}

	static int NumberOfMinuteInMonth(short Month, short Year)
	{
		return NumberOfHourInMonth(Month, Year) * 60;
	}
	int NumberOfMinuteInMonth()
	{
		return NumberOfMinuteInMonth(_Month, _Year);
	}

	static int NumberOfSecondInMonth(short Month, short Year)
	{
		return NumberOfMinuteInMonth(Month, Year) * 60;
	}
	int NumberOfSecondInMonth()
	{
		return NumberOfSecondInMonth(_Month, _Year);
	}


	static short DayOfWeekOrder(short day, short month, short year)
	{
		short a, y, m;
		a = (14 - month) / 12;
		y = year - a;
		m = month + (12 * a) - 2;
		// Gregorian:
		//0:sun, 1:Mon, 2:Tue...etc
		return (day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
	}
	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Day, _Month, _Year);
	}

	static string DayName(short Day, short Month, short Year)
	{
		string arrName[] = { "Sun","Mon","Tue","Wed","Thu","Fri","Sat" };
		short DayOrder;
		DayOrder = DayOfWeekOrder(Day, Month, Year);
		return arrName[DayOrder];
	}
	string DayName()
	{
		return DayName(_Day, _Month, _Year);
	}


	static string MonthName(short Month)
	{
		string arrName[12] = { "Jan","Feb","Mar","Apr"
							 ,"May","Jun","Jul","Aug"
							,"Sep","Oct","Nov","Dec" };
		return arrName[Month - 1];
	}
	string MonthName()
	{
		return MonthName(_Month);
	}

	static void PrintMonthCalendar(short month, short year)
	{
		printf("\n_________________%s_________________\n\n",
			MonthName(month).c_str());

		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
		short current = DayOfWeekOrder(1, month, year);

		short i = 0;
		for (i = 0; i < current; i++)
			printf("     ");
		for (short j = 1; j <= NumberOfDaysInMonth(month, year); j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				printf("\n");
			}

		}
		printf("\n_____________________________________\n");
	}
	void PrintMonthCalendar()
	{
		PrintMonthCalendar(_Month, _Year);
	}

	static void PrintYearCalendar(short Year)
	{
		printf("\n -------------------------------------\n");
		printf("           Calendar - %d", Year);
		printf("\n _____________________________________\n");


		for (short i = 1; i <= 12; i++)
		{
			PrintMonthCalendar(i, Year);
		}
		printf("\n _____________________________________\n");
	}
	void PrintYearCalendar()
	{
		PrintYearCalendar(_Year);
	}

	static short NumberOfDaysFromTheBeginingOfYear(short Day, short Month, short year)
	{
		short TotalDays = 0;
		for (short i = 1; i <= Month - 1; i++)
		{
			TotalDays += NumberOfDaysInMonth(i, year);
		}
		TotalDays += Day;
		return TotalDays;
	}
	short NumberOfDaysFromTheBeginingOfYear()
	{
		return NumberOfDaysFromTheBeginingOfYear(_Day, _Month, _Year);
	}

	static void AddDaysToDate(short Days, clsDate& Date)
	{
		short RemainingDays = Days + NumberOfDaysFromTheBeginingOfYear(Date.Day, Date.Month, Date.Year);
		short MonthDays = 0;
		Date.Month = 1;

		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date.Month, Date.Year);
			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;
				Date.Month++;

				if (Date.Month > 12)
				{
					Date.Year++;
					Date.Month = 1;

				}
			}

			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}
	}
	void AddDaysToDate(short Day)
	{
		AddDaysToDate(Day, *this);
	}

	static bool IsDate1BeforDate2(clsDate DateStart, clsDate DateEnd)
	{
		return (DateStart.Year < DateEnd.Year) ? true :
			((DateStart.Year == DateEnd.Year) ?
				((DateStart.Month < DateEnd.Month) ? true :
					(DateStart.Month == DateEnd.Month ?
						(DateStart.Day < DateEnd.Day) : false)) : false);
	}
	bool IsDateBeforDate2(clsDate DateEnd)
	{
		return IsDate1BeforDate2(*this, DateEnd);
	}

	static bool IsDate1EqualDate2(clsDate DateStart, clsDate DateEnd)
	{
		return (DateStart.Year == DateEnd.Year) ? ((DateStart.Month == DateEnd.Month) ? (DateStart.Day == DateEnd.Day) : false) : false;
	}
	bool IsDateEqualDate2(clsDate Date2)
	{
		return IsDate1EqualDate2(*this, Date2);
	}

	static bool IsDate1AfterDate2(clsDate DateStart, clsDate DateEnd)
	{
		return !IsDate1BeforDate2(DateStart, DateEnd) && !IsDate1EqualDate2(DateStart, DateEnd);
	}
	bool IsDate1AfterDate2(clsDate Date2)
	{
		return IsDate1AfterDate2(*this, Date2);
	}

	static bool IsLastDayInMonth(clsDate Date)
	{
		return Date.Day == NumberOfDaysInMonth(Date.Month, Date.Year);
	}
	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}

	static bool IsLastMonthInYear(short Month)
	{
		return (Month == 12);
	}
	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}


	//_____________________Increase Date__________________________// 
	static clsDate IncreaseDateByOneDay(clsDate Date)
	{

		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Day = 1;
				Date.Month = 1;
				Date.Year++;
			}
			else
			{
				Date.Day = 1;
				Date.Month++;
			}
		}

		else
		{
			Date.Day++;
		}
		return Date;
	}
	void IncreaseDateByOneDay()
	{
		*this = IncreaseDateByOneDay(*this);
	}

	static clsDate IncreaseDateByXDay(clsDate Date, short Days)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByXDay(short Days)
	{
		*this = IncreaseDateByXDay(*this, Days);
	}


	static clsDate IncreaseDateByOneWeek(clsDate Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;

	}
	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}

	static clsDate IncreaseDateByXWeek(clsDate Date, short Weeks)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void IncreaseDateByXWeek(short Weeks)
	{
		*this = IncreaseDateByXWeek(*this, Weeks);
	}

	static clsDate IncreaseDateByOneMonth(clsDate Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;
		}
		else
		{
			Date.Month++;
		}

		short NumberDaysOfMonth = NumberOfDaysInMonth(Date.Month, Date.Year);

		if (Date.Day > NumberDaysOfMonth)
		{
			Date.Day = NumberDaysOfMonth;
		}

		return Date;

	}
	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}

	static clsDate IncreaseDateByXMonth(clsDate Date, short Month)
	{
		for (short i = 1; i <= Month; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void IncreaseDateByXMonth(short Month)
	{
		*this = IncreaseDateByXMonth(*this, Month);
	}

	static clsDate IncreaseDateByOneYear(clsDate Date)
	{
		Date.Year++;
		return Date;
	}
	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}

	static clsDate IncreaseDateByXYear(clsDate Date, short Years)
	{
		for (short i = 1; i <= Years; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}
		return Date;
	}
	void IncreaseDateByXYear(short Year)
	{
		*this = IncreaseDateByXYear(*this, Year);
	}

	static clsDate IncreaseDateByXYearFaster(clsDate Date, short Years)
	{
		Date.Year += Years;
		return Date;
	}
	void IncreaseDateByXYearFaster(short Years)
	{
		*this = IncreaseDateByXYearFaster(*this, Years);
	}

	static clsDate IncreaseDateByOneDecade(clsDate Date)
	{

		Date.Year += 10;
		return Date;

	}
	void IncreaseDateByOneDecade()
	{
		*this = IncreaseDateByOneDecade(*this);
	}

	static clsDate IncreaseDateByXDecade(clsDate Date, short Decades)
	{
		for (short i = 1; i <= Decades; i++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}
		return Date;
	}
	void IncreaseDateByXDecade(short Decades)
	{
		IncreaseDateByXDecade(*this, Decades);
	}

	static clsDate IncreaseDateByXDecadeFaster(clsDate Date, short Decades)
	{

		Date.Year += Decades * 10;
		return Date;
	}
	void IncreaseDateByXDecadeFaster(short Decades)
	{
		*this = IncreaseDateByXDecadeFaster(*this, Decades);
	}

	static clsDate IncreaseDateByOneCentury(clsDate Date)
	{

		Date.Year += 100;
		return Date;

	}
	void IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}

	static clsDate IncreaseDateByOneMillennium(clsDate Date)
	{
		Date.Year += 1000;
		return Date;
	}
	void IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}
	//_____________________________________________________________// 

	//_____________________Decrease Date__________________________// 
	static clsDate DecreaseDateByOneDay(clsDate Date)
	{

		if (Date.Day == 1)
		{
			if (Date.Month == 1)
			{
				Date.Year--;
				Date.Month = 12;
				Date.Day = 31;

			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
			}
		}

		else
		{
			Date.Day--;
		}

		return Date;
	}
	void DecreaseDateByOneDay()
	{
		*this = DecreaseDateByOneDay(*this);
	}

	static clsDate DecreaseDateByXDay(clsDate Date, short Days)
	{
		for (short i = 1; i <= Days; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByXDay(short Days)
	{
		*this = DecreaseDateByXDay(*this, Day);
	}

	static clsDate DecreaseDateByOneWeek(clsDate Date)
	{
		for (short i = 1; i <= 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;

	}
	void DecreaseDateByOneWeek()
	{
		*this = DecreaseDateByOneWeek(*this);
	}

	static clsDate DecreaseDateByXWeek(clsDate Date, short Weeks)
	{
		for (short i = 1; i <= Weeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void DecreaseDateByXWeek(short Weeks)
	{
		*this = DecreaseDateByXWeek(*this, Weeks);
	}

	static clsDate DecreaseDateByOneMonth(clsDate Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}
		else
		{
			Date.Month--;
		}


		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Month, Date.Year);
		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Month = NumberOfDaysInCurrentMonth;
		}
		return Date;

	}
	void DecreaseDateByOneMonth()
	{
		*this = DecreaseDateByOneMonth(*this);
	}

	static clsDate DecreaseDateByXMonth(clsDate Date, short Month)
	{
		for (short i = 1; i <= Month; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}
		return Date;
	}
	void DecreaseDateByXMonth(short Month)
	{
		*this = DecreaseDateByXMonth(*this, Month);
	}

	static clsDate DecreaseDateByOneYear(clsDate Date)
	{
		Date.Year--;
		return Date;
	}
	void DecreaseDateByOneYear()
	{
		*this = DecreaseDateByOneYear(*this);
	}

	static clsDate DecreaseDateByXYearFaster(clsDate Date, short Years)
	{
		Date.Year -= Years;
		return Date;
	}
	void DecreaseDateByXYearFaster(short Years)
	{
		*this = DecreaseDateByXYearFaster(*this, Years);
	}

	static clsDate DecreaseDateByOneDecade(clsDate Date)
	{

		Date.Year -= 10;
		return Date;

	}
	void DecreaseDateByOneDecade()
	{
		*this = DecreaseDateByOneDecade(*this);
	}

	static clsDate DecreaseDateByXDecadeFaster(clsDate Date, short Decades)
	{

		Date.Year -= Decades * 10;
		return Date;
	}
	void DecreaseDateByXDecadeFaster(short Decades)
	{
		*this = DecreaseDateByXDecadeFaster(*this, Decades);
	}

	static clsDate DecreaseDateByOneCentury(clsDate Date)
	{

		Date.Year -= 100;
		return Date;

	}
	void DecreaseDateByOneCentury()
	{
		*this = DecreaseDateByOneCentury(*this);
	}

	static clsDate DecreaseDateByOneMillennium(clsDate Date)
	{
		Date.Year -= 1000;
		return Date;
	}
	void DecreaseDateByOneMillennium()
	{
		*this = DecreaseDateByOneMillennium(*this);
	}

	//_____________________________________________________________// 
	static void SwapDate(clsDate& Date1, clsDate& Date2)
	{
		clsDate TempDate;

		TempDate = Date1;
		Date1 = Date2;
		Date2 = TempDate;

	}
	void SwapDate(clsDate Date2)
	{
		SwapDate(*this, Date2);
	}

	static int GetDiffrenceInDays(clsDate DateStart, clsDate DateEnd, bool IncludingEndDay = false)
	{
		int Days = 0;
		while (IsDate1BeforDate2(DateStart, DateEnd))
		{
			Days++;
			DateStart = IncreaseDateByOneDay(DateStart);
		}

		return IncludingEndDay ? ++Days : Days;
	}
	int GetDiffrenceInDays(clsDate DateEnd, bool IncludingEndDay = false)
	{
		return GetDiffrenceInDays(DateEnd, *this, IncludingEndDay);
	}

	static int YearAgeInDays(clsDate DateStart, clsDate DateEnd, bool IncludingEndDay = false)
	{
		int Days = 0;
		while (IsDate1BeforDate2(DateStart, DateEnd))
		{
			Days++;
			DateStart = IncreaseDateByOneDay(DateStart);
		}

		return IncludingEndDay ? Days + 1 : Days;
	}

	int YearAgeInDays(clsDate DateStart, bool IncludingEndDay = false)
	{
		return YearAgeInDays(DateStart, *this, IncludingEndDay);
	}
	//_____________________________________________________________// 

	static bool IsEndOfWeek(clsDate Date)
	{
		return 6 == DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
	}
	bool IsEndOfWeek()
	{
		return IsEndOfWeek(*this);
	}

	static bool IsWeekEnd(clsDate Date)
	{
		short DaysOfWeek = DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
		return (DaysOfWeek == 5 || DaysOfWeek == 6);
	}
	bool IsWeekEnd()
	{
		return IsWeekEnd(*this);
	}

	static bool IsBusinessDay(clsDate Date)
	{
		return !IsWeekEnd(Date);
	}
	bool IsBusinessDay()
	{
		return IsBusinessDay(*this);
	}

	static short DaysUntilTheEndOfWeek(clsDate Date)
	{
		return 6 - DayOfWeekOrder(Date.Day, Date.Month, Date.Year);
	}
	short DaysUntilTheEndOfWeek()
	{
		return DaysUntilTheEndOfWeek(*this);
	}

	static short DaysUntilTheEndOfMonth(clsDate Date)
	{
		clsDate EndOfMonth;
		EndOfMonth.Day = NumberOfDaysInMonth(Date.Month, Date.Year);
		EndOfMonth.Month = Date.Month;
		EndOfMonth.Year = Date.Year;

		return GetDiffrenceInDays(Date, EndOfMonth, true);
	}
	short DaysUntilTheEndOfMonth()
	{
		return DaysUntilTheEndOfMonth(*this);
	}

	static short DaysUntilTheEndOfYear(clsDate Date)
	{

		clsDate EndOfMonth;

		EndOfMonth.Day = 31;
		EndOfMonth.Month = 12;
		EndOfMonth.Year = Date.Year;

		return GetDiffrenceInDays(Date, EndOfMonth, true);

	}
	short DaysUntilTheEndOfYear()
	{
		return DaysUntilTheEndOfYear(*this);
	}
	//______________________Format Date__________________________________

	static vector <string> Split(string S1, string delim)
	{
		vector <string> vString;
		short pos = 0;
		string sWord; // define a string variable

		do
		{
			pos = S1.find(delim);
			sWord = S1.substr(0, pos); // store the word
			if (sWord != delim)
			{
				vString.push_back(sWord);
			}
			//erase() until positon and move to next word.
			S1.erase(0, pos + delim.length());

		} while (pos != std::string::npos);

		return vString;
	}

	static string DateToString(clsDate Date)
	{
		return to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);

	}
	string DateToString()
	{
		return DateToString(*this);
	}

	static clsDate StringToDate(string stLine, string Seperator = "/")
	{
		clsDate Date;
		vector <string> DateString;

		DateString = Split(stLine, Seperator);
		Date.Day = stoi(DateString[0]);
		Date.Month = stoi(DateString[1]);
		Date.Year = stoi(DateString[2]);

		return Date;
	}
	void GetDateFromString(string stLine, string Seperator = "/")
	{
		*this = StringToDate(stLine, Seperator);
	}

	static string ReplaceWordInString(string S1, string StringToReplace, string sRepalceTo)
	{
		short pos = S1.find(StringToReplace);
		while (pos != std::string::npos)
		{
			S1 = S1.replace(pos, StringToReplace.length(),
				sRepalceTo);
			pos = S1.find(StringToReplace);//find next
		}
		return S1;
	}

	static string FormatDate(clsDate Date, string DateFormat = "dd/mm/yyyy")
	{
		string FormattedDateString = "";
		FormattedDateString = ReplaceWordInString(DateFormat, "dd", to_string(Date.Day));
		FormattedDateString = ReplaceWordInString(FormattedDateString, "mm", to_string(Date.Month));
		FormattedDateString = ReplaceWordInString(FormattedDateString, "yyyy", to_string(Date.Year));
		return FormattedDateString;
	}
	string FormatDate(string DateFormat = "dd/mm/yyyy")
	{
		return FormatDate(*this, DateFormat);
	}

	//_____________________________________________________________// 
	static clsDate CalcluteVactionReturnDate(clsDate DateFrom, short VacationDays)
	{

		short WeekEndCounter = 0;

		while (IsWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		for (short i = 1; i <= VacationDays + WeekEndCounter; i++)
		{
			if (IsWeekEnd(DateFrom))
				WeekEndCounter++;

			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		while (IsWeekEnd(DateFrom))
		{
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}

		return DateFrom;
	}
	void CalcluteVactionReturnDate(short VacationDays)
	{
		*this = CalcluteVactionReturnDate(*this, VacationDays);
	}

	enum eDateCompare { Before = -1, Equal = 0, After = 1 };

	static eDateCompare CompareDate(clsDate DateStart, clsDate DateEnd)
	{
		if (IsDate1BeforDate2(DateStart, DateEnd))
			return eDateCompare::Before;
		else if (IsDate1EqualDate2(DateStart, DateEnd))
			return eDateCompare::Equal;
		else
			return eDateCompare::After;
	}
	eDateCompare CompareDate(clsDate DateEnd)
	{
		return CompareDate(*this, DateEnd);
	}

	static string GetSystemDateTimeString()
	{
		time_t t = time(0); // get time now
		tm* now = localtime(&t);
		string stDtae = "";

		short Day, Month, Year, Hour, Minutes, Second;

		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday;
		Hour = now->tm_hour;
		Minutes = now->tm_min;
		Second = now->tm_sec;

		return (to_string(Day) + "/" + to_string(Month) + "/"
			+ to_string(Year)
			+ "  -  " + to_string(Hour) + ":" + to_string(Minutes)
			+ ":" + to_string(Second));
	}

};