#include "Core.hpp"

arcade::Core::Core()
{
  this->_handle_game = NULL;
  this->_handle_graphic = NULL;
  this->_game = NULL;
  this->_graphic = NULL;
}

arcade::Core::~Core()
{
  dlclose(this->_handle_game);
  dlclose(this->_handle_graphic);
}

void   				arcade::Core::LoadGame(const std::string& lib)
{
  if (this->_handle_game != NULL)
    dlclose(this->_handle_game);
  this->_handle_game = dlopen(lib.c_str(), RTLD_LAZY);
  arcade::IGame				*(*CreateGame)();
  CreateGame = (arcade::IGame *(*)(void))dlsym(this->_handle_game, "CreateGame");

  if (this->_game != NULL)
    delete this->_game;
  this->_game = (*CreateGame)();
}

void   				arcade::Core::LoadGraphic(const std::string& lib)
{
  if (this->_handle_graphic != NULL)
    dlclose(this->_handle_graphic);
  this->_handle_graphic = dlopen(lib.c_str(), RTLD_LAZY);
  arcade::IGraphic				*(*CreateDisplayModule)();
  CreateDisplayModule = (arcade::IGraphic *(*)(void))dlsym(this->_handle_graphic, "CreateDisplayModule");

  if (this->_graphic != NULL)
    delete this->_graphic;
  this->_graphic = (*CreateDisplayModule)();
}

void									arcade::Core::RunArcade()
{
  int									j = 0;

  this->LoadGame("./games/lib_arcade_solarfox.so");
  while (1)
  {
    this->_graphic->GetInput(this);
    if (j % 5 == 0)
      this->_game->Update(arcade::CommandType::PLAY, false);
    if (!this->_game->IsGameOver())
      this->_graphic->ShowGame(this->_game->GetPlayer(false), this->_game->GetMap(false));
    else
    {
      this->_graphic->PrintGameOver();
      while(this->_game->IsGameOver())
        this->_graphic->GetInput(this);
      this->LoadGame("./games/lib_arcade_solarfox.so");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
    j++;
  }
  this->unloadLibrairies();
}

void		arcade::Core::Notify(arcade::CommandType type)
{
  /*if (type == arcade::CommandType::GO_UP)
    std::cout << "GO UP" << std::endl;
  if (type == arcade::CommandType::GO_DOWN)
    std::cout << "GO DOWN" << std::endl;
  if (type == arcade::CommandType::PLAY)
    std::cout << "PLAY" << std::endl;*/
  this->_game->Update(type, false);
}
