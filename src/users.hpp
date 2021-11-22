#include <bits/stdc++.h>
#include <fstream>

#include "../lib/hash.hpp"

#ifndef user_h
#define user_h

using namespace std;

// CLASSE RATING
class Rating
{
private:
    float rate_;
    int player_id_;

public:
    Rating(float rate, int id);
    Rating();

    const float rate() const { return rate_; }
    const int playerId() const { return player_id_; }
};

Rating::Rating(float rate, int id)
{
  rate_ = rate;
  player_id_ = id;
}

Rating::Rating()
{
  rate_ = 0;
  player_id_ = 0;
}

// CLASSE USER

class User
{
private:
  int id_;
  vector<Rating> rating_;

public:
  User(int id, vector<Rating> rating);
  User();

  const int id() const { return id_; }
  const vector<Rating> rating() const { return rating_; }

  void addRating(Rating newRate);
};

User::User(int id, vector<Rating> rating)
{
  id_ = id;
  rating_ = rating;
}

User::User()
{
  id_ = 0;
}

void User::addRating(Rating newRate)
{
  (this->rating_).push_back(newRate);
}

// CLASSE DE HASH TABLE DOS USERS

int userHashingFunction(int key, int size)
{
  return (key + 1) % size;
}

class UsersHashTable
{
private:
  HashTable<User, int> *hashTable_;

public:
  UsersHashTable();
  void insert(int key, User user);
  User *search(int key);
};

UsersHashTable::UsersHashTable()
{
  hashTable_ = new HashTable<User, int>(33238, userHashingFunction);
}

void UsersHashTable::insert(int key, User user)
{
  hashTable_->insertItem(key, user);
}

User *UsersHashTable::search(int key)
{
  return hashTable_->searchItem(key);
}

#endif