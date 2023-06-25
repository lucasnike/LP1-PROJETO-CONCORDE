#include <iostream>
#include <vector>
#include <algorithm>

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
	vector<Usuario> usuarios;
	vector<Servidor> servidores;
	int idUsuarioLogado = 0;
	Servidor* servidorVisualizado;
	Canal* canalVisualizado;

	void createUser(string args);
	void login(string args);
	void disconnect();
	void createServer(string name);
	void setServerDescription(string desc);
	void setServerInviteCode(string args);
	void listServers();
	void removeServer(string args);


	int classificadorDeComandos(string comand);
public:
	int getIdUsuarioLogadoId() const { return this->idUsuarioLogado; }
	Servidor* getServidorVisualizado() const { return this->servidorVisualizado; }
	Canal* getCanalVisualidado() const { return this->canalVisualizado; }

	void setUsuarioLogadoId(int userId);
	void setServidorViasualizado(Servidor* servidor);
	void setCanalVisualizado(Canal* canal);

	Sistema() = default;

	bool comandsManager(string comand);
	void displayAllUsers();
};