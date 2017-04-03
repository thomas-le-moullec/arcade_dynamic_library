#ifndef GSNAKE_HPP_
#define GSNAKE_HPP_

#include "IGame.hpp"

#define HEIGHT_MAP			20
#define WIDTH_MAP				20

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
      virtual arcade::Status						GetStatus() const;
      virtual const arcade::Assets      &GetAssets() const;
      virtual unsigned int							GetScore() const;

    private:
      std::vector<arcade::CommandType>	_dir;
      TileType													_map[HEIGHT_MAP * WIDTH_MAP];
      std::vector<arcade::Position>     _player;
      arcade::Status										_statusGame;
      bool															_isGameOver;
      arcade::Assets                    _assets;
      unsigned int											_score;
      unsigned int											_lvl;

      void														  initMap();
      void														  initPlayer();
      void                              increaseSnake(int, int);
      void															move();
      void															dropApple();
      bool															isOnSnake(int);
      void												 			gameEnd(arcade::Status);
      bool															snakeBitesItself() const;
      bool															checkDir(arcade::CommandType type);
      void                              initAssets();
  };
};

#endif
