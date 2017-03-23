#ifndef ICORE_HPP_
#define ICORE_HPP_

#include <unistd.h>
#include <dlfcn.h>
#include "ArcadeProtocol.hpp"

namespace arcade
{
  class ICore
  {
    public:
	     virtual ~ICore() {};
       virtual void		Notify(arcade::CommandType) = 0;
       virtual void		RunArcade(const std::string&) = 0;
  };
};

#endif
