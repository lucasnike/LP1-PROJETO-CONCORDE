cmake_minimum_required(VERSION 3.16)
project(teste VERSION 0.1 LANGUAGES CXX )

include_directories( include )


add_executable( concorde 
Concorde.cpp
src/CanalTexto.cpp
src/CanalVoz.cpp
src/Mensagem.cpp
src/Servidor.cpp
src/Sistema.cpp
src/Usuario.cpp
src/interns/TerminalColors.cpp
)