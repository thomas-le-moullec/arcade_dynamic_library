#ifndef GCENTIPED_HPP_
#define GCENTIPED_HPP_

#include "IGame.hpp"

#define WIDTH_MAP   20
#define HEIGHT_MAP  20

namespace arcade
{
  struct Actor
  {
    CommandType	dir;
    CommandType dirX;
    CommandType dirY;
    Position		pos;
    int					lifes;
  };

  class GCentiped : public IGame
  {
    public:
      GCentiped();
      virtual														~GCentiped() {};
      virtual void	    							  Update(CommandType, bool);
      virtual struct GetMap	  					*GetMap(bool) const;
      virtual struct WhereAmI	     			*GetPlayer(bool) const;
      virtual bool											IsGameOver() const;
      virtual arcade::Status						GetStatus() const;
      virtual arcade::Assets            &GetAssets();
      virtual unsigned int							GetScore() const;

    private:
      struct Actor																	_player;
      struct Actor													 				_playerShoot;
      std::vector<std::vector<struct Actor>>  			_enemies;
      std::vector<struct Actor>											_obstacles;
      TileType																			_map[HEIGHT_MAP * WIDTH_MAP];
      arcade::Status																_statusGame;
      arcade::Assets                    						_assets;
      unsigned int																	_score;

      void															initMap();
      void															initAssets();
      void															initEnemies();
      void															initPlayer();
      void															initMyShoot();
      void															initObstacles();
			void															addEnemy(std::vector<arcade::Actor>);
      void															addBodyEnemy(std::vector<arcade::Actor> *, int, int, CommandType, CommandType);
      void															addObstacle(int, int);
      void															deleteObstacle(int);
      void															moveEnemies();
      void															movePlayer(CommandType);
      void															moveMyShoot();
      void															shootEvilDude();
      void															shootObstacle();
      void															execMove(int);
      void															cutCenti(int, int);
      void															gameEnd(arcade::Status);
      bool															isOnPlayer(int, int);
  };
};

#endif
