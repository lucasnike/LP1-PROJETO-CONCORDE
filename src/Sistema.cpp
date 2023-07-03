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

Sistema::~Sistema()
{
	
}

bool Sistema::comandsManager(string comand)
{
	int string_index = comand.find(" ");

	string comandName = comand.substr(0, string_index);
	bool existe = find_element(COMANDOS, comandName);
	if (!existe)
	{
		cout << str_red("\nCOMANDO NÃO EXISTE\n\n");
		return false;
	}

	if (find_element(COMANDOS_DESLOGADOS, comandName) && this->idUsuarioLogado != 0)
	{
		cout << str_red("\nUSUÁRIO PRECISA ESTAR DESCONECTADO PARA USAR ESTE COMANDO\n\n");
		return true;
	}

	if (find_element(COMANDOS_LOGADOS, comandName) && this->idUsuarioLogado == 0)
	{
		cout << str_red("\nUSUÁRIO PRECISA ESTAR CONECTADO PARA USAR ESTE COMANDO\n\n");
		return false;
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
		return true;
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
	case (int)ComandsEnum::create_server:
		this->createServer(comand);
		break;
	case (int)ComandsEnum::set_server_desc:
		this->setServerDescription(comand);
		break;
	case (int)ComandsEnum::set_server_invite_code:
		this->setServerInviteCode(comand);
		break;
	case (int)ComandsEnum::list_servers:
		this->listServers();
		break;
	case (int)ComandsEnum::remove_server:
		this->removeServer(comand);
		break;
	case (int)ComandsEnum::enter_server:
		this->enterServer(comand);
		break;
	case (int)ComandsEnum::leave_server:
		this->leaveServer();
		break;
	case (int)ComandsEnum::list_participants:
		this->listParticipants();
		break;
	case (int)ComandsEnum::create_chanel:
		this->createChanel(comand);
		break;
	case (int)ComandsEnum::list_channels:
		this->listChannels();
		break;
	default:
		break;
	}

	return false;
}

void Sistema::displayAllUsers()
{
	for (Usuario user : usuarios)
	{
		cout << user.getId() << " " << user.getEmail() << endl;
	}
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
		cout << str_red("\nJÁ EXISTE UM USUÁRIO COM ESSE EMAIL\n\n");
		return;
	}

	this->usuarios.push_back(Usuario(usuarios.size() + 1, nome, email, senha));
	cout << str_green("\nUSUÁRIO CRIADO COM SUCESSO\n\n");
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
				return;
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
	for (Usuario u : this->usuarios)
	{
		if (u.getId() == this->idUsuarioLogado)
		{
			cout << str_green("\nDESCONECTANDO USUÁRIO " + u.getEmail() + "\n\n");
			this->idUsuarioLogado = 0;
			this->servidorVisualizado = nullptr;
			this->canalVisualizado = nullptr;
		}
	}
}

void Sistema::createServer(string name)
{
	for (Servidor server : this->servidores)
	{
		if (server.getNome() == name)
		{
			cout << str_red("\nJÁ EXISTE UM SERVIDOR COM O NOME INFORMADO\n\n");
			return;
		}
	}

	this->servidores.push_back(Servidor(name, this->idUsuarioLogado));
	cout << str_green("\nSERVIDOR CRIADO COM O NOME " + name + "\n\n");
}

void Sistema::setServerDescription(string desc)
{
	int index = desc.find(' ');

	string nome = desc.substr(0, index);
	desc.erase(0, index + 1);

	std::replace(desc.begin(), desc.end(), '\"', '\0');

	for (Servidor &server : this->servidores)
	{
		if (server.getNome() == nome)
		{
			if (server.getUsuarioDonoId() == this->idUsuarioLogado)
			{
				server.setDescricao(desc);
				cout << str_green("\nDESCRIÇÃO DO SERVIDOR CONFIGURADA COM SUCESSO\n\n");
				return;
			}
			else
			{
				cout << str_red("\nSÓ O DONO DO SERVIDOR PODE ALTERAR SUA DESCRIÇÃO\n\n");
				return;
			}
		}
	}

	cout << str_red("\nNÃO EXISTE UM SERVIDOR COM ESSE NOME\n\n");
}

void Sistema::setServerInviteCode(string args)
{
	int index = args.find(' ');
	string nome = args.substr(0, index);
	string codigo;

	if (index == -1)
	{
		codigo = "";
	}
	else
	{
		args.erase(0, index + 1);
		codigo = args;
	}

	for (Servidor &server : this->servidores)
	{
		if (server.getNome() == nome)
		{
			if (server.getUsuarioDonoId() == this->idUsuarioLogado)
			{
				server.setCondigoConvite(codigo);
				if (codigo == "")
				{
					cout << str_green("\nCÓDIGO DE CONVITE ALTERADO COM SUCESSO, AGORA QUALQUER UM PODE ENTRAR NO SEU SERVIDOR\n\n");
					return;
				}

				cout << str_green("\nCÓDIGO DE CONVITE ALTERADO COM SUCESSO\n\n");
				return;
			}
			else
			{
				cout << str_red("\nAPENAS O DONO DO SERVIDOR PODE CONFIGURAR O CÓDIGO DE CONVITE\n\n");
				return;
			}
		}
	}

	cout << str_red("\nNÃO EXISTE NENHUM SERVIDOR COM O NOME INFORMADO\n\n");
}

void Sistema::listServers()
{
	if (this->servidores.size() == 0)
	{
		cout << str_red("\nNÃO EXISTE NENHUM SERVIDOR CRIADO\n\n");
		return;
	}

	cout << str_blue("\nINICIANDO LISTAGEM DE SERVIDORES\n\n");
	for (Servidor server : this->servidores)
	{
		cout << str_purple(server.getNome() + "\n");
	}
	cout << str_blue("\nFINALIZANDO LISTAGEM DE SERVIDORES\n\n");
}

void Sistema::removeServer(string args)
{
	if (args == "")
	{
		cout << str_red("\nNÃO FOI INFORMADO UM NOME DE SERVIDOR PARA SER REMOVIDO\n\n");
		return;
	}

	for (int i = 0; i < this->servidores.size(); i++)
	{
		Servidor server = this->servidores[i];
		if (server.getNome() == args)
		{
			if (server.getUsuarioDonoId() == idUsuarioLogado)
			{
				this->servidores.erase(servidores.begin() + i);
				cout << str_green("\nSERVIDOR " + server.getNome() + " REMOVIDO\n\n");
				return;
			}
			else
			{
				cout << str_red("\nAPENAS O DONO DO SERVIDOR PODE EXCLUI-LO\n\n");
				return;
			}
		}
	}

	cout << str_red("\nNÃO EXISTE NENHUM SERVIDOR COM O NOME INFORMADO\n\n");
}

void Sistema::enterServer(string args)
{
	if (args == "")
	{
		cout << str_red("\nPELO MENOS O NOME DO SERVIDOR DEVE SER INFORMADO\n\n");
		return;
	}

	int index = args.find(' ');
	string name = args.substr(0, index);

	for (Servidor &server : this->servidores)
	{
		if (server.getNome() == name)
		{
			bool participa = server.participanteExiste(this->idUsuarioLogado);
			if (server.getCondigoConvite() == "" || server.getUsuarioDonoId() == this->idUsuarioLogado || participa)
			{
				if (!participa)
				{
					server.inserirParticipante(this->idUsuarioLogado);
				}
				this->servidorVisualizado = &server;
				cout << str_green("\nENTROU NO SERVIDOR COM SUCESSO\n\n");
				return;
			}
			else
			{
				if (index == -1)
				{
					cout << str_red("\nÉ NECESSÁRIO INFORMAR O CÓDIGO DE CONVITE PARA ENTRAR NESTE SERVIDOR\n\n");
					return;
				}
				args.erase(0, index + 1);

				if (server.getCondigoConvite() == args)
				{
					server.inserirParticipante(this->idUsuarioLogado);
					this->servidorVisualizado = &server;
					cout << str_green("\nENTROU NO SERVIDOR COM SUCESSO\n\n");
					return;
				}
				else
				{
					cout << str_red("\nO CÓDIGO DO CONVITE INFORMADO É INVÁLIDO\n\n");
					return;
				}
			}
		}
	}

	cout << str_red("\nNÃO EXISTE UM SERVIDOR COM O NOME INFORMADO\n\n");
}

void Sistema::leaveServer()
{
	if (this->servidorVisualizado == nullptr)
	{
		cout << str_red("\nVOCÊ NÃO ESTÁ VISUALIZANDO NENHUM SERVIDOR\n\n");
		return;
	}

	cout << str_green("\nSAINDO DO SERVIDOR '" + this->servidorVisualizado->getNome() + "'\n\n");
	this->servidorVisualizado = nullptr;
}

void Sistema::listParticipants()
{
	if (this->servidorVisualizado == nullptr)
	{
		cout << str_red("\nVOCÊ NÃO ESTÁ CONECTADO A NENHUM SERVIDOR\n\n");
		return;
	}

	vector<int> ids = this->servidorVisualizado->getParticipantesIds();
	cout << str_blue("\nINICIANDO LISTAGEM DE SERVIDORES\n\n");
	for (int id : ids)
	{
		for (Usuario user : this->usuarios)
		{
			if (user.getId() == id)
			{
				cout << str_purple(user.getNome()) << endl;
				break;
			}
		}
	}
	cout << str_blue("\nFINALIZANDO LISTAGEM DE SERVIDORES\n\n");
}

void Sistema::createChanel(string args)
{
	int index = args.find(' ');

	if (args == "")
	{
		cout << str_red("\nESSE COMANDO NECESSITA DE DOIS ARGUMENTOS <NOME DO CANAL>, <TIPO DO CANAL>\n\n");
		return;
	}
	else if (index == -1)
	{
		cout << str_red("\nINFORMAR O TIPO DO CANAL É OBRIGATÓRIO\n\n");
		return;
	}

	if (this->servidorVisualizado == nullptr)
	{
		cout << str_red("\nÉ PRECISO ESTAR VISUALIZANDO ALGUM SERVIDOR PARA CRIAR UM CANAL\n\n");
		return;
	}

	if (this->servidorVisualizado->getUsuarioDonoId() != this->idUsuarioLogado)
	{
		cout << str_red("\nAPENAS O DONO DO SERVIDO PODE CRIAR O CANAL\n\n");
		return;
	}

	string name = args.substr(0, index);
	args.erase(0, index + 1);
	string tipo = to_Upper_Case(args);

	Servidor *server = this->servidorVisualizado;
	vector<Canal *> *canais = server->getCanais();

	for (Canal *canal : *canais)
	{
		if (canal->getNome() == name)
		{
			cout << str_red("\nJÁ EXISTE UM CANAL COM O NOME INFORMADO\n\n");
			return;
		}
	}

	if (tipo == "VOZ")
	{
		CanalVoz *canal = new CanalVoz(name);
		canais->push_back(canal);
	}
	else
	{
		CanalTexto *canal = new CanalTexto(name);
		canais->push_back(canal);
	}

	cout << str_green("\nCANAL DE " + tipo + " CRIADO COM SUCESSO\n\n");
}

void Sistema::listChannels()
{
	if (this->servidorVisualizado == nullptr)
	{
		cout << str_red("\nÉ PRECISO ESTAR VISUALIZANDO ALGUM SERVIDOR PARA CRIAR UM CANAL\n\n");
		return;
	}

	int contagem[2] = {0, 0};
	vector<Canal *> *canais = this->servidorVisualizado->getCanais();

	cout << str_blue("# CANAIS DE VOZ\n\n");
	for (Canal *canal : *canais)
	{
		if (canal->getTipo() == "Voz")
		{
			contagem[0]++;
			cout << str_purple(canal->getNome()) << endl;
		}
	}
	if (contagem[0] == 0)
		cout << str_red("NENHUM CANAL DE VOZ\n\n");

	cout << str_blue("\n# CANAIS DE TEXTO\n\n");
	for (Canal *canal : *canais)
	{
		if (canal->getTipo() == "Texto")
		{
			contagem[1]++;
			cout << str_purple(canal->getNome()) << endl;
		}
	}
	if (contagem[1] == 0)
		cout << str_red("NENHUM CANAL DE TEXTO\n");
}

void Sistema::enterChannel(string name)
{
	if (this->servidorVisualizado == nullptr)
	{
		cout << str_red("\nÉ PRECISO ESTAR VISUALIZANDO ALGUM SERVIDOR PARA CRIAR UM CANAL\n\n");
		return;
	}
	else if (this->canalVisualizado != nullptr)
	{
		cout << str_red("\nSAIA DO CANAL " + this->canalVisualizado->getNome() + " PARA ENTRAR EM OUTRO\n\n");
		return;
	}
	else if (name == "")
	{
		cout << str_red("\nESSE COMANDO NECESSITA DE UM ARGUMENTO <NOME DO CANAL>\n\n");
		return;
	}

	Servidor *server = this->servidorVisualizado;
	vector<Canal *> *canais = server->getCanais();

	for (Canal *canal : *canais)
	{
		if (canal->getNome() == name)
		{

			return;
		}
	}

	cout << str_red("\nSERVIDOR NÃO EXISTE\n\n");
}

int Sistema::classificadorDeComandos(string comand)
{
	comand = to_Upper_Case(comand);

	if (comand == "LOGIN")
		return (int)ComandsEnum::login;
	else if (comand == "QUIT")
		return (int)ComandsEnum::quit;
	else if (comand == "CREATE-USER")
		return (int)ComandsEnum::create_user;
	else if (comand == "DISCONNECT")
		return (int)ComandsEnum::disconnect;
	else if (comand == "CREATE-SERVER")
		return (int)ComandsEnum::create_server;
	else if (comand == "SET-SERVER-DESC")
		return (int)ComandsEnum::set_server_desc;
	else if (comand == "SET-SERVER-INVITE-CODE")
		return (int)ComandsEnum::set_server_invite_code;
	else if (comand == "LIST-SERVERS")
		return (int)ComandsEnum::list_servers;
	else if (comand == "REMOVE-SERVER")
		return (int)ComandsEnum::remove_server;
	else if (comand == "ENTER-SERVER")
		return (int)ComandsEnum::enter_server;
	else if (comand == "LEAVE-SERVER")
		return (int)ComandsEnum::leave_server;
	else if (comand == "LIST-PARTICIPANTS")
		return (int)ComandsEnum::list_participants;
	else if (comand == "CREATE-CHANNEL")
		return (int)ComandsEnum::create_chanel;
	else if (comand == "LIST-CHANNELS")
		return (int)ComandsEnum::list_channels;
	else if (comand == "ENTER-CHANNEL")
		return (int)ComandsEnum::enter_channel;

	return 0;
}