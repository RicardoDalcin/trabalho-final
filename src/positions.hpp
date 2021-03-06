#include <bits/stdc++.h>
#include <fstream>

#include "../lib/hash.hpp"

#ifndef position_h
#define position_h

using namespace std;

// CLASSE Position
// Guarda o nome da posicao e a lista de jogadores associados a ela
// Implementa a logica de adicionar um novo jogador na lista

class Position
{
private:
  string position_;
  vector<int> playerIds_;

public:
  Position(string position, vector<int> playerIds);
  Position();

  const string position() const { return position_; }
  const vector<int> playerIds() const { return playerIds_; }

  void addPlayer(int playerId);
};

Position::Position(string position, vector<int> playerIds)
{
  position_ = position;
  playerIds_ = playerIds;
}

Position::Position()
{
  position_ = "";
}

void Position::addPlayer(int playerId)
{
  (this->playerIds_).push_back(playerId);
}

// CLASSE DE HASH TABLE DAS POSITIONS
// Lida com a logica de hash table especifica das posicoes
// Define os tipos para a hash table generica e "exporta" as funcoes de insert e search
// Tambem define a hashing function e o tamanho da hash table

int positionHashingFunction(string key, int size)
{
  int sum = 0;
  for (int i = 0; i < key.size(); i++)
  {
    sum += key[i];
  }

  return (sum + 1) % size;
}

class PositionHashTable
{
private:
  HashTable<Position, string> *hashTable_;

public:
  PositionHashTable();
  void insert(string key, Position position);
  Position *search(string key);
};

PositionHashTable::PositionHashTable()
{
  hashTable_ = new HashTable<Position, string>(29, positionHashingFunction);
}

void PositionHashTable::insert(string key, Position position)
{
  hashTable_->insertItem(key, position);
}

Position *PositionHashTable::search(string key)
{
  return hashTable_->searchItem(key);
}

#endif