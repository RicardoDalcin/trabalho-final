// Standard libraries
#include <bits/stdc++.h>
#include <iostream>

// Internal libraries
#include "../lib/trie.hpp"

// Logic libraries
#include "./player.hpp"

#ifndef console_h
#define console_h

using namespace std;

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
  commands.push_back(Command("(top[1-9]+)(?![^ ])(.*)", topCommand));
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
}

void Console::userCommand(string command)
{
  cout << endl
       << "Command not implemented" << endl
       << command << endl
       << endl;
}

void Console::topCommand(string command)
{
  cout << endl
       << "Command not implemented" << endl
       << command << endl
       << endl;
}

void Console::tagsCommand(string command)
{
  cout << endl
       << "Command not implemented" << endl
       << command << endl
       << endl;
}

void Console::exitCommand(string command)
{
  shouldExit_ = true;
}

void Console::helpCommand(string command)
{
  cout << endl
       << "Help command placeholder" << endl
       << endl;
}

void Console::commandNotFound()
{
  cout << endl
       << "Command not found" << endl
       << "Use the 'help' command for more information" << endl
       << endl;
}

#endif