#include "Core.hpp"

const unsigned int                 arcade::Core::SIZE_PATH = 17;

arcade::Core::Core()
{
  this->_handle_game = NULL;
  this->_handle_graphic = NULL;
  this->_game = NULL;
  this->_graphic = NULL;
  this->takeLibInDir("games/", 0);
  this->takeLibInDir("lib/", 1);
  this->_coreCmd = arcade::CoreCommand::NOTHING;
  this->_idxGraphicLib = -1;
  this->_idxGamesLib = 0;
  this->_changeGraphicMenu = false;
  this->_addScore = true;
  this->initMapCore();
  this->initMapShowScene();
  this->initMapNotifyScene();
  this->_scene = arcade::Scene::MENU;
  this->_status = arcade::Status::RUNNING;
  this->_player.name = "AAA";
  this->_player.idx = 0;
  this->_checkSwitch = false;
}

arcade::Core::~Core()
{
  delete this->_graphic;
  delete this->_game;
  dlclose(this->_handle_game);
  dlclose(this->_handle_graphic);
}

void					arcade::Core::initMapShowScene()
{
  this->_mapShowScene[arcade::Scene::GAME] = &arcade::Core::ShowSceneGame;
  this->_mapShowScene[arcade::Scene::MENU] = &arcade::Core::ShowSceneMenu;
  this->_mapShowScene[arcade::Scene::SCOREBOARD] = &arcade::Core::ShowSceneScoreboard;
}

void					arcade::Core::initMapNotifyScene()
{
  this->_notifyScene[arcade::Scene::GAME] = &arcade::Core::NotifySceneGame;
  this->_notifyScene[arcade::Scene::MENU] = &arcade::Core::NotifySceneMenu;
  this->_notifyScene[arcade::Scene::SCOREBOARD] = &arcade::Core::NotifySceneScoreboard;
}

void					arcade::Core::initMapCore()
{
  this->_mapCore[arcade::CoreCommand::PREV_GRAPHIC] = &arcade::Core::LoadPrevGraphic;
  this->_mapCore[arcade::CoreCommand::NEXT_GRAPHIC] = &arcade::Core::LoadNextGraphic;
  this->_mapCore[arcade::CoreCommand::PREV_GAME] = &arcade::Core::LoadPrevGame;
  this->_mapCore[arcade::CoreCommand::NEXT_GAME] = &arcade::Core::LoadNextGame;
  this->_mapCore[arcade::CoreCommand::PAUSE] = &arcade::Core::Pause;
  this->_mapCore[arcade::CoreCommand::RESTART] = &arcade::Core::Restart;
  this->_mapCore[arcade::CoreCommand::MENU] = &arcade::Core::Menu;
  this->_mapCore[arcade::CoreCommand::ESCAPE] = &arcade::Core::Quit;
}

void								arcade::Core::takeLibInDir(const char *dirName, int mode)
{
  DIR 							*Dir = opendir(dirName);
  struct dirent 		*DirEntry;
  std::string				str;
  std::string				path(dirName);

  while((DirEntry = readdir(Dir)) != NULL)
  {
    str = path + DirEntry->d_name;
    if (mode == 0 && str.compare(0, 17, "games/lib_arcade_") == 0)
      this->_gamesLibs.insert(this->_gamesLibs.begin(), this->cutName(str, 17));
    if (mode == 1 && str.compare(0, 15, "lib/lib_arcade_") == 0)
      this->_graphicLibs.insert(this->_graphicLibs.begin(), this->cutName(str, 15));
  }
}

void										arcade::Core::getIndexLib(bool isGame, const std::string& lib)
{
  unsigned int					j = 0;

  if (isGame == true)
  {
    while (j < this->_gamesLibs.size() && "games/lib_arcade_" + this->_gamesLibs[j] + ".so" != lib)
      j++;
    this->_idxGamesLib = j;
  }
  else
  {
    while (j < this->_graphicLibs.size() && "lib/lib_arcade_" + this->_graphicLibs[j] + ".so" != lib)
    {
    //  std::cout << "./games/lib_arcade_" + this->_graphicLibs[j] + ".so" << ":::" << lib;
      j++;
    }
    this->_idxGraphicLib = j;
  }
}

void   				arcade::Core::LoadGame(const std::string& lib)
{
  char *error;

  dlerror();
  if (this->_idxGamesLib == -1)
    this->getIndexLib(true, lib);
  if (this->_game != NULL)
    delete this->_game;
  if (this->_handle_game != NULL)
    dlclose(this->_handle_game);
  this->_handle_game = dlopen(lib.c_str(), RTLD_LAZY);
  arcade::IGame				*(*CreateGame)();
  if ((error = dlerror()) != NULL)
  {
    delete this->_graphic;
    throw RunTimeErrorCore(error);
  }
  if ((CreateGame = (arcade::IGame *(*)(void))dlsym(this->_handle_game, "CreateGame")) == NULL)
    throw RunTimeErrorCore("Error in Dloader");
  this->_game = (*CreateGame)();
  this->_status = arcade::Status::RUNNING;
}

void   				arcade::Core::LoadGraphic(const std::string& lib)
{
  char *error;

  dlerror();
  if (this->_idxGraphicLib == -1)
    this->getIndexLib(false, lib);
  if (this->_graphic != NULL)
    delete this->_graphic;
  if (this->_handle_graphic != NULL)
    dlclose(this->_handle_graphic);
  this->_handle_graphic = dlopen(lib.c_str(), RTLD_LAZY);
  arcade::IGraphic				*(*CreateDisplayModule)();
  if ((error = dlerror()) != NULL)
  {
    //delete this->_graphi;
    throw RunTimeErrorCore(error);
  }
  if ((CreateDisplayModule = (arcade::IGraphic *(*)(void))dlsym(this->_handle_graphic, "CreateDisplayModule")) == NULL)
  {
    throw RunTimeErrorCore("Error in Dloader");
  }
  this->_graphic = (*CreateDisplayModule)();
}

void		arcade::Core::LoadPrevGraphic()
{
  this->_checkSwitch = true;
  this->_idxGraphicLib--;
  if (this->_idxGraphicLib == -1)
    this->_idxGraphicLib = this->_graphicLibs.size() - 1;
  if (this->_scene == arcade::Scene::GAME)
    {
      try {
        this->LoadGraphic("./lib/lib_arcade_" + this->_graphicLibs[this->_idxGraphicLib] + ".so");
      }
      catch (RunTimeErrorCore const &stdErr) {
        std::cerr << stdErr.what() << std::endl;
        exit(-1);
      }
    }
}

void		arcade::Core::LoadNextGraphic()
{
  this->_checkSwitch = true;
  this->_idxGraphicLib++;
  if (this->_idxGraphicLib == (int)this->_graphicLibs.size())
    this->_idxGraphicLib = 0;
  if (this->_scene == arcade::Scene::GAME)
  {
    try {
      this->LoadGraphic("./lib/lib_arcade_" + this->_graphicLibs[this->_idxGraphicLib] + ".so");
    }
    catch (RunTimeErrorCore const &stdErr) {
      std::cerr << stdErr.what() << std::endl;
      exit(-1);
    }
  }
}

void		arcade::Core::LoadPrevGame()
{
  this->_idxGamesLib--;
  if (this->_idxGamesLib == -1)
    this->_idxGamesLib = this->_gamesLibs.size() - 1;
  try {
    this->LoadGame("./games/lib_arcade_" + this->_gamesLibs[this->_idxGamesLib] + ".so");
  }
  catch (RunTimeErrorCore const &stdErr) {
    std::cerr << stdErr.what() << std::endl;
    exit(-1);
  }
}

void		arcade::Core::LoadNextGame()
{
  this->_idxGamesLib++;
  if (this->_idxGamesLib == (int)this->_gamesLibs.size())
    this->_idxGamesLib = 0;
  try {
    this->LoadGame("./games/lib_arcade_" + this->_gamesLibs[this->_idxGamesLib] + ".so");
  }
  catch (RunTimeErrorCore const &stdErr) {
    std::cerr << stdErr.what() << std::endl;
  }
}

void		arcade::Core::Restart()
{
  try {
    this->LoadGame("./games/lib_arcade_" + this->_gamesLibs[this->_idxGamesLib] + ".so");
  }
  catch (RunTimeErrorCore const &stdErr) {
    std::cerr << stdErr.what() << std::endl;
    exit(-1);
  }
}

void	  arcade::Core::Menu()
{
}

void		arcade::Core::Quit()
{
  if (this->_scene != arcade::Scene::MENU)
    this->_scene = arcade::Scene::MENU;
  else
  {
    //delete this->_scoreBoard;
    //this->_scoreBoard.writeScore();
    this->_scene = arcade::Scene::QUIT;
  }
}

void		arcade::Core::Pause()
{
  if (this->_status == arcade::Status::PAUSE)
    this->_status = arcade::Status::RUNNING;
  else
    this->_status = arcade::Status::PAUSE;
}

std::string	arcade::Core::takeGameName() const
{
  int				idx = this->_idxGamesLib;

  return this->_gamesLibs[idx];
}

std::string	arcade::Core::cutName(std::string &libName, int size_path) const
{
  return libName.substr(size_path, libName.length() - 3 - size_path);
}

void		arcade::Core::loadLibAfterMenu()
{
  try {
    this->LoadGraphic("./lib/lib_arcade_" + this->_graphicLibs[this->_idxGraphicLib] + ".so");
  }
  catch (RunTimeErrorCore const &stdErr) {
    std::cerr << stdErr.what() << std::endl;
    exit(-1);
  }
  this->_changeGraphicMenu = false;
}

void									arcade::Core::RunArcade()
{
  int									j = 0;

  try {
    this->LoadGame("./games/lib_arcade_" + this->_gamesLibs[this->_idxGamesLib] + ".so");
  }
  catch (RunTimeErrorCore const &stdErr) {
    std::cerr << stdErr.what() << std::endl;
    exit(-1);
  }
  while (this->_scene != arcade::Scene::QUIT)
  {
    this->_graphic->GetInput(this);
    if (this->_changeGraphicMenu == true)
      this->loadLibAfterMenu();
    if (j++ % 6 == 0 && this->_scene == arcade::Scene::GAME &&
        this->_status == arcade::Status::RUNNING)
      this->_game->Update(arcade::CommandType::PLAY, false);
    (this->*_mapShowScene[this->_scene])();
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
    if (this->_coreCmd != arcade::CoreCommand::NOTHING)
    {
      (this->*_mapCore[this->_coreCmd])();
      std::cout << "";
      this->_coreCmd = arcade::CoreCommand::NOTHING;
    }
    if (this->_scene == arcade::Scene::GAME && this->_status != arcade::Status::RUNNING && this->_addScore)
    {
      this->_scoreBoard.PostScore(this->takeGameName(), this->_player.name, this->_game->GetScore());
      this->_addScore = false;
    }
  }
}

void		arcade::Core::NotifySceneGame(arcade::CommandType type)
{
  if (this->_status != arcade::Status::RUNNING && type == arcade::CommandType::SHOOT)
  {
    this->_status = arcade::Status::RUNNING;
    try {
      this->LoadGame("./games/lib_arcade_" + this->_gamesLibs[this->_idxGamesLib] + ".so");
    }
    catch (RunTimeErrorCore const &stdErr) {
      std::cerr << stdErr.what() << std::endl;
      exit(-1);
    }
    this->_addScore = true;
  }
  this->_game->Update(type, false);
}

void		arcade::Core::NotifySceneMenu(arcade::CommandType type)
{
  if (type == arcade::CommandType::SHOOT)
  {
    this->_scene = arcade::Scene::GAME;
    try {
      this->LoadGame("./games/lib_arcade_" + this->_gamesLibs[this->_idxGamesLib] + ".so");
    }
    catch (RunTimeErrorCore const &stdErr) {
      std::cerr << stdErr.what() << std::endl;
      exit(-1);
    }
    if (this->_checkSwitch == true)
    {
      this->_changeGraphicMenu = true;
      this->_checkSwitch = false;
    }
  }

  else if (type == arcade::CommandType::GO_RIGHT)
    this->_player.idx++;
  else if (type == arcade::CommandType::GO_LEFT)
    this->_player.idx--;
  else if (type == arcade::CommandType::GO_UP)
    this->_player.name[this->_player.idx]++;
  else if (type == arcade::CommandType::GO_DOWN)
    this->_player.name[this->_player.idx]--;
  else if (type == arcade::CommandType::ILLEGAL)
    this->_scene = arcade::Scene::SCOREBOARD;
  if (this->_player.idx == 3)
    this->_player.idx = 0;
  else if (this->_player.idx > 3)
    this->_player.idx = 2;
  if (this->_player.name[this->_player.idx] < 'A')
    this->_player.name[this->_player.idx] = 'Z';
  else if (this->_player.name[this->_player.idx] > 'Z')
    this->_player.name[this->_player.idx] = 'A';
}

void		arcade::Core::NotifySceneScoreboard(arcade::CommandType type)
{
  if (type == arcade::CommandType::GO_RIGHT)
    this->LoadNextGame();
  if (type == arcade::CommandType::GO_LEFT)
    this->LoadPrevGame();
}

void		arcade::Core::NotifyScene(arcade::CommandType type)
{
  (this->*_notifyScene[this->_scene])(type);
}

void		arcade::Core::NotifyCore(arcade::CoreCommand type)
{
  this->_coreCmd = type;
}

void							arcade::Core::ShowSceneGame()
{
  arcade::IScore	*score = new arcade::Score("", "", this->_game->GetScore());

  if (this->_status != arcade::Status::PAUSE)
    this->_status = this->_game->GetStatus();
  if (this->_status == arcade::Status::RUNNING || this->_status == arcade::Status::PAUSE)
  {
    this->_graphic->ShowGame(this->_game->GetPlayer(false), this->_game->GetMap(false), this->_game->GetAssets());
    this->_graphic->ShowScore(score, this->_scoreBoard.GetBestScores(this->takeGameName(), 3));
  }
  else
  {
    this->_graphic->PrintGameOver(this->_status);
  }
}

void		arcade::Core::ShowSceneMenu()
{
  this->_graphic->ShowMenu(this->_gamesLibs, this->_idxGamesLib, this->_graphicLibs, this->_idxGraphicLib, arcade::Button::PLAY, this->_player);
}

void		arcade::Core::ShowSceneScoreboard()
{
  this->_graphic->ShowScoreBoard(this->takeGameName(), this->_scoreBoard.GetBestScores(this->takeGameName(), 20));
}
