#include "CanalTexto.h"

string CanalTexto::getNome()
{
    return this->nome;
}

void CanalTexto::setNome(string nome)
{
    this->nome = nome;
}

string CanalTexto::getTipo()
{
    return "Texto";
}

CanalTexto::CanalTexto(string nome)
{
    this->nome = nome;
}
