#pragma once
#include <fstream>

using std::ofstream;
using std::ifstream;
using std::exception;

class JsonSaver final : public ISaver<json>
{
	string Path;
	ofstream Fout;
public:
	explicit JsonSaver(const string& path) : Path(path) {}

	void Save(const json& object) override
	{
		Fout.open(Path);
		if (!Fout.is_open()) throw exception("File open error");
		Fout << object.dump(2);
		Fout.close();
	}
};

class JsonLoader final : public ILoader<json>
{
	string Path;
	ifstream Fin;
public:
	explicit JsonLoader(const string& path) : Path(path) {}

	json Load() override
	{
		Fin.open(Path);

		if (!Fin.is_open())
		{
			ofstream fout(Path);
			fout << "{}";
			fout.close();
		}

		string str, tmp;

		while (getline(Fin, tmp)) str.append(tmp);

		json result;

		if (!str.empty()) result = json::parse(str);

		Fin.close();

		return result;
	}

};