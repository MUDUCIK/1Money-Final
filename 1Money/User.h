#pragma once
#include <deque>
#include "interfaces.h"
#include "functions.h"
#include "reports.h"
#include "Date.h"

class BaseUser : public IUser
{
protected:
	bool Logged = false;
	string PhoneNumber,
		FIO,
		Password;
	IInterval* IntervalBase = nullptr;
	IInterval* TopExpenses = nullptr;
	IInterval* TopCategory = nullptr;
	IPurse* Card = nullptr;
	Date Date;
	static json Users;
public:

	explicit BaseUser(class IntervalBase* intervalBase, class TopExpenses* TopExpenses, class TopCategory* TopCategory);

	virtual void Check();

	virtual void CreateUser(const string& phoneNumber, const string& fio, const string& password, const std::deque<string>& avalaible);

	string GetFIO() const override;

	tuple<int, string, bool> GetCardInfo() const override;

	void Reset() override;

	bool GetLoggedField() const override;

	bool Login(const string& phoneNumber, const string& password) override;

	bool Register(const string& phoneNumber, const string& fio, const string& password) override;

	void TakeJsonObject(const json& object) override;

	json GetJsonObject() const override;

	void SubmitExpense(const double& bill) override;

	void Replenishment(const string& category, const double& sum) override;

	void Create() override;

	void ClearCategory(const string& card, const string& category) override;

	void DeleteCategory(const string& card, const string& category) override;

	void ShowAllCards() override;

	void Day() override;

	void Week() override;

	void Month() override;

	void ExpenseDay() override;

	void ExpenseWeek() override;

	void ExpenseMonth() override;

	void CategoryDay() override;

	void CategoryWeek() override;

	void CategoryMonth() override;

	void ChangeCard(IPurse* purse) override;

	string GetCardType() const override;

	string GetCardCode() const override;

	void LastSessionSave() override;

	void LastSessionLoad() override;

	bool CheckAvailability(const string& type) override;

	bool CheckCardExistence() override;
};

class VipUser final : public BaseUser
{
public:
	explicit VipUser(class IntervalBase* intervalBase, class TopExpenses* TopExpenses, class TopCategory* TopCategory);

	bool Register(const string& phoneNumber, const string& fio, const string& password) override;

};

class GoldUser final : public BaseUser
{
public:
	explicit GoldUser(class IntervalBase* intervalBase, class TopExpenses* TopExpenses, class TopCategory* TopCategory);


	bool Register(const string& phoneNumber, const string& fio, const string& password) override;

};