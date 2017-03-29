#ifndef IGRAPHIC_HPP_
#define IGRAPHIC_HPP_

#include <curses.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <map>
#include "ICore.hpp"
#include "ArcadeProtocol.hpp"

namespace arcade
{
  class IGraphic
  {
    public:
      virtual ~IGraphic() {};
      virtual void				ShowGame(WhereAmI *, GetMap *) = 0;
      virtual void				ShowMenu(std::vector<std::string>, std::vector<std::string>, int, int) = 0;
      virtual void				ShowScoreboard() = 0;
      virtual void				GetInput(ICore *) = 0;
      virtual void				PrintGameOver() const = 0;
  };
};

#endif
