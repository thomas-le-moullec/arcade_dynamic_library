#ifndef LSFML_HPP_
#define LSFML_HPP_

#include "IGraphic.hpp"

namespace arcade
{
  class LSfml : public IGraphic
  {
    public:
      virtual ~LSfml() {};
      virtual void		ShowGame(WhereAmI *, GetMap *);
  };
};

#endif
