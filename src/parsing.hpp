// Standard libraries
#include <bits/stdc++.h>
#include <iostream>
#include <windows.h>
#include <chrono>
#include <thread>

// External libraries
#include "../include/parser.hpp"
#include "../include/indicators.hpp"

// Project libraries
#include "../lib/trie.hpp"

// Logic libraries
#include "./player.hpp"

#ifndef parsing_h
#define parsing_h

using namespace std;
using namespace aria::csv;

string DATASETS_FOLDER_PATH = "../datasets";

string MINIRATING_DATASET_PATH = DATASETS_FOLDER_PATH + "/minirating.csv";
string PLAYERS_DATASET_PATH = DATASETS_FOLDER_PATH + "/players.csv";
string RATING_DATASET_PATH = DATASETS_FOLDER_PATH + "/rating.csv";
string TAGS_DATASET_PATH = DATASETS_FOLDER_PATH + "/tags.csv";

// Funções de Parse
// parametros: PlayersTrie *playersTrie, PositionsHash *pos_hash, PlayersHash play_hash[]
void parsePlayers(PlayersTrie *playersTrie, PlayersHashTable *playersHashTable, indicators::BlockProgressBar *bar)
{
  ifstream f(PLAYERS_DATASET_PATH);
  CsvParser parser(f);

  int line = 0;

  for (auto &row : parser)
  {
    if (line)
    {
      int id = stoi(row[0]);
      string name = row[1];
      vector<string> positions;

      // separa a string com as posicoes em um vetor
      size_t first = 0;
      size_t separator = row[2].find(", ", 0);

      while (separator != string::npos)
      {
        positions.push_back(row[2].substr(first, separator - first));
        first = separator + 2;
        separator = row[2].find(", ", first);
      }
      positions.push_back(row[2].substr(first, row[2].length()));

      Player playerObject(id, name, positions);

      playersHashTable->insert(id, playerObject);

      playersTrie->insert(name, id);

      if (line % 100000 == 0)
        bar->tick();
    }

    line++;
  }
}

// Parâmetros: TagHash *t_hash
void parseTag()
{
  ifstream f(TAGS_DATASET_PATH);
  CsvParser parser(f);

  int line = 0;

  for (auto &row : parser)
  {
    if (line)
    {
      int userId = stoi(row[0]);
      int playerId = stoi(row[1]);
      string tag = row[2];
    }

    line++;
  }

  //populateTagTrie(t_trie, tags, players_ids);
}

// Parâmetros: UserHash u_hash[], PlayersHash play_hash[]
void parseRatings(PlayersHashTable *playersHashTable, indicators::BlockProgressBar *bar)
{
  ifstream f(RATING_DATASET_PATH);
  CsvParser parser(f);

  int line = 0;

  for (auto &row : parser)
  {
    if (line)
    {
      int userId = stoi(row[0]);
      int playerId = stoi(row[1]);
      float rating = stof(row[2]);

      Player *player = playersHashTable->search(playerId);
      player->addRating(rating);

      // ratings.push_back(ra);
      // players_ids.push_back(p_id);
      // user_ids.push_back(u_id);

      if ((line + 18944) % 100000 == 0)
        bar->tick();
    }
    line++;
  }
  // populateUserHash(u_hash, play_hash, ratings, players_ids, user_ids);
}

void parseData(PlayersTrie *playersTrie, PlayersHashTable *playersHashTable)
{
  // Hide cursor
  indicators::show_console_cursor(false);

  using namespace indicators;
  BlockProgressBar bar{
      option::BarWidth{80},
      option::ForegroundColor{Color::white},
      option::FontStyles{
          std::vector<FontStyle>{FontStyle::bold}},
      option::MaxProgress{242}};

  const clock_t begin_time = clock();

  parsePlayers(playersTrie, playersHashTable, &bar);
  parseRatings(playersHashTable, &bar);
  // parseTag();

  bar.mark_as_completed();

  // // Show cursor
  // indicators::show_console_cursor(true);

  float t = float(clock() - begin_time) / CLOCKS_PER_SEC;

  cout << "Elapsed time: " << t << " seconds" << endl;

  return;
}

#endif