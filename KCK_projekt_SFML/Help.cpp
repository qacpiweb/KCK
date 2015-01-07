#include "stdafx.h"
#include "Help.h"
#include "BorderMan.h"
#include "Pirate.h"

Ship* Help::statek;
float * Help::dt;
map<string, Planet*> Help::planety;
string Help::komenda;
string Help::argument;
bool Help::flaga = false;

Help::Help()
{
}


Help::~Help()
{
}


std::wstring Help::s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

std::string Help::ws2s(const std::wstring& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);
	std::string r(buf);
	delete[] buf;
	return r;
}

int Help::ssearch(string a, string b) //(gdzie, szukany)
{
	unsigned int present;
	for (auto i = 0; i < a.length(); i++)
	{
		for (auto j = i; j < a.length(); j++)
		{
			present = 0;
			for (auto k = 0; k < b.length() && (j + k)<a.length(); k++)
			{
				if (a[j + k] == b[k])
				{
					present++;
				}
				if (present == b.length())
				{
					return j;
				}
			}
		}
	}
	return 1000;
}

std::wstring Help::textAnalysis(std::wstring text)
{
	//slownik

	vector<string> bezargumentowe = { "wita", "czesc", "siem", "hej", "doberek", "plac" };
	vector<string> przeklenstwa = { "kurw", "jeb", "pierd", "chuj" };
	vector<string> operatory = { "lec", "kup"};
	vector<string> latanie = { "prawo", "lewo", "gora", "dol", "Merkury" };
	vector<string> przekupowanie = { "celn", "gran", "pira" };
	vector<vector<string>*> wskazniki = { &latanie, &przekupowanie };

	//tokenizacja

	string sentence = ws2s(text);
	istringstream iss(sentence);
	vector<string> tokens;
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(tokens));

	//analiza

	//ugrzeczniacz
	int j = 0;
	int k = 0;
	while (j < tokens.size())
	{
		k = 0;
		while (k <przeklenstwa.size() && ssearch(tokens.at(j), przeklenstwa.at(k)) == 1000)
		{
			k++;
		}
		if (k == przeklenstwa.size()) //nie bylo operatora, nastepne slowo
		{
			j++;
		}
		else
		{
			return L"Nie! Grzeczniej prosze!";
		}
	}


	//wyszukiwanie bezargumentowych
	j = 0;
	k = 0;
	while (j < tokens.size())
	{
		k = 0;
		while (k < bezargumentowe.size() && ssearch(tokens.at(j), bezargumentowe.at(k)) == 1000)
		{
			k++;
		}
		if (k == bezargumentowe.size()) //nie bylo operatora, nastepne slowo
		{
			j++;
		}
		if (ssearch(tokens.at(j), "plac") != 1000)
		{
			komenda == "plac";
			flaga = true;
			return L"Placimy, Kapitanie!";
		}
		else
		{
			return s2ws(tokens.at(j)) + L" Kapitanie!";
		}
	}
	j = 0;
	k = 0;
	//wyszukiwanie operatorow
	while (j < tokens.size())
	{
		k = 0;
		while (k<operatory.size() && ssearch(tokens.at(j), operatory.at(k)) == 1000)
		{
			k++;
		}
		if (k == operatory.size()) //nie bylo operatora, nastepne slowo
		{
			j++;
		}
		else //byl operator, szukamy argumentu
		{
			for (auto i = j; i < tokens.size(); i++)//slowa po operatorze
			{
				for (auto l = 0; l < (*wskazniki.at(k)).size(); l++)
				{
					if (ssearch(tokens.at(i), (*wskazniki.at(k)).at(l)) != 1000)
					{
						//wywolanie funkcji operator z argumentem 
						komenda = tokens.at(j);
						argument = tokens.at(i);
						flaga = true;
						return L"Wykonuje komende \"" + s2ws(tokens.at(j)) + L" " + s2ws(tokens.at(i)) + L"\"";
					}
				}

			}
			return L"Komenda \"" + s2ws(tokens.at(j)) + L"\" wymaga argumentu!";
			j++;
		}
	}
	return L"Komenda nieznana";
}

/*void Help::wykonaj_komende()
{
	if (komenda == "lec")
	{
		if (argument == "lewo" || argument == "prawo" || argument == "gora" || argument == "dol" )
		{
			statek->fly(*dt, s2ws(argument));
		}
		else
		{
			//map<string, Planet*> temp = *planety;
			string name = "Merkury";
			statek->flyTo(*	dt, *planety[name]);
		}
	}
	if (komenda == "plac")
	{
		if (Pirate::busy)
		{
			Pirate::positiveAnswer(*statek);
		}
	}
	

	flaga = false;
}*/

void Help::podaj_statek(Ship * st, float * time, map<string, Planet*> planets)
{
	statek = st;
	dt = time;
	planety = planets;
}
