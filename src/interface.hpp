// Standard libraries
#include <bits/stdc++.h>
#include <iostream>
#include <windows.h>

#include "../include/termcolor.hpp"

#ifndef interface_h
#define interface_h

using namespace std;

void introduction()
{
  system("cls");

  cout << termcolor::bright_cyan << R"(
                     _______.  ______    _______  __   _______    ___      )"
       << R"(
                    /       | /  __  \  |   ____||  | |   ____|  /   \     )"
       << R"(
                   |   (----`|  |  |  | |  |__   |  | |  |__    /  ^  \    )"
       << R"(
                    \   \    |  |  |  | |   __|  |  | |   __|  /  /_\  \   )"
       << R"(
                .----)   |   |  `--'  | |  |     |  | |  |    /  _____  \  )"
       << R"(
                |_______/     \______/  |__|     |__| |__|   /__/     \__\ )"
       << R"(
                                                                           )"
       << R"(
)" << endl;

  cout << termcolor::blue;
  cout << "\t\t\t\tClassificação e Pesquisa de Dados" << endl;
  cout << endl;
  cout << "\t\t\t\t         Integrantes" << endl;
  cout << "\t\t\t\t - Bernardo Beneduzi Borba" << endl;
  cout << "\t\t\t\t - Ricardo Hermes Dalcin" << endl;
}

#endif