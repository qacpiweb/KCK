#pragma once

#include "stdafx.h"
#include "Ship.h"
#include "Planet.h"


class Help
{
public:
	Help();
	~Help();
	static std::wstring Help::s2ws(const std::string& s);
	static std::string Help::ws2s(const std::wstring& s);
	static int ssearch(string a, string b);
	static std::wstring textAnalysis(std::wstring text);
	//static void wykonaj_komende();
	static void podaj_statek(Ship * st, float * time, map<string, Planet*> planets);
	static bool flaga;

	static Ship * statek;
	static float *  dt;
	static map<string, Planet*> planety;
	static string komenda;
	static string argument;
};

