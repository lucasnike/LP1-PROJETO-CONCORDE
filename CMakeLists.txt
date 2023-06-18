# CMakeList.txt: projeto de CMake para Concorde, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Concorde")

# Adicione a origem ao executável deste projeto.
add_executable (Concorde "Concorde.cpp" "Concorde.h" "include/Usuario.h" "src/Usuario.cpp" "include/Mensagem.h" "src/Mensagem.cpp" "include/Canal.h" "include/CanalTexto.h" "src/CanalTexto.cpp" "include/CanalVoz.h" "src/CanalVoz.cpp" "include/Servidor.h" "src/Servidor.cpp" "include/Sistema.h" "src/Sistema.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Concorde PROPERTY CXX_STANDARD 20)
endif()

# TODO: Adicione testes e instale destinos, se necessário.
