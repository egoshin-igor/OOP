#include "stdafx.h"
#include "CBodyController.h"

using namespace std;

int main()
{
	CBodyController bodyController(cin, cout);
	while (!cin.eof() && !cin.fail())
	{
		bodyController.HandleCommand();
	}
    return 0;
}

