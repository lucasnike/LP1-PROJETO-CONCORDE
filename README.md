# CONCORDE CLI

Antes de tudo gostaria de deixar os link do [repositório do github](https://github.com/lucasnike/LP1-PROJETO-CONCORDE.git), e da [documentação do projeto](https://lucasnike.github.io/LP1-PROJETO-CONCORDE/) para consultas mais detalhadas.

## Discentes
| Nome                            | Matrícula   |
| ------------------------------- | ----------- |
| Lucas Vinicius Pereira da Silva | 20220060694 |
## O que é?

O projeto se trata de uma CLI(Comand line interface), totalmente programada em C++, que oferece ferramentas que simulam um "clone" do discorde, com o intuito de aprender a usar os recursos da linguagem c++. Esse projeto faz parte da terceira unidade da matéria LP1(Liguagem de programação 1) do curso BTI(Bacharelado em tecnologia da informação) da UFRN(Universidade federal do Rio Grande do Norte).

## Compilação
Para compilar e executar o projeto é necessário ter uma distribuição linux ou o WSL2 (Windows Subsystem for Linux), o compilador g++ do linux e o cmake.
Execute o comando a seguir para criar o arquivo **Makefile** que será usado para compilar todos os arquivos do projeto

```bash
cmake CMakeLists.txt
```
Logo em seguida execute o comando **make** para gerar o arquivo executável **concorde** 
```bash
make
```

Por fim, execute o comando seguinte para executar o sistema:
```bash
./concorde
```

## Comandos

### Comandos para usar sem estar logado

|    Comando    |  1°   |  2°   |  3°   | Descrição            |
| :-----------: | :---: | :---: | :---: | :------------------- |
|    `quit`     |       |       |       | Fecha o programa     |
| `create-user` | Email | Senha | Nome  | Cria um usuário      |
|    `login`    | Email | Senha |       | Faz login no sistema |

### Comandos para usar logado

|         Comando          |        1°        |          2°           |  3°   | Descrição                                                                      |
| :----------------------: | :--------------: | :-------------------: | :---: | :----------------------------------------------------------------------------- |
|       `disconnect`       |                  |                       |       | Desloga o usuário do sistema                                                   |
|     `create-server`      | Nome do servidor |                       |       | Cria um servidor com o nome informado                                          |
|    `set-server-desc`     | Nome do servidor | Descrição do servidor |       | Salva a descrição de um servidor                                               |
| `set-server-invite-code` | Nome do servidor |   Código de convite   |       | Configura o código de convite do servidor, que será usado para entrar no mesmo |
|      `list-servers`      |                  |                       |       | Mostra todos os servidores criados                                             |
|     `remove-server`      | Nome do servidor |                       |       | Remove um servidor do sistema                                                  |
|      `enter-server`      | Nome do servidor |  ? Código de convite  |       | Entra em um servidor                                                           |

### Comandos para usar ao enquanto estiver em um servidor

|       Comando       |        1°        |  2°   |  3°   | Descrição                                |
| :-----------------: | :--------------: | :---: | :---: | :--------------------------------------- |
|   `leave-server`    | Nome do servidor |       |       | Sai do servidor                          |
| `list-participants` |                  |       |       | Lista todos os participantes do servidor |