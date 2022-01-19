#pragma once
#include "interfaces.h"
#include "functions.h"
#include <string>
#include <iostream>

using std::exception;
using std::cout;
using std::endl;

class CardBase : public IPurse
{
protected:
	double Limit = 0;
	string Type = "base";
public:
	CardBase() = default;

	void Check(const string& number, const json& object) override;

	string GetType() const override;

	string GetCode(const string& number, const json& object) const override;

	tuple<int, string, bool> GetInfo(const string& number, const json& object) override;

	void SubmitExpense(const string& number, const double& bill, json& object) override;

	void Replenishment(const string& number, const string& date, const string& category, const double& sum, json& object) override;

	void Create(const string& userNumber, json& object) override;

	void ClearCategory(const string& userNumber, const string& card, const string& category, json& object) override;

	void DeleteCategory(const string& userNumber, const string& card, const string& category, json& object) override;

	void ShowAllCards(const string& number, const json& object) override;
};

class Card final : public CardBase
{
public:
	explicit Card();
};

class Debit final : public CardBase
{
public:
	explicit Debit();
};

class Vip final : public CardBase
{
public:
	explicit Vip();
};

class Gold final : public CardBase
{
public:
	explicit Gold();
};