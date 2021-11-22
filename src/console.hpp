// Standard libraries
#include <bits/stdc++.h>
#include <iostream>
#include <sstream>
#include <iomanip>

// Internal libraries
#include "../lib/trie.hpp"
#include "../lib/quicksort.hpp"
#include "../lib/sorting.hpp"

// Logic libraries
#include "./messages.hpp"
#include "./player.hpp"
#include "./users.hpp"
#include "./tag.hpp"
#include "./positions.hpp"

#ifndef console_h
#define console_h

using namespace std;

// FUNCOES HELPERS

template <typename T>
void printElement(T t, const int &width)
{
  cout << right << setw(width) << setfill(' ') << t;
}

void printCharWithSize(char toPrint, int width)
{
  for (int i = 1; i <= width; i++)
  {
    cout << toPrint;
  }
}

void printPlayerHeader()
{
  cout << endl;
  printElement("sofifa_id", 12);
  printElement("name", 48);
  printElement("player_positions", 24);
  printElement("rating", 12);
  printElement("count", 8);
  cout << endl;

  printCharWithSize('-', 12 + 48 + 24 + 12 + 8);
  cout << endl;
}

void printPlayerData(Player *player)
{
  printElement(player->id(), 12);
  printElement(player->name(), 48);
  printElement(player->positionsString(), 24);
  cout << fixed << setprecision(6);
  printElement(player->globalRating(), 12);
  printElement(player->ratingsCount(), 8);
  cout << endl;
}

void printPlayerData(Player player)
{
  printElement(player.id(), 12);
  printElement(player.name(), 48);
  printElement(player.positionsString(), 24);
  cout << fixed << setprecision(6);
  printElement(player.globalRating(), 12);
  printElement(player.ratingsCount(), 8);
  cout << endl;
}

void printUserHeader()
{
  cout << endl;
  printElement("sofifa_id", 12);
  printElement("name", 48);
  printElement("global_rating", 16);
  printElement("count", 8);
  printElement("rating", 8);
  cout << endl;

  printCharWithSize('-', 12 + 48 + 16 + 8 + 8);
  cout << endl;
}

void printUserRates(Player player, float rate)
{
  printElement(player.id(), 12);
  printElement(player.name(), 48);
  cout << fixed << setprecision(6);
  printElement(player.globalRating(), 16);
  printElement(player.ratingsCount(), 8);
  cout << fixed << setprecision(2);
  printElement(rate, 8);
  cout << endl;
}

bool isEmpty(string word)
{
  regex emptyString("([ ]*)");

  return regex_match(word.begin(), word.end(), emptyString);
}

bool isNumber(string word)
{
  regex numberString("([0-9]+)");

  return regex_match(word.begin(), word.end(), numberString);
}

vector<string> splitString(string word, char separator)
{
  vector<string> tokens;
  stringstream stream(word);
  string currentToken;

  while (getline(stream, currentToken, separator))
  {
    if (!isEmpty(currentToken))
      tokens.push_back(currentToken);
  }

  return tokens;
}

string parseArguments(string command)
{
  vector<string> tokens;
  stringstream stream(command);
  string currentToken;
  int i = 0;

  string argument;

  while (getline(stream, currentToken, ' '))
  {
    if (i > 0)
      tokens.push_back(currentToken);

    i++;
  }

  i = 0;

  for (auto token : tokens)
  {
    if (i == 0)
      argument = token;
    else
      argument = argument + " " + token;

    i++;
  }

  return argument;
}

string parseCommandName(string command)
{
  string commandOnly = command.substr(0, command.find(" "));

  return commandOnly;
}

vector<int> intersection(vector<int> &firstVector,
                         vector<int> &secondVector)
{
  vector<int> intersectionVector;

  int *firstArray = &firstVector[0];
  int *secondArray = &secondVector[0];

  basicQuicksort(firstArray, (int)firstVector.size());
  basicQuicksort(secondArray, (int)secondVector.size());

  set_intersection(firstVector.begin(), firstVector.end(),
                   secondVector.begin(), secondVector.end(),
                   back_inserter(intersectionVector));
  return intersectionVector;
}

// CLASSE DE COMMAND
// Lida com a logica de regex matching e execucao do comando

class Console;
class Command
{
private:
  regex matchExpression_;
  void (Console::*commandFunction_)(string);

public:
  Command(string expression, void (Console::*commandCallback)(string));
  bool match(string command);
  void run(Console *console, string command);
};

Command::Command(string expression, void (Console::*commandCallback)(string))
{
  matchExpression_ = regex(expression);
  commandFunction_ = commandCallback;
}

bool Command::match(string command)
{
  return regex_match(command.begin(), command.end(), matchExpression_);
}

void Command::run(Console *console, string command)
{
  (console->*commandFunction_)(command);
}

// CLASSE DE CONSOLE
// Registra, faz o parse e executa os comandos disponiveis
// A logica de cada comando se encontra nessa classe

class Console
{
private:
  bool shouldExit_;
  PlayersTrie *playersTrie_;
  PlayersHashTable *playersHashTable_;
  PositionHashTable *positionHashTable_;
  TagsHashTable *tagsHashTable_;
  UsersHashTable *userHashTable_;

  void playerCommand(string command);
  void userCommand(string command);
  void topCommand(string command);
  void tagsCommand(string command);
  void helpCommand(string command);
  void exitCommand(string command);

  void commandNotFound();

  vector<Command> commands;

public:
  Console(PlayersTrie *playersTrie, PlayersHashTable *playersHashTable, PositionHashTable *positionHashTable, UsersHashTable *userHashTable, TagsHashTable *tagsHashTable);

  const int shouldExit() const { return shouldExit_; }

  void parseCommand(string command);
};

// Configura as estruturas de dados recebidas (ja carregadas na fase 1)
// Registra os comandos disponiveis
Console::Console(PlayersTrie *playersTrie, PlayersHashTable *playersHashTable, PositionHashTable *positionHashTable, UsersHashTable *userHashTable, TagsHashTable *tagsHashTable)
{
  shouldExit_ = false;
  playersTrie_ = playersTrie;
  playersHashTable_ = playersHashTable;
  positionHashTable_ = positionHashTable;
  userHashTable_ = userHashTable;
  tagsHashTable_ = tagsHashTable;

  // Cada comando eh composto por um regex de identificacao e uma funcao callback
  commands.push_back(Command("(player)(?![^ ])(.*)", playerCommand));
  commands.push_back(Command("(user)(?![^ ])(.*)", userCommand));
  commands.push_back(Command("(top[0-9]+)(?![^ ])(.*)", topCommand));
  commands.push_back(Command("(tags)(?![^ ])(.*)", tagsCommand));
  commands.push_back(Command("(help)([ ]*)", helpCommand));
  commands.push_back(Command("(exit)([ ]*)", exitCommand));
}

// Faz o parse do comando recebido procurando se algum dos comandos registrados da match no regex
void Console::parseCommand(string command)
{
  if (command.length() == 0)
    return;

  for (Command consoleCommand : commands)
  {
    // Caso encontre o comando, executa
    if (consoleCommand.match(command))
    {
      consoleCommand.run(this, command);
      return;
    }
  }

  // Caso contrario, exibe uma mensagem de erro
  commandNotFound();
}

void Console::playerCommand(string command)
{
  string playerArgument = parseArguments(command);

  // se o argumento for vazio, mostra uma mensagem de erro
  if (isEmpty(playerArgument))
  {
    invalidArgumentsMessage();
    return;
  }

  // busca todos os jogadores com o prefixo informado
  vector<int> matchedPlayers = playersTrie_->prefixSearch(playerArgument);

  // se a lista for vazia, mostra a mensagem de nenhum dado encontrado
  if (!matchedPlayers.size())
  {
    noDataFoundMessage();
    return;
  }

  // se houver jogadores, exibe a tabela
  printPlayerHeader();

  for (auto playerId : matchedPlayers)
  {
    // busca o objeto do jogador na hash table
    Player *player = playersHashTable_->search(playerId);

    // caso o jogador existir, exibe
    if (player != NULL)
      printPlayerData(player);
  }

  cout << endl;
}

void Console::userCommand(string command)
{
  string userArgument = parseArguments(command);

  // se o argumento fornecido nao for um numero, mostra uma mensagem de erro
  if (!isNumber(userArgument))
  {
    invalidArgumentsMessage();
    return;
  }

  // converte o argumento para int
  int userId = stoi(userArgument);

  // busca o usuario na hash table
  User *user = userHashTable_->search(userId);

  // se nao encontrar o usuario, mostra uma mensagem de erro
  if (user == NULL)
  {
    userNotFound();
    return;
  }

  // se encontrar, pega as avaliacoes do usuario e aplica o sort
  vector<Rating> userRatings = user->rating();

  Rating ratingsArr[userRatings.size()];
  copy(userRatings.begin(), userRatings.end(), ratingsArr);

  int n = sizeof(ratingsArr) / sizeof(ratingsArr[0]);
  quickSortRatings(ratingsArr, 0, n - 1);

  vector<Player *> topPlayers;

  // mostra apenas as 20 maiores avaliacoes
  int topSize = 20;
  if (topSize > n)
  {
    topSize = n;
  }

  printUserHeader();

  for (int i = 0; i < topSize; i++)
  {
    int playerId = ratingsArr[n - 1 - i].playerId();
    float userRate = ratingsArr[n - 1 - i].rate();
    Player *player = playersHashTable_->search(playerId);

    if (player != NULL)
      printUserRates(*player, userRate);
  }

  cout << endl;
}

void Console::topCommand(string command)
{
  string positionArgument = parseArguments(command);
  string commandArgument = parseCommandName(command);

  // remove as aspas simples do argumento
  positionArgument.erase(remove(positionArgument.begin(), positionArgument.end(), '\''), positionArgument.end());

  // apaga a palavra "top" do comando
  commandArgument.erase(0, 3);

  // se o argumento for vazio ou o parametro nao for numero, mostra uma mensagem de erro
  if (isEmpty(positionArgument) || !isNumber(commandArgument))
  {
    invalidArgumentsMessage();
    return;
  }

  // converte o parametro para int
  int topSize = stoi(commandArgument);

  // se o parametro for 0, mostra uma mensagem de erro
  if (topSize == 0)
  {
    invalidArgumentsMessage();
    return;
  }

  // busca a posicao na hash table
  Position *positionObject = positionHashTable_->search(positionArgument);

  // se nao existir, mostra uma mensagem de erro
  if (positionObject == NULL)
  {
    positionNotFound();
    return;
  }

  // busca os jogadores da posicao
  vector<int> allPlayersIds = positionObject->playerIds();
  vector<Player> allPlayers;
  for (auto playerId : allPlayersIds)
  {
    Player *player = playersHashTable_->search(playerId);

    if (player != NULL)
    {
      // coloca todos os jogadores com mais de 1000 avaliacoes em um vetor
      if (player->ratingsCount() >= 1000)
      {
        allPlayers.push_back(*player);
      }
    }
  }

  Player playerArr[allPlayers.size()];

  // ordena os jogadores por media global
  for (int i = 0; i < allPlayers.size(); i++)
  {
    playerArr[i] = allPlayers[i];
  }

  int n = sizeof(playerArr) / sizeof(playerArr[0]);
  quickSortPlayers(playerArr, 0, n - 1);

  // se a quantidade requisitada for maior que o numero de jogadores, mostra uma mensagem de aviso
  if (topSize > n)
  {
    topSize = n;
    topValueTooBigMessage(topSize);
  }

  // exibe os N jogadores com melhor avaliacao
  printPlayerHeader();

  for (int i = 0; i < topSize; i++)
  {
    printPlayerData(playerArr[n - 1 - i]);
  }

  cout << endl;
}

void Console::tagsCommand(string command)
{
  string tagsArgument = parseArguments(command);

  vector<string> tags;

  vector<int> associatedPlayers;

  // se o argumento for vazio, mostra uma mensagem de erro
  if (isEmpty(tagsArgument))
  {
    invalidArgumentsMessage();
    return;
  }

  // faz o parse dos argumentos e coloca em um vetor
  istringstream iss(tagsArgument);
  string token;

  while (iss >> quoted(token, '\''))
    tags.push_back(token);

  associatedPlayers.clear();

  int i = 0;

  // para cada tag informada
  for (auto tag : tags)
  {
    // busca a tag
    Tag *searchTag = tagsHashTable_->search(tag);

    // se nao existir, mostra uma mensagem de erro
    if (searchTag == NULL)
    {
      noPlayerAssociated(tag);
      return;
    }

    // se for a primeira tag, popula o vetor com os jogadores
    if (i == 0)
    {
      for (auto player : searchTag->players())
        associatedPlayers.push_back(player);
    }
    // senao, faz a interseccao do vetor atual com o anterior
    else
    {
      vector<int> players = searchTag->players();
      associatedPlayers = intersection(associatedPlayers, players);
    }

    i++;
  }

  // se nao houver jogadores associados as tags, mostra uma mensagem de aviso
  if (!associatedPlayers.size())
  {
    noDataFoundMessage();
    return;
  }

  // exibe os jogadores associados
  printPlayerHeader();

  for (auto playerId : associatedPlayers)
  {
    Player *player = playersHashTable_->search(playerId);

    if (player != NULL)
      printPlayerData(player);
  }

  cout << endl;
}

void Console::exitCommand(string command)
{
  // liga a flag de saida
  shouldExit_ = true;
}

void Console::helpCommand(string command)
{
  // mostra a mensagem de ajuda
  helpMessage();
}

void Console::commandNotFound()
{
  // mostra a mensagem de comando nao encontrado
  commandNotFoundMessage();
}

#endif
