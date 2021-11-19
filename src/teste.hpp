#include <bits/stdc++.h>
#include <fstream>

#ifndef teste_h
#define teste_h

using namespace std;

class PlayerTest
{
public:
  int id;
  int age;
  string name;
  string toString();
  PlayerTest(int id, int age, string name);
  PlayerTest();
};

PlayerTest::PlayerTest(int _id, int _age, string _name)
{
  id = _id;
  age = _age;
  name = _name;
}

PlayerTest::PlayerTest()
{
  id = NULL;
  age = NULL;
  name = "";
}

string PlayerTest::toString()
{
  return name + ": id - " + to_string(id) + ", age - " + to_string(age);
}

#endif