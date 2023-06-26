#include <iostream>

using namespace std;

#pragma once

class Usuario
{
private:
	/// @brief Identificador único do usuário
	int id;
	/// @brief Nome do usuário
	string nome;
	/// @brief Email do usuário
	string email;
	/// @brief Senha da conta do usuário
	string senha;

public:
	/// @brief Construtor padrão do usuário
	Usuario() = default;
	/// @brief Construtor do Usuario
	/// @param id Identificado único auto-incremental
	/// @param nome Nome do usuário
	/// @param email Email do usuário
	/// @param senha Senha do usuário
	Usuario(int id, string nome, string email, string senha);

	/// @brief Função Get do identificador
	/// @return Identificado do usuário
	int getId() const { return this->id; }
	/// @brief Função Get do Email
	/// @return Emal do usuário
	string getEmail() const { return this->email; }
	/// @brief Função Get do Nome
	/// @return Nome do usuário
	string getNome() const { return this->nome; }
	/// @brief Função Get da Senha
	/// @return Senha do usuário
	string getSenha() const { return this->senha; }

	/// @brief Função Set do Email
	/// @param email Email que será salvo
	void setEmail(string email);
	/// @brief Função Set do Nome
	/// @param nome Nome que será salvo
	void setNome(string nome);
	/// @brief Função Set da senha
	/// @param senha Senha que será salva
	void setSenha(string senha);
};