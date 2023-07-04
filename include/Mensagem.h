#include <iostream>

using namespace std;

#pragma once

class Mensagem
{
private:
	/// @brief Datetime que salva a data e hora que a mensagem foi enviada
	string dataHora;
	/// @brief Id do usuário que enviou a mensagem
	int enviadoPor;
	/// @brief  Conteudo da mensagem
	string conteudo;

public:
	/// @brief Contrutor padrão da classe Mensagem
	Mensagem() = default;
	/// @brief Construtor da classe Mensagem
	/// @param dataHora Data e hora da mensagem
	/// @param enviadoPor Id do usuário que enviou a mensagem
	/// @param conteudo Texto com o conteúdo da mensagem
	Mensagem(string dataHora, int enviadoPor, string conteudo);

	/// @brief Função Get do atributo Data e hora
	/// @return Data e hora do envio da mensagem
	string getDataHora() const { return this->dataHora; }
	/// @brief Função Get do atributo que salva o id do usuário que enviou
	/// @return Id do usuário que enviou a mensagem
	int getEnviadoPor() const { return this->enviadoPor; }
	/// @brief Função Get do atributo conteúdo da mensagem
	/// @return Texto do conteúdo da mensagem
	string getConteudo() const { return this->conteudo; }

	/// @brief Função Set do data e hora
	/// @param dataHora Data e hora que será salva no atributo
	void setDataHora(string dataHora);
	/// @brief Função Set do id do usuário que enviou a mensagem
	/// @param userId 
	void setEnviadoPor(int userId);
	/// @brief Função Set do conteúdo da mensagem
	/// @param conteudo Conteúdo da mensagem que será salvo
	void setConteudo(string conteudo);

	/// @brief Formata a mensagem para mostrar na listagem
	/// @param userNmae nome do usuário que enviou a mensagem
	/// @return A mensagem formatada
	string toString(string userNmae);
};