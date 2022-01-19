#pragma once
#include "interfaces.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <deque>
#include "functions.h"
#include "Date.h"

using std::cout;
using std::endl;
using std::sort;
using std::stod;
using std::deque;
using std::pair;
using nlohmann::ordered_json;

class IntervalBase : public IInterval
{
public:
	void Day(const string& number, const json& object) override;

	void Week(const string& number, const json& object) override;

	void Month(const string& number, const json& object) override;

	void Check(const string& number, const json& object) override;

	virtual void Show(const json& object);

	virtual void Sort(json& object);
};

class TopExpenses : public IntervalBase
{
public:
	void Day(const string& number, const json& object) override;

	void Week(const string& number, const json& object) override;

	void Month(const string& number, const json& object) override;

	void Show(const json& object) override;
};

class TopCategory : public IntervalBase
{
public:
	void Day(const string& number, const json& object) override;

	void Week(const string& number, const json& object) override;

	void Month(const string& number, const json& object) override;

	ordered_json SortWithoutOrder(json& object);

	void ShowWithoutOrder(const ordered_json& object);
};
