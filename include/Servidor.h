#include <iostream>
#include <vector>
#include "Canal.h"

using namespace std;

#pragma once

class Servidor
{
private:
	int usuarioDonoId;
	string nome;
	string descricao;
	string codigoConvite;
	vector<Canal*> canais;
	vector<int> participantesIds;
public:
	int getUsuarioDonoId() const { return this->usuarioDonoId; }
	string getNome() const { return this->nome; }
	string getDescricao() const { return this->descricao; }
	string getCondigoConvite() const { return this->codigoConvite; }

	void setUsuarioDonoId(int userId);
	void setNome(string nome);
	void setDescricao(string descricao);
	void setCondigoConvite(string codigoConvite);
};