#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <nlohmann/json.hpp>
#include <string>
#include <memory>
#include "reports.h"
#include "Saver.h"
#include "cards.h"
#include "Date.h"
#include "User.h"

using namespace std;
using namespace nlohmann;

constexpr auto PATH = "users.json";

HANDLE hConsole;

enum Colors
{
	white = 15,
	red = 4,
	yellow = 14
};

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "");
	srand((unsigned)time(nullptr));

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, white);

	auto loader = shared_ptr<ILoader<json>>(new JsonLoader(PATH));
	auto saver = shared_ptr<ISaver<json>>(new JsonSaver(PATH));

	IUser* user = new BaseUser(new IntervalBase(), new TopExpenses(), new TopCategory());
	user->TakeJsonObject(loader->Load());
	char choose;


	user->LastSessionLoad();
	user->ChangeCard(new Card);

	IPurse* tmp = new Card;


	do
	{
		system("cls");

		if (!user->GetLoggedField())
		{
			cout << "1 - Логин\n2 - Регистрация\nВвод: ";
			choose = (char)_getch();
			cout << choose << "\n\n";
			try
			{
				switch (choose)
				{
				case '1':
				{
					cout << "Номер телефона: "; string number = ConvertToAscii(Getline());
					cout << "\n\nПароль: "; string password = ConvertToAscii(Getline());
					if (user->Login(number, password)) cout << "Успешно!" << endl;

					cout << "\nОставаться в системе? (да,нет): ";
					if (string choice = Getline(); choice == "да") user->LastSessionSave();
				}
				system("cls");
				break;
				case '2':
				{
					system("cls");
					cout << "1 - Обычный пользователь\n2 - Vip\n3 - Gold\nInput: ";
					choose = (char)_getch();
					cout << choose << "\n\n";

					switch (choose)
					{
					case '1':
						user = new BaseUser(new IntervalBase(), new TopExpenses(), new TopCategory());
						break;
					case '2':
						user = new VipUser(new IntervalBase(), new TopExpenses(), new TopCategory());
						break;
					case '3':
						user = new GoldUser(new IntervalBase(), new TopExpenses(), new TopCategory());
						break;
					default: {}
					}


					cout << "Номер телефона: "; string number = ConvertToAscii(Getline());
					cout << "\n\nФИО: "; string fio = ConvertToAscii(Getline());
					cout << "\n\nПароль: "; string password = ConvertToAscii(Getline());
					try
					{
						user->ChangeCard(new Card);
						if (user->Register(number, fio, password)) cout << "Успешно!" << endl;
					}
					catch (const exception& err)
					{
						cerr << err.what() << endl;
					}
					system("pause");
				}
				break;
				default: {}
				}
			}
			catch (const exception& err)
			{
				cerr << err.what() << endl;
				system("pause");
			}
		}

		saver->Save(user->GetJsonObject());

		if (user->GetLoggedField())
		{
			system("cls");
			//Например метод GetCardInfo возвращает false, если карты не существует, но это было сделано до того,
			//как я добавил проверку пин-кода. Про него я совсем забыл. Поэтому теперь код с 479 по 489 не имеет смысла.
			auto [bill, cardNumber, check] = user->GetCardInfo();
			cout << "ФИО: " << user->GetFIO() << "\nТекущая карта: ";

			SetConsoleTextAttribute(hConsole, yellow);
			cout << user->GetCardType();
			SetConsoleTextAttribute(hConsole, white);
			cout << "\nНомер: ";
			if (!check) SetConsoleTextAttribute(hConsole, red);
			cout << cardNumber;
			SetConsoleTextAttribute(hConsole, white);
			cout << "\nБаланс: " << bill << "\n\n";

			if (!check)
			{
				try
				{
					user->Create();
					saver->Save(user->GetJsonObject());
					continue;
				}
				catch (const exception& err)
				{
					cerr << err.what() << endl;
				}
			}

			cout << "\n0 - Выйти\n1 - Сменить карту\n2 - Управление картой\nВвод: ";
			choose = (char)_getch();
			cout << choose << "\n\n";

			switch (choose)
			{
			case '0':
				user->Reset();
				break;
			case '1':
			{
				system("cls");
				cout << "1 - Кредитка\n2 - Дебитовая\n3 - Vip\n4 - Gold\nВвод: ";
				choose = (char)_getch();
				cout << choose << "\n\n";

				switch (choose)
				{
				case '1':
					tmp = new Card;
					break;
				case '2':
					tmp = new Debit;
					break;
				case '3':
					tmp = new Vip;
					break;
				case '4':
					tmp = new Gold;
					break;
				default: {}
				}

				if (user->CheckAvailability(tmp->GetType()))
				{
					user->ChangeCard(tmp);
					if (!user->CheckCardExistence())
					{
						SetConsoleTextAttribute(hConsole, red);
						cout << "Кредитной карты не существует!" << endl;
						SetConsoleTextAttribute(hConsole, white);
						cout << "Давайте создадим кредитную карту..." << "\n\n";
						try
						{
							user->Create();
						}
						catch (const exception& err)
						{
							cerr << err.what() << endl;
						}
					}
					else
					{
						cout << "Введите пин-код: ";
						if (string code = Getline(); code == user->GetCardCode())
							cout << "Успешно!" << endl;
						else
						{
							cout << "Неверный пин-код!" << endl;
							user->ChangeCard(new Card);
						}
					}
				}
				else cout << "Карта не доступна!" << endl;
				system("pause");

			}
			break;
			case '2':
			{
				try
				{
					while (choose != '0')
					{
						system("cls");
						cout << "0 - Назад\n1 - Пополнение\n2 - Запись расходов\n3 - Вывести все расходы\n4 - Топ 3 затрат\n5 - Топ 3 категорий\nВвод: ";
						choose = (char)_getch();
						cout << choose << "\n\n";

						switch (choose)
						{
						case '1':
						{
							cout << "Введите сумму: "; double sum; cin >> sum;
							user->SubmitExpense(sum);
							system("pause");
						}
						break;
						case '2':
						{
							cout << "Введите категорию: "; string category = Getline();
							ToLower(category);
							category = ConvertToAscii(category);
							cout << "\nВведите сумму: "; double sum; cin >> sum;
							user->Replenishment(category, sum);
						}
						break;
						case '3':
						{
							try
							{
								system("cls");
								cout << "1 - День\n2 - Неделя\n3 - Месяц\nВвод: ";
								choose = (char)_getch();
								cout << choose << "\n\n";

								switch (choose)
								{
								case '1':
									user->Day();
									break;
								case '2':
									user->Week();
									break;
								case '3':
									user->Month();
									break;
								default: {}
								}

							}
							catch (const exception& err)
							{
								cerr << err.what() << endl;
							}
							system("pause");
						}
						break;
						case '4':
						{
							try
							{
								system("cls");
								cout << "1 - День\n2 - Неделя\n3 - Месяц\nInput: ";
								choose = (char)_getch();
								cout << choose << "\n\n";

								switch (choose)
								{
								case '1':
									user->ExpenseDay();
									break;
								case '2':
									user->ExpenseWeek();
									break;
								case '3':
									user->ExpenseMonth();
									break;
								default: {}
								}

							}
							catch (const exception& err)
							{
								cerr << err.what() << endl;
							}
							system("pause");
						}
						break;
						case '5':
						{
							try
							{
								system("cls");
								cout << "1 - День\n2 - Неделя\n3 - Месяц\nInput: ";
								choose = (char)_getch();
								cout << choose << "\n\n";

								switch (choose)
								{
								case '1':
									user->CategoryDay();
									break;
								case '2':
									user->CategoryWeek();
									break;
								case '3':
									user->CategoryMonth();
									break;
								default: {}
								}

							}
							catch (const exception& err)
							{
								cerr << err.what() << endl;
							}
							system("pause");
						}
						break;
						default: {}
						}

						saver->Save(user->GetJsonObject());
					}
				}
				catch (const exception& err)
				{
					cerr << err.what() << endl;
					system("pause");
				}
			}
			break;
			default: {}
			}
		}

		cout << "\n\n\n";
		saver->Save(user->GetJsonObject());
	} while (true);
}

json BaseUser::Users = {};