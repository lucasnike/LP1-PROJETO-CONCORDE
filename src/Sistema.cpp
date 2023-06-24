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
	int string_index = comand.find(" ");

	string comandName = comand.substr(0, string_index);
	bool existe = find_element(COMANDOS, comandName);

	if (!existe)
	{
		cout << endl << str_red("COMANDO NÃO EXISTE") << endl;
		return;
	}

	int comandId = classificadorDeComandos(comandName);

	if (string_index == -1)
	{
		comand.erase(0, string_index);
	}
	else
	{
		comand.erase(0, string_index + 1);
	}

	switch (comandId)
	{
	case (int)ComandsEnum::quit:
		this->quit();
		break;
	case (int)ComandsEnum::create_user:
		createUser(comand);
		break;
	default:
		break;
	}
}

void Sistema::quit()
{
	exit(0);
}

void Sistema::createUser(string args)
{
	cout << "String size = " << args.size() << endl;
	cout << "Argumentos recebidos = " << args << endl;
}

int Sistema::classificadorDeComandos(string comand)
{
	for (char &c : comand)
	{
		c = std::toupper(c);
	}

	cout << comand << endl;

	if (comand == "LOGIN")
	{
		return (int)ComandsEnum::login;
	}
	else if (comand == "QUIT")
	{
		return (int)ComandsEnum::quit;
	}
	else if (comand == "CREATE-USER")
	{
		return (int)ComandsEnum::create_user;
	}

	return 0;
}