#include "IGraphic.hpp"
#include "IGame.hpp"

#include <unistd.h>

void			execArcade()
{
  arcade::IGraphic		*graphic = CreateDisplayModule();
  arcade::IGame				*game = CreateGame();
  arcade::CommandType	type;

  while (!game->IsGameOver())
  {
    type = graphic->GetInput();
    game->Update(type, false);
    game->Update(arcade::CommandType::PLAY, false);
    if (!game->IsGameOver())
      graphic->ShowGame(game->GetPlayer(false), game->GetMap(false));
    else
      graphic->PrintGameOver();
    usleep(400000);
  }
  while(1);
}

int	main()
{
  execArcade();
}
