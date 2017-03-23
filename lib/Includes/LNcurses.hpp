#ifndef LNcurses_HPP_
#define LNcurses_HPP_

#include <curses.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <map>

#include "IGraphic.hpp"

#define	MARGIN_Y	LINES / 2
#define MARGIN_X	COLS / 2

namespace arcade
{
  class LNcurses : public IGraphic
  {
    public:
      LNcurses();
      virtual ~LNcurses();
      virtual void									ShowGame(WhereAmI *, GetMap *);
      virtual CommandType						GetInput() const;
      virtual void									PrintGameOver() const;
    private:
      std::map<arcade::TileType, char>		map;
      void													initWindow() const;
      bool													isOnMap(WhereAmI *, int) const;
      int														modeCanon(int) const;
  };
};

#endif
