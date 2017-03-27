#include "Core.hpp"

typedef void	(arcade::Core::*coreFct)();

arcade::Core::Core()
{
  this->_handle_game = NULL;
  this->_handle_graphic = NULL;
  this->_game = NULL;
  this->_graphic = NULL;
  this->_libs.insert(this->_libs.begin(), "./lib/lib_arcade_ncurses.so");
  this->_libs.insert(this->_libs.begin(), "./lib/lib_arcade_sfml.so");
  this->_coreCmd = arcade::CoreCommand::NOTHING;
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
  if (this->_graphic != NULL)
    delete this->_graphic;
  if (this->_handle_graphic != NULL)
    dlclose(this->_handle_graphic);
  this->_handle_graphic = dlopen(lib.c_str(), RTLD_LAZY);
  arcade::IGraphic				*(*CreateDisplayModule)();
  CreateDisplayModule = (arcade::IGraphic *(*)(void))dlsym(this->_handle_graphic, "CreateDisplayModule");
  this->_graphic = (*CreateDisplayModule)();
}

void		arcade::Core::LoadPrevGraphic()
{
  exit(0);
}

void		arcade::Core::LoadNextGraphic()
{
}

void		arcade::Core::LoadPrevGame()
{
}

void		arcade::Core::LoadNextGame()
{
}

void		arcade::Core::Restart()
{
}

void	  arcade::Core::Menu()
{
}

void		arcade::Core::Quit()
{
}

void		arcade::Core::Pause()
{
}

void									arcade::Core::RunArcade()
{
  int									j = 0;
  int									i = 0;
  std::map<arcade::CoreCommand, coreFct> _mapCore;
  coreFct																 _abc;

  _mapCore[arcade::CoreCommand::PREV_GRAPHIC] = &arcade::Core::LoadPrevGraphic;
  _mapCore[arcade::CoreCommand::NEXT_GRAPHIC] = &arcade::Core::LoadNextGraphic;
  _mapCore[arcade::CoreCommand::PREV_GAME] = &arcade::Core::LoadPrevGraphic;
  _mapCore[arcade::CoreCommand::NEXT_GAME] = &arcade::Core::LoadNextGraphic;
  _mapCore[arcade::CoreCommand::PAUSE] = &arcade::Core::LoadPrevGame;
  _mapCore[arcade::CoreCommand::RESTART] = &arcade::Core::LoadNextGame;
  _mapCore[arcade::CoreCommand::MENU] = &arcade::Core::Restart;
  _mapCore[arcade::CoreCommand::ESCAPE] = &arcade::Core::Menu;

  this->LoadGame("./games/lib_arcade_snake.so");
  while (1)
  {
    this->_graphic->GetInput(this);
    if (j % 3 == 0)
      this->_game->Update(arcade::CommandType::PLAY, false);
    if (!this->_game->IsGameOver())
      this->_graphic->ShowGame(this->_game->GetPlayer(false), this->_game->GetMap(false));
    else
    {
      this->_graphic->PrintGameOver();
      while(this->_game->IsGameOver())
        this->_graphic->GetInput(this);
      this->LoadGame("./games/lib_arcade_snake.so");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
    j++;
    if (this->_coreCmd != arcade::CoreCommand::NOTHING)
    {
      _abc = _mapCore[arcade::CoreCommand::PREV_GRAPHIC];
      (_abc)();
      //_mapCore[this->_coreCmd];
      this->_coreCmd = arcade::CoreCommand::NOTHING;
    }
  }
}

void		arcade::Core::NotifyGame(arcade::CommandType type)
{
  this->_game->Update(type, false);
}

void		arcade::Core::NotifyCore(arcade::CoreCommand type)
{
  this->_coreCmd = type;
}
