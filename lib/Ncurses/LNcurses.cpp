#include "LNcurses.hpp"
#include <stdio.h>

const std::string                       arcade::LNcurses::RESSOURCES_ASCII = "./ressources/ascii_files/";
//const unsigned int                      arcade::LNcurses::MARGIN_Y = LINES / 2;
//const unsigned int                      arcade::LNcurses::MARGIN_X = COLS / 2;

arcade::LNcurses::LNcurses()
{
  this->initWindow();
  this->initMapInputGame();
  this->initMapInputCore();
  this->initMapDisplay();
  try {
    this->modeCanon(0);
  }
  catch (RunTimeErrorGraphic const &stdErr) {
    std::cerr << stdErr.what() << std::endl;
    exit(-1);
  }
}

arcade::LNcurses::~LNcurses()
{
  try {
    this->modeCanon(1);
  }
  catch (RunTimeErrorGraphic const &stdErr) {
    std::cerr << stdErr.what() << std::endl;
    exit(-1);
  }
  endwin();
}

void                          arcade::LNcurses::initColors(const Assets &assets)
{
  init_color(COLOR_BLUE, assets.c_player.val.r * (1000 / 255), assets.c_player.val.v * (1000 / 255), assets.c_player.val.b * (1000 / 255));
  init_color(COLOR_YELLOW, assets.c_map[static_cast<int>(arcade::TileType::BLOCK)].val.r * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::BLOCK)].val.v * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::BLOCK)].val.b * (1000 / 255));
  init_color(COLOR_RED, assets.c_map[static_cast<int>(arcade::TileType::EVIL_DUDE)].val.r * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::EVIL_DUDE)].val.v * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::EVIL_DUDE)].val.b * (1000 / 255));
  init_color(COLOR_MAGENTA, assets.c_map[static_cast<int>(arcade::TileType::EVIL_SHOOT)].val.r * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::EVIL_SHOOT)].val.v * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::EVIL_SHOOT)].val.b * (1000 / 255));
  init_color(COLOR_CYAN, assets.c_map[static_cast<int>(arcade::TileType::MY_SHOOT)].val.r * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::MY_SHOOT)].val.v * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::MY_SHOOT)].val.b * (1000 / 255));
  init_color(COLOR_GREEN, assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].val.r * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].val.v * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].val.b * (1000 / 255));

  init_pair(static_cast<int>(arcade::TileType::EMPTY), COLOR_BLACK, COLOR_BLACK);
  init_pair(static_cast<int>(arcade::TileType::BLOCK), COLOR_YELLOW, COLOR_YELLOW);
  init_pair(static_cast<int>(arcade::TileType::OBSTACLE), COLOR_WHITE, COLOR_WHITE);
  init_pair(static_cast<int>(arcade::TileType::EVIL_DUDE), COLOR_RED, COLOR_RED);
  init_pair(static_cast<int>(arcade::TileType::EVIL_SHOOT), COLOR_MAGENTA, COLOR_MAGENTA);
  init_pair(static_cast<int>(arcade::TileType::MY_SHOOT), COLOR_CYAN, COLOR_CYAN);
  init_pair(static_cast<int>(arcade::TileType::POWERUP), COLOR_GREEN, COLOR_GREEN);
  init_pair(static_cast<int>(arcade::TileType::OTHER), COLOR_BLUE, COLOR_BLUE);
}

void													arcade::LNcurses::initMapInputGame()
{
  this->input_game['z'] = arcade::CommandType::GO_UP;
  this->input_game['q'] = arcade::CommandType::GO_LEFT;
  this->input_game['s'] = arcade::CommandType::GO_DOWN;
  this->input_game['d'] = arcade::CommandType::GO_RIGHT;
  this->input_game['t'] = arcade::CommandType::ILLEGAL;
  this->input_game['\r'] = arcade::CommandType::SHOOT;
}

void													arcade::LNcurses::initMapInputCore()
{
  this->input_core['2'] = arcade::CoreCommand::PREV_GRAPHIC;
  this->input_core['3'] = arcade::CoreCommand::NEXT_GRAPHIC;
  this->input_core['4'] = arcade::CoreCommand::PREV_GAME;
  this->input_core['5'] = arcade::CoreCommand::NEXT_GAME;
  this->input_core[' '] = arcade::CoreCommand::PAUSE;
  this->input_core['8'] = arcade::CoreCommand::RESTART;
  this->input_core[27] = arcade::CoreCommand::ESCAPE;
}

void													arcade::LNcurses::initMapDisplay()
{
  this->map_disp[arcade::TileType::EMPTY] = ' ';
  this->map_disp[arcade::TileType::EVIL_DUDE] = 'X';
  this->map_disp[arcade::TileType::MY_SHOOT] = '#';
  this->map_disp[arcade::TileType::EVIL_SHOOT] = '@';
  this->map_disp[arcade::TileType::BLOCK] = '|';
  this->map_disp[arcade::TileType::POWERUP] = 'O';
  this->map_disp[arcade::TileType::OBSTACLE] = 'w';
}

void		arcade::LNcurses::initWindow() const
{
  newterm(NULL, stderr, stdin);
  start_color();
  keypad(stdscr, TRUE);
  set_escdelay(25);
  noecho();
  curs_set(0);
  refresh();
}

bool		arcade::LNcurses::isOnMap(arcade::WhereAmI *player, int i, int width) const
{
  for (int pos = 0; pos < player->lenght; pos++)
    if (player->position[pos].x + player->position[pos].y * width == i)
      return true;
  return false;
}

void		arcade::LNcurses::printCmd(arcade::GetMap *map)
{
  int		y = MARGIN_Y;
  int		x = MARGIN_X + map->width + 3;
//Ne pas mettre en dur
  attron(A_REVERSE);
  mvprintw(y++, x, "Commandes du jeu");
  attroff(A_REVERSE);
  y++;
  mvprintw(y++, x, "z - Se déplacer vers le haut");
  mvprintw(y++, x, "s - Se déplacer vers le bas");
  mvprintw(y++, x, "q - Se déplacer vers la droite");
  mvprintw(y++, x, "d - Se déplacer vers la gauche");
  y++;
  mvprintw(y++, x, "espace - Mettre le jeu en pause");
  mvprintw(y++, x, "esc - Quitter le jeu");
  mvprintw(y++, x, "8 - Recommencer le jeu");
  mvprintw(y++, x, "9 - Quitter l'arcade");
}

void		arcade::LNcurses::ShowGame(arcade::WhereAmI *player, arcade::GetMap *map, Assets &assets)
{
  int		x;
  int		y = 0;
  int		i = 0;

  initColors(assets);
  clear();
  this->_width_map = map->width;
  this->_heigth_map = map->height;
  while (y < map->height)
  {
    x = 0;
    while (x < map->width && i < map->width * map->height)
    {
      if (this->isOnMap(player, i, map->width) == true)
      {
        attron(COLOR_PAIR(static_cast<int>(arcade::TileType::OTHER)));
        mvprintw(y + (MARGIN_Y - map->height / 2), x + (MARGIN_X - map->width / 2), " ");
        attroff(COLOR_PAIR(static_cast<int>(arcade::TileType::OTHER)));
      }
      else {
        attron(COLOR_PAIR(static_cast<int>(map->tile[i])));
        mvprintw(y + (MARGIN_Y - map->height / 2), x + (MARGIN_X - map->width / 2), "%c", this->map_disp[map->tile[i]]);
        attroff(COLOR_PAIR(static_cast<int>(map->tile[i])));
      }
      i++;
      x++;
    }
    y++;
  }
  this->printCmd(map);
}

int									arcade::LNcurses::modeCanon(int mode) const
{
  static struct termios prev;
  static struct termios next;

  if (mode == 0)
    {
      if (ioctl(0, TCGETS, &prev) < 0)
        throw RunTimeErrorGraphic("Error with ioctl");
      if (ioctl(0, TCGETS, &next) < 0)
        throw RunTimeErrorGraphic("Error with ioctl");
      next.c_lflag &= ~ECHO;
      next.c_lflag &= ~ICANON;
      next.c_cc[VMIN] = 0;
      next.c_cc[VTIME] = 0;
      if (ioctl(0, TCSETS, &next) < 0)
        throw RunTimeErrorGraphic("Error with ioctl");
    }
  else
    if (ioctl(0, TCSETS, &prev) < 0)
      throw RunTimeErrorGraphic("Error with ioctl");
  return (0);
}

void									arcade::LNcurses::GetInput(ICore *core)
{
  char							  c;

  read(0, &c, 1);
  if (c == 'q' || c == 'z' || c == 'd' || c == 's' || c == '\r' || c == 't')
    core->NotifyScene(this->input_game[c]);
  if (c == '2' || c == '3' || c == '4' ||c == '5' || c == '8' || c == 27 || c == ' ')
    core->NotifyCore(this->input_core[c]);
}

bool								arcade::LNcurses::printFile(const char *fileName, int y)
{
  std::fstream			file;
  std::string				str;

  file.open(fileName);
  if (file)
  {
    getline(file, str);
    while(!file.eof())
    {
      mvprintw((LINES / 2) - 5 + y++, (COLS / 2) - (str.length() / 2), "%s", str.c_str());
      getline(file, str);
    }
    return true;
  }
  return false;
}

void										arcade::LNcurses::ShowMenu(const std::vector<std::string> gamesLibs, int idxGame,
                                                   const std::vector<std::string> graphicsLibs, int idxGraphic,
                                                   arcade::Button button, const arcade::playerName &player)
{
  int 									y = 5;
  int										x = -2;

  (void)button;
  clear();
  if (!this->printFile((RESSOURCES_ASCII + "menu.txt").c_str(), -10))
    mvprintw(MARGIN_Y - 3, MARGIN_X - 2, "ARCADE");
  for (unsigned int i = 0; i < 3; i++)
  {
    if (i == player.idx)
      attron(A_REVERSE);
    mvprintw(MARGIN_Y, MARGIN_X + x , "%c", player.name[i]);
    if (i == player.idx)
    attroff(A_REVERSE);
    x += 2;
  }
  for(unsigned int i = 0; i < graphicsLibs.size(); i++)
  {
    if ((int)i == idxGraphic)
      attron(A_REVERSE);
    mvprintw(y + MARGIN_Y - graphicsLibs.size() / 2, MARGIN_X - 10 - graphicsLibs[i].length() + 20, " %s ", graphicsLibs[i].c_str());
    if ((int)i == idxGraphic)
      attroff(A_REVERSE);
    y += 2;
  }
  y = 5;
  for(unsigned int i = 0; i < gamesLibs.size(); i++)
  {
    if ((int)i == idxGame)
      attron(A_REVERSE);
    mvprintw(y + MARGIN_Y - gamesLibs.size() / 2, MARGIN_X + 10 , " %s ", gamesLibs[i].c_str());
    if ((int)i == idxGame)
      attroff(A_REVERSE);
    y += 2;
  }
  refresh();
  (void)graphicsLibs;
  (void)gamesLibs;
}

void									arcade::LNcurses::ShowScoreboard(const std::string &game, const std::vector<arcade::IScore *> &score)
{
  int									y = 0;

	clear();
  attron(A_REVERSE);
  mvprintw(MARGIN_Y / 4, MARGIN_X - (game.length() / 2) - 2, "[ %s ]", game.c_str());
  mvprintw(MARGIN_Y / 3, MARGIN_X - 13, "Top 20 des meilleurs scores");
  for (int i = 0; i < 20 && i < (int)score.size(); i++)
  {
    mvprintw(MARGIN_Y - 5 + y, MARGIN_X - 8, "%d. %s", i, score[i]->getName().c_str());
    mvprintw(MARGIN_Y - 5 + y++, MARGIN_X + 3, "%d", score[i]->getScore());
  }
  attroff(A_REVERSE);
  refresh();
}

void										arcade::LNcurses::ShowScore(arcade::IScore *currentScore, const std::vector<arcade::IScore *> &bestScore)
{
  int										y = MARGIN_Y - (this->_heigth_map / 2);
  int										x = MARGIN_X + this->_width_map + 3;

  attron(A_REVERSE);
  mvprintw(y++, x, "Meilleurs scores");
  attroff(A_REVERSE);
  y++;
  for (unsigned int i = 0; i < bestScore.size() && bestScore.size() > 0; i++)
    mvprintw(y++, x, "%s:%u", bestScore[i]->getName().c_str(), bestScore[i]->getScore());
  y++;
  attron(A_REVERSE);
  mvprintw(y++, x, "Score actuel");
  attroff(A_REVERSE);
  mvprintw(y++, x, "%u", currentScore->getScore());
  refresh();
}

void										arcade::LNcurses::PrintGameOver(arcade::Status status)
{
  clear();
  if (status == arcade::Status::LOSE)
  {
    if (!this->printFile((RESSOURCES_ASCII + "game_over.txt").c_str(), 0))
      mvprintw(MARGIN_Y, MARGIN_X - 4, "Game Over");
  }
  else
  {
    if (!this->printFile((RESSOURCES_ASCII + "win.txt").c_str(), 0))
      mvprintw(MARGIN_Y, MARGIN_X - 1, "Win");
  }
  refresh();
}

extern "C" arcade::IGraphic		*CreateDisplayModule()
{
  return new arcade::LNcurses();
}
