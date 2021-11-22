// Standard libraries
#include <bits/stdc++.h>
#include <iostream>

#ifndef messages_h
#define messages_h

using namespace std;

void helpMessage()
{
  cout << endl
       << "  Commands documentation" << endl
       << endl;

  cout << "    player <name or prefix>" << endl;
  cout << "\t- Returns the list of players whose names begins with or is equal to the parameter provided" << endl;
  cout << "\t- Example: player Cris" << endl;
  cout << endl;

  cout << "    user <userID>" << endl;
  cout << "\t- Returns the list of players rated by the user (20 max.), ordered from highest to lowest rating" << endl;
  cout << "\t- Example: user 51" << endl;
  cout << endl;

  cout << "    top<N> '<position>'" << endl;
  cout << "\t- Returns the list of the top N players in a given position, ordered from highest to lowest rating" << endl;
  cout << "\t- Only considers players with at least 1000 ratings" << endl;
  cout << "\t- Example: top50 'ST'" << endl;
  cout << endl;

  cout << "    tags <list of tags>" << endl;
  cout << "\t- Returns the list of players associated with a set of tags" << endl;
  cout << "\t- Example: tags 'Brazil' 'Dribbler'" << endl;
  cout << endl;

  cout << "    help" << endl;
  cout << "\t- List commands and documentation" << endl;
  cout << endl;

  cout << "    exit" << endl;
  cout << "\t- Quit the console" << endl;
  cout << endl;
}

void noDataFoundMessage()
{
  cout << endl
       << "  No players found with given parameter" << endl
       << endl;
}

void noPlayerAssociated(string tag)
{
  cout << endl
       << "  There are no players associated to the tag \"" << tag << "\"" << endl
       << endl;
}

void invalidArgumentsMessage()
{
  cout << endl
       << "  The arguments provided are invalid" << endl
       << endl;
}

void commandNotFoundMessage()
{
  cout << endl
       << "  Command not found" << endl
       << "  Use the 'help' command for more information" << endl
       << endl;
}

void topValueTooBigMessage(int topSize)
{
  cout << endl
       << "  The given argument is greater than the number of players in that position." << endl
       << "  Printing only " << topSize << endl
       << endl;
}

#endif