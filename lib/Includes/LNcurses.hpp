#ifndef LNcurses_HPP_
#define LNcurses_HPP_

#include <fstream>
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
      virtual void									ShowGame(WhereAmI *, GetMap *, Assets &);
      virtual void									ShowMenu(std::vector<std::string>, int, std::vector<std::string>, int, Button, const arcade::playerName &);
      virtual void									GetInput(ICore *);
      virtual void					        PrintGameOver(arcade::Status);
      virtual void									ShowScoreboard(const std::string &, std::vector<arcade::IScore *>);
      void                          initColors(const Assets &);
      virtual void									ShowScore(const arcade::IScore *, const std::vector<arcade::IScore *> &);

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

      bool													printFile(const char *, int);

      static const std::string                            RESSOURCES_ASCII;
  };
};

#endif
