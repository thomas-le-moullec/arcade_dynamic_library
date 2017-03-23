#include "Core.hpp"

arcade::Core::Core()
{
}

/*template<typename T>
T					*arcade::Core::loadArcade(const std::string &lib, const char *constructor)
{
  void		*handle;
  T				*(*create)();

  handle = dlopen(lib.c_str(), RTLD_LAZY);
  create = (T *(*)(void))dlsym(handle, constructor);
  return (*create)();
}*/

void									arcade::Core::loadLibraries(const std::string &lib)
{
  this->_handle_graphic = dlopen(lib.c_str(), RTLD_LAZY);
  this->_handle_game = dlopen("./games/lib_arcade_snake.so", RTLD_LAZY);
  arcade::IGraphic		*(*CreateDisplayModule)();
  arcade::IGame				*(*CreateGame)();
  CreateDisplayModule = (arcade::IGraphic *(*)(void))dlsym(this->_handle_graphic, "CreateDisplayModule");
  CreateGame = (arcade::IGame *(*)(void))dlsym(this->_handle_game, "CreateGame");

  this->_graphic = (*CreateDisplayModule)();
  this->_game = (*CreateGame)();
}

void									arcade::Core::unloadLibrairies()
{
  dlclose(this->_handle_graphic);
  dlclose(this->_handle_game);
}

void									arcade::Core::RunArcade(const std::string &lib)
{
  this->loadLibraries(lib);
  while (1)
  {
    this->_graphic->GetInput(this);
    this->_game->Update(arcade::CommandType::PLAY, false);
    if (!this->_game->IsGameOver())
      this->_graphic->ShowGame(this->_game->GetPlayer(false), this->_game->GetMap(false));
    else
    {
      this->_graphic->PrintGameOver();
      while(this->_game->IsGameOver())
        this->_graphic->GetInput(this);
      delete this->_game;
      this->_game = (*CreateGame)();
    }
    usleep(300000);
  }
  this->unloadLibrairies();
}

void		arcade::Core::Notify(arcade::CommandType type)
{
  this->_game->Update(type, false);
}
