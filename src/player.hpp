#include <bits/stdc++.h>
#include <fstream>

#ifndef player_h
#define player_h

using namespace std;

class Player
{
public:
  Player(int id, string name, vector<string> positions);
  Player();

private:
  int id;
  string name;
  vector<string> positions;
  int ratingsCount;
  double ratingsTotal;
};

Player::Player(int _id, string _name, vector<string> _positions)
{
  id = _id;
  name = _name;
  positions = _positions;
  ratingsCount = 0;
  ratingsTotal = 0;
}

Player::Player()
{
  id = 0;
  name = "";
  ratingsCount = 0;
  ratingsTotal = 0;
}

#endif