#include <iostream>
#include <vector>

using namespace std;

#pragma once

/// @brief Lista com todos os comandos do sistema
const vector<string> COMANDOS = 
{ "login", "quit", "create-user", "disconnect", "create-server", "set-server-desc", 
"set-server-invite-code", "list-servers", "remove-server", "enter-server", "leave-server", 
"list-participants", "create-channel", "list-channels", "enter-channel", "leave-channel",
"send-message", "list-messages"};

/// @brief Lista com todos os comandos que podem ser executados enquanto o usuário está deslogado
const vector<string> COMANDOS_DESLOGADOS = 
{ "login", "quit", "create-user"};

/// @brief Lista com todos os comandos que podem ser executados enquanto o usuário está logado
const vector<string> COMANDOS_LOGADOS = 
{"disconnect", "create-server", "set-server-desc", "set-server-invite-code", 
"list-servers", "remove-server", "enter-server", "leave-server", "list-participants",
"create-channel", "list-channels", "enter-channel", "leave-channel", "send-message",
"list-messages"};