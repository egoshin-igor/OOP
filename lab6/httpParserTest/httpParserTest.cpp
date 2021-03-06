#include "stdafx.h"
#include "../httpParser/CHttpUrl.h"
#include "../httpParser/CUrlParsingError.h"

using namespace std;

TEST_CASE("Testing constructors with methods")
{
	cout << "Testing constructors with methods\n";
	cout << "--string url\n";
	{
		try
		{
			CHttpUrl url("https://vk.com/doc95031707_464641007?hash=eaf6dd47f4c2d30305&dl=ac7585bb29dbf904d7");
			REQUIRE(url.GetURL() == "https://vk.com/doc95031707_464641007?hash=eaf6dd47f4c2d30305&dl=ac7585bb29dbf904d7");
			REQUIRE(url.GetProtocolString() == "https");
			REQUIRE(url.GetDomain() == "vk.com");
			REQUIRE(url.GetDocument() == "/doc95031707_464641007?hash=eaf6dd47f4c2d30305&dl=ac7585bb29dbf904d7");
			REQUIRE(url.GetPort() == 443);
		}
		catch (CUrlParsingError e)
		{
			REQUIRE("Not worked" == e.What());
		}
	}

	cout << "--url without port\n";
	{
		try
		{
			CHttpUrl url("vk.com", "/doc95031707_464641007?hash=eaf6dd47f4c2d30305&dl=ac7585bb29dbf904d7", HTTPS);
			REQUIRE(url.GetURL() == "https://vk.com/doc95031707_464641007?hash=eaf6dd47f4c2d30305&dl=ac7585bb29dbf904d7");
			REQUIRE(url.GetProtocolString() == "https");
			REQUIRE(url.GetDomain() == "vk.com");
			REQUIRE(url.GetDocument() == "/doc95031707_464641007?hash=eaf6dd47f4c2d30305&dl=ac7585bb29dbf904d7");
			REQUIRE(url.GetPort() == 443);
		}
		catch (CUrlParsingError e)
		{
			REQUIRE("It will not work" == e.What());
		}
	}

	cout << "--url with port\n";
	{
		try
		{
			CHttpUrl url("vk.com", "/doc95031707_464641007?hash=eaf6dd47f4c2d30305&dl=ac7585bb29dbf904d7", HTTPS, 555);
			REQUIRE(url.GetURL() == "https://vk.com:555/doc95031707_464641007?hash=eaf6dd47f4c2d30305&dl=ac7585bb29dbf904d7");
			REQUIRE(url.GetProtocolString() == "https");
			REQUIRE(url.GetDomain() == "vk.com");
			REQUIRE(url.GetDocument() == "/doc95031707_464641007?hash=eaf6dd47f4c2d30305&dl=ac7585bb29dbf904d7");
			REQUIRE(url.GetPort() == 555);
		}
		catch (CUrlParsingError e)
		{
			REQUIRE("It will not work" == e.What());
		}
	}

	cout << "--incorrect urls\n";
	{
		try
		{
			CHttpUrl url("abc:https://vk.com/doc95031707_464641007?hash=eaf6dd47f4c2d30305&dl=ac7585bb29dbf904d7");
		}
		catch (CUrlParsingError e)
		{
			REQUIRE(string("You have printed incorrect url") == e.What());
		}

		try
		{
			CHttpUrl url("hhttps://vk.com/doc95031707_464641007?hash=eaf6dd47f4c2d30305&dl=ac7585bb29dbf904d7");
		}
		catch (CUrlParsingError e)
		{
			REQUIRE(string("You have printed incorrect url") == e.What());
		}

		try
		{
			CHttpUrl url("https://vk.#com/doc95031707_464641007?hash=eaf6dd47f4c2d30305&dl=ac7585bb29dbf904d7");
		}
		catch (CUrlParsingError e)
		{
			REQUIRE(string("You have printed incorrect url") == e.What());
		}

		try
		{
			CHttpUrl url("vk.#com", "/doc95031707_464641007?hash=eaf6dd47f4c2d30305&dl=ac7585bb29dbf904d7", HTTPS, 555);
		}
		catch (CUrlParsingError e)
		{
			REQUIRE(string("Incorrect domain") == e.What());
		}

		try
		{
			CHttpUrl url("vk.com", "/doc95031707_464641007?hash=eaf6dd47f4c2d30305&dl=ac7585bb29dbf904d7", HTTPS, -1);
		}
		catch (CUrlParsingError e)
		{
			REQUIRE(string("Incorrect port") == e.What());
		}
	}
}