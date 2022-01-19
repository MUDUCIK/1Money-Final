#pragma once
#include <nlohmann/json.hpp>
#include <string>

using std::string;
using nlohmann::json;

template<class T>
class ISaver
{
public:
	virtual void Save(const T& object) = 0;

	virtual ~ISaver() = default;
};

template<class T>
class ILoader
{
public:
	virtual T Load() = 0;

	virtual ~ILoader() = default;
};

class IPurse
{
public:
	IPurse() = default;
	virtual ~IPurse() = default;

	virtual void Check(const string& number, const json& object) = 0;

	virtual string GetType() const = 0;

	virtual string GetCode(const string& number, const json& object) const = 0;

	virtual std::tuple<int, string, bool> GetInfo(const string& number, const json& object) = 0;

	virtual void ShowAllCards(const string& number, const json& object) = 0;

	virtual void SubmitExpense(const string& number, const double& bill, json& object) = 0;

	virtual void Replenishment(const string& number, const string& date, const string& category, const double& sum, json& object) = 0;

	virtual void Create(const string& userNumber, json& object) = 0;

	virtual void ClearCategory(const string& userNumber, const string& card, const string& category, json& object) = 0;

	virtual void DeleteCategory(const string& userNumber, const string& card, const string& category, json& object) = 0;
};

class IInterval
{
public:
	virtual ~IInterval() = default;

	virtual void Day(const string& number, const json& object) = 0;

	virtual void Week(const string& number, const json& object) = 0;

	virtual void Month(const string& number, const json& object) = 0;

	virtual void Check(const string& number, const json& object) = 0;
};

class IUser
{
public:
	virtual ~IUser() = default;

	virtual string GetFIO() const = 0;

	virtual std::tuple<int, string, bool> GetCardInfo() const = 0;

	virtual bool GetLoggedField() const = 0;

	virtual bool Login(const string& phoneNumber, const string& password) = 0;

	virtual bool Register(const string& phoneNumber, const string& fio, const string& password) = 0;

	virtual void TakeJsonObject(const json& object) = 0;

	virtual json GetJsonObject() const = 0;

	virtual void ShowAllCards() = 0;

	virtual void SubmitExpense(const double& bill) = 0;

	virtual void Replenishment(const string& category, const double& sum) = 0;

	virtual void Create() = 0;

	virtual void ClearCategory(const string& card, const string& category) = 0;

	virtual void DeleteCategory(const string& card, const string& category) = 0;

	virtual void Day() = 0;

	virtual void Week() = 0;

	virtual void Month() = 0;

	virtual void ExpenseDay() = 0;

	virtual void ExpenseWeek() = 0;

	virtual void ExpenseMonth() = 0;

	virtual void CategoryDay() = 0;

	virtual void CategoryWeek() = 0;

	virtual void CategoryMonth() = 0;

	virtual void ChangeCard(IPurse* purse) = 0;

	virtual void Reset() = 0;

	virtual void LastSessionSave() = 0;

	virtual void LastSessionLoad() = 0;

	virtual bool CheckAvailability(const string& type) = 0;

	virtual bool CheckCardExistence() = 0;

	virtual string GetCardType() const = 0;

	virtual string GetCardCode() const = 0;
};