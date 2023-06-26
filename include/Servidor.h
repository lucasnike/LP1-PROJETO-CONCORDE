#include <iostream>
#include <vector>
#include "Canal.h"
#include "./interns/Helper.h"

using namespace std;

#pragma once

class Servidor
{
private:
	/// @brief Id do usuário que criou o servidor
	int usuarioDonoId;
	/// @brief Nome do servidor
	string nome;
	/// @brief Descrição do servidor
	string descricao;
	/// @brief Código de convite que é usado para entrar no servidor
	string codigoConvite;
	/// @brief Lista com os canais do servidor
	vector<Canal *> canais;
	/// @brief Lista com os ids dos usuários que participam do servidor
	vector<int> participantesIds;

public:
	/// @brief Construtor padrão do Servidor
	Servidor() = default;

	/// @brief Construtor do servidor
	/// @param nome Nome do servidor
	/// @param dono id do usuário que criou o servidor
	Servidor(string nome, int dono);
	/// @brief Função Get do atributo usuarioDonoId 
	/// @return id do criador do usuário
	int getUsuarioDonoId() const { return this->usuarioDonoId; }
	/// @brief Função Get do atributo nome
	/// @return Retorna o nome do servidor
	string getNome() const { return this->nome; }
	/// @brief Função Get do atributo descricao
	/// @return Retorna descrição do servidor
	string getDescricao() const { return this->descricao; }
	/// @brief Função Get do atributo codigoConvite
	/// @return Retorna o código do convite do servidor
	string getCondigoConvite() const { return this->codigoConvite; }

	/// @brief Função Set do atributo usuarioDonoId
	/// @param userId Valor que será salvo no atributo usuarioDonoId
	void setUsuarioDonoId(int userId);
	/// @brief Função set do atributo nome
	/// @param nome Valor que será salvo no atributo nome
	void setNome(string nome);
	/// @brief Função Set do atributo descricao
	/// @param descricao Valor que será salvo no atributo descricao
	void setDescricao(string descricao);
	/// @brief Função set do atributo codigoConvite
	/// @param codigoConvite Valor que será salvo no atributo codigoConvite
	void setCondigoConvite(string codigoConvite);

	/// @brief Inseri um usuário à lista de participantes
	/// @param id id do usuário que será inserido
	void inserirParticipante(int id);
	/// @brief Função que verifica se um usuário existe na lista de participantes
	/// @param id Id do usuário que será procurado
	/// @return Retorna valor booleano indicando se existe ou não o participante no servidor
	bool participanteExiste(int id);

	/// @brief Função Get da lista de participantes
	/// @return Cópia da lista de participantes
	vector<int> getParticipantesIds() const { return this->participantesIds; };
};