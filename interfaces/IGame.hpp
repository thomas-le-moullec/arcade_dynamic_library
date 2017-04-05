#ifndef IGAME_HPP
#define IGAME_HPP

#include "ICore.hpp"
#include "IGraphic.hpp"

namespace arcade
{
  class IGame
  {
    public:
      virtual												~IGame() {};
      virtual void									Update(CommandType, bool) = 0;
      virtual struct GetMap     		*GetMap(bool) const = 0;
      virtual struct WhereAmI				*GetPlayer(bool) const = 0;
      virtual bool									IsGameOver() const = 0;
      virtual arcade::Status				GetStatus() const = 0;
      virtual arcade::Assets        &GetAssets() = 0;
      virtual unsigned int					GetScore() const = 0;
  };
};

extern "C"
void						Play();
extern "C"
arcade::IGame*	CreateGame();

#endif
