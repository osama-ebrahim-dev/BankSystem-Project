#pragma once

#include <iostream>
#include <string>

using namespace std;


class clsUtil
{
public:


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


};

