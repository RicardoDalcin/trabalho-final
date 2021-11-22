#include <bits/stdc++.h>
#include <fstream>

#include "../lib/hash.hpp"

#ifndef player_h
#define player_h

using namespace std;

// CLASSE PLAYER
// Guarda as informacoes principais do jogador (nome, id, posicoes, avaliacao total e quantidade de avaliacoes)
// Lida com a logica de avaliacoes (adiciona avaliacao e calcula media global)

class Player
{
private:
  int id_;
  string name_;
  vector<string> positions_;
  int ratingsCount_;
  float ratingsTotal_;

public:
  Player(int id, string name, vector<string> positions);
  Player();

  const int id() const { return id_; }
  const string name() const { return name_; }
  const vector<string> positions() const { return positions_; }
  const int ratingsCount() const { return ratingsCount_; }

  string positionsString();
  void addRating(float rating);
  float globalRating();
};

Player::Player(int id, string name, vector<string> positions)
{
  id_ = id;
  name_ = name;
  positions_ = positions;
  ratingsCount_ = 0;
  ratingsTotal_ = 0;
}

Player::Player()
{
  id_ = 0;
  name_ = "";
  ratingsCount_ = 0;
  ratingsTotal_ = 0;
}

string Player::positionsString()
{
  string positionsValue;

  int i = 0;

  for (auto position : positions_)
  {
    if (i == 0)
      positionsValue = position;
    else
      positionsValue = positionsValue + ", " + position;

    i++;
  }

  return positionsValue;
}

void Player::addRating(float rating)
{
  ratingsCount_++;
  ratingsTotal_ += rating;
}

float Player::globalRating()
{
  return ratingsTotal_ / ratingsCount_;
}

// CLASSE DE HASH TABLE DOS PLAYERS
// Lida com a logica de hash table especifica dos jogadores
// Define os tipos para a hash table generica e "exporta" as funcoes de insert e search
// Tambem define a hashing function e o tamanho da hash table

int playerHashingFunction(int key, int size)
{
  return (key + 1) % size;
}

class PlayersHashTable
{
private:
  HashTable<Player, int> *hashTable_;

public:
  PlayersHashTable();
  void insert(int key, Player player);
  Player *search(int key);
};

PlayersHashTable::PlayersHashTable()
{
  hashTable_ = new HashTable<Player, int>(3889, playerHashingFunction);
}

void PlayersHashTable::insert(int key, Player player)
{
  hashTable_->insertItem(key, player);
}

Player *PlayersHashTable::search(int key)
{
  return hashTable_->searchItem(key);
}

#endif