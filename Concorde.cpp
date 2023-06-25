#include "Concorde.h"

int main()
{
	string currentComand;
	Sistema sys;

	while (true)
	{
		getline(cin, currentComand, '\n');

		sys.comandsManager(currentComand);
		// sys.displayAllUsers();
	}
}
