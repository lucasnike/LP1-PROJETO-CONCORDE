#include <iostream>

using namespace std;

#pragma once

class Canal {
protected:
	string nome;
public:

	Canal() = default;
	Canal(const string& nome) : nome(nome) {}


	virtual string getNome() = 0;
	virtual void setNome(string nome) = 0;
};