#include "stdafx.h"
#include "TvSet.h"

using namespace std;
void TurnOn(TvSet& tv);
void TurnOff(TvSet& tv);
void SelectChannel(TvSet& tv, int channel);
void Info(TvSet& tv);
void Help();

int main()
{
	bool exit = false;
	string instruction;
	TvSet tv;
	int channel;

	Help();

	while (!exit)
	{
		cin >> instruction;
		exit = instruction != "exit" ? false : true;
		if (!exit)
		{
			if (instruction == "TurnOn")
			{
				TurnOn(tv);
			}
			else if (instruction == "TurnOff")
			{
				TurnOff(tv);
			}
			else if (instruction == "SelectChannel")
			{
				cin >> channel;
				SelectChannel(tv, channel);
			}
			else if (instruction == "Info")
			{
				Info(tv);
			}
			else if (instruction == "Help")
			{
				Help();
			}
		}
	}
	return 0;
}

void TurnOn(TvSet& tv)
{
	if (!tv.IsTurnedOn())
	{
		tv.TurnOn();
	}
}
void TurnOff(TvSet& tv)
{
	if (tv.IsTurnedOn())
	{
		tv.TurnOff();
	}
}
void SelectChannel(TvSet& tv, int channel)
{
	tv.SelectChannel(channel);
}
void Info(TvSet& tv)
{
	if (tv.IsTurnedOn())
	{
		cout << "tv is on" << '\n';
		cout << "tv in a channel " << tv.GetChannel();
	}
	else
	{
		cout << "tv is off";
	}
	cout << '\n';
}
void Help()
{
	cout << "command \"TurnOn\" - It turn on a tv\n";
	cout << "command \"TurnOff\" - It turn off a tv\n";
	cout << "command \"SelectChannel\" <channel> - It selects channel on a tv\n";
	cout << "command \"Info\" - It gives information about a tv\n";
	cout << "command \"Help\" - Show commands\n";
	cout << "command \"exit\" - It turn off the programm\n";
}