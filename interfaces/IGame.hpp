#ifndef IGAME_HPP
#define IGAME_HPP

#include "ArcadeProtocol.hpp"

namespace arcade
{

  

  class IGame
  {
    public:
      virtual										~IGame() {};
      virtual void							Update(CommandType, bool) = 0;
      virtual struct GetMap     *GetMap(bool) const = 0;
      virtual struct WhereAmI		*GetPlayer(bool) const = 0;
      virtual bool							IsGameOver() const = 0;
  };
};

extern "C"
void						Play();
extern "C"
arcade::IGame*	CreateGame();

#endif
