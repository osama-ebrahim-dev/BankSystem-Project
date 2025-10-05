#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;


class clsString
{

public:
    enum enLetterCase { Small = 0, Capital = 1, None = 2 };
private:
    string _Value;
private:
    static char _InvertLetterCase(char Char)
    {
        return isupper(Char) ? tolower(Char) : toupper(Char);
    }
public:



    clsString(string Value)
    {
        _Value = Value;
    }
    clsString()
    {
        _Value = "";
    }

    void SetValue(string Value)
    {
        _Value = Value;
    }
    string GetValue()
    {
        return _Value;
    }

    static short CountWords(string Sentence)
    {
        Sentence = Sentence + " ";
        string delim = " ";
        short Counter = 0;
        short pos = 0;
        string sWord;

        while ((pos = Sentence.find(delim)) != string::npos)
        {
            sWord = Sentence.substr(0, pos);
            if (sWord != "")
            {
                Counter++;
            }


            Sentence.erase(0, pos + delim.length());
        }

        return Counter;

    }
    short CountWords()
    {
        return CountWords(_Value);
    }

    static string UpperOrLowerAllLetters(string& Sentence, bool IsUpper)
    {
        if (IsUpper)
        {
            for (char& Letter : Sentence)
            {
                Letter = toupper(Letter);
            }
        }
        else
        {
            for (char& Letter : Sentence)
            {
                Letter = tolower(Letter);
            }

        }

        return Sentence;
    }
    void UpperOrLowerAllLetters(bool IsUpper)
    {
        _Value = UpperOrLowerAllLetters(_Value, IsUpper);

    }


    static string InvertAllLettersCase(string Sentence)
    {
        for (char& Letter : Sentence)
        {
            Letter = _InvertLetterCase(Letter);
        }

        return Sentence;
    }
    string InvertAllLettersCase()
    {
        return InvertAllLettersCase(_Value);
    }


    static short CountLetters(string Sentence, enLetterCase LetterCase)
    {
        if (LetterCase == enLetterCase::None)
        {
            return Sentence.size();
        }

        short Counter = 0;

        if (LetterCase == enLetterCase::Small)
        {
            for (char& Letter : Sentence)
            {
                if (islower(Letter))
                {
                    Counter++;
                }
            }
        }
        else
        {
            for (char& Letter : Sentence)
            {
                if (isupper(Letter))
                {
                    Counter++;
                }
            }
        }

        return Counter;
    }
    short CountLetters(enLetterCase LetterCase)
    {
        return CountLetters(_Value, LetterCase);
    }

    static vector <string> vSplit(string Sentence, string delimiter)
    {
        Sentence = Sentence + delimiter;
        short Counter = 0;
        short pos = 0;
        string Word;
        vector <string> vWords;

        pos = Sentence.find(delimiter);

        while (pos != string::npos)
        {
            Word = Sentence.substr(0, pos);

            vWords.push_back(Word);

            Sentence.erase(0, pos + delimiter.length());

            pos = Sentence.find(delimiter);
        }

        return vWords;

    }
    vector <string> vSplit(string delimiter)
    {
        return vSplit(_Value, delimiter);
    }

    static string trim(const string& Sentence)
    {
        size_t start = 0;
        size_t end = Sentence.length();

        while (start < end && std::isspace(static_cast<unsigned char>(Sentence[start]))) {
            start++;
        }

        while (end > start && std::isspace(static_cast<unsigned char>(Sentence[end - 1]))) {
            end--;
        }

        return Sentence.substr(start, end - start);
    }
    string trim()
    {
        return trim(_Value);
    }

    static string JoinStrings(vector<string> vWords, string delimiter)
    {
        string Sentence = "";
        for (string& Word : vWords)
        {
            Sentence += (Word + delimiter);
        }
        return Sentence.substr(0, Sentence.length() - delimiter.length());
    }

};


