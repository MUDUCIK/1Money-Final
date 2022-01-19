#include "cards.h"

//throw exception
void CardBase::Check(const string& number, const json& object)
{
	if (!object.contains(number)) throw exception("Пользователь не найден!");
	if(!object[number].contains("cards")) throw exception("Пользователь не имеет карт!");
	if(!object[number]["cards"].contains(Type)) throw exception("Кредитная карта не найдена!");
}

string CardBase::GetType() const
{
	return Type;
}

string CardBase::GetCode(const string& number, const json& object) const
{
	string code;
	if (object[number].contains("cards"))
		if (object[number]["cards"].contains(Type))
			code = object[number]["cards"][Type]["code"];
	return code;
}

tuple<int, string, bool> CardBase::GetInfo(const string& number, const json& object)
{
	long double bill = 0;
	string cardNumber = "Кредитная карта не найдена!";

	if (object[number].contains("cards"))
		if (object[number]["cards"].contains(Type))
		{
			bill = (double)object[number]["cards"][Type]["bill"];
			cardNumber = object[number]["cards"][Type]["number"];
			return tuple(bill, cardNumber, true);
		}
	return tuple(bill, cardNumber, false);
}

//throw exception
void CardBase::SubmitExpense(const string& number, const double& bill, json& object)
{
	Check(number, object);
	double temp = 0;

	temp = object[number]["cards"][Type]["bill"];
	temp += bill;
	object[number]["cards"][Type]["bill"] = temp;
}

//throw exception
void CardBase::Replenishment(const string& number, const string& date, const string& category, const double& sum, json& object)
{
	Check(number, object);
	if (sum <= 0) throw exception("Сумма не может быть меньше или равной нулю!");

	if (double bill = object[number]["cards"][Type]["bill"];
		bill + 1 <= (Limit * -1))
		throw exception("Достигнут кредитный лимит!");
	
	if (double bill = object[number]["cards"][Type]["bill"];
		bill + 1 + (sum * -1) <= (Limit * -1))
		throw exception("Сумма расхода превышает кредитный лимит!");

	object[number]["cards"][Type]["expenses"][category].push_back({
		{ "sum", sum },
		{ "date", date }
	});

	double tmp = object[number]["cards"][Type]["bill"];
	tmp -= sum;
	object[number]["cards"][Type]["bill"] = tmp;
}

//throw exception
void CardBase::Create(const string& userNumber,json& object)
{
	if (object[userNumber]["cards"].contains(Type)) throw exception("Карта уже существует!");
	cout << "Введите пин-код: ";

	string code = Getline();

	if (bool check = PinCodeChecker(code); check)
		object[userNumber]["cards"][Type] = {
			{"bill",0},
			{"code", code},
			{"expenses",json::object()},
			{"number", CardNumberGenerator()}
		};
}

//throw exception
void CardBase::ClearCategory(const string& userNumber, const string& card, const string& category, json& object)
{
	if (auto& tmp = object[userNumber]["cards"][card]["expenses"];
		tmp.contains(category)) tmp[category] = { json::object() };
	else throw exception("Категория не найдена!");
}

//throw exception
void CardBase::DeleteCategory(const string& userNumber, const string& card, const string& category, json& object)
{
	if (auto& tmp = object[userNumber]["cards"][card]["expenses"];
		tmp.contains(category)) tmp.erase(category);
	else throw exception("Категория не найдена!");
}

void CardBase::ShowAllCards(const string& number, const json& object)
{
	string SPACES = "    ";
	if (object[number].contains("cards"))
	{
		for (const auto& [name, value] : object[number]["cards"].items())
		{
			cout << "Card: " << name;
			int cash = value["bill"];
			string	cardNumber = value["number"];
			cout << "\n" << SPACES << "Cash: " << cash
				<< "\n" << SPACES << "Number: " << cardNumber;
			if (const auto expenses = value["expenses"]; !expenses.empty())
			{
				cout << "\n\tExpenses:";
				for (const auto& [category, expense] : expenses.items())
				{
					cout << "\n\t" << SPACES << "Category: " << category
						<< "\n\t" << SPACES << SPACES << "Values:";
					for (const auto& [i, iValue] : expense.items())
					{
						string date = iValue["date"];
						int bill = iValue["sum"];
						cout << "\n\t\t" << SPACES << "Date: " << date
							<< "\n\t\t" << SPACES << "Sum: " << bill
							<< endl;
					}
				}
			}
			cout << endl;
		}
	}
	else throw exception("The user has no cards!");
}

//Конструкторы

Card::Card()
{
	this->Type = "credit";
	this->Limit = 5000;
}

Debit::Debit()
{
	this->Type = "debit";
	this->Limit = 2000;
}

Vip::Vip()
{
	this->Type = "vip";
	this->Limit = 10000;
}

Gold::Gold()
{
	this->Type = "gold";
	this->Limit = 20000;
}