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
  cout << termcolor::cyan << R"(
      _______.  ______    _______  __   _______    ___      
    /       | /  __  \  |   ____||  | |   ____|  /   \     
   |   (----`|  |  |  | |  |__   |  | |  |__    /  ^  \    
    \   \    |  |  |  | |   __|  |  | |   __|  /  /_\  \   
.----)   |   |  `--'  | |  |     |  | |  |    /  _____  \  
|_______/     \______/  |__|     |__| |__|   /__/     \__\ 
                                                           
)" << endl;

  cout << "\t\tClassificação e Pesquisa de Dados" << endl;
  cout << endl;
  cout << "\t\tIntegrantes:" << endl;
  cout << "\t\t  - Bernardo Beneduzi Borba" << endl;
  cout << "\t\t  - Ricardo Hermes Dalcin" << endl;
}

#endif