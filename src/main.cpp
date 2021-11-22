// Standard libraries
#include <bits/stdc++.h>
#include <iostream>

// Project libraries
#include "../lib/hash.hpp"
#include "../lib/trie.hpp"

// Logic libraries
#include "./interface.hpp"
#include "./parsing.hpp"
#include "./player.hpp"
#include "./positions.hpp"
#include "./users.hpp"
#include "./tag.hpp"
#include "./console.hpp"

#pragma execution_character_set("utf-8")

using namespace std;

int main()
{
  // arruma o encoding de output para suportar acentuacao
  SetConsoleOutputCP(65001);

  // mostra a introducao
  introduction();

  // espera um "enter"
  cin.get();

  // instancia as estruturas de dados necessarias
  PlayersTrie playersTrie;
  PlayersHashTable playersHashTable;
  PositionHashTable positionHashTable;
  UsersHashTable usersHashTable;
  TagsHashTable tagsHashTable;

  // instancia o console passando as referencias para as estruturas
  Console console(&playersTrie, &playersHashTable, &positionHashTable, &usersHashTable, &tagsHashTable);

  // FASE 1 - CONSTRUCAO DAS ESTRUTURAS
  parseData(&playersTrie, &playersHashTable, &positionHashTable, &usersHashTable, &tagsHashTable);

  // FASE 2 - MODO CONSOLE
  while (!console.shouldExit())
  {
    string command;

    // pega o comando via input do usuario
    cout << "> ";
    getline(cin, command);

    // faz o parse do comando na classe Console
    console.parseCommand(command);
  }

  return 0;
}