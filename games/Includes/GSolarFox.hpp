#ifndef GSOLARFOX_HPP_
#define GSOLARFOX_HPP_

#include "IGame.hpp"

#define HEIGHT_MAP			40
#define WIDTH_MAP				40

namespace arcade
{
  struct Actor
  {
    CommandType dir;
    Position		pos;
  };

  struct	MyShoot
  {
    CommandType dir;
    Position		pos;
    int					lifes;
  };

  class GSolarFox : public IGame
  {
    public:
      GSolarFox();
      virtual														~GSolarFox() {};
      virtual void	    							  Update(CommandType, bool);
      virtual struct GetMap	  					*GetMap(bool) const;
      virtual struct WhereAmI	     			*GetPlayer(bool) const;
      virtual bool											IsGameOver() const;
      virtual const arcade::Assets      &GetAssets() const;

    private:
      struct Actor											_player;
      struct MyShoot										_playerShoot;
      std::vector<struct Actor>         _shoots;
      std::vector<struct Actor>			    _enemies;
      TileType													_map[HEIGHT_MAP * WIDTH_MAP];
      bool															_isGameOver;
      int																_countMovesWidth;
      int																_countMovesHeight;
      arcade::Assets                    _assets;

      void														  initMap();
      void														  initPlayer();
      void                              initAssets();
      void															move();
      void												 			gameOver();
      void											        modifyMapActors(std::vector<struct Actor>, TileType);

      void                              addEnemy(int, int, CommandType);
      void															initEnemies();
      void											        moveEnemies();
      void															inverseDir(int, CommandType, CommandType);
      void															manageCycleEnemies();

      void															shoot(int);
			void                 							addShoot(int, int, CommandType);
      void															moveShoot();

      void															addMyShoot(int, int, CommandType);
      void															moveMyShoot();
      void															initMyShoot();
    };
};

#endif
