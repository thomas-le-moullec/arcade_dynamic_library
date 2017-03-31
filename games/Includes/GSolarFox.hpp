#ifndef GSOLARFOX_HPP_
#define GSOLARFOX_HPP_

#include "IGame.hpp"

#define HEIGHT_MAP			40
#define WIDTH_MAP				40
#define RANGE						4

namespace arcade
{
  struct Actor
  {
    CommandType dir;
    Position		pos;
    int					lifes;
    bool				isStoned;
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
      virtual arcade::Status						GetStatus() const;
      virtual const arcade::Assets      &GetAssets() const;
      virtual unsigned int							GetScore() const;

    private:
      struct Actor											_player;
      struct Actor											_playerShoot;
      std::vector<struct Actor>         _shoots;
      std::vector<struct Actor>			    _enemies;
      std::vector<Position>							_powerUp;
      TileType													_map[HEIGHT_MAP * WIDTH_MAP];
      arcade::Status										_statusGame;
      int																_countMovesWidth;
      int																_countMovesHeight;
      arcade::Assets                    _assets;
      unsigned int											_score;
      int																_cmpt;

      void														  initMap();
      void														  initPlayer();
      void                              initAssets();
      void															initPowerUp();
      void															addPowerup(int, int);
      bool															shootPowerup();
      void															deletePowerup();
      bool															shootEvilShoot();
      void															deleteEvilShoot();
      void															move();
      void												 			gameEnd(arcade::Status);
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
