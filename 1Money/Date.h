#pragma once
#include <ctime>
#include <tuple>

using std::tuple;

class Date
{
	time_t _now = time(nullptr);
	tm* _ltm = localtime(&_now);
	int _year = _ltm->tm_year + 1900,
		_month = _ltm->tm_mon + 1,
		_day = _ltm->tm_mday;
public:
	virtual ~Date() = default;

	virtual tuple<int, int, int> Today() const;
};
