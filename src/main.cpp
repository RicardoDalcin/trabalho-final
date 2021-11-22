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
#include "./console.hpp"

#pragma execution_character_set("utf-8")

using namespace std;

int main()
{
  SetConsoleOutputCP(65001);

  introduction();

  cin.get();

  PlayersTrie playersTrie;
  PlayersHashTable playersHashTable;
  PositionHashTable positionHashTable;
  UsersHashTable usersHashTable;

  Console console(&playersTrie, &playersHashTable);

  // // FASE 1 - CONSTRUCAO DAS ESTRUTURAS
  parseData(&playersTrie, &playersHashTable, &positionHashTable, &usersHashTable);

  // FASE 2 - MODO CONSOLE
  while (!console.shouldExit())
  {
    string command;

    cout << "> ";
    getline(cin, command);

    console.parseCommand(command);
  }

  return 0;
}