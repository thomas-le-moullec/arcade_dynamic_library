#include "IGraphic.hpp"
#include "IGame.hpp"

#include <unistd.h>

void			execArcade()
{
  arcade::IGraphic		*graphic = CreateDisplayModule();
  arcade::IGame				*game = CreateGame();
  arcade::CommandType	type;

  while (1)
  {
    type = graphic->GetInput();
    game->Update(type, false);
    game->Update(arcade::CommandType::PLAY, false);
    graphic->ShowGame(game->GetPlayer(false), game->GetMap(false));
    usleep(700000);
  }
}

int	main()
{
  execArcade();
}
