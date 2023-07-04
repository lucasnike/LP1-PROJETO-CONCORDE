#include "Mensagem.h"
#include "../include/interns/TerminalColors.h"

Mensagem::Mensagem(string dataHora, int enviadoPor, string conteudo)
{
	this->conteudo = conteudo;
	this->dataHora = dataHora;
	this->enviadoPor = enviadoPor;
}

void Mensagem::setDataHora(string dataHora)
{
	this->dataHora = dataHora;
}

void Mensagem::setEnviadoPor(int userId)
{
	this->enviadoPor = userId;
}

void Mensagem::setConteudo(string conteudo)
{
	this->conteudo = conteudo;
}
string Mensagem::toString(string userName)
{
	string f = str_cyan(userName) + "<" + str_green(this->dataHora) + ">: " + this->conteudo + "\n";

    return f;
}
