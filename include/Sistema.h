#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <string.h>
#include <fstream>

#include "Usuario.h"
#include "Servidor.h"
#include "Canal.h"
#include "CanalTexto.h"
#include "CanalVoz.h"
#include "./interns/Helper.h"
#include "./interns/Comands.h"
#include "./interns/TerminalColors.h"
#include "./interns/Definitions.h"


#pragma once

class Sistema
{
private:
	/// @brief Lista de usuários do Concorde
	vector<Usuario> usuarios;

	/// @brief Lista de servidores do Concorde
	vector<Servidor> servidores;

	/// @brief Id do usuário logado no momento da execução
	int idUsuarioLogado = 0;

	/// @brief Ponteiro para o Servidor visualizado no momento
	Servidor* servidorVisualizado = nullptr;

	/// @brief Ponteiro para o canal visualiazado no momento
	Canal* canalVisualizado = nullptr;

	/// @brief Função do comando create-user
	/// @param args Argumentos do comando
	void createUser(string args);

	/// @brief Função do comando login
	/// @param args Argumentos do comando
	void login(string args);

	/// @brief Função do comando disconnect
	void disconnect();

	/// @brief Função do comando create-server
	/// @param name nome do servidor a ser criado
	void createServer(string name);

	/// @brief Função do comando set-server-desc
	/// @param desc descrição a ser configurada
	void setServerDescription(string desc);

	/// @brief Função do comando et-server-invite-code
	/// @param args Argumentos do comando
	void setServerInviteCode(string args);

	/// @brief Função do comando list-servers
	void listServers();

	/// @brief Função do comando remove-server
	/// @param args Argumentos do comando
	void removeServer(string args);

	/// @brief Função do comando enter-server
	/// @param args Argumentos do comando
	void enterServer(string args);

	/// @brief Função do comando leave-server
	void leaveServer();

	/// @brief Função do comando list-participants
	void listParticipants();

	/// @brief Função do comando create-channel
	/// @param args Argumentos do comando
	void createChanel(string args);

	/// @brief Lista todos os canais do servidor visualizado
	void listChannels();

	/// @brief Entra no canal especificado
	/// @param name Nome do canal
	void enterChannel(string name);

	/// @brief Sai do canal atual
	void leaveChannel();

	/// @brief Função do comando que envia uma mensagem em um canal 
	/// @param content Conteúdo da mensagem 
	void sendMessage(string content);

	/// @brief Lista todas as mensagens envidas no canal
	void listMessages();

	/// @brief Classefica qual comando foi digitado 
	/// @param comand Comando digitado
	/// @return Indice da Enumeração que identifica os comandos
	int classificadorDeComandos(string comand);

	/// @brief Função que guarda todos os usuários em disco
	void salvarUsuarios();

	/// @brief Função que guarda todos os servidores em disco
	void salvarServidores();

	/// @brief Busca um usuário pelo id
	/// @param id id do usuário
	/// @return Usuario do id especificado
	Usuario getUserById(int id);

public:
	/// @brief Função Get do id do usuário logado
	/// @return Id do usuário logado
	int getIdUsuarioLogadoId() const { return this->idUsuarioLogado; }

	/// @brief Função Get do ponteiro do Servidor que está sendo visualizado no momento
	/// @return Ponteiro para um Servidor
	Servidor* getServidorVisualizado() const { return this->servidorVisualizado; }

	/// @brief Função Get do ponteiro para o Canal que está sendo visualizado
	/// @return Ponteiro para um Canal
	Canal* getCanalVisualidado() const { return this->canalVisualizado; }

	/// @brief Função Set para o id do usuário logado
	/// @param userId Id do usuário que será salvo no atributo da classe
	void setUsuarioLogadoId(int userId);

	/// @brief Função Set do ponteiro para o Servidor em visualização
	/// @param servidor Ponteiro para o servidor que será salvo
	void setServidorViasualizado(Servidor* servidor);

	/// @brief Função Set do ponteiro para o Canal em visualização
	/// @param canal Ponteiro para o canal que será salvo
	void setCanalVisualizado(Canal* canal);

	/// @brief Contrutor padrão da classe
	Sistema() = default;

	/// @brief Função que recebe o comando, identifica qual é o comando e executa sua respectiva função
	/// @param comand Comando digitado pelo usuário
	/// @return Valor booleano que define se a aplicação deve fechar ou não
	bool comandsManager(string comand);
	
	/// @brief Mostra no terminal todos os emails dos usuários
	void displayAllUsers();

	/// @brief Salva o estado de todos os elementos do programa
	void salvar();
};