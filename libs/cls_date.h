#pragma once
#include <iostream>
#include <string>
using namespace std;

class ClsDate
{
private:
    short _day;
    short _month;
    short _year;
    short _hour;
    short _minute;
    short _second;

protected:
    static string _monthShortName(short MonthNumber)
    {
        string Months[12] = {"Jan", "Feb", "Mar",
                             "Apr", "May", "Jun",
                             "Jul", "Aug", "Sep",
                             "Oct", "Nov", "Dec"};
        return (Months[MonthNumber - 1]);
    }
    static short _numberOfDaysInAMonth(short Month, short Year)
    {
        if (Month < 1 || Month > 12)
            return 0;
        int NumberOfDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        return (Month == 2) ? (isLeapYear(Year) ? 29 : 28) : NumberOfDays[Month - 1];
    }
    static string _dayShortName(short dayOfWeekOrder)
    {
        string arrDayNames[] = {
            "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
        return arrDayNames[dayOfWeekOrder];
    }
    static void _printDaysLine()
    {
        cout << "\nSun  Mon  Tue  Wed  Thu  Fri  Sat  \n";
    }
    static void _fillEmptySpaces(int count)
    {
        for (int i = 1; i <= count; i++)
            cout << " ";
    }
    static void _orderDays(short numberDaysOfMonth, short dayOfWeek)
    {
        int specesToSkip = dayOfWeek * 5;
        int spacesInEachLine = 35 - specesToSkip;
        int countMonth = 1;
        _fillEmptySpaces(specesToSkip);

        while (countMonth <= numberDaysOfMonth)
        {
            if (spacesInEachLine == 0)
            {
                cout << "\n";
                spacesInEachLine = 35;
            }

            _fillEmptySpaces(countMonth <= 9 ? 2 : 1);
            cout << countMonth;
            _fillEmptySpaces(2);
            countMonth++;
            spacesInEachLine -= 5;
        }
    }
    void _setDateFromOrderDayInYear(short dayOrder, short year)
    {

        short daysInMonth = 0;
        short month = 1;
        for (; month <= 12; month++)
        {
            daysInMonth = _numberOfDaysInAMonth(month, year);
            if (dayOrder > daysInMonth)
                dayOrder -= daysInMonth;
            else
                break;
        }
        _day = dayOrder;
        _month = month;
        _year = year;
    };
    // 12 Add Days to Date.
    static ClsDate _addDaysToDate(short &day, short &month, short &year, short daysToAdd)
    {
        short daysInMonth = _numberOfDaysInAMonth(month, year);
        day += daysToAdd;

        while (day > daysInMonth)
        {
            day -= daysInMonth;
            month++;
            if (month > 12)
            {
                month = 1;
                year++;
            }
            daysInMonth = _numberOfDaysInAMonth(month, year);
        }
        return ClsDate(day, month, year);
    }

    static bool isLastDayInMonth(ClsDate date)
    {
        return date.getDay() == _numberOfDaysInAMonth(date.getMonth(), date.getYear());
    }

    static bool isLastMonthInYear(ClsDate date)
    {
        return date.getMonth() == 12;
    }

public:
    // Constructors
    ClsDate()
    {
        time_t now = time(0);
        tm *localTime = localtime(&now);

        _second = localTime->tm_sec;
        _minute = localTime->tm_min;
        _hour = localTime->tm_hour;
        _day = localTime->tm_mday;
        _month = localTime->tm_mon + 1;
        _year = localTime->tm_year + 1900;
    };
    ClsDate(short day, short month, short year)
    {
        _day = day;
        _month = month;
        _year = year;
    };
    ClsDate(string date)
    {
        short pos1 = date.find("/");
        _day = stoi(date.substr(0, pos1));
        date.erase(0, pos1 + 1);
        short pos2 = date.find("/");
        _month = stoi(date.substr(0, pos2));
        date.erase(0, pos2 + 1);
        _year = stoi(date);
    }
    ClsDate(short dayOfYear, short year)
    {
        _setDateFromOrderDayInYear(dayOfYear, year);
    }

    // Setters & Getters
    void setSeconds(short second)
    {
        _second = second;
    }
    short getSeconds()
    {
        return _second;
    }
    void setMintues(short mintues)
    {
        _minute = mintues;
    }
    short getMintues()
    {
        return _minute;
    }
    void setHour(short hour)
    {
        _hour = hour;
    }
    short getHour()
    {
        return _hour;
    }
    void setDay(short day)
    {
        _day = day;
    }
    short getDay()
    {
        return _day;
    }
    void setMonth(short month)
    {
        _month = month;
    }
    short getMonth()
    {
        return _month;
    }
    void setYear(short year)
    {
        _year = year;
    }
    short getYear()
    {
        return _year;
    }

    void print()
    {
        cout
            << _day << "/"
            << _month << "/"
            << _year
            << "\n";
    }
    string getDateTime()
    {
        string dateTime = "";
        dateTime += to_string(_day) + "/";
        dateTime += to_string(_month) + "/";
        dateTime += to_string(_year) + " - ";
        dateTime += to_string(_hour) + ":";
        dateTime += to_string(_minute) + ":";
        dateTime += to_string(_second);
        return dateTime;
    }
    //=========================
    // Is Valid Date.
    static bool isValidDate(ClsDate date)
    {
        return (date.getYear() > 0 &&
                date.getMonth() > 0 && date.getMonth() <= 12 &&
                date.getDay() > 0 && date.getDay() <= _numberOfDaysInAMonth(date.getMonth(), date.getYear()));
    }
    bool isValidDate()
    {
        return isValidDate(*this);
    }
    // =========================
    // 1 - Leap Year
    static bool isLeapYear(short year)
    {
        return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
    }
    bool isLeapYear()
    {
        return isLeapYear(_year);
    }
    // =================

    // 4 -
    static short numberDaysOfYear(short year)
    {
        if (isLeapYear(year))
            return 366;

        return 365;
    }
    short numberDaysOfYear()
    {
        return numberDaysOfYear(_year);
    }
    static int numberOfHours(short year)
    {
        return numberDaysOfYear(year) * 24;
    }
    int numberOfHours()
    {
        return numberOfHours(_year);
    }
    static int numberOfMinutes(short year)
    {
        return numberOfHours(year) * 60;
    }
    int numberOfMinutes()
    {
        return numberOfMinutes(_year);
    }
    static int numberOfSeconds(short year)
    {
        return numberOfMinutes(year) * 60;
    }
    int numberOfSeconds()
    {
        return numberOfSeconds(_year);
    }
    //==========================

    // 7- Day Name
    static short dayOfWeekOrder(short Day, short Month, short Year)
    {
        short a, y, m;
        a = (14 - Month) / 12;
        y = Year - a;
        m = Month + (12 * a) - 2;
        // Gregorian:
        // 0:sun, 1:Mon, 2:Tue...etc
        return (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
    }
    short dayOfWeekOrder()
    {
        return dayOfWeekOrder(_day, _month, _year);
    }
    static string dayName(short day, short month, short year)
    {
        return _dayShortName(dayOfWeekOrder(day, month, year));
    }
    string dayName()
    {
        return dayName(_day, _month, _year);
    }
    //==========================

    // 8 - Month Calendar
    static void printMonthCalendar(short month, short year)
    {
        short dayOrderOfWeekForFirstDayOfMonth = dayOfWeekOrder(1, month, year);
        short numberDaysOfMonth = _numberOfDaysInAMonth(month, year);

        cout << "\n_______________" << _monthShortName(month) << "___________________\n";
        _printDaysLine();
        _orderDays(numberDaysOfMonth, dayOrderOfWeekForFirstDayOfMonth);
        cout << "\n______________________________________\n";
    }
    void printMonthCalendar()
    {
        printMonthCalendar(_month, _year);
    }
    static void printYearCalendar(int year)
    {
        cout << "____________________________________\n";
        cout << "         Calendar [" << year << "]\n";
        cout << "____________________________________\n";

        int month = 1;
        for (; month <= 12; month++)
        {
            printMonthCalendar(month, year);
        }
    }
    void printYearCalendar()
    {
        printYearCalendar(_year);
    }
    //======================

    // 10 - Days From Beginning  of Year.
    static short numberOfDaysFromBeginningOfYear(ClsDate date)
    {
        short daysCount = 0;
        for (short iMonth = 1; iMonth < date.getMonth(); iMonth++)
            daysCount += _numberOfDaysInAMonth(iMonth, date.getYear());

        return daysCount + date.getDay();
    };
    short numberOfDaysFromBeginningOfYear()
    {
        return numberOfDaysFromBeginningOfYear(*this);
    }
    //======================

    // 12 Add Days to Date.

    ClsDate addDaysToDate(short daysToAdd)
    {
        return _addDaysToDate(_day, _month, _year, daysToAdd);
    }
    // ======================

    // 13- Date1 Less than Date2.
    static bool isDateLessThan(ClsDate date1, ClsDate date2)
    {
        return (date1.getYear() < date2.getYear()) ||
               (date1.getYear() == date2.getYear() && date1.getMonth() < date2.getMonth()) ||
               (date1.getYear() == date2.getYear() && date1.getMonth() == date2.getMonth() && date1.getDay() < date2.getDay());
    }
    bool isDateLessThan(ClsDate date2)
    {
        return isDateLessThan(*this, date2);
    }
    // ======================

    // 14- Date1 Equals Date2.
    static bool isDateEquals(ClsDate date1, ClsDate date2)
    {
        return (date1.getYear() == date2.getYear() && date1.getMonth() == date2.getMonth() && date1.getDay() == date2.getDay());
    }
    bool isDateEquals(ClsDate date2)
    {
        return isDateEquals(*this, date2);
    }
    // ======================

    // 16- Increase Date by One Day.
    static ClsDate increaseDateByOneDay(ClsDate &date)
    {

        if (isLastDayInMonth(date))
        {
            date.setDay(1);

            if (isLastMonthInYear(date))
            {
                date.setMonth(1);
                date.setYear(date.getYear() + 1);
            }
            else
            {
                date.setMonth(date.getMonth() + 1);
            }
        }
        else
        {
            date.setDay(date.getDay() + 1);
        }

        return date;
    }
    ClsDate increaseDateByOneDay()
    {
        return increaseDateByOneDay(*this);
    }
    // =========================

    // 17- Diff in Days .
    static short diffInDays(ClsDate date1, ClsDate date2, bool isIncludeEndDay = false)
    {
        int numberOfDaysDate1 = numberOfDaysFromBeginningOfYear(date1);
        int numberOfDaysDate2 = numberOfDaysFromBeginningOfYear(date2);

        int diff = numberOfDaysDate2 - numberOfDaysDate1;
        for (int year = date1.getYear(); year < date2.getYear(); year++)
        {
            diff += numberDaysOfYear(year);
        }
        if (isIncludeEndDay)
            ++diff;
        return diff;
    }
    short diffInDays(ClsDate date2, bool isIncludeEndDay = false)
    {
        return diffInDays(*this, date2, isIncludeEndDay);
    }
    // =======================

    // 18- Your Age in Days.
    static short yourAgeInDays(ClsDate dateOfBirth, ClsDate currentDate)
    {
        return diffInDays(currentDate, dateOfBirth);
    }
    short yourAgeInDays(ClsDate currentDate)
    {
        return yourAgeInDays(*this, currentDate);
    }
    // =======================

    //  Diff in Days (Negative Days).
    static short diffInDaysNegative(ClsDate date1, ClsDate date2, bool isIncludeEndDay = false)
    {
        if (isDateLessThan(date1, date2))
            return -diffInDays(date2, date1, isIncludeEndDay);
        return diffInDays(date1, date2, isIncludeEndDay);
    }
    short diffInDaysNegative(ClsDate date2, bool isIncludeEndDay = false)
    {
        return diffInDaysNegative(*this, date2, isIncludeEndDay);
    }
    // =======================

    // 20 - To 32
    // 	1- Increase Date by X Days.

    // 	2- // by One Week
    static ClsDate increaseDateByOneWeek(ClsDate &date)
    {
        return _addDaysToDate(date._day, date._month, date._year, 7);
    }
    ClsDate increaseDateByOneWeek()
    {
        return increaseDateByOneWeek(*this);
    }
    // 	3- // by X Weeks
    static ClsDate increaseDateByXWeeks(ClsDate &date, int numberOfWeeks)
    {
        return _addDaysToDate(date._day, date._month, date._year, numberOfWeeks * 7);
    }
    ClsDate increaseDateByXWeeks(int numberOfWeeks)
    {
        return increaseDateByXWeeks(*this, numberOfWeeks);
    }
    // 	4- // by One Month
    static ClsDate increaseDateByOneMonth(ClsDate &date)
    {
        int countDaysOfNextMonth = _numberOfDaysInAMonth(date.getMonth(), date.getYear());
        return _addDaysToDate(date._day, date._month, date._year, countDaysOfNextMonth);
    }
    ClsDate increaseDateByOneMonth()
    {
        return increaseDateByOneMonth(*this);
    }
    // 	5- // by X Months
    static ClsDate increaseDateByXMonths(ClsDate &date, int numberOfMonths)
    {
        int countDaysOfNextMonth = _numberOfDaysInAMonth(date.getMonth(), date.getYear());
        return _addDaysToDate(date._day, date._month, date._year, countDaysOfNextMonth * numberOfMonths);
    }
    ClsDate increaseDateByXMonths(int numberOfMonths)
    {
        return increaseDateByXMonths(*this, numberOfMonths);
    }
    // 	6- // by One Year
    static ClsDate increaseDateByOneYear(ClsDate &date)
    {
        return _addDaysToDate(date._day, date._month, date._year, numberDaysOfYear(date.getYear()));
    }
    ClsDate increaseDateByOneYear()
    {
        return increaseDateByOneYear(*this);
    }
    // 	7- // by X Years
    static ClsDate increaseDateByXYears(ClsDate &date, int numberOfYears)
    {
        return _addDaysToDate(date._day, date._month, date._year, numberDaysOfYear(date.getYear()) * numberOfYears);
    }
    ClsDate increaseDateByXYears(int numberOfYears)
    {
        return increaseDateByXYears(*this, numberOfYears);
    }
    // 	8- // by One Decade - mean 10 years
    static ClsDate increaseDateByOneDecade(ClsDate &date)
    {
        return _addDaysToDate(date._day, date._month, date._year, numberDaysOfYear(date.getYear()) * 10);
    }
    ClsDate increaseDateByOneDecade()
    {
        return increaseDateByOneDecade(*this);
    }
    // 	9- // by X Decades
    static ClsDate increaseDateByXDecades(ClsDate &date, int numberOfDecades)
    {
        return _addDaysToDate(date._day, date._month, date._year, numberDaysOfYear(date.getYear()) * 10 * numberOfDecades);
    }
    ClsDate increaseDateByXDecades(int numberOfDecades)
    {
        return increaseDateByXDecades(*this, numberOfDecades);
    }
    // 	10- // By One Century - mean 100 years
    static ClsDate increaseDateByOneCentury(ClsDate &date)
    {
        return _addDaysToDate(date._day, date._month, date._year, numberDaysOfYear(date.getYear()) * 100);
    }
    ClsDate increaseDateByOneCentury()
    {
        return increaseDateByOneCentury(*this);
    }
    // 	11- // by One Millennium - mean 1000 years
    static ClsDate increaseDateByOneMillennium(ClsDate &date)
    {
        return _addDaysToDate(date._day, date._month, date._year, numberDaysOfYear(date.getYear()) * 1000);
    }
    ClsDate increaseDateByOneMillennium()
    {
        return increaseDateByOneMillennium(*this);
    }
    // All these Incresed data function implemented by AI, so it is not efficient,
    // ==========================================================

    // Public accessors for protected helpers
    static short numberOfDaysInAMonth(short month, short year)
    {
        return _numberOfDaysInAMonth(month, year);
    }
    short numberOfDaysInAMonth()
    {
        return _numberOfDaysInAMonth(_month, _year);
    }
    // =========================

    static string monthShortName(short monthNumber)
    {
        return _monthShortName(monthNumber);
    }
    string monthShortName()
    {
        return _monthShortName(_month);
    }
    // =========================

    static string dayShortName(short dayOfWeekOrder)
    {
        return _dayShortName(dayOfWeekOrder);
    }
    static string dayShortName(short day, short month, short year)
    {
        return _dayShortName(dayOfWeekOrder(day, month, year));
    }
    string dayShortName()
    {
        return _dayShortName(dayOfWeekOrder(_day, _month, _year));
    }
    // =========================

    // Get System Date
    static ClsDate getSystemDate()
    {
        time_t t = time(0);
        tm *now = localtime(&t);

        short day = now->tm_mday;
        short month = now->tm_mon + 1;
        short year = now->tm_year + 1900;

        return ClsDate(day, month, year);
    }
    // =========================

    // Date To String
    static string dateToString(ClsDate date)
    {
        return to_string(date.getDay()) + "/" + to_string(date.getMonth()) + "/" + to_string(date.getYear());
    }
    string dateToString()
    {
        return dateToString(*this);
    }
    // =========================

    // Time Calculations in Months
    static short numberOfHoursInAMonth(short month, short year)
    {
        return numberOfDaysInAMonth(month, year) * 24;
    }
    short numberOfHoursInAMonth()
    {
        return numberOfDaysInAMonth(_month, _year) * 24;
    }

    static int numberOfMinutesInAMonth(short month, short year)
    {
        return numberOfHoursInAMonth(month, year) * 60;
    }
    int numberOfMinutesInAMonth()
    {
        return numberOfHoursInAMonth(_month, _year) * 60;
    }

    static int numberOfSecondsInAMonth(short month, short year)
    {
        return numberOfMinutesInAMonth(month, year) * 60;
    }
    int numberOfSecondsInAMonth()
    {
        return numberOfMinutesInAMonth(_month, _year) * 60;
    }
    // =========================

    // Get Days From Beginning Of Year
    static short getDaysFromBeginningOfYear(ClsDate date)
    {
        short daysCount = 0;
        for (short iMonth = 1; iMonth < date.getMonth(); iMonth++)
            daysCount += numberOfDaysInAMonth(iMonth, date.getYear());

        return daysCount + date.getDay();
    }
    short getDaysFromBeginningOfYear()
    {
        return getDaysFromBeginningOfYear(*this);
    }
    // =========================

    // Get Date From Day Order In Year
    static ClsDate getDateFromDayOrderInYear(short dayOrderInYear, short year)
    {
        ClsDate date(1, 1, year);
        short remainingDays = dayOrderInYear;
        short monthDays = 0;

        while (true)
        {
            monthDays = numberOfDaysInAMonth(date.getMonth(), date.getYear());

            if (remainingDays > monthDays)
            {
                remainingDays -= monthDays;
                date.setMonth(date.getMonth() + 1);
            }
            else
            {
                date.setDay(remainingDays);
                break;
            }
        }

        return date;
    }
    // =========================

    // Add Days to Date
    void addDays(short daysToAdd)
    {
        short remainingDays = daysToAdd + getDaysFromBeginningOfYear(*this);
        short monthDays = 0;

        _month = 1;

        while (true)
        {
            monthDays = numberOfDaysInAMonth(_month, _year);

            if (remainingDays > monthDays)
            {
                remainingDays -= monthDays;
                _month++;

                if (_month > 12)
                {
                    _month = 1;
                    _year++;
                }
            }
            else
            {
                _day = remainingDays;
                break;
            }
        }
    }
    // =========================

    // Swap Dates
    static void swapDates(ClsDate &date1, ClsDate &date2)
    {
        ClsDate tempDate;
        tempDate = date1;
        date1 = date2;
        date2 = tempDate;
    }
    // =========================

    // Date Comparison Functions
    static bool isDate1BeforeDate2(ClsDate date1, ClsDate date2)
    {
        return (date1.getYear() < date2.getYear()) ? true : ((date1.getYear() == date2.getYear()) ? (date1.getMonth() < date2.getMonth() ? true : (date1.getMonth() == date2.getMonth() ? date1.getDay() < date2.getDay() : false)) : false);
    }
    bool isDateBeforeDate2(ClsDate date2)
    {
        return isDate1BeforeDate2(*this, date2);
    }

    static bool isDate1EqualDate2(ClsDate date1, ClsDate date2)
    {
        return (date1.getYear() == date2.getYear()) ? ((date1.getMonth() == date2.getMonth()) ? ((date1.getDay() == date2.getDay()) ? true : false) : false) : false;
    }
    bool isDateEqualDate2(ClsDate date2)
    {
        return isDate1EqualDate2(*this, date2);
    }

    static bool isDate1AfterDate2(ClsDate date1, ClsDate date2)
    {
        return (!isDate1BeforeDate2(date1, date2) && !isDate1EqualDate2(date1, date2));
    }
    bool isDateAfterDate2(ClsDate date2)
    {
        return isDate1AfterDate2(*this, date2);
    }
    // =========================

    // Add One Day
    static ClsDate addOneDay(ClsDate date)
    {
        if (isLastDayInMonth(date))
        {
            if (isLastMonthInYear(date))
            {
                date.setMonth(1);
                date.setDay(1);
                date.setYear(date.getYear() + 1);
            }
            else
            {
                date.setDay(1);
                date.setMonth(date.getMonth() + 1);
            }
        }
        else
        {
            date.setDay(date.getDay() + 1);
        }

        return date;
    }
    void addOneDay()
    {
        *this = addOneDay(*this);
    }
    // =========================

    // Get Difference In Days
    static int getDifferenceInDays(ClsDate date1, ClsDate date2, bool includeEndDay = false)
    {
        int days = 0;
        short swapFlagValue = 1;

        if (!isDate1BeforeDate2(date1, date2))
        {
            swapDates(date1, date2);
            swapFlagValue = -1;
        }

        while (isDate1BeforeDate2(date1, date2))
        {
            days++;
            date1 = addOneDay(date1);
        }

        return includeEndDay ? ++days * swapFlagValue : days * swapFlagValue;
    }
    int getDifferenceInDays(ClsDate date2, bool includeEndDay = false)
    {
        return getDifferenceInDays(*this, date2, includeEndDay);
    }
    // =========================

    // Decrease Date By One Day
    static ClsDate decreaseDateByOneDay(ClsDate date)
    {
        if (date.getDay() == 1)
        {
            if (date.getMonth() == 1)
            {
                date.setMonth(12);
                date.setDay(31);
                date.setYear(date.getYear() - 1);
            }
            else
            {
                date.setMonth(date.getMonth() - 1);
                date.setDay(numberOfDaysInAMonth(date.getMonth(), date.getYear()));
            }
        }
        else
        {
            date.setDay(date.getDay() - 1);
        }

        return date;
    }
    void decreaseDateByOneDay()
    {
        *this = decreaseDateByOneDay(*this);
    }
    // =========================

    // Decrease Date By One Week
    static ClsDate decreaseDateByOneWeek(ClsDate &date)
    {
        for (int i = 1; i <= 7; i++)
        {
            date = decreaseDateByOneDay(date);
        }

        return date;
    }
    void decreaseDateByOneWeek()
    {
        decreaseDateByOneWeek(*this);
    }
    // =========================

    // Decrease Date By X Weeks
    static ClsDate decreaseDateByXWeeks(short weeks, ClsDate &date)
    {
        for (short i = 1; i <= weeks; i++)
        {
            date = decreaseDateByOneWeek(date);
        }
        return date;
    }
    void decreaseDateByXWeeks(short weeks)
    {
        decreaseDateByXWeeks(weeks, *this);
    }
    // =========================

    // Decrease Date By One Month
    static ClsDate decreaseDateByOneMonth(ClsDate &date)
    {
        if (date.getMonth() == 1)
        {
            date.setMonth(12);
            date.setYear(date.getYear() - 1);
        }
        else
            date.setMonth(date.getMonth() - 1);

        short daysInCurrentMonth = numberOfDaysInAMonth(date.getMonth(), date.getYear());
        if (date.getDay() > daysInCurrentMonth)
        {
            date.setDay(daysInCurrentMonth);
        }

        return date;
    }
    void decreaseDateByOneMonth()
    {
        decreaseDateByOneMonth(*this);
    }
    // =========================

    // Decrease Date By X Days
    static ClsDate decreaseDateByXDays(short days, ClsDate &date)
    {
        for (short i = 1; i <= days; i++)
        {
            date = decreaseDateByOneDay(date);
        }
        return date;
    }
    void decreaseDateByXDays(short days)
    {
        decreaseDateByXDays(days, *this);
    }
    // =========================

    // Decrease Date By X Months
    static ClsDate decreaseDateByXMonths(short months, ClsDate &date)
    {
        for (short i = 1; i <= months; i++)
        {
            date = decreaseDateByOneMonth(date);
        }
        return date;
    }
    void decreaseDateByXMonths(short months)
    {
        decreaseDateByXMonths(months, *this);
    }
    // =========================

    // Decrease Date By One Year
    static ClsDate decreaseDateByOneYear(ClsDate &date)
    {
        date.setYear(date.getYear() - 1);
        return date;
    }
    void decreaseDateByOneYear()
    {
        decreaseDateByOneYear(*this);
    }
    // =========================

    // Decrease Date By X Years
    static ClsDate decreaseDateByXYears(short years, ClsDate &date)
    {
        date.setYear(date.getYear() - years);
        return date;
    }
    void decreaseDateByXYears(short years)
    {
        decreaseDateByXYears(years, *this);
    }
    // =========================

    // Decrease Date By One Decade
    static ClsDate decreaseDateByOneDecade(ClsDate &date)
    {
        date.setYear(date.getYear() - 10);
        return date;
    }
    void decreaseDateByOneDecade()
    {
        decreaseDateByOneDecade(*this);
    }
    // =========================

    // Decrease Date By X Decades
    static ClsDate decreaseDateByXDecades(short decades, ClsDate &date)
    {
        date.setYear(date.getYear() - decades * 10);
        return date;
    }
    void decreaseDateByXDecades(short decades)
    {
        decreaseDateByXDecades(decades, *this);
    }
    // =========================

    // Decrease Date By One Century
    static ClsDate decreaseDateByOneCentury(ClsDate &date)
    {
        date.setYear(date.getYear() - 100);
        return date;
    }
    void decreaseDateByOneCentury()
    {
        decreaseDateByOneCentury(*this);
    }
    // =========================

    // Decrease Date By One Millennium
    static ClsDate decreaseDateByOneMillennium(ClsDate &date)
    {
        date.setYear(date.getYear() - 1000);
        return date;
    }
    void decreaseDateByOneMillennium()
    {
        decreaseDateByOneMillennium(*this);
    }
    // =========================

    // Business Day Functions
    static bool isEndOfWeek(ClsDate date)
    {
        return dayOfWeekOrder(date.getDay(), date.getMonth(), date.getYear()) == 6;
    }
    bool isEndOfWeek()
    {
        return isEndOfWeek(*this);
    }
    // =========================

    static bool isWeekEnd(ClsDate date)
    {
        short dayIndex = dayOfWeekOrder(date.getDay(), date.getMonth(), date.getYear());
        return (dayIndex == 5 || dayIndex == 6);
    }
    bool isWeekEnd()
    {
        return isWeekEnd(*this);
    }
    // =========================

    static bool isBusinessDay(ClsDate date)
    {
        return !isWeekEnd(date);
    }
    bool isBusinessDay()
    {
        return isBusinessDay(*this);
    }
    // =========================

    static short daysUntilTheEndOfWeek(ClsDate date)
    {
        return 6 - dayOfWeekOrder(date.getDay(), date.getMonth(), date.getYear());
    }
    short daysUntilTheEndOfWeek()
    {
        return daysUntilTheEndOfWeek(*this);
    }
    // =========================

    static short daysUntilTheEndOfMonth(ClsDate date1)
    {
        ClsDate endOfMonthDate;
        endOfMonthDate.setDay(numberOfDaysInAMonth(date1.getMonth(), date1.getYear()));
        endOfMonthDate.setMonth(date1.getMonth());
        endOfMonthDate.setYear(date1.getYear());

        return getDifferenceInDays(date1, endOfMonthDate, true);
    }
    short daysUntilTheEndOfMonth()
    {
        return daysUntilTheEndOfMonth(*this);
    }
    // =========================

    static short daysUntilTheEndOfYear(ClsDate date1)
    {
        ClsDate endOfYearDate;
        endOfYearDate.setDay(31);
        endOfYearDate.setMonth(12);
        endOfYearDate.setYear(date1.getYear());

        return getDifferenceInDays(date1, endOfYearDate, true);
    }
    short daysUntilTheEndOfYear()
    {
        return daysUntilTheEndOfYear(*this);
    }
    // =========================

    // Vacation and Business Days Calculation
    static short calculateBusinessDays(ClsDate dateFrom, ClsDate dateTo)
    {
        short days = 0;
        while (isDate1BeforeDate2(dateFrom, dateTo))
        {
            if (isBusinessDay(dateFrom))
                days++;

            dateFrom = addOneDay(dateFrom);
        }

        return days;
    }
    // =========================

    static short calculateVacationDays(ClsDate dateFrom, ClsDate dateTo)
    {
        return calculateBusinessDays(dateFrom, dateTo);
    }
    // =========================

    static ClsDate calculateVacationReturnDate(ClsDate dateFrom, short vacationDays)
    {
        short weekEndCounter = 0;

        for (short i = 1; i <= vacationDays; i++)
        {
            if (isWeekEnd(dateFrom))
                weekEndCounter++;

            dateFrom = addOneDay(dateFrom);
        }
        for (short i = 1; i <= weekEndCounter; i++)
            dateFrom = addOneDay(dateFrom);

        return dateFrom;
    }
    // =========================

    // Date Comparison Enum
    enum enDateCompare
    {
        Before = -1,
        Equal = 0,
        After = 1
    };

    static enDateCompare compareDates(ClsDate date1, ClsDate date2)
    {
        if (isDate1BeforeDate2(date1, date2))
            return enDateCompare::Before;

        if (isDate1EqualDate2(date1, date2))
            return enDateCompare::Equal;

        return enDateCompare::After;
    }
    enDateCompare compareDates(ClsDate date2)
    {
        return compareDates(*this, date2);
    }
    // =========================
};