#include "LNcurses.hpp"
#include <stdio.h>

arcade::LNcurses::LNcurses()
{
  this->initWindow();
  this->initMapInputGame();
  this->initMapInputCore();
  this->initMapDisplay();
  this->modeCanon(0);
}

arcade::LNcurses::~LNcurses()
{
  this->modeCanon(1);
  endwin();
}

void                          arcade::LNcurses::initColors(const Assets &assets)
{
  init_color(COLOR_BLUE, assets.c_player.val.r * (1000 / 255), assets.c_player.val.v * (1000 / 255), assets.c_player.val.b * (1000 / 255));
  //init_color(COLOR_BLACK, assets.c_map[static_cast<int>(arcade::TileType::EMPTY)].val.r * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::EMPTY)].val.v * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::EMPTY)].val.b * (1000 / 255));
  init_color(COLOR_YELLOW, assets.c_map[static_cast<int>(arcade::TileType::BLOCK)].val.r * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::BLOCK)].val.v * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::BLOCK)].val.b * (1000 / 255));
  //init_color(COLOR_WHITE, assets.c_map[static_cast<int>(arcade::TileType::OBSTACLE)].val.r * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::OBSTACLE)].val.v * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::OBSTACLE)].val.b * (1000 / 255));
  init_color(COLOR_RED, assets.c_map[static_cast<int>(arcade::TileType::EVIL_DUDE)].val.r * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::EVIL_DUDE)].val.v * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::EVIL_DUDE)].val.b * (1000 / 255));
  init_color(COLOR_MAGENTA, assets.c_map[static_cast<int>(arcade::TileType::EVIL_SHOOT)].val.r * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::EVIL_SHOOT)].val.v * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::EVIL_SHOOT)].val.b * (1000 / 255));
  init_color(COLOR_CYAN, assets.c_map[static_cast<int>(arcade::TileType::MY_SHOOT)].val.r * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::MY_SHOOT)].val.v * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::MY_SHOOT)].val.b * (1000 / 255));
  init_color(COLOR_GREEN, assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].val.r * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].val.v * (1000 / 255), assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].val.b * (1000 / 255));
  //miss one arcade::TileType::OTHER

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

void		arcade::LNcurses::ShowGame(arcade::WhereAmI *player, arcade::GetMap *map, const Assets &assets)
{
  int		x;
  int		y = 0;
  int		i = 0;

  (void)assets;
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
        return (-1);
      if (ioctl(0, TCGETS, &next) < 0)
        return (-1);
      next.c_lflag &= ~ECHO;
      next.c_lflag &= ~ICANON;
      next.c_cc[VMIN] = 0;
      next.c_cc[VTIME] = 0;
      if (ioctl(0, TCSETS, &next) < 0)
        return (-1);
    }
  else
    if (ioctl(0, TCSETS, &prev) < 0)
      return (-1);
  return (0);
}

void									arcade::LNcurses::GetInput(ICore *core)
{
  char							  c;

  read(0, &c, 1);
  if (c == 'q' || c == 'z' || c == 'd' || c == 's' || c == '\r')
    core->NotifyScene(this->input_game[c]);
  if (c == '2' || c == '3' || c == '4' ||c == '5' || c == '8' || c == 27 || c == ' ')
    core->NotifyCore(this->input_core[c]);
}

void								arcade::LNcurses::printFile(const char *fileName, int y)
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
  }
}

std::string	arcade::LNcurses::cutName(std::string &libName, int size_path) const
{
  return libName.substr(size_path, libName.length() - 3 - size_path);
}

void										arcade::LNcurses::ShowMenu(std::vector<std::string> gamesLibs, int idxGame,
                                                   std::vector<std::string> graphicsLibs, int idxGraphic)
{
  int 									y = 5;

  clear();
  this->printFile("ascii_files/menu.txt", -10);
  //mvprintw(MARGIN_Y, MARGIN_X - 2, "MENU");
  for(unsigned int i = 0; i < graphicsLibs.size(); i++)
  {
    if ((int)i == idxGraphic)
      attron(A_REVERSE);
    mvprintw(y + MARGIN_Y - graphicsLibs.size() / 2, MARGIN_X - 10 - graphicsLibs[i].length() + 20, " %s ", this->cutName(graphicsLibs[i], 15).c_str());
    if ((int)i == idxGraphic)
      attroff(A_REVERSE);
    y += 2;
  }
  y = 5;
  for(unsigned int i = 0; i < gamesLibs.size(); i++)
  {
    if ((int)i == idxGame)
      attron(A_REVERSE);
    mvprintw(y + MARGIN_Y - gamesLibs.size() / 2, MARGIN_X + 10 , " %s ", this->cutName(gamesLibs[i], 17).c_str());
    if ((int)i == idxGame)
      attroff(A_REVERSE);
    y += 2;
  }
  refresh();
  (void)graphicsLibs;
  (void)gamesLibs;
}

void										arcade::LNcurses::ShowScoreboard()
{
}

void										arcade::LNcurses::ShowScore(const arcade::Score &currentScore, const std::vector<arcade::Score> &bestScore)
{
  int										y = MARGIN_Y - (this->_heigth_map / 2);
  int										x = MARGIN_X + this->_width_map + 3;

  attron(A_REVERSE);
  mvprintw(y++, x, "Meilleurs scores");
  attroff(A_REVERSE);
  y++;
  for (unsigned int i = 0; i < bestScore.size() && bestScore.size() > 0; i++)
    mvprintw(y++, x, "%s:%u", bestScore[i].namePlayer.c_str(), bestScore[i].valueScore);
  y++;
  attron(A_REVERSE);
  mvprintw(y++, x, "Score actuel");
  attroff(A_REVERSE);
  mvprintw(y++, x, "%u", currentScore.valueScore);
  refresh();
}

void										arcade::LNcurses::PrintGameOver(arcade::Status status)
{
  clear();
  if (status == arcade::Status::LOSE)
    this->printFile("./ascii_files/game_over.txt", 0);
  else
    this->printFile("./ascii_files/win.txt", 0);
  refresh();
}

extern "C" arcade::IGraphic		*CreateDisplayModule()
{
  return new arcade::LNcurses();
}
