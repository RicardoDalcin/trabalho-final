#include <bits/stdc++.h>
#include <fstream>

#include "../lib/hash.hpp"

#ifndef tag_h
#define tag_h

using namespace std;

// CLASSE TAG
// Guarda o nome da tag e os jogadores associados a ela
// Lida com a logica de adicionar um jogador novo na lista (pulando duplicatas)

class Tag
{
private:
  string name_;
  vector<int> playerIds_;

public:
  Tag(string name);
  Tag();

  const string name() const { return name_; }
  const vector<int> players() const { return playerIds_; }

  void addPlayer(int player);
};

Tag::Tag(string name)
{
  name_ = name;
  playerIds_.clear();
}

Tag::Tag()
{
  name_ = "";
  playerIds_.clear();
}

void Tag::addPlayer(int player)
{
  if (find(playerIds_.begin(), playerIds_.end(), player) == playerIds_.end())
    playerIds_.push_back(player);
}

// CLASSE DE HASH TABLE DOS TAGS
// Lida com a logica de hash table especifica das tags
// Define os tipos para a hash table generica e "exporta" as funcoes de insert e search
// Tambem define a hashing function e o tamanho da hash table

int TagHashingFunction(string key, int size)
{
  unsigned long longHash = 5381;
  int hash;

  for (char &currentChar : key)
  {
    longHash = ((longHash << 5) + longHash) + currentChar;
  }

  hash = longHash % size;

  return hash;
}

class TagsHashTable
{
private:
  HashTable<Tag, string> *hashTable_;

public:
  TagsHashTable();
  void insert(string key, Tag Tag);
  Tag *search(string key);
};

TagsHashTable::TagsHashTable()
{
  hashTable_ = new HashTable<Tag, string>(3889, TagHashingFunction);
}

void TagsHashTable::insert(string key, Tag Tag)
{
  hashTable_->insertItem(key, Tag);
}

Tag *TagsHashTable::search(string key)
{
  return hashTable_->searchItem(key);
}

#endif