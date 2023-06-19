#include "../include/Sistema.h"


void Sistema::setUsuarioLogadoId(int userId)
{
	this->idUsuarioLogado = userId;
}

void Sistema::setServidorViasualizado(Servidor* servidor)
{
	this->servidorVisualizado = servidor;
}

void Sistema::setCanalVisualizado(Canal* canal)
{
	this->canalVisualizado = canal;
}

Sistema::Sistema()
{
}

void Sistema::comandsManager(string comand)
{
	string comandName = comand.substr(0, comand.find(" "));
	cout << comandName << endl;
}

void Sistema::quit()
{
}