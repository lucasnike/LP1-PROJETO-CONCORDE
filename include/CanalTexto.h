#include "Canal.h"
#include "Mensagem.h"
#include <vector>

#pragma once

class CanalTexto : public Canal
{
public:
	vector<Mensagem> mensagens;
	// Herdado por meio de Canal
	virtual string getNome() override;
	virtual void setNome(string nome) override;

	CanalTexto() = default;
};