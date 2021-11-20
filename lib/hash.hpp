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
  int (*hashFunction)(TKey, int);

public:
  void insertItem(TKey key, T values);
  T *searchItem(TKey key);
  HashTable(int tableSize, int (*_hashFunction)(TKey, int));
};

template <class T, typename TKey>
HashTable<T, TKey>::HashTable(int tableSize, int (*_hashFunction)(TKey, int))
{
  size = tableSize;
  hashFunction = _hashFunction;
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
void HashTable<T, TKey>::insertItem(TKey key, T values)
{
  int hashKey = (*hashFunction)(key, size);

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
T *HashTable<T, TKey>::searchItem(TKey key)
{
  int hashKey = (*hashFunction)(key, size);

  entry<T, TKey> *node = hashTable[hashKey];

  if (node == NULL)
    return NULL;

  while (node->id != key)
  {
    node = node->nextEntry;

    if (node == NULL)
    {
      return NULL;
    }
  }

  return &node->value;
}

#endif