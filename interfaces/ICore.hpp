#ifndef ICORE_HPP_
#define ICORE_HPP_

#include <unistd.h>
#include <dlfcn.h>
#include "ArcadeProtocol.hpp"

namespace arcade
{
  enum class			CoreCommand : uint16_t
  {
    PREV_GRAPHIC = 0,
    NEXT_GRAPHIC = 1,
    PREV_GAME	= 2,
    NEXT_GAME	= 3,
    PAUSE	= 4,
    RESTART = 5,
    MENU = 6,
    ESCAPE = 7,
    NOTHING = 8
  };

  class ICore
  {
    public:
	     virtual ~ICore() {};
       virtual void		NotifyGame(arcade::CommandType) = 0;
       virtual void		NotifyCore(arcade::CoreCommand) = 0;
       virtual void		RunArcade() = 0;
       virtual void   LoadGame(const std::string&) = 0;
       virtual void   LoadGraphic(const std::string&) = 0;
       virtual void		LoadPrevGraphic() = 0;
       virtual void		LoadNextGraphic() = 0;
       virtual void		LoadPrevGame() = 0;
       virtual void		LoadNextGame() = 0;
       virtual void		Restart() = 0;
       virtual void	  Menu() = 0;
       virtual void		Quit() = 0;
       virtual void		Pause() = 0;
  };
};

#endif
