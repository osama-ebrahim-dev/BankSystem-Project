#pragma once

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>



using namespace std;


class clsUtil
{
public:

    static string GetCurrentTime()
    {
        using namespace std::chrono;

        auto now = system_clock::now();
        std::time_t nowTime = system_clock::to_time_t(now);

        std::tm localTime;
#ifdef _WIN32
        localtime_s(&localTime, &nowTime);   
#else
        localtime_r(&localTime, &nowTime);   
#endif

        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << localTime.tm_hour << ":"
            << std::setw(2) << std::setfill('0') << localTime.tm_min << ":"
            << std::setw(2) << std::setfill('0') << localTime.tm_sec;

        return oss.str();
    }

    static string GetTodayDate()
    {
        using namespace std::chrono;

        auto now = system_clock::now();
        std::time_t tt = system_clock::to_time_t(now);

        std::tm localTime{};
#ifdef _WIN32
        localtime_s(&localTime, &tt);
#else
        localtime_r(&tt, &localTime);
#endif

        int day = localTime.tm_mday;
        int month = localTime.tm_mon + 1; 
        int year = localTime.tm_year + 1900;

        return std::to_string(day) + "-" +
            std::to_string(month) + "-" +
            std::to_string(year);
    }

    static string numberToWords(long long number) 
    {
        string ones[] = { "", "one", "two", "three", "four", "five", "six",
                         "seven", "eight", "nine", "ten", "eleven", "twelve",
                         "thirteen", "fourteen", "fifteen", "sixteen", "seventeen",
                         "eighteen", "nineteen" };

        string tens[] = { "", "", "twenty", "thirty", "forty", "fifty",
                         "sixty", "seventy", "eighty", "ninety" };

        if (number == 0)
            return "zero";

        if (number < 0)
            return "minus " + numberToWords(-number);

        string result = "";

        if (number >= 1000000) {
            result += numberToWords(number / 1000000) + " million";
            number %= 1000000;
            if (number > 0) result += " ";
        }

        if (number >= 1000) {
            result += numberToWords(number / 1000) + " thousand";
            number %= 1000;
            if (number > 0) result += " ";
        }

        if (number >= 100) {
            result += ones[number / 100] + string(" hundred");
            number %= 100;
            if (number > 0) result += " ";
        }

        if (number >= 20) {
            result += tens[number / 10];
            if (number % 10 > 0)
                result += "-" + ones[number % 10];
        }
        else if (number > 0) {
            result += ones[number];
        }

        return result;
    }

    static bool AddLineToFile(string Line , string FileName)
    {
        fstream File;
        File.open(FileName, ios::out | ios::app);
        if (File.is_open())
        {
            File << Line << endl;
            File.close();
            return true;
        }
        return false;
        
    }


};

