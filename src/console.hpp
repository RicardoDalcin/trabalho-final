// Standard libraries
#include <bits/stdc++.h>
#include <iostream>

// Internal libraries
#include "../lib/trie.hpp"

// Logic libraries
#include "./messages.hpp"
#include "./player.hpp"

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

// CLASSE DE COMMAND

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

class Console
{
private:
  bool shouldExit_;
  PlayersTrie *playersTrie_;
  PlayersHashTable *playersHashTable_;

  void playerCommand(string command);
  void userCommand(string command);
  void topCommand(string command);
  void tagsCommand(string command);
  void helpCommand(string command);
  void exitCommand(string command);

  void commandNotFound();

  vector<Command> commands;

public:
  Console(PlayersTrie *playersTrie, PlayersHashTable *playersHashTable);

  const int shouldExit() const { return shouldExit_; }

  void parseCommand(string command);
};

Console::Console(PlayersTrie *playersTrie, PlayersHashTable *playersHashTable)
{
  shouldExit_ = false;
  playersTrie_ = playersTrie;
  playersHashTable_ = playersHashTable;

  commands.push_back(Command("(player)(?![^ ])(.*)", playerCommand));
  commands.push_back(Command("(user)(?![^ ])(.*)", userCommand));
  commands.push_back(Command("(top[0-9]+)(?![^ ])(.*)", topCommand));
  commands.push_back(Command("(tags)(?![^ ])(.*)", tagsCommand));
  commands.push_back(Command("(help)([ ]*)", helpCommand));
  commands.push_back(Command("(exit)([ ]*)", exitCommand));
}

void Console::parseCommand(string command)
{
  if (command.length() == 0)
    return;

  for (Command consoleCommand : commands)
  {
    if (consoleCommand.match(command))
    {
      consoleCommand.run(this, command);
      return;
    }
  }

  commandNotFound();
}

void Console::playerCommand(string command)
{
  string playerArgument = parseArguments(command);

  if (isEmpty(playerArgument))
  {
    invalidArgumentsMessage();
    return;
  }

  vector<int> matchedPlayers = playersTrie_->prefixSearch(playerArgument);

  if (!matchedPlayers.size())
  {
    noDataFoundMessage();
    return;
  }

  printPlayerHeader();

  for (auto playerId : matchedPlayers)
  {
    Player *player = playersHashTable_->search(playerId);

    if (player != NULL)
      printPlayerData(player);
  }

  cout << endl;
}

void Console::userCommand(string command)
{
  string userArgument = parseArguments(command);

  if (!isNumber(userArgument))
  {
    invalidArgumentsMessage();
    return;
  }

  int userId = stoi(userArgument);

  cout << endl
       << "USERID: <" << userId << ">";

  cout << endl;
}

void Console::topCommand(string command)
{
  string positionArgument = parseArguments(command);
  string commandArgument = parseCommandName(command);

  positionArgument.erase(remove(positionArgument.begin(), positionArgument.end(), '\''), positionArgument.end());

  commandArgument.erase(0, 3);

  if (isEmpty(positionArgument) || !isNumber(commandArgument))
  {
    invalidArgumentsMessage();
    return;
  }

  int topSize = stoi(commandArgument);

  if (topSize == 0)
  {
    invalidArgumentsMessage();
    return;
  }

  cout << endl
       << "TOP N: <" << topSize << ">" << endl
       << "POSITION: <" << positionArgument << ">" << endl
       << endl;

  cout << endl;
}

void Console::tagsCommand(string command)
{
  string tagsArgument = parseArguments(command);

  vector<string> positions;

  if (isEmpty(tagsArgument))
  {
    invalidArgumentsMessage();
    return;
  }

  positions = splitString(tagsArgument, ' ');

  for (auto &position : positions)
    position.erase(remove(position.begin(), position.end(), '\''), position.end());

  cout << endl;
}

void Console::exitCommand(string command)
{
  shouldExit_ = true;
}

void Console::helpCommand(string command)
{
  helpMessage();
}

void Console::commandNotFound()
{
  commandNotFoundMessage();
}

#endif