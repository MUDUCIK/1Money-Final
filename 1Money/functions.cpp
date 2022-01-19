#include "functions.h"

int JDN(const int& day, const int& month, const int& year)
{
	int a = (14 - month) / 12,
		y = year + 4800 - a,
		m = month + 12 * a - 3,
		JDN = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;

	return JDN;
}

tuple<int,int,int> DateParser(const string& date)
{
	int day = stoi(date.substr(0, 2)),
		month = stoi(date.substr(3, 5)),
		year = stoi(date.substr(6, 10));
	return tuple(day, month, year);
}

//throw exception
bool PinCodeChecker(const string& code)
{
	if (code.length() != 4) throw exception("Длина пин-кода должна составлять 4 цифры!");
	for (const char& symbol : code) if (symbol < '0' || symbol > '9') throw exception("Пин-код может содержать только цифры!");
	return true;
}

string CardNumberGenerator()
{
	string number;
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
			number.append(to_string(rand() % 9));
		number.append(" ");
	}
	number.erase(number.length() - 1);
	return number;
}

string Getline()
{
	string temp;

	while (temp.empty()) getline(cin, temp);

	return temp;
}

string ConvertToAscii(const string& str)
{
	string res;
	for (int ascii : str)
		res.append(to_string(ascii) + " ");
	return res;
}

string ConvertFromAscii(const string& str)
{
	string res, tmp;
	for (const char& symbol : str)
	{
		tmp.push_back(symbol);

		if (symbol == ' ')
		{
			res.push_back(stoi(tmp));
			tmp.clear();
		}

	}
	return res;
}

void ToLower(string& str)
{
	std::ranges::for_each(str, [](char& c) {c = tolower(c); });
}