﻿#include "stdafx.h"
#include "Help.h"
#include "BorderMan.h"
#include "Pirate.h"

Ship* Help::statek;
float * Help::dt;
map<wstring, Planet*> Help::planety;
wstring Help::komenda;
wstring Help::argument;
bool Help::flaga = false;

Help::Help()
{
}


Help::~Help()
{
}

std::vector<std::wstring> Help::tokenize(const std::wstring& source)
{
	std::vector<std::wstring> tokens;
	std::wstring temp;

	for (const auto& letter : source)
	{
		if (letter != L' ')
			temp.push_back(letter);

		if (letter == L' ' || letter == source.back())
		{
			tokens.push_back(temp);
			temp.clear();
		}
	}

	return tokens;
}



int Help::ssearch(wstring a, wstring b) //(gdzie, szukany)
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

	vector<wstring> bezargumentowe = { L"wita", L"cześć", L"siem", L"hej", L"doberek", L"płać" , L"sprzedaj"};
	vector<wstring> przeklenstwa = { L"kurw", L"jeb", L"pierd", L"chuj", L"dziwk"};
	vector<wstring> operatory = { L"leć", L"sprzedaj"};
	vector<wstring> latanie = { L"prawo", L"lewo", L"góra", L"dół", L"Merkury" , L"Uran", L"Jowisz", L"Neptun", L"Matk", L"matk"};
	vector<vector<wstring>*> wskazniki = { &latanie };

	
	vector<wstring> tokens = tokenize(text);

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
		else if (ssearch(tokens.at(j), L"płać") != 1000)
		{
			komenda = L"płać";
			flaga = true;
			statek->isStuck = false;
			//statek->setMoney(statek->getMoney() - 220);
			
			return L"Płacimy, Kapitanie!";
		}
		else if (ssearch(tokens.at(j), L"sprzedaj") != 1000)
		{
			komenda = L"sprzedaj";
			flaga = true;
			return L"Sprzedajemy!";
		}
		else
		{
			return tokens.at(j) + L" Kapitanie!";
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
						komenda = operatory.at(k);//tokens.at(j);
						argument = (*wskazniki.at(k)).at(l);//tokens.at(i);
						flaga = true;

						//////
						statek->isStuckv2 = false;
						//////
						return L"Wykonuję komendę \"" + tokens.at(j) + L" " + tokens.at(i) + L"\"";
					}
				}

			}
		
			return L"Komenda \"" + tokens.at(j) + L"\" wymaga argumentu!";
			j++;
		}
	}
	return L"Komenda nieznana";
}

void Help::podaj_statek(Ship * st, float * time, map<wstring, Planet*> planets)
{
	statek = st;
	dt = time;
	planety = planets;
}
