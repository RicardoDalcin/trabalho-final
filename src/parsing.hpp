// Standard libraries
#include <bits/stdc++.h>
#include <iostream>

// External libraries
#include "../include/parser.hpp"

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
void parsePlayers(PlayersTrie *playersTrie, PlayersHashTable *playersHashTable)
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
    }
    line++;
  }
}

// Parâmetros: TagHash *t_hash
void parseTag()
{
  ifstream f(TAGS_DATASET_PATH);
  CsvParser parser(f);

  vector<string> tags;
  vector<int> players_ids;
  vector<int> user_ids;

  int line = 0;

  for (auto &row : parser)
  {
    if (line)
    {
      int u_id = stoi(row[0]);
      int m_id = stoi(row[1]);
      string tag = row[2];

      // tags.push_back(tag);
      // players_ids.push_back(m_id);
      // user_ids.push_back(u_id);
    }
    line++;
  }

  //populateTagTrie(t_trie, tags, players_ids);
}

// Parâmetros: UserHash u_hash[], PlayersHash play_hash[]
void parseRatings()
{
  ifstream f(RATING_DATASET_PATH);
  CsvParser parser(f);

  vector<float> ratings;
  vector<int> user_ids;
  vector<int> players_ids;

  int line = 0;

  for (auto &row : parser)
  {
    if (line)
    {
      int u_id = stoi(row[0]);
      int p_id = stoi(row[1]);
      float ra = stof(row[2]);

      // ratings.push_back(ra);
      // players_ids.push_back(p_id);
      // user_ids.push_back(u_id);
    }
    line++;
  }
  // populateUserHash(u_hash, play_hash, ratings, players_ids, user_ids);
}

#endif