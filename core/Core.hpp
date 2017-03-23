#ifndef CORE_HPP_
#define CORE_HPP_

#include "ICore.hpp"
#include "IGraphic.hpp"
#include "IGame.hpp"

namespace arcade
{
  class Core : public ICore
  {
    public:
      Core();
	    virtual ~Core() {};
      virtual void		Notify(arcade::CommandType);
      virtual void		RunArcade(const std::string&);
    private:
      IGame						*_game;
  };
};

#endif
