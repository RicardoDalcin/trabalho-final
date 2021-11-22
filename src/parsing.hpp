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
#include "./tag.hpp"
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

// Quantidade de registros de cada arquivo para a barra de progresso
const int PLAYERS_DATA_SIZE = 18944;
const int TAGS_DATA_SIZE = 364950;
const int RATINGS_DATA_SIZE = 24188078;

const int TOTAL_DATA_SIZE = PLAYERS_DATA_SIZE + TAGS_DATA_SIZE + RATINGS_DATA_SIZE;

// Atualiza a barra de progresso a cada N registros
const int UPDATE_PROGRESS_EVERY = 100000;

// Faz o parse do arquivo CSV dos jogadores
// Insere os nomes na arvore Trie
// Insere os dados dos jogadores na hash table
// Adiciona o jogador nas suas posicoes na hash table
// Lida com a barra de progresso
void parsePlayers(PlayersTrie *playersTrie, PlayersHashTable *playersHashTable, PositionHashTable *positionHashTable, indicators::BlockProgressBar *bar)
{
  ifstream f(PLAYERS_DATASET_PATH);
  CsvParser parser(f);

  int line = 0;

  // altera o texto da barra de progresso
  bar->set_option(indicators::option::PostfixText{"Loading players 1/3"});

  for (auto &row : parser)
  {
    if (line)
    {
      // pega as informacoes da linha
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

      // instancia a classe jogador com as informacoes
      Player playerObject(id, name, positions);

      // insere o jogador na hash table
      playersHashTable->insert(id, playerObject);

      // insere o nome e id na arvore Trie
      playersTrie->insert(name, id);

      for (int i = 0; i < positions.size(); i++)
      {
        // busca a posicao atual na hash table
        Position *position = positionHashTable->search(positions[i]);

        // se nao existir, cria a posicao, adiciona o jogador e insere na hash table
        if (position == NULL)
        {
          vector<int> playerIds;
          playerIds.push_back(id);
          Position newPosition = Position(positions[i], playerIds);
          positionHashTable->insert(positions[i], newPosition);
        }
        // se ja existir, apenas adiciona o jogador
        else
        {
          position->addPlayer(id);
        }
      }

      // atualiza a barra de progresso a cada N registros
      if (line % UPDATE_PROGRESS_EVERY == 0)
        bar->tick();
    }

    line++;
  }
}

// Faz o parse do arquivo CSV das avaliacoes
// Insere os usuarios e suas avaliacoes na hash table de usuarios
// Atualiza a classificacao global dos jogadores
// Lida com a barra de progresso
void parseRatings(UsersHashTable *usersHashTable, PlayersHashTable *playersHashTable, indicators::BlockProgressBar *bar)
{
  ifstream f(RATING_DATASET_PATH);
  CsvParser parser(f);

  int line = 0;

  // altera o texto da barra de progresso
  bar->set_option(indicators::option::PostfixText{"Loading ratings 2/3"});

  for (auto &row : parser)
  {
    if (line)
    {
      // pega as informacoes da linha
      int userId = stoi(row[0]);
      int playerId = stoi(row[1]);
      float rating = stof(row[2]);

      // busca o jogador na hash table
      Player *player = playersHashTable->search(playerId);

      // se encontrar o jogador, adiciona a avaliacao
      if (player != NULL)
        player->addRating(rating);

      // instancia uma nova avaliacao
      Rating newRate = Rating(rating, playerId);

      // busca o usuario atual na hash table
      User *user = usersHashTable->search(userId);

      // se nao existir, cria um novo usuario, adiciona a avaliacao e insere na hash table
      if (user == NULL)
      {
        vector<Rating> ratingVec;
        ratingVec.push_back(newRate);
        User newUser = User(userId, ratingVec);
        usersHashTable->insert(userId, newUser);
      }
      // se existir, apenas adiciona a avaliacao
      else
      {
        user->addRating(newRate);
      }

      // atualiza a barra de progresso a cada N registros
      if ((line + PLAYERS_DATA_SIZE) % UPDATE_PROGRESS_EVERY == 0)
        bar->tick();
    }
    line++;
  }
}

// Faz o parse do arquivo CSV das tags
// Insere as tags e seus jogadores na hash table
// Lida com a barra de progresso
void parseTags(TagsHashTable *tagsHashTable, indicators::BlockProgressBar *bar)
{
  ifstream f(TAGS_DATASET_PATH);
  CsvParser parser(f);

  int line = 0;

  // altera o texto da barra de progresso
  bar->set_option(indicators::option::PostfixText{"Loading tags 3/3"});

  for (auto &row : parser)
  {
    if (line)
    {
      // pega as informacoes da linha
      int playerId = stoi(row[1]);
      string name = row[2];

      // busca a tag atual
      Tag *tag = tagsHashTable->search(name);

      // se existir, adiciona o jogador
      if (tag != NULL)
      {
        tag->addPlayer(playerId);
      }
      // se nao existir, instancia uma nova tag, adiciona o jogador e insere na hash table
      else
      {
        Tag newTag(name);
        newTag.addPlayer(playerId);

        tagsHashTable->insert(name, newTag);
      }

      // atualiza a barra de progresso a cada N registros
      if ((line + PLAYERS_DATA_SIZE + RATINGS_DATA_SIZE) % UPDATE_PROGRESS_EVERY == 0)
        bar->tick();
    }

    line++;
  }
}

// Faz o parse de todos os dados
// Lida com a contagem do tempo
// Cria e lida com a barra de progresso
void parseData(
    PlayersTrie *playersTrie,
    PlayersHashTable *playersHashTable,
    PositionHashTable *positionHashTable,
    UsersHashTable *usersHashTable,
    TagsHashTable *tagsHashTable)
{
  using namespace indicators;

  // esconde o cursor
  show_console_cursor(false);

  // instancia a barra de progresso
  BlockProgressBar bar{
      option::BarWidth{60},
      option::ForegroundColor{Color::white},
      option::FontStyles{std::vector<FontStyle>{FontStyle::bold}},
      option::MaxProgress{floor(TOTAL_DATA_SIZE / UPDATE_PROGRESS_EVERY)},
      option::Start{"[ "},
      option::End{" ]"},
      option::PrefixText{"             "}};

  // comeca a contagem de tempo
  const clock_t begin_time = clock();

  // chama as respectivas funcoes de parse
  parsePlayers(playersTrie, playersHashTable, positionHashTable, &bar);
  parseRatings(usersHashTable, playersHashTable, &bar);
  parseTags(tagsHashTable, &bar);

  // termina a contagem
  float t = float(clock() - begin_time) / CLOCKS_PER_SEC;

  // ao terminar, remove o texto da barra de progresso e marca como completo
  bar.set_option(option::PostfixText{""});
  bar.mark_as_completed();

  // exibe o tempo total
  cout << endl
       << "\t\t\t\tElapsed time: " << t << " seconds" << endl;

  // volta a exibir o cursor
  show_console_cursor(true);

  // espera um "enter"
  cin.get();

  // limpa o terminal
  system("cls");

  return;
}

#endif