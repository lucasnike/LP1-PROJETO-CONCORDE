#include <iostream>
#include <vector>

#include "Usuario.h"
#include "Servidor.h"
#include "Canal.h"
#include "CanalTexto.h"
#include "CanalVoz.h"


#pragma once

class Sistema
{
private:
	vector<Usuario> usuarios;
	vector<Servidor> servidores;
	int idUsuarioLogado;
	Servidor* servidorVisualizado;
	Canal* canalVisualizado;
public:
	int getIdUsuarioLogadoId() const { return this->idUsuarioLogado; }
	Servidor* getServidorVisualizado() const { return this->servidorVisualizado; }
	Canal* getCanalVisualidado() const { return this->canalVisualizado; }

	void setUsuarioLogadoId(int userId);
	void setServidorViasualizado(Servidor* servidor);
	void setCanalVisualizado(Canal* canal);
};