#include "stdafx.h"
#include "../TvSet/TvSet.h"

using namespace std;

TEST_CASE("TvSet test")
{
	TvSet tv;
	CHECK(tv.IsTurnedOn() == false); // Телевизор выключен изначально
	SECTION("Проверка включения и выключения")
	{
		CHECK(tv.IsTurnedOn() == false);
		tv.TurnOn();
		CHECK(tv.IsTurnedOn() == true);
		tv.TurnOff();
		CHECK(tv.IsTurnedOn() == false);
	}

	TvSet tvOn;
	tvOn.TurnOn();
	TvSet tvOff;
	tvOff.TurnOff();

	CHECK(tvOff.GetChannel() == 0); // Проверка канала когда он выключен
	CHECK(tvOn.GetChannel() == 1); // Проверка канала когда он включен

	SECTION("Проверка невозможности переключения канала в выключенном состоянии")
	{
		tvOff.SelectChannel(2);
		CHECK(tvOff.GetChannel() == 0);
	}

	SECTION("Проверка возможности переключения каналов")
	{
		CHECK(tvOn.SelectChannel(1) == true);
		CHECK(tvOn.GetChannel() == 1);

		CHECK(tvOn.SelectChannel(99) == true);
		CHECK(tvOn.GetChannel() == 99);

		CHECK(tvOn.SelectChannel(64) == true);
		CHECK(tvOn.GetChannel() == 64);

		CHECK(tvOn.SelectChannel(0) == false);
		CHECK(tvOn.GetChannel() == 64);

		CHECK(tvOn.SelectChannel(100) == false);
		CHECK(tvOn.GetChannel() == 64);
	}

	SECTION("Проверка канала при изменении в включенном и выключенном состоянии")
	{
		tv.TurnOn();
		tv.SelectChannel(5);
		tv.TurnOff();
		CHECK(tv.GetChannel() == 0);
		tv.TurnOn();
		CHECK(tv.GetChannel() == 5);
	}
}