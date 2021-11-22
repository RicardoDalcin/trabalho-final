#include <vector>
#include <algorithm>
#include <string>

#ifndef trie_h
#define trie_h

#define ALPH_SIZE 31    // 'a'-'z', ' ', '-', '.', '\'', '"'
#define ASCII_OFFSET 97 // 'a'

using namespace std;

// Players
class PlayersTrie
{
public:
  PlayersTrie *children[ALPH_SIZE];
  bool final; // se alguma palavra termina nesse nodo
  int PlayersId;

  PlayersTrie();
  void insert(string Player, int id);
  int search(string Player);
  vector<int> prefixSearch(string arg);
};

// -------------------------------------------
//      mapeamento de todos char's usados
// -------------------------------------------
int trieIndex(char c)
{
  switch (c)
  {
  case '\'':
    return 26;
  case ' ':
    return 27;
  case '-':
    return 28;
  case '.':
    return 29;
  case '"':
    return 30;
  default:
    if (c >= 'A' && c <= 'Z')
    {
      return c - 'A';
    }
    if (c >= 'a' && c <= 'z')
    {
      int to_upper = 'A' - 'a';
      return c + to_upper - 'A';
    }
    else
      return -1;
  }
}

// ----------- Players -----------------
PlayersTrie::PlayersTrie()
{
  final = false;
  // nulo em todos filhos
  for (int i = 0; i < ALPH_SIZE; i++)
  {
    children[i] = NULL;
  }
  PlayersId = 0;
}

void PlayersTrie::insert(string Players, int id)
{
  PlayersTrie *aux = this;
  char c;

  for (int i = 0; i < Players.length(); i++)
  {

    // index dentro da arvore
    c = Players[i];
    int index = trieIndex(c);

    if (!aux->children[index])
    {
      // indice nao ocupado, cria outro nodo
      aux->children[index] = new PlayersTrie();
      aux = aux->children[index];
    }
    else
    {
      // indice ocupado, anda para proximo
      aux = aux->children[index];
    }
  }
  // terminou de varrer a palavra, setar folha como final
  aux->final = true;
  aux->PlayersId = id;
}

bool isLastPlayers(PlayersTrie *p)
{
  for (int i = 0; i < ALPH_SIZE; i++)
  {
    if (p->children[i])
      return false;
  }
  return true;
}

int PlayersTrie::search(string Players)
{

  PlayersTrie *aux = this;
  char c;

  for (int i = 0; i < Players.length(); i++)
  {
    c = Players[i];
    int index = trieIndex(c);

    if (!aux->children[index])
    {
      // n existe, retorna false
      return -1;
    }
    else
    {
      // existe, anda proximo
      aux = aux->children[index];
    }
  }

  // varreu toda palavra
  // pode ser nodo nulo (n encontrou)
  // se nodo n é nulo, ver se é final
  // se for final, encontrou retorna true
  if (aux == NULL || !aux->final || aux->PlayersId == 0)
    return -1;
  return aux->PlayersId;
}

void collectPlayers(PlayersTrie *root, vector<int> *ids)
{

  PlayersTrie *aux = root;

  // base da recursao
  if (aux->final)
    ids->push_back(aux->PlayersId);

  //passo
  for (int i = 0; i < ALPH_SIZE; i++)
  {
    if (aux->children[i])
      collectPlayers(aux->children[i], ids);
  }
}

vector<int> PlayersTrie::prefixSearch(string arg)
{

  PlayersTrie *aux = this;
  vector<int> v;
  char c;

  for (int i = 0; i < arg.length(); i++)
  {
    c = arg[i];
    int index = trieIndex(c);

    if (!aux->children[index])
    {
      // n existe, retorna false
      return v;
    }

    if (aux->children[index])
    {
      // existe, anda proximo
      aux = aux->children[index];
    }
  }

  // parou de percorrer
  // nesse ponto, aux é a 'raiz' da busca
  collectPlayers(aux, &v);

  return v;
}

void populatePlayersTrie(PlayersTrie *p_trie, vector<string> Players, vector<int> ids)
{
  for (int i = 0; i < Players.size(); ++i)
  {
    p_trie->insert(Players[i], ids[i]);
  }
}

#endif