#ifndef LNcurses_HPP_
#define LNcurses_HPP_

#include <curses.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "IGraphic.hpp"

#define	MARGIN_Y	15 //à remplacer
#define MARGIN_X	80 //à remplacer

namespace arcade
{
  class LNcurses : public IGraphic
  {
    public:
      LNcurses();
      virtual ~LNcurses();
      virtual void				ShowGame(WhereAmI *, GetMap *);
      virtual CommandType	GetInput() const;
    private:
      void								initWindow() const;
      bool								isOnMap(WhereAmI *, int) const;
      int									modeCanon(int) const;
  };
};

#endif
