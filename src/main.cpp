// Standard libraries
#include <bits/stdc++.h>
#include <iostream>

// Project libraries
#include "../lib/hash.hpp"
#include "../lib/trie.hpp"

// Logic libraries
#include "./parsing.hpp"
#include "./player.hpp"

using namespace std;

int main()
{
  PlayersTrie playersTrie;
  PlayersHashTable playersHashTable;

  // FASE 1 - CONSTRUCAO DAS ESTRUTURAS
  const clock_t begin_time = clock();
  parsePlayers(&playersTrie, &playersHashTable);
  // parseRatings();
  // parseTag();
  float t = float(clock() - begin_time) / CLOCKS_PER_SEC;

  // FASE 2 - MODO CONSOLE
  

  return 0;
}