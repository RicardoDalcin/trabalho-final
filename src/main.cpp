#include <bits/stdc++.h>
#include <iostream>

#include "../include/parser.hpp"

#include "./lib/trie.hpp"

using namespace std;
using namespace aria::csv;

string DATASETS_FOLDER_PATH = "../datasets";

string MINIRATING_DATASET_PATH = DATASETS_FOLDER_PATH + "/minirating.csv";
string PLAYERS_DATASET_PATH = DATASETS_FOLDER_PATH + "/players.csv";
string RATING_DATASET_PATH = DATASETS_FOLDER_PATH + "/rating.csv";
string TAGS_DATASET_PATH = DATASETS_FOLDER_PATH + "/tags.csv";

// Funções de Parse
// parametros: PlayersTrie *play_trie, PositionsHash *pos_hash, PlayersHash play_hash[]
void parsePlayers(PlayersTrie *play_trie) {
  ifstream f(PLAYERS_DATASET_PATH);
  CsvParser parser(f);

  vector<string> players;
  vector<vector<string>> positions;
  vector<int> ids;

	int line = 0;

	for (auto& row : parser) {
		if(line) {
			int id = stoi(row[0]);
			string name = row[1];
			vector<string> pos;
			// separa a string com as posicoes em um vetor
			size_t first = 0;
			size_t sep = row[2].find(',',0);
			while(sep!=string::npos){
				pos.push_back(row[2].substr(first,sep-first));
				first = sep+1;
				sep = row[2].find(',',first);
			}
			pos.push_back(row[2].substr(first,row[2].length()));

			players.push_back(name);
			ids.push_back(id);
			positions.push_back(pos);
		}
		line++;
	}

  populatePlayersTrie(play_trie, players, ids);
  // populatePositionsHash(pos_hash, positions, ids);
  // populatePlayersHash(play_hash, players, ids, positions);
}

// Parâmetros: TagHash *t_hash
void parseTag(){
	ifstream f(TAGS_DATASET_PATH);
	CsvParser parser(f);
	
	vector<string> tags;
	vector<int> players_ids;
	vector<int> user_ids;
	
	int line = 0;
	
	for (auto& row : parser) {
		if(line) {
			int u_id = stoi(row[0]);
			int m_id = stoi(row[1]);
			string tag = row[2];
			
			tags.push_back(tag);
			players_ids.push_back(m_id);
			user_ids.push_back(u_id);
		}
		line++;
	}
	
	//populateTagTrie(t_trie, tags, players_ids);
}

// Parâmetros: UserHash u_hash[], PlayersHash play_hash[]
void parseRatings(){
  ifstream f(RATING_DATASET_PATH);
	CsvParser parser(f);
	
	vector<float> ratings;
	vector<int> user_ids;
	vector<int> players_ids;
	
	int line = 0;
	
	for (auto& row : parser) {
		if(line) {
			int u_id = stoi(row[0]);
			int p_id = stoi(row[1]);
			float ra = stof(row[2]);
			
			ratings.push_back(ra);
			players_ids.push_back(p_id);
			user_ids.push_back(u_id);
    }	
		line++;
	}
	// populateUserHash(u_hash, play_hash, ratings, players_ids, user_ids);
}

int main()
{
  PlayersTrie play_trie;

  const clock_t begin_time = clock();
  parsePlayers(&play_trie);
  parseRatings();
  parseTag();
  float t = float( clock () - begin_time ) /  CLOCKS_PER_SEC;

  cout << "Tempo de parsing" << t <<endl;

  return 0;
}