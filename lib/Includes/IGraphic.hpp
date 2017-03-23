#ifndef IGRAPHIC_HPP_
#define IGRAPHIC_HPP_

#include "ArcadeProtocol.hpp"

namespace arcade
{
  class IGraphic
  {
    public:
      virtual ~IGraphic() {};
      virtual void				ShowGame(WhereAmI *, GetMap *) = 0;
      virtual CommandType	GetInput() const = 0;
      virtual void				PrintGameOver() const = 0;
  };
};

extern "C"
arcade::IGraphic*	CreateDisplayModule();

#endif
