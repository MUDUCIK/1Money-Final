#include "reports.h"
#include "cards.h"

constexpr auto SPACES = "    ";

void IntervalBase::Day(const string& number, const json& object)
{
	Check(number, object);
	json temp;

	for (const auto& [cardName, cardValue] : object[number]["cards"].items())
		for (const auto& [category, expense] : cardValue["expenses"].items())
			for (const auto& [index, indexValue] : expense.items())
			{
				Date Date;
				string date = indexValue["date"],
					name = cardName;
				double sum = indexValue["sum"];
				auto [expenseDay, expenseMonth, expenseYear] = DateParser(date);
				auto [day, month, year] = Date.Today();

				auto expenseJDN = JDN(expenseDay, expenseMonth, expenseYear);
				if (auto nowJDN = JDN(day, month, year);
					expenseJDN == nowJDN)
					temp[category].push_back({
						{"date", date},
						{"sum",sum}
						});
			}
	Sort(temp);

	Show(temp);
}

void IntervalBase::Week(const string& number, const json& object)
{
	Check(number, object);
	json temp;

	for (const auto& [cardName, cardValue] : object[number]["cards"].items())
		for (const auto& [category, expense] : cardValue["expenses"].items())
			for (const auto& [index, indexValue] : expense.items())
			{
				Date Date;
				string date = indexValue["date"],
					name = cardName;
				double sum = indexValue["sum"];
				auto [expenseDay, expenseMonth, expenseYear] = DateParser(date);
				auto [day, month, year] = Date.Today();

				auto expenseJDN = JDN(expenseDay, expenseMonth, expenseYear);
				if (auto nowJDN = JDN(day, month, year);
					expenseJDN <= nowJDN && expenseJDN >= nowJDN - 7)
					temp[category].push_back({
						{"date", date},
						{"sum",sum}
						});
			}
	Sort(temp);
	Show(temp);
}

void IntervalBase::Month(const string& number, const json& object)
{
	Check(number, object);
	json temp;

	for (const auto& [cardName, cardValue] : object[number]["cards"].items())
		for (const auto& [category, expense] : cardValue["expenses"].items())
			for (const auto& [index, indexValue] : expense.items())
			{
				Date Date;
				string date = indexValue["date"],
					name = cardName;
				double sum = indexValue["sum"];
				auto [expenseDay, expenseMonth, expenseYear] = DateParser(date);
				auto [day, month, year] = Date.Today();

				auto expenseJDN = JDN(expenseDay, expenseMonth, expenseYear);
				if (auto nowJDN = JDN(day, month, year);
					expenseJDN <= nowJDN && expenseJDN >= nowJDN - 30)
					temp[category].push_back({
						{"date", date},
						{"sum",sum}
						});
			}
	Sort(temp);
	Show(temp);
}

void IntervalBase::Check(const string& number, const json& object)
{
	if (!object.contains(number)) throw exception("User not found!");
	if (!object[number].contains("cards")) throw exception("The user has no cards!");
}

void TopExpenses::Day(const string& number, const json& object)
{
	Check(number, object);
	json temp;

	for (const auto& [cardName, cardValue] : object[number]["cards"].items())
		for (const auto& [category, expense] : cardValue["expenses"].items())
			for (const auto& [index, indexValue] : expense.items())
			{
				Date Date;
				string date = indexValue["date"],
					name = cardName;
				double sum = indexValue["sum"];
				auto [expenseDay, expenseMonth, expenseYear] = DateParser(date);
				auto [day, month, year] = Date.Today();

				auto expenseJDN = JDN(expenseDay, expenseMonth, expenseYear);
				if (auto nowJDN = JDN(day, month, year);
					expenseJDN == nowJDN)
					temp[category].push_back({
						{"date", date},
						{"sum",sum}
						});
			}

	Sort(temp);

	Show(temp);
}

void TopExpenses::Week(const string& number, const json& object)
{
	Check(number, object);
	json temp;

	for (const auto& [cardName, cardValue] : object[number]["cards"].items())
		for (const auto& [category, expense] : cardValue["expenses"].items())
			for (const auto& [index, indexValue] : expense.items())
			{
				Date Date;
				string date = indexValue["date"],
					name = cardName;
				double sum = indexValue["sum"];
				auto [expenseDay, expenseMonth, expenseYear] = DateParser(date);
				auto [day, month, year] = Date.Today();

				auto expenseJDN = JDN(expenseDay, expenseMonth, expenseYear);
				if (auto nowJDN = JDN(day, month, year);
					expenseJDN <= nowJDN && expenseJDN >= nowJDN - 7)
					temp[category].push_back({
						{"date", date},
						{"sum",sum}
						});
			}

	Sort(temp);

	Show(temp);
}

void TopExpenses::Month(const string& number, const json& object)
{
	Check(number, object);
	json temp;

	for (const auto& [cardName, cardValue] : object[number]["cards"].items())
		for (const auto& [category, expense] : cardValue["expenses"].items())
			for (const auto& [index, indexValue] : expense.items())
			{
				Date Date;
				string date = indexValue["date"],
					name = cardName;
				double sum = indexValue["sum"];
				auto [expenseDay, expenseMonth, expenseYear] = DateParser(date);
				auto [day, month, year] = Date.Today();

				auto expenseJDN = JDN(expenseDay, expenseMonth, expenseYear);
				if (auto nowJDN = JDN(day, month, year);
					expenseJDN <= nowJDN && expenseJDN >= nowJDN - 30)
					temp[category].push_back({
						{"date", date},
						{"sum",sum}
						});
			}
	Sort(temp);

	Show(temp);
}

void TopCategory::Day(const string& number, const json& object)
{
	Check(number, object);
	json temp;

	for (const auto& [cardName, cardValue] : object[number]["cards"].items())
		for (const auto& [category, expense] : cardValue["expenses"].items())
			for (const auto& [index, indexValue] : expense.items())
			{
				Date Date;
				string date = indexValue["date"],
					name = cardName;
				double sum = indexValue["sum"];
				auto [expenseDay, expenseMonth, expenseYear] = DateParser(date);
				auto [day, month, year] = Date.Today();

				auto expenseJDN = JDN(expenseDay, expenseMonth, expenseYear);
				if (auto nowJDN = JDN(day, month, year);
					expenseJDN == nowJDN)
					temp[category].push_back({
						{"date", date},
						{"sum",sum}
						});
			}

	ordered_json result = SortWithoutOrder(temp);

	ShowWithoutOrder(result);
}

void TopCategory::Week(const string& number, const json& object)
{
	Check(number, object);
	json temp;

	for (const auto& [cardName, cardValue] : object[number]["cards"].items())
		for (const auto& [category, expense] : cardValue["expenses"].items())
			for (const auto& [index, indexValue] : expense.items())
			{
				Date Date;
				string date = indexValue["date"],
					name = cardName;
				double sum = indexValue["sum"];
				auto [expenseDay, expenseMonth, expenseYear] = DateParser(date);
				auto [day, month, year] = Date.Today();

				auto expenseJDN = JDN(expenseDay, expenseMonth, expenseYear);
				if (auto nowJDN = JDN(day, month, year);
					expenseJDN <= nowJDN && expenseJDN >= nowJDN - 7)
					temp[category].push_back({
						{"date", date},
						{"sum",sum}
						});
			}

	ordered_json result = SortWithoutOrder(temp);

	ShowWithoutOrder(result);
}

void TopCategory::Month(const string& number, const json& object)
{
	Check(number, object);
	json temp;

	for (const auto& [cardName, cardValue] : object[number]["cards"].items())
		for (const auto& [category, expense] : cardValue["expenses"].items())
			for (const auto& [index, indexValue] : expense.items())
			{
				Date Date;
				string date = indexValue["date"],
					name = cardName;
				double sum = indexValue["sum"];
				auto [expenseDay, expenseMonth, expenseYear] = DateParser(date);
				auto [day, month, year] = Date.Today();

				auto expenseJDN = JDN(expenseDay, expenseMonth, expenseYear);
				if (auto nowJDN = JDN(day, month, year);
					expenseJDN <= nowJDN && expenseJDN >= nowJDN - 30)
					temp[category].push_back({
						{"date", date},
						{"sum",sum}
						});
			}

	ordered_json result = SortWithoutOrder(temp);

	ShowWithoutOrder(result);
}

void IntervalBase::Show(const json& object)
{
	for (const auto& [category, array] : object.items())
	{
		cout << "Категория: " << ConvertFromAscii(category) << endl;
		for (const auto& [i, value] : array.items())
			cout << SPACES << "Дата: " << string(value["date"]) << endl
			<< SPACES << "Сумма: " << value["sum"] << "\n\n";
	}
}

void IntervalBase::Sort(json& object)
{
	for (const auto& [category, value] : object.items())
	{
		sort(value.begin(), value.end(), [](const json& first, const json& second)
			{
				return first["sum"] > second["sum"];
			});
	}
}

void TopExpenses::Show(const json& object)
{
	for (const auto& [category, array] : object.items())
	{
		cout << "Категория: " << ConvertFromAscii(category) << endl;
		for (int i = 0; i < array.size(); ++i)
		{
			if (i == 3) break;
			cout << SPACES << "Дата: " << string(array[i]["date"]) << endl
				<< SPACES << "Сумма: " << array[i]["sum"] << "\n\n";
		}
	}
}

//Changes the passed object 
ordered_json TopCategory::SortWithoutOrder(json& object)
{
	deque<pair<string, double>> temp;
	bool check = false;
	for(const auto& [category,array]: object.items())
		for(const auto& [i,value] : array.items())
		{
			double sum = value["sum"];
			for (auto& [tempKey, tempValue] : temp)
				if (tempKey == category)
				{
					tempValue += sum;
					check = true;
				}
				else check = false;
			if (!check) temp.emplace_back(category, sum);
		}

	std::ranges::sort(temp, [](const pair<string, double>& first, const pair<string, double>& second)
	{
		return first.second > second.second;
	});

	ordered_json result;

	for (const auto& [key, value] : temp)
		result[key] = value;

	return result;
}

void TopCategory::ShowWithoutOrder(const ordered_json& object)
{
	int i = 0;
	auto it = object.begin();
	while (i<3)
	{
		if (it == object.end()) break;
		cout << "Категория: " << ConvertFromAscii(it.key())
			<< "\nСумма: " << it.value()
			<< "\n\n";
		++it;
		++i;
	}
}

