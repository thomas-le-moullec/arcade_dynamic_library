#include "LNcurses.hpp"

arcade::LNcurses::LNcurses()
{
  this->initWindow();
  this->modeCanon(0);

  this->map_disp[arcade::TileType::EMPTY] = ' ';
  this->map_disp[arcade::TileType::BLOCK] = '|';
  this->map_disp[arcade::TileType::POWERUP] = 'O';

  this->map_input['z'] = arcade::CommandType::GO_UP;
  this->map_input['q'] = arcade::CommandType::GO_LEFT;
  this->map_input['s'] = arcade::CommandType::GO_DOWN;
  this->map_input['d'] = arcade::CommandType::GO_RIGHT;
  this->map_input['\r'] = arcade::CommandType::PLAY;

  //this->map_input[13] = arcade::CommandType::GO_UP;
  //this->map_input['z'] = arcade::CommandType::GO_UP;

}

arcade::LNcurses::~LNcurses()
{
  this->modeCanon(1);
  endwin();
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
      refresh();
      x++;
    }
    y++;
  }
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
      next.c_cc[VTIME] = 1;
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
  char									c = 0;

  read(0, &c, 1);
  if (c == 'q' || c == 'z' || c == 'd' || c == 's' || c == '\r')
    core->Notify(this->map_input[c]);
}

void										arcade::LNcurses::PrintGameOver() const
{
  clear();
  attron(A_REVERSE);
  mvprintw(LINES / 2, COLS / 2 - 4, "Game Over");
  attroff(A_REVERSE);
  refresh();
}

arcade::IGraphic		*CreateDisplayModule()
{
  return new arcade::LNcurses();
}
