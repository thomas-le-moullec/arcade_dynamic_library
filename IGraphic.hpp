#ifndef IGRAPHIC_HPP_
#define IGRAPHIC_HPP_

#include "Protocol.hpp"

namespace arcade
{
  class IGraphic
  {
    public:
      virtual ~IGraphic() {};
      virtual void		ShowGame(WhereAmI *, GetMap *) = 0;
  };
};

#endif
