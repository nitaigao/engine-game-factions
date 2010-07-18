/*!
*  @company Black Art Studios
*  @author Nicholas Kostelnik
*  @file   src\4ha6EW2cru.Application\main_osx.cpp
*  @date   2009/04/25
*/
#include <string>

#include "Game/IGame.hpp"
#include "Game/GameFactory.h"
using namespace Game;

int main()
{
  
  GameFactory gameFactory;
  IGame* game = gameFactory.CreateGame();
  game->Initialize();

  while(!game->IsQuitting())
  {
    game->Update();
  }

  game->Release();

  delete game;
  
  return 0;
}

// EOF