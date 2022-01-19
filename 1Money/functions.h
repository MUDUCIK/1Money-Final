#pragma once
#include <algorithm>
#include <string>
#include <iostream>

using std::string;
using std::tuple;
using std::exception;
using std::cin;
using std::to_string;

tuple<int,int,int> DateParser(const string& date);

int JDN(const int& day, const int& month, const int& year);

bool PinCodeChecker(const string& code);

string CardNumberGenerator();

string Getline();

string ConvertToAscii(const string& str);

string ConvertFromAscii(const string& str);

void ToLower(string& str);