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
#include "./users.hpp"
#include "./positions.hpp"

#ifndef parsing_h
#define parsing_h

using namespace std;
using namespace aria::csv;

string DATASETS_FOLDER_PATH = "../datasets";

string MINIRATING_DATASET_PATH = DATASETS_FOLDER_PATH + "/minirating.csv";
string PLAYERS_DATASET_PATH = DATASETS_FOLDER_PATH + "/players.csv";
string RATING_DATASET_PATH = DATASETS_FOLDER_PATH + "/rating.csv";
string TAGS_DATASET_PATH = DATASETS_FOLDER_PATH + "/tags.csv";

const int PLAYERS_DATA_SIZE = 18944;
const int TAGS_DATA_SIZE = 364950;
const int RATINGS_DATA_SIZE = 24188078;

const int TOTAL_DATA_SIZE = PLAYERS_DATA_SIZE + TAGS_DATA_SIZE + RATINGS_DATA_SIZE;

const int UPDATE_PROGRESS_EVERY = 100000;

// Funções de Parse
// parametros: PlayersTrie *playersTrie, PositionsHash *pos_hash, PlayersHash play_hash[]
void parsePlayers(PlayersTrie *playersTrie, PlayersHashTable *playersHashTable, PositionHashTable *positionHashTable, indicators::BlockProgressBar *bar)
{
  ifstream f(PLAYERS_DATASET_PATH);
  CsvParser parser(f);

  int line = 0;

  bar->set_option(indicators::option::PostfixText{"Loading players 1/3"});

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

      for (int i = 0; i < positions.size(); i++)
      {
        Position *position = positionHashTable->search(positions[i]);
        if (position == NULL)
        {
          vector<int> playerIds;
          playerIds.push_back(id);
          Position newPosition = Position(positions[i], playerIds);
          positionHashTable->insert(positions[i], newPosition);
        }
        else
        {
          position->addPlayer(id);
        }
      }

      if (line % UPDATE_PROGRESS_EVERY == 0)
        bar->tick();
    }

    line++;
  }
}

// Parâmetros: UserHash u_hash[], PlayersHash play_hash[]
void parseRatings(UsersHashTable *usersHashTable, PlayersHashTable *playersHashTable, indicators::BlockProgressBar *bar)
{
  ifstream f(RATING_DATASET_PATH);
  CsvParser parser(f);

  int line = 0;

  bar->set_option(indicators::option::PostfixText{"Loading ratings 2/3"});

  for (auto &row : parser)
  {
    if (line)
    {
      int userId = stoi(row[0]);
      int playerId = stoi(row[1]);
      float rating = stof(row[2]);

      Player *player = playersHashTable->search(playerId);
      player->addRating(rating);
      Rating newRate = Rating(rating, playerId);

      User *user = usersHashTable->search(userId);
      if (user == NULL)
      {
        vector<Rating> ratingVec;
        ratingVec.push_back(newRate);
        User newUser = User(userId, ratingVec);
        usersHashTable->insert(userId, newUser);
      }
      else
      {
        user->addRating(newRate);
      }

      if ((line + PLAYERS_DATA_SIZE) % UPDATE_PROGRESS_EVERY == 0)
        bar->tick();
    }
    line++;
  }
}

// Parâmetros: TagHash *t_hash
void parseTags(indicators::BlockProgressBar *bar)
{
  ifstream f(TAGS_DATASET_PATH);
  CsvParser parser(f);

  int line = 0;

  bar->set_option(indicators::option::PostfixText{"Loading tags 3/3"});

  for (auto &row : parser)
  {
    if (line)
    {
      int userId = stoi(row[0]);
      int playerId = stoi(row[1]);
      string tag = row[2];

      if ((line + PLAYERS_DATA_SIZE + RATINGS_DATA_SIZE) % UPDATE_PROGRESS_EVERY == 0)
        bar->tick();
    }

    line++;
  }

  //populateTagTrie(t_trie, tags, players_ids);
}

void parseData(PlayersTrie *playersTrie, PlayersHashTable *playersHashTable, PositionHashTable *positionHashTable, UsersHashTable *usersHashTable)
{
  indicators::show_console_cursor(false);

  system("cls");

  using namespace indicators;

  BlockProgressBar bar{
      option::BarWidth{60},
      option::ForegroundColor{Color::white},
      option::FontStyles{std::vector<FontStyle>{FontStyle::bold}},
      option::MaxProgress{floor(TOTAL_DATA_SIZE / UPDATE_PROGRESS_EVERY)},
      option::Start{"[ "},
      option::End{" ]"}};

  const clock_t begin_time = clock();

  parsePlayers(playersTrie, playersHashTable, positionHashTable, &bar);
  parseRatings(usersHashTable, playersHashTable, &bar);
  parseTags(&bar);

  bar.set_option(option::PostfixText{""});
  bar.mark_as_completed();

  float t = float(clock() - begin_time) / CLOCKS_PER_SEC;

  cout << "Elapsed time: " << t << " seconds" << endl;

  indicators::show_console_cursor(true);

  cin.get();

  system("cls");

  return;
}

#endif