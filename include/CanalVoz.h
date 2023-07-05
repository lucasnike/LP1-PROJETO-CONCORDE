#include "Mensagem.h"
#include "Canal.h"

#pragma once

class CanalVoz : public Canal
{
private:
	/// @brief Guarda a última mensagem do canal de voz
	Mensagem ultimaMensagem;

public:
	/// @brief Construtor padrão
	CanalVoz() = default;

	/// @brief Construtor da classe
	/// @param nome Nome do canal
	CanalVoz(string nome);

	/// @brief Função Get do Nome do canal
	/// @return Nome do canal
	virtual string getNome() override;

	/// @brief Função Set do nome do canal
	/// @param nome Nome do canal que será salvo
	virtual void setNome(string nome) override;

	/// @brief Função que retorna a última mensagem enviada no canal
	/// @return Última mensagem enviada no canal de voz
	Mensagem getMensagem();

	/// @brief Configura a última mensagem enviada no canal de voz
	/// @param mensagem Mensagem que será salva
	void setMensagem(Mensagem mensagem);

	/// @brief Retorna o tipo do canal
	/// @return "Voz"
	virtual string getTipo() override;
};