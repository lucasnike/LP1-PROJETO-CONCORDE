#include <iostream>

using namespace std;

#pragma once

class Mensagem {
private:
	string dataHora;
	int enviadoPor;
	string conteudo;
public:
	Mensagem();
	Mensagem(string dataHora, int enviadoPor, string conteudo);

#pragma region GET FUNCTIONS
	string getDataHora() const { return this->dataHora; }
	int getEnviadoPor() const { return this->enviadoPor; }
	string getConteudo() const { return this->conteudo; }
#pragma endregion

#pragma region SET FUNCTIONS
	void setDataHora(string dataHora);
	void setEnviadoPor(int userId);
	void setConteudo(string conteudo);
#pragma endregion


};