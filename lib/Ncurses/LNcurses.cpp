#include "LNcurses.hpp"

arcade::LNcurses::LNcurses()
{
  this->initWindow();
  this->modeCanon(0);
}

arcade::LNcurses::~LNcurses()
{
  endwin();
  this->modeCanon(1);
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

bool		arcade::LNcurses::isOnMap(arcade::WhereAmI *player, int i) const
{
  for (int pos = 0; pos < player->lenght; pos++)
    if (player->position[pos].x + player->position[pos].y * 8 == i)
      return true;
  return false;
}

void		arcade::LNcurses::ShowGame(arcade::WhereAmI *player, arcade::GetMap *map)
{
  int		x;
  int		y = 0;
  int		i = 0;

  while (y < map->height)
  {
    x = 0;
    while (x < map->width && i < map->width * map->height)
    {
      if (this->isOnMap(player, i) == true)
      {
        attron(A_REVERSE);
        mvprintw(y + MARGIN_Y, x + MARGIN_X, "S");
        attroff(A_REVERSE);
      }
      else
        mvprintw(y + MARGIN_Y, x + MARGIN_X, "%d", (int)map->tile[i]);
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

arcade::CommandType			arcade::LNcurses::GetInput() const
{
  arcade::CommandType		type = arcade::CommandType::ILLEGAL;
  char									c ;

  //while (c != 'z' && c != 'q' && c != 's' && c != 'd')
  read(0, &c, 1);//std::cin.read(&c, 1);
  if (c == 'z')
    type = arcade::CommandType::GO_UP;
  if (c == 'q')
    type = arcade::CommandType::GO_LEFT;
  if (c == 's')
    type = arcade::CommandType::GO_DOWN;
  if (c == 'd')
    type = arcade::CommandType::GO_RIGHT;
  return (type);
}

arcade::IGraphic*		CreateDisplayModule()
{
  return new arcade::LNcurses();
}
