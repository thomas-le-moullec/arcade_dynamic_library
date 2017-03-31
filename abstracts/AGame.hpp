#ifndef AGAME_HPP_
#define AGAME_HPP_

#include "IGame.hpp"

namespace arcade
{
  class AGame : public IGame
  {
    public:
      GSnake();
      virtual														~AGame() {};
      virtual void	    							  Update(CommandType, bool);
      virtual struct GetMap	  					*GetMap(bool) const;
      virtual struct WhereAmI	     			*GetPlayer(bool) const;
      virtual bool											IsGameOver() const;
      virtual arcade::Status						GetStatus() const;
      virtual const arcade::Assets      &GetAssets() const;
      virtual unsigned int							GetScore() const;

    private:

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
