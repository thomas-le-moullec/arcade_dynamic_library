#include "Core.hpp"

arcade::Core::Core()
{
}

void			arcade::Core::RunArcade(const std::string &lib)
{
  void		*handle;
  arcade::IGame		*(*CreateGame)();
  char *error;

  handle = dlopen(lib.c_str(), RTLD_LAZY);
  if (!handle)
    std::cout << "handle NULL" << std::endl;
  dlerror();
  CreateGame = (arcade::IGame *(*)(void))dlsym(handle, "CreateGame");


  arcade::IGraphic		*graphic = CreateDisplayModule();
  if (CreateGame == NULL)
    std::cout << "vaut NULL" << std::endl;
  if ((error = dlerror()) != NULL)  {
      fprintf(stderr, "%s\n", error);
      exit(EXIT_FAILURE);}
  arcade::IGame				*game = (*CreateGame)();
  std::cout << "Debug --> 4" << std::endl;

  (void)lib;
  this->_game = game;
  while (!game->IsGameOver())
  {
    graphic->GetInput(this);
    game->Update(arcade::CommandType::PLAY, false);
    if (!game->IsGameOver())
      graphic->ShowGame(game->GetPlayer(false), game->GetMap(false));
    else
      graphic->PrintGameOver();
    usleep(300000);
  }
  dlclose(handle);
  while(1);
}

void		arcade::Core::Notify(arcade::CommandType type)
{
  this->_game->Update(type, false);
}
