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
	for (Servidor *server : servidores)
	{
		delete server;
	}
}

bool Sistema::comandsManager(string comand)
{
	int string_index = comand.find(" ");
	bool salvar = false;

	string comandName = to_Lower_Case(comand.substr(0, string_index));
	bool existe = find_element(COMANDOS, comandName);
	if (!existe)
	{
		cout << str_red("\nCOMANDO NÃO EXISTE\n\n");
		return false;
	}
	else if (find_element(COMANDOS_LOGADOS, comandName) && this->idUsuarioLogado == 0)
	{
		cout << str_red("\nUSUÁRIO PRECISA ESTAR CONECTADO PARA USAR ESTE COMANDO\n\n");
		return false;
	}
	else if (find_element(COMANDOS_DESLOGADOS, comandName) && this->idUsuarioLogado != 0)
	{
		cout << str_red("\nUSUÁRIO PRECISA ESTAR DESCONECTADO PARA USAR ESTE COMANDO\n\n");
		return false;
	}
	else if (find_element(COMANDOS_SALVAR, comandName))
	{
		salvar = true;
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
	case (int)ComandsEnum::enter_channel:
		this->enterChannel(comand);
		break;
	case (int)ComandsEnum::leave_channel:
		this->leaveChannel();
		break;
	case (int)ComandsEnum::send_message:
		this->sendMessage(comand);
		break;
	case (int)ComandsEnum::list_messages:
		this->listMessages();
	default:
		break;
	}

	if (salvar)
	{
		this->salvar();
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

void Sistema::salvar()
{
	this->salvarUsuarios();
	// this->salvarServidores();
}

void Sistema::carregar()
{
	this->idUsuarioLogado = 0;
	this->carregarUsuarios();
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
	for (Servidor *server : this->servidores)
	{
		if (server->getNome() == name)
		{
			cout << str_red("\nJÁ EXISTE UM SERVIDOR COM O NOME INFORMADO\n\n");
			return;
		}
	}
	Servidor *server = new Servidor(name, this->idUsuarioLogado);
	this->servidores.push_back(server);
	cout << str_green("\nSERVIDOR CRIADO COM O NOME " + name + "\n\n");
}

void Sistema::setServerDescription(string desc)
{
	int index = desc.find(' ');

	string nome = desc.substr(0, index);
	desc.erase(0, index + 1);

	std::replace(desc.begin(), desc.end(), '\"', '\0');

	for (Servidor *server : this->servidores)
	{
		if (server->getNome() == nome)
		{
			if (server->getUsuarioDonoId() == this->idUsuarioLogado)
			{
				
				server->setDescricao(desc);
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

	for (Servidor *server : this->servidores)
	{
		if (server->getNome() == nome)
		{
			if (server->getUsuarioDonoId() == this->idUsuarioLogado)
			{
				server->setCondigoConvite(codigo);
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
	for (Servidor *server : this->servidores)
	{
		cout << str_purple(server->getNome() + "\n");
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
		Servidor *server = this->servidores[i];
		if (server->getNome() == args)
		{
			if (server->getUsuarioDonoId() == idUsuarioLogado)
			{
				cout << str_green("\nSERVIDOR " + server->getNome() + " REMOVIDO\n\n");
				delete server;
				this->servidores.erase(servidores.begin() + i);
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

	for (int i = 0; i < servidores.size(); i++)
	{
		Servidor *server = servidores[i];
		if (server->getNome() == name)
		{
			bool participa = server->participanteExiste(this->idUsuarioLogado);
			if (server->getCondigoConvite() == "" || server->getUsuarioDonoId() == this->idUsuarioLogado || participa)
			{
				if (!participa)
				{
					server->inserirParticipante(this->idUsuarioLogado);
				}

				this->servidorVisualizado = server;
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

				if (server->getCondigoConvite() == args)
				{
					server->inserirParticipante(this->idUsuarioLogado);
					this->servidorVisualizado = server;
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
	this->canalVisualizado = nullptr;
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
	if (index == -1)
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
		cout << str_red("\nÉ PRECISO ESTAR VISUALIZANDO ALGUM SERVIDOR PARA ENTRAR EM UM CANAL\n\n");
		return;
	}
	if (this->canalVisualizado != nullptr)
	{
		cout << str_red("\nSAIA DO CANAL " + this->canalVisualizado->getNome() + " PARA ENTRAR EM " + name + "\n\n");
		return;
	}
	if (name == "")
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
			this->canalVisualizado = canal;
			cout << str_green("\nENTROU NO CANAL `" + name + "` \n\n");
			return;
		}
	}

	cout << str_red("\nSERVIDOR NÃO EXISTE\n\n");
}

void Sistema::leaveChannel()
{
	if (this->canalVisualizado == nullptr)
	{
		cout << str_red("\nNENHUM CANAL VISUALIZADO NO MOMENTO\n\n");
		return;
	}

	cout << str_green("\nSAINDO DO CANAL `" + this->canalVisualizado->getNome() + "`\n\n");
	this->canalVisualizado = nullptr;
}

void Sistema::sendMessage(string content)
{
	if (content == "")
	{
		cout << str_red("\nO COMANDO send-message PRECISA DE UM ARGUMENTO <Conteudo da mensgem>\n\n");
		return;
	}
	else if (this->canalVisualizado == nullptr)
	{
		cout << str_red("\nÉ PRECISO ENTRAR EM UM CANAL PARA ENVIAR UM MENSAGEM\n\n");
		return;
	}
	time_t now = time(0);
	tm *dateTime = localtime(&now);
	char sendDateTime[80];
	strftime(sendDateTime, 80, "%d/%m/%Y - %X", dateTime);

	if (this->canalVisualizado->getTipo() == "Texto")
	{
		CanalTexto *canal = dynamic_cast<CanalTexto *>(this->canalVisualizado);
		Mensagem m = Mensagem(sendDateTime, idUsuarioLogado, content);
		canal->mensagens.push_back(m);

		cout << str_green("\nMENSAGEM ENVIADA\n\n");

		return;
	}
	else
	{
		CanalVoz *canal = dynamic_cast<CanalVoz *>(this->canalVisualizado);

		canal->setMensagem(Mensagem(sendDateTime, idUsuarioLogado, content));
		cout << str_green("\nMENSAGEM ENVIADA\n\n");
		return;
	}
}

void Sistema::listMessages()
{
	if (this->canalVisualizado == nullptr)
	{
		cout << str_red("\nÉ PRECISA ESTAR VISUALIZANDO UM CANAL PARA LISTAR AS MENSAGENS\n\n");
		return;
	}

	if (this->canalVisualizado->getTipo() == "Texto")
	{
		CanalTexto *canal = dynamic_cast<CanalTexto *>(this->canalVisualizado);

		if (canal->mensagens.size() == 0)
		{
			cout << str_red("\nNENHUM MENSAGEM FOI ENVIADA NESTE CANAL\n\n");
			return;
		}

		cout << str_blue("\nLISTANDO MENSAGENS\n\n");
		for (Mensagem m : canal->mensagens)
		{
			cout << m.toString(getUserById(m.getEnviadoPor()).getNome());
		}
		cout << str_blue("\nFINAL LISTAGEM MENSAGENS\n\n");
		// delete canal;
		return;
	}
	else
	{
		CanalVoz *canal = dynamic_cast<CanalVoz *>(this->canalVisualizado);

		if (canal->getMensagem().getConteudo() == "")
		{
			cout << str_red("\nNENHUM MENSAGEM FOI ENVIADA NESTE CANAL\n\n");
			return;
		}
		cout << str_blue("\nULTIMA MENSAGEN\n\n");

		Mensagem ultima = canal->getMensagem();
		cout << ultima.toString(getUserById(ultima.getEnviadoPor()).getNome());

		cout << endl;
		// delete canal;

		return;
	}
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
	else if (comand == "LEAVE-CHANNEL")
		return (int)ComandsEnum::leave_channel;
	else if (comand == "SEND-MESSAGE")
		return (int)ComandsEnum::send_message;
	else if (comand == "LIST-MESSAGES")
		return (int)ComandsEnum::list_messages;
	return 0;
}

void Sistema::salvarUsuarios()
{
	string file = "./data/usuarios.txt";
	ofstream writter;
	writter.open(file);

	if (!writter)
	{
		return;
	}
	int size = usuarios.size();
	writter << size << endl;

	for (int i = 0; i < size; i++)
	{
		Usuario user = usuarios[i];

		writter << user.getId() << endl;
		writter << user.getNome() << endl;
		writter << user.getEmail() << endl;
		writter << user.getSenha() << endl;
	}
	writter << this->idUsuarioLogado << endl;

	writter.close();
}

void Sistema::salvarServidores()
{
	string file = "./data/servidores.txt";
	ofstream writter;
	writter.open(file);

	if (!writter)
	{
		cout << str_red("\nArquivo inválido\n\n");
		return;
	}

	int size = servidores.size();
	for (int i = 0; i < size; i++)
	{
		Servidor *server = servidores.at(i);

		cout << server->getNome() << endl;

		writter << server->getUsuarioDonoId();
		if (server == servidorVisualizado)
		{
			writter << " View";
		}
		writter << endl;
		
		writter << server->getNome() << endl;
		writter << server->getDescricao() << endl;
		writter << server->getCondigoConvite() << endl;
		writter << server->getParticipantesIds().size() << endl;

		vector<int> ids = server->getParticipantesIds();
		for (int j = 0; j < ids.size(); j++)
		{
			writter << ids[j] << endl;
		}

		vector<Canal *> *canais = server->getCanais();

		writter << canais->size() << endl;

		for (int y = 0; y < canais->size(); y++)
		{
			Canal *canal = canais->at(y);

			if (canal->getTipo() == "Texto")
			{
				CanalTexto *canalTexto = dynamic_cast<CanalTexto *>(canal);

				writter << canalTexto->getNome() << endl;
				writter << "TEXTO" << endl;

				writter << canalTexto->mensagens.size() << endl;

				vector<Mensagem> mensagens = canalTexto->mensagens;

				for (int k = 0; k < mensagens.size(); k++)
				{
					Mensagem mensagem = mensagens[k];

					writter << mensagem.getEnviadoPor() << endl;
					writter << mensagem.getDataHora() << endl;
					writter << mensagem.getConteudo() << endl;
				}
			}
			else
			{
				CanalVoz *canalVoz = dynamic_cast<CanalVoz *>(canal);

				writter << canalVoz->getNome() << endl;
				writter << "VOZ" << endl;
				if (canalVoz->getMensagem().getConteudo() != "")
				{
					writter << 1 << endl;
					writter << canalVoz->getMensagem().getEnviadoPor() << endl;
					writter << canalVoz->getMensagem().getDataHora() << endl;
					writter << canalVoz->getMensagem().getConteudo() << endl;
				}
				else
				{
					writter << 0 << endl;
				}
			}
		}
	}

	writter.close();
}

Usuario Sistema::getUserById(int id)
{
	for (Usuario user : usuarios)
	{
		if (user.getId() == id)
		{
			return user;
		}
	}

	return Usuario();
}

void Sistema::carregarUsuarios()
{
	string file = "./data/usuarios.txt";
	ifstream reader;
	reader.open(file);

	if (!reader.is_open())
	{
		cout << str_red("\nNÃO FOI POSSÍVEL CARREGAR OS DADOS SALVOS\n\n");
		return;
	}

	while (!reader.eof())
	{
		string line;

		getline(reader, line);

		// Sai da função pois o arquivo está vazio
		if (line == "")
		{
			return;
		}

		int nUsers = stoi(line);

		for (int i = 0; i < nUsers; i++)
		{
			getline(reader, line);
			int id = stoi(line);

			getline(reader, line);
			string name = line;

			getline(reader, line);
			string email = line;

			getline(reader, line);
			string password = line;

			Usuario user(id, name, email, password);
			this->usuarios.push_back(user);
		}

		getline(reader, line);
		int logedUser = stoi(line);
		this->idUsuarioLogado = logedUser;
	}

	reader.close();
}

void Sistema::carregarServidores()
{
	string file = "./data/servidores.txt";
	ifstream reader;
	reader.open(file);

	if (!reader.is_open())
	{
		cout << str_red("\nNÃO FOI POSSÍVEL CARREGAR OS DADOS SALVOS\n\n");
		return;
	}

	while (!reader.eof())
	{
		string line;

		getline(reader, line);
		int creator = stoi(line);

		getline(reader, line);
		string name = line;

		getline(reader, line);
		string desc = line;

		getline(reader, line);
		string inviteCode = line;

		Servidor server;
		server.setUsuarioDonoId(creator);
		server.setNome(name);
		server.setDescricao(desc);
		server.setCondigoConvite(inviteCode);

		getline(reader, line);
		int nUsers = stoi(line);

		for (int i = 0; i < nUsers; i++)
		{
			getline(reader, line);
			int id = stoi(line);
			server.addParticipante(id);
		}

		getline(reader, line);
		int nChannels = stoi(line);

		for (int i = 0; i < nChannels; i++)
		{
			
		}
		
	}

	reader.close();
}
