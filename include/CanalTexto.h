#include "Canal.h"
#include "Mensagem.h"
#include <vector>

#pragma once

class CanalTexto : public Canal
{
public:
	/// @brief Lista com todas as mensagens do canal
	vector<Mensagem> mensagens;

	// Herdado por meio de Canal

	/// @brief Função Get do atributo nome da classe base
	/// @return Nome do canal
	virtual string getNome() override;

	/// @brief Função Set do atributo nome da classe base
	/// @param nome Nome que será salvo
	virtual void setNome(string nome) override;

	/// @brief Retorta o tipo do canal
	/// @return "Texto"
	virtual string getTipo() override;

	/// @brief Construtor padrão
	CanalTexto() = default;

	/// @brief Construtor da classe
	/// @param nome Nome do canal de texto
	CanalTexto(string nome);
};