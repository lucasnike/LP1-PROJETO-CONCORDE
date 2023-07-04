#include "Concorde.h"
#include <ctime>

using namespace std;

int main()
{

	Sistema sys;
	string currentComand;

	bool quiting = false;

	while (true)
	{
		getline(cin, currentComand);

		quiting = sys.comandsManager(currentComand);

		if (quiting)
		{
			break;
		}
	}

	cout << str_cyan("\nSAINDO DO CONCORDE\n\n");
}
