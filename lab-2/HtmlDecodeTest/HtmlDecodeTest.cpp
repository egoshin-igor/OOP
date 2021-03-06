#include "stdafx.h"
#include <string>
#include <iostream>
#include "../HtmlDecode/HtmlDecode.h"

using namespace std;

/*
" (двойная кавычка) заменяется на &quot;
· ' (апостроф) заменяется на &apos;
· < (знак меньше) заменяется на &lt;
· > (знак больше) заменяется на &gt;
· & (амперсанд) заменяется на &amp;
*/


TEST_CASE("HtmlDecode test")
{
	CHECK(HtmlDecode("") == "");
	CHECK(HtmlDecode("a") == "a");
	CHECK(HtmlDecode("&quot;") == "\"");
	CHECK(HtmlDecode("&apos;") == "\'");
	CHECK(HtmlDecode("&lt;") == "<");
	CHECK(HtmlDecode("&gt;") == ">");
	CHECK(HtmlDecode("&amp;") == "&");
	CHECK(HtmlDecode("&quot;aasdasda das daswqd qwd qwdqwq wdqw&quot;") == "\"aasdasda das daswqd qwd qwdqwq wdqw\"");
	CHECK(HtmlDecode("Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s") == "Cat <says> \"Meow\". M&M's");
}