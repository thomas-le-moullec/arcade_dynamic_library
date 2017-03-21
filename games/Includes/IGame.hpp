#ifndef IGAME_HPP
#define IGAME_HPP

#include "ArcadeProtocol.hpp"

extern "C" void Play(void);

namespace arcade
{
  class IGame
  {
    public:
      virtual										~IGame() {};
      virtual void							Update(CommandType, bool) = 0;
      virtual struct GetMap     *GetMap(bool) const = 0;
      virtual struct WhereAmI		*GetPlayer(bool) const = 0;
  };
}

#endif
