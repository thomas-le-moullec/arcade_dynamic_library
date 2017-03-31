#ifndef LNcurses_HPP_
#define LNcurses_HPP_

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
      virtual void									ShowGame(WhereAmI *, GetMap *, const Assets &);
      virtual void									ShowMenu(std::vector<std::string>, int, std::vector<std::string>, int);
      virtual void									GetInput(ICore *);
      virtual void					        PrintGameOver(arcade::Status) const;
      virtual void									ShowScoreboard();
      virtual void									ShowScore(const arcade::Score &, const std::vector<arcade::Score> &);

    private:
      std::map<arcade::TileType, char>			map_disp;
      std::map<char, arcade::CommandType>		input_game;
      std::map<char, arcade::CoreCommand>		input_core;
      int																		_width_map;
      int																		_heigth_map;

      void													initWindow() const;
      bool													isOnMap(WhereAmI *, int, int) const;
      int														modeCanon(int) const;
      void													printCmd(arcade::GetMap *);
      void													initMapInputGame();
      void													initMapInputCore();
      void													initMapDisplay();
  };
};

#endif
