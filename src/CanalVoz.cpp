#include "../include/CanalVoz.h"
#include "CanalVoz.h"

CanalVoz::CanalVoz(string nome)
{
	this->nome = nome;
}
string CanalVoz::getNome()
{
	return this->nome;
}

void CanalVoz::setNome(string nome)
{
	this->nome = nome;
}

Mensagem CanalVoz::getMensagem()
{
	return this->ultimaMensagem;
}

void CanalVoz::setMensagem(Mensagem mensagem)
{
	this->ultimaMensagem = mensagem;
}

string CanalVoz::getTipo()
{
    return "Voz";
}
