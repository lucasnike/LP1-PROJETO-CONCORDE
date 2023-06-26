#include "../include/Usuario.h"

Usuario::Usuario(int id, string nome, string email, string senha)
{
	this->id = id;
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
