#ifndef IGRAPHIC_HPP_
#define IGRAPHIC_HPP_

#include <curses.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <map>
#include "ICore.hpp"
#include "ScoreBoard.hpp"
#include "ArcadeProtocol.hpp"

namespace arcade
{
  union                 Color
  {
    struct              s_color {
      uint8_t           a;
      uint8_t           b;
      uint8_t           v;
      uint8_t           r;
    }                   val;
    unsigned int        color;
  };

  struct                   Assets
  {
    arcade::Color       c_player;
    arcade::Color       c_map[8];
  };

  class IGraphic
  {
    public:
      virtual ~IGraphic() {};
      virtual void				ShowGame(WhereAmI *, GetMap *, const Assets &) = 0;
      virtual void				ShowMenu(std::vector<std::string>, int, std::vector<std::string>, int) = 0;
      virtual void				ShowScoreboard() = 0;
      virtual void				ShowScore(const arcade::Score &, const std::vector<arcade::Score>) = 0;
      virtual void				GetInput(ICore *) = 0;
      virtual void				PrintGameOver(arcade::Status) const = 0;
  };
};

#endif
