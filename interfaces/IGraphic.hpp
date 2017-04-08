#ifndef IGRAPHIC_HPP_
#define IGRAPHIC_HPP_

#include <curses.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <map>
#include "ICore.hpp"
#include "IScore.hpp"
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
    arcade::SoundType   sound;
    bool                loadMap;
    std::string         t_map;
    bool                loadPlayer;
    std::string         t_player;
    bool                loadBg;
    std::string         t_bg;
    arcade::CommandType dir;
  };

  class IGraphic
  {
    public:
      virtual ~IGraphic() {};
      virtual void				ShowGame(WhereAmI *, GetMap *, Assets &) = 0;
      virtual void				ShowMenu(const std::vector<std::string>, int, const std::vector<std::string>, int, Button, const arcade::playerName &) = 0;
      virtual void				ShowScore(arcade::IScore *, const std::vector<arcade::IScore *> &) = 0;
      virtual void				ShowScoreboard(const std::string &, const std::vector<arcade::IScore *> &) = 0;
      virtual void				GetInput(ICore *) = 0;
      virtual void				PrintGameOver(arcade::Status) = 0;
  };
};

#endif
