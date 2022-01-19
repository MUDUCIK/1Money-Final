#include "User.h"

BaseUser::BaseUser(::IntervalBase* intervalBase, ::TopExpenses* TopExpenses, ::TopCategory* TopCategory)
	: IntervalBase(intervalBase), TopExpenses(TopExpenses), TopCategory(TopCategory) {}

void BaseUser::Check()
{
	if (Users.empty()) throw exception("Object is empty!");
}

void BaseUser::CategoryDay()
{
	TopCategory->Day(PhoneNumber, Users);
}

void BaseUser::CategoryWeek()
{
	TopCategory->Week(PhoneNumber, Users);
}

void BaseUser::CategoryMonth()
{
	TopCategory->Month(PhoneNumber, Users);
}

void BaseUser::ChangeCard(IPurse* purse)
{
	Card = purse;
}

bool BaseUser::CheckAvailability(const string& type)
{
	return std::ranges::any_of(Users[PhoneNumber]["avalaible"],
		[type](const string& item) {return item == type; });
}

bool BaseUser::CheckCardExistence()
{
	if (!Users[PhoneNumber]["cards"].contains(Card->GetType())) return false;
	return true;
}

void BaseUser::ClearCategory(const string& card, const string& category)
{
	Card->ClearCategory(PhoneNumber, card, category, Users);
}

void BaseUser::Create()
{
	Card->Create(PhoneNumber, Users);
}

void BaseUser::CreateUser(const string& phoneNumber, const string& fio, const string& password, const deque<string>& avalaible)
{
	Users[phoneNumber] = {
			{"name", fio},
			{"password", password}
	};

	for (const auto& str : avalaible)
		Users[phoneNumber]["avalaible"].push_back(str);
}

void BaseUser::Day()
{
	IntervalBase->Day(PhoneNumber, Users);
}

void BaseUser::DeleteCategory(const string& card, const string& category)
{
	Card->DeleteCategory(PhoneNumber, card, category, Users);
}

void BaseUser::ExpenseDay()
{
	TopExpenses->Day(PhoneNumber, Users);
}

void BaseUser::ExpenseMonth()
{
	TopExpenses->Month(PhoneNumber, Users);
}

void BaseUser::ExpenseWeek()
{
	TopExpenses->Week(PhoneNumber, Users);
}

string BaseUser::GetCardCode() const
{
	return Card->GetCode(PhoneNumber, Users);
}

tuple<int, string, bool> BaseUser::GetCardInfo() const
{
	return Card->GetInfo(PhoneNumber, Users);
}

string BaseUser::GetCardType() const
{
	return Card->GetType();
}

string BaseUser::GetFIO() const
{
	return FIO;
}

json BaseUser::GetJsonObject() const
{
	return Users;
}

void BaseUser::SubmitExpense(const double& bill)
{
	Card->SubmitExpense(PhoneNumber, bill, Users);
}

bool BaseUser::GetLoggedField() const
{
	return Logged;
}

void BaseUser::LastSessionLoad()
{
	if (Users.contains("lastSession"))
	{
		string phone = Users["lastSession"]["phone"],
			password = Users["lastSession"]["password"];
		Login(phone, password);
	}
}

void BaseUser::LastSessionSave()
{
	Users["lastSession"] = {
			{"password", Password},
			{"phone", PhoneNumber}
	};
}

bool BaseUser::Login(const string& phoneNumber, const string& password)
{
	if (Users.contains(phoneNumber))
		if (Users[phoneNumber]["password"] == password)
		{
			PhoneNumber = phoneNumber;
			FIO = ConvertFromAscii(Users[phoneNumber]["name"]);
			Password = password;
			Logged = true;
		}
		else throw exception("wrong login or password");
	else throw exception("User not found!");
	return true;
}

void BaseUser::Month()
{
	IntervalBase->Month(PhoneNumber, Users);
}

bool BaseUser::Register(const string& phoneNumber, const string& fio, const string& password)
{
	if (Users.contains(phoneNumber)) throw exception("User already exists");

	for (const char& symbol : phoneNumber)
		if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'))
			throw exception("The number cannot contain letters!");

	CreateUser(phoneNumber, fio, password, deque<string>{ "credit", "debit" });

	return true;
}

void BaseUser::Replenishment(const string& category, const double& sum)
{
	auto [day, month, year] = Date.Today();

	string date, dayR, monthR;

	day <= 9 ? dayR.append("0" + to_string(day)) : dayR.append(to_string(day));

	month <= 9 ? monthR.append("0" + to_string(month)) : monthR.append(to_string(month));

	date.append(dayR + "." + monthR + "." + to_string(year));

	Card->Replenishment(PhoneNumber, date, category, sum, Users);
}

void BaseUser::Reset()
{
	Logged = false;
	PhoneNumber = "";
	FIO = "";
	Password = "";

	if (Users.contains("lastSession")) Users.erase("lastSession");
}

void BaseUser::ShowAllCards()
{
	Card->ShowAllCards(PhoneNumber, Users);
}

void BaseUser::TakeJsonObject(const json& object)
{
	Users = object;
}

void BaseUser::Week()
{
	IntervalBase->Week(PhoneNumber, Users);
}

VipUser::VipUser(::IntervalBase* intervalBase, ::TopExpenses* TopExpenses, ::TopCategory* TopCategory)
	: BaseUser(intervalBase, TopExpenses, TopCategory) {}

bool VipUser::Register(const string& phoneNumber, const string& fio, const string& password)
{
	if (Users.contains(phoneNumber)) throw exception("User already exists");

	for (const char& symbol : phoneNumber)
		if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'))
			throw exception("The number cannot contain letters!");

	CreateUser(phoneNumber, fio, password, deque<string>{ "credit", "debit", "vip" });

	return true;
}

GoldUser::GoldUser(::IntervalBase* intervalBase, ::TopExpenses* TopExpenses, ::TopCategory* TopCategory)
	: BaseUser(intervalBase, TopExpenses, TopCategory) {}

bool GoldUser::Register(const string& phoneNumber, const string& fio, const string& password)
{
	if (Users.contains(phoneNumber)) throw exception("User already exists");

	for (const char& symbol : phoneNumber)
		if ((symbol >= 'a' && symbol <= 'z') || (symbol >= 'A' && symbol <= 'Z'))
			throw exception("The number cannot contain letters!");

	CreateUser(phoneNumber, fio, password, deque<string>{ "credit", "debit", "vip", "gold" });

	return true;
}










