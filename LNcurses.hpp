#ifndef LNcurses_HPP_
#define LNcurses_HPP_

#include "IGraphic.hpp"


namespace arcade
{
  class LNcurses : public IGraphic
  {
    public:
      virtual ~LNcurses() {};
      virtual void		ShowGame(WhereAmI *, GetMap *);
  };
};

#endif
