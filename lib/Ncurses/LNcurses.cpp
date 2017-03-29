#include "LNcurses.hpp"

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
  this->input_core['9'] = arcade::CoreCommand::ESCAPE;
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
  mvprintw(y++, x, "8 - Recommencer le jeu");
  mvprintw(y++, x, "9 - Quitter le jeu");
}

void		arcade::LNcurses::ShowGame(arcade::WhereAmI *player, arcade::GetMap *map)
{
  int		x;
  int		y = 0;
  int		i = 0;

  clear();
  while (y < map->height)
  {
    x = 0;
    while (x < map->width && i < map->width * map->height)
    {
      if (this->isOnMap(player, i, map->width) == true)
      {
        attron(A_REVERSE);
        mvprintw(y + (MARGIN_Y - map->height / 2), x + (MARGIN_X - map->width / 2), " ");
        attroff(A_REVERSE);
      }
      else
        mvprintw(y + (MARGIN_Y - map->height / 2), x + (MARGIN_X - map->width / 2), "%c", this->map_disp[map->tile[i]]);
      i++;
      x++;
    }
    y++;
  }
  this->printCmd(map);
  refresh();
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
  //char								buff[];
  char							  c;

  read(0, &c, 1);
  //c = buff[0];
  //if (c == '\r')

  if (c == 'q' || c == 'z' || c == 'd' || c == 's' || c == '\r')
    core->NotifyGame(this->input_game[c]);
  if (c == '2' || c == '3' || c == '4' ||c == '5' || c == '8' || c == '9' || c == ' ')
    core->NotifyCore(this->input_core[c]);
}

void										arcade::LNcurses::ShowMenu(std::vector<std::string> graphicsLibs,
                                                   std::vector<std::string> gamesLibs,
                                                   int idxGraphic, int idxGame)
{
  int 									y = 0;

  clear();
  mvprintw(MARGIN_Y, MARGIN_X - 2, "MENU");
  for(unsigned int i = 0; i < graphicsLibs.size(); i++)
  {
    if ((int)i == idxGraphic)
      attron(A_REVERSE);
    mvprintw(y + MARGIN_Y - graphicsLibs.size() / 2, MARGIN_X - 10 - graphicsLibs[i].length(), "%s", graphicsLibs[i].c_str());
    if ((int)i == idxGraphic)
      attroff(A_REVERSE);
    y++;
  }
  y = 0;
  for(unsigned int i = 0; i < gamesLibs.size(); i++)
  {
    if ((int)i == idxGame)
      attron(A_REVERSE);
    mvprintw(y + MARGIN_Y - gamesLibs.size() / 2, MARGIN_X + 10 , "%s", gamesLibs[i].c_str());
    if ((int)i == idxGame)
      attroff(A_REVERSE);
    y++;
  }
  refresh();

  (void)graphicsLibs;
  (void)gamesLibs;
}

void										arcade::LNcurses::PrintGameOver() const
{
  clear();
  attron(A_REVERSE);
  mvprintw(LINES / 2, COLS / 2 - 4, "Game Over");
  attroff(A_REVERSE);
  refresh();
}

extern "C" arcade::IGraphic		*CreateDisplayModule()
{
  return new arcade::LNcurses();
}
