// Standard libraries
#include <bits/stdc++.h>
#include <iostream>

// External libraries
#include "../include/parser.hpp"

// Project libraries
#include "../lib/hash.hpp"

// Test
#include "./teste.hpp"

using namespace std;
using namespace aria::csv;

string DATASETS_FOLDER_PATH = "../datasets";

string MINIRATING_DATASET_PATH = DATASETS_FOLDER_PATH + "/minirating.csv";
string PLAYERS_DATASET_PATH = DATASETS_FOLDER_PATH + "/players.csv";
string RATING_DATASET_PATH = DATASETS_FOLDER_PATH + "/rating.csv";
string TAGS_DATASET_PATH = DATASETS_FOLDER_PATH + "/tags.csv";

// typedef struct teste
// {
//   int id;
//   string name;
//   int age;
// } teste;

int main()
{
  // ifstream miniratingFile(MINIRATING_DATASET_PATH);

  // CsvParser parser(miniratingFile);

  // for (auto &row : parser)
  // {
  //   for (auto &field : row)
  //   {
  //     cout << field << " | ";
  //   }
  //   cout << endl;
  // }

  HashTable<PlayerTest, string> hashTable(2000);

  // teste *player = new teste;
  // teste *playerReturn = new teste;

  // player->age = 19;
  // player->name = "Ricardo Dalcin";
  // player->id = 12345;

  PlayerTest player(12345, 19, "Ricardo Dalcin");
  PlayerTest playerReturn;

  hashTable.insertItem("Teste", player);

  playerReturn = hashTable.searchItem("Teste");

  cout << playerReturn.toString() << endl;

  // HashTable<int, string> intHashTable(2000);

  // int intTeste = 50;

  // intHashTable.insertItem("Chave do Teste", (int *)intTeste);

  // cout << intHashTable.searchItem("Chave do Teste");
}