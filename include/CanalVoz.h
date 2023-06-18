#include "Mensagem.h"
#include "Canal.h"

#pragma once

class CanalVoz : public Canal
{
private:
	Mensagem ultimaMensagem;

public:
	CanalVoz() = default;
	CanalVoz(const Mensagem& ultimaMensagem) : ultimaMensagem(ultimaMensagem) {}

	virtual string getNome() override;
	virtual void setNome(string nome) override;

	Mensagem getMensagem();
	void setMensagem(Mensagem mensagem);

};