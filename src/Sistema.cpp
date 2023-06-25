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
		cout << str_red("\nCOMANDO NÃO EXISTE\n");
		return;
	}

	if (find_element(COMANDOS_DESLOGADOS, comandName) && this->idUsuarioLogado != 0)
	{
		cout << str_red("\nUSUÁRIO PRECISA ESTAR DESCONECTADO PARA USAR ESTE COMANDO\n\n");
	}

	if (find_element(COMANDOS_LOGADOS, comandName) && this->idUsuarioLogado == 0)
	{
		cout << str_red("\nUSUÁRIO PRECISA ESTAR CONECTADO PARA USAR ESTE COMANDO\n\n");
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
		this->createUser(comand);
		break;
	case (int)ComandsEnum::login:
		this->login(comand);
		break;
	case (int)ComandsEnum::disconnect:
		this->disconnect();
		break;
	default:
		break;
	}
}

void Sistema::displayAllUsers()
{
	for(Usuario user : usuarios)
	{
		cout << user.getId() << " " << user.getEmail() << endl;
	}
}

void Sistema::quit()
{
	exit(0);
}

void Sistema::createUser(string args)
{
	int index = args.find(' ');
	bool emailExiste = false;
	string email = args.substr(0, index);
	args.erase(0, index + 1);
	index = args.find(' ');
	string senha = args.substr(0, index);
	args.erase(0, index + 1);
	string nome = args;

	for (Usuario user : this->usuarios)
	{
		if (user.getEmail() == email)
		{
			emailExiste = true;
			break;
		}
	}

	if (emailExiste)
	{
		cout << str_red("\nJÁ EXISTE UM USUÁRIO COM ESSE EMAIL\n");
	}

	this->usuarios.push_back(Usuario(usuarios.size() + 1, nome, email, senha));
}

void Sistema::login(string args)
{
	bool emailExiste = false;

	int index = args.find(' ');
	
	string email = args.substr(0, index);
	args.erase(0, index + 1);
	index = args.find(' ');

	string senha = args.substr(0, index);

	for (Usuario user : this->usuarios)
	{
		if (user.getEmail() == email)
		{
			if (user.getSenha() == senha)
			{
				this->idUsuarioLogado = user.getId();
				cout << str_green("\nLOGADO COMO " + user.getEmail() + "\n\n");
				return;
			}
			else
			{
				cout << str_red("\nSENHA ERRADA\n\n");
			}
		}
	}

	if (!emailExiste)
	{
		cout << str_red("\nNÃO EXISTE NENHUM USUÁRIO COM O EMAIL INFORMADO\n\n");
	}
}

void Sistema::disconnect()
{
	this->idUsuarioLogado = 0;
}

int Sistema::classificadorDeComandos(string comand)
{
	for (char &c : comand)
	{
		c = std::toupper(c);
	}

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
	else if(comand == "DISCONNECT")
	{
		return (int)ComandsEnum::disconnect;
	}

	return 0;
}