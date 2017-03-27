#include "Core.hpp"

arcade::Core::Core()
{
  this->_handle_game = NULL;
  this->_handle_graphic = NULL;
  this->_game = NULL;
  this->_graphic = NULL;
  this->_libs.insert(this->_libs.begin(), "lib/lib_arcade_ncurses.so"); // A REVOIR POUR LE PATH
  this->_libs.insert(this->_libs.begin(), "lib/lib_arcade_sfml.so");
  this->_coreCmd = arcade::CoreCommand::NOTHING;
  this->_idxLib = -1;
  this->initMap();
}

arcade::Core::~Core()
{
  dlclose(this->_handle_game);
  dlclose(this->_handle_graphic);
}

void					arcade::Core::initMap()
{
  this->_mapCore[arcade::CoreCommand::PREV_GRAPHIC] = &arcade::Core::LoadPrevGraphic;
  this->_mapCore[arcade::CoreCommand::NEXT_GRAPHIC] = &arcade::Core::LoadNextGraphic;
  this->_mapCore[arcade::CoreCommand::PREV_GAME] = &arcade::Core::LoadPrevGraphic;
  this->_mapCore[arcade::CoreCommand::NEXT_GAME] = &arcade::Core::LoadNextGraphic;
  this->_mapCore[arcade::CoreCommand::PAUSE] = &arcade::Core::LoadPrevGame;
  this->_mapCore[arcade::CoreCommand::RESTART] = &arcade::Core::LoadNextGame;
  this->_mapCore[arcade::CoreCommand::MENU] = &arcade::Core::Restart;
  this->_mapCore[arcade::CoreCommand::ESCAPE] = &arcade::Core::Menu;
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
  int					j = 0;

  if (this->_idxLib == -1)
  {
    while (j < this->_libs.size() && this->_libs[j] != lib)
      j++;
    this->_idxLib = j;
  }
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
  this->_idxLib--;
  if (this->_idxLib == -1)
    this->_idxLib = this->_libs.size() - 1;
  this->LoadGraphic(this->_libs[this->_idxLib]);
}

void		arcade::Core::LoadNextGraphic()
{
  this->_idxLib++;
  if (this->_idxLib == this->_libs.size())
    this->_idxLib = 0;
  this->LoadGraphic(this->_libs[this->_idxLib]);
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

  this->LoadGame("./games/lib_arcade_snake.so");
  while (1)
  {
    this->_graphic->GetInput(this);
    if (j % 4 == 0)
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
      (this->*_mapCore[this->_coreCmd])();
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
