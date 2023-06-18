// Concorde.cpp: define o ponto de entrada para o aplicativo.
//

#include "Concorde.h"

using namespace std;

int main()
{
	vector<Usuario> usuarios;
	usuarios.push_back(Usuario("Lucas", "lucas4cristal@gmail.com", "lucas123"));
	usuarios.push_back(Usuario("Isabel", "isabel4cristal@gmail.com", "isabel123"));
	usuarios.push_back(Usuario("Lucas", "marcos4cristal@gmail.com", "marcos123"));
	usuarios.push_back(Usuario("Mario", "mario4cristal@gmail.com", "mario123"));



	for (Usuario user : usuarios)
	{
		cout << user.getNome() << endl;
	}
}
