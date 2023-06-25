#include <iostream>
#include <vector>

using namespace std;

#pragma once

const vector<string> COMANDOS = 
{ "login", "quit", "create-user", "disconnect", "create-server", "set-server-desc", 
"set-server-invite-code", "list-servers", "remove-server", "enter-server", "leave-server", 
"list-participants"};

const vector<string> COMANDOS_DESLOGADOS = 
{ "login", "quit", "create-user"};

const vector<string> COMANDOS_LOGADOS = 
{"disconnect", "create-server", "set-server-desc", "set-server-invite-code", 
"list-servers", "remove-server", "enter-server", "leave-server", "list-participants"};