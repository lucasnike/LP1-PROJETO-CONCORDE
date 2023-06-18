#include "../include/Usuario.h"

Usuario::Usuario()
{
}

Usuario::Usuario(string nome, string email, string senha)
{
	this->nome = nome;
	this->email = email;
	this->senha = senha;
}

void Usuario::setEmail(string email)
{
	this->email = email;
}

void Usuario::setNome(string nome)
{
	this->nome = nome;
}

void Usuario::setSenha(string senha)
{
	this->senha = senha;
}
