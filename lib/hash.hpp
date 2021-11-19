#include <bits/stdc++.h>
#include <fstream>

#ifndef hash_h
#define hash_h

using namespace std;

template <class T, typename TKey>
struct entry
{
  TKey id;
  T value;
  struct entry<T, TKey> *nextEntry;
};

template <class T, typename TKey>
class HashTable
{
private:
  int size;
  entry<T, TKey> *createEntry(TKey key, T values);
  entry<T, TKey> **hashTable;

public:
  int hashFunction(TKey key);
  void insertItem(TKey key, T values);
  T searchItem(TKey key);
  HashTable(int tableSize);
};

template <class T, typename TKey>
HashTable<T, TKey>::HashTable(int tableSize)
{
  size = tableSize;
  hashTable = (entry<T, TKey> **)calloc(size, sizeof(entry<T, TKey> *));
}

template <class T, typename TKey>
entry<T, TKey> *HashTable<T, TKey>::createEntry(TKey key, T values)
{
  entry<T, TKey> *newNode = new entry<T, TKey>;

  newNode->id = key;
  newNode->nextEntry = NULL;
  newNode->value = values;

  return newNode;
}

template <class T, typename TKey>
int HashTable<T, TKey>::hashFunction(TKey key)
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

template <class T, typename TKey>
void HashTable<T, TKey>::insertItem(TKey key, T values)
{
  int hashKey = hashFunction(key);

  entry<T, TKey> *node = hashTable[hashKey];

  if (node == NULL)
  {
    hashTable[hashKey] = createEntry(key, values);
    return;
  }

  entry<T, TKey> *next;

  while (node != NULL)
  {
    next = node;
    node = next->nextEntry;
  }

  next->nextEntry = createEntry(key, values);
}

template <class T, typename TKey>
T HashTable<T, TKey>::searchItem(TKey key)
{
  int hashKey = hashFunction(key);

  entry<T, TKey> *node = hashTable[hashKey];

  if (node == NULL)
    return T();

  while (node->id != key)
  {
    node = node->nextEntry;

    if (node == NULL)
    {
      return T();
    }
  }

  return node->value;
}

#endif