#include <iostream>

using namespace std;

#pragma once

class Usuario
{
private:
	int id;
	string nome;
	string email;
	string senha;
public:
	Usuario();
	Usuario(int id, string nome, string email, string senha);

#pragma region GET FUNCTIONS
	int getId() const { return this->id; }
	string getEmail() const { return this->email; }
	string getNome() const { return this->nome; }
	string getSenha() const { return this->senha; }
#pragma endregion

#pragma region SET FUNCTIONS
	void setEmail(string email);
	void setNome(string nome);
	void setSenha(string senha);
#pragma endregion

};