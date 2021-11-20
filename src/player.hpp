#include <bits/stdc++.h>
#include <fstream>

#ifndef player_h
#define player_h

using namespace std;

// CLASSE PLAYER

class Player
{
private:
  int id_;
  string name_;
  vector<string> positions_;
  int ratingsCount_;
  double ratingsTotal_;

public:
  Player(int id, string name, vector<string> positions);
  Player();

  const int id() const { return id_; }
  const string name() const { return name_; }
  const vector<string> positions() const { return positions_; }

  void addRating(double rating);
  double globalRating();
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

void Player::addRating(double rating)
{
  ratingsCount_++;
  ratingsTotal_ += rating;
}

double Player::globalRating()
{
  return ratingsTotal_ / ratingsCount_;
}

// CLASSE DE HASH TABLE DOS PLAYERS

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