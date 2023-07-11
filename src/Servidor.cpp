#include "Servidor.h"

Servidor::~Servidor()
{
	for (Canal *canal : canais)
	{	
		delete canal;
	}
}

Servidor::Servidor(string nome, int dono)
{
	this->nome = nome;
	this->usuarioDonoId = dono;
}

void Servidor::setUsuarioDonoId(int userId)
{
	this->usuarioDonoId = userId;
}

void Servidor::setNome(string nome)
{
	this->nome = nome;
}

void Servidor::setDescricao(string descricao)
{
	this->descricao = descricao;
}

void Servidor::setCondigoConvite(string codigoConvite)
{
	this->codigoConvite = codigoConvite;
}

void Servidor::inserirParticipante(int id)
{
	this->participantesIds.push_back(id);
}

bool Servidor::participanteExiste(int id)
{
    return find_element(this->participantesIds, id);
}

vector<Canal*> *Servidor::getCanais()
{
    return &this->canais;
}

void Servidor::addParticipante(int id)
{
	this->participantesIds.push_back(id);
}
