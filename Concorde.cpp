#include "Concorde.h"


int main()
{
	Sistema sys;

	string currentComand = "";

	while (true)
	{
		getline(cin, currentComand);
		cout << currentComand;

		sys.comandsManager(currentComand);
	}
}
