// Concorde.cpp: define o ponto de entrada para o aplicativo.
//

#include "Concorde.h"

using namespace std;

int main()
{
	Sistema sys;

	string currentComand;

	while (true)
	{
		getline(cin, currentComand);

		sys.comandsManager(currentComand);
		break;
	}
}
