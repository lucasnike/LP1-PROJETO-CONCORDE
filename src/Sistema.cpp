#include "../include/Sistema.h"
#include "Sistema.h"

void Sistema::setUsuarioLogadoId(int userId)
{
	this->idUsuarioLogado = userId;
}

void Sistema::setServidorViasualizado(Servidor *servidor)
{
	this->servidorVisualizado = servidor;
}

void Sistema::setCanalVisualizado(Canal *canal)
{
	this->canalVisualizado = canal;
}

Sistema::Sistema()
{
}

void Sistema::comandsManager(string comand)
{
	string comandName = comand.substr(0, comand.find(" "));
	bool existe = find_element(COMANDOS, comandName);

	cout << "Comando interpretado = " << comandName << endl;

	if (!existe)
	{
		cout << endl << str_red("COMANDO NÃO EXISTE") << endl;
		return;
	}

	int comandId = classificadorDeComandos(comandName);

	switch (comandId)
	{
	case (int)ComandsEnum::quit:
		this->quit();
		break;

	default:
		break;
	}
}

void Sistema::quit()
{
	exit(0);
}

int Sistema::classificadorDeComandos(string comand)
{
	for (char& c : comand) {
        c = std::toupper(c);
    }

	cout << comand << endl;

	if (comand == "LOGIN")
	{
		return (int)ComandsEnum::login;
	}
	else if(comand == "QUIT")
	{
		return (int)ComandsEnum::quit;
	}
	else if(comand == "CREATE-USER")
	{
		return (int)ComandsEnum::create_user;
	}
	
	return 0;
}