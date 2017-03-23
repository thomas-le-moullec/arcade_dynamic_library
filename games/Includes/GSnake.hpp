#ifndef GSNAKE_HPP_
#define GSNAKE_HPP_

#include "IGame.hpp"

#define HEIGHT_MAP			30
#define WIDTH_MAP				30

namespace arcade
{
  class GSnake : public IGame
  {
    public:
      GSnake();
      virtual														~GSnake() {};
      virtual void	    							  Update(CommandType, bool);
      virtual struct GetMap	  					*GetMap(bool) const;
      virtual struct WhereAmI	     			*GetPlayer(bool) const;
      virtual bool											IsGameOver() const;

    private:
      CommandType												_dir;
      TileType													_map[HEIGHT_MAP * WIDTH_MAP];
      std::vector<arcade::Position>     _player;
      bool															_isGameOver;

      void														  initMap();
      void														  initPlayer();
      void                              increaseSnake(int, int);
      void															move();
      void															dropApple();
      bool															isOnSnake(int);
      void												 			gameOver();
      bool															snakeBitesItself() const;
  };
};

#endif
