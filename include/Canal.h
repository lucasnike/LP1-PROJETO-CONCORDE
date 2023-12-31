#include <iostream>

using namespace std;

#pragma once

class Canal {
protected:
	/// @brief Nome do canal
	string nome;
public:
	/// @brief Construtor padrão do canal
	Canal() = default;

	/// @brief Construtor do canal
	/// @param nome Nome do cancal
	Canal(const string& nome) : nome(nome) {}

	/// @brief Destrutor virtual do Canal
	virtual ~Canal() = default;

	/// @brief Função Get para o nome do canal
	/// @return Nome do canal
	virtual string getNome() = 0;
	/// @brief Configura o nome do canal
	/// @param nome Nome do canal a ser configurado
	virtual void setNome(string nome) = 0;
	/// @brief Retorna o tipo do canal
	/// @return "Texto" ou "Voz"
	virtual string getTipo() = 0;
};