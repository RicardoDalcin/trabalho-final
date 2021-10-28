#include <bits/stdc++.h>
#include <iostream>

#include "../include/parser.hpp"

using namespace std;
using namespace aria::csv;

string DATASETS_FOLDER_PATH = "../datasets";

string MINIRATING_DATASET_PATH = DATASETS_FOLDER_PATH + "/minirating.csv";
string PLAYERS_DATASET_PATH = DATASETS_FOLDER_PATH + "/players.csv";
string RATING_DATASET_PATH = DATASETS_FOLDER_PATH + "/rating.csv";
string TAGS_DATASET_PATH = DATASETS_FOLDER_PATH + "/tags.csv";

int main()
{
  ifstream miniratingFile(MINIRATING_DATASET_PATH);

  CsvParser parser(miniratingFile);

  for (auto &row : parser)
  {
    for (auto &field : row)
    {
      cout << field << " | ";
    }
    cout << endl;
  }
}