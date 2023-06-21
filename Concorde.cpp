#include "Concorde.h"


int main()
{
	Sistema sys;

	string currentComand;

	while (true)
	{
		getline(cin, currentComand);

		sys.comandsManager(currentComand);
	}
}
