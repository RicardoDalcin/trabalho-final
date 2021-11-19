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

int main()
{
  HashTable<PlayerTest, string> hashTable(2000);

  PlayerTest player(12345, 19, "Ricardo Dalcin");
  PlayerTest *playerReturn;

  hashTable.insertItem("Teste", player);

  playerReturn = hashTable.searchItem("Teste");

  cout << playerReturn->toString() << endl;

  playerReturn->age = 45;

  cout << playerReturn->toString() << endl;

  playerReturn = hashTable.searchItem("TestAsdasde");

  if (playerReturn == NULL)
  {
    cout << "NULL" << endl;
  }
  else
  {
    cout << playerReturn->toString() << endl;
  }
}