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
	virtual string getNome() override;
	virtual void setNome(string nome) override;

	/// @brief Construtor padrão
	CanalTexto() = default;
};