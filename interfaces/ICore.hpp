#ifndef ICORE_HPP_
#define ICORE_HPP_

#include <unistd.h>
#include <dlfcn.h>
#include "ArcadeProtocol.hpp"

namespace arcade
{
  enum class			CoreCommand : uint16_t
  {
    PREV_GRAPHIC  = 0,
    NEXT_GRAPHIC  = 1,
    PREV_GAME	    = 2,
    NEXT_GAME	    = 3,
    PAUSE	        = 4,
    RESTART       = 5,
    MENU          = 6,
    ESCAPE        = 7,
    NOTHING       = 8
  };

  enum class			Scene : uint16_t
  {
    MENU = 0,
    GAME = 1,
    SCOREBOARD = 2,
    QUIT = 3
  };

  enum class			Status : uint16_t
  {
    RUNNING = 0,
    WIN = 1,
    LOSE = 2,
    PAUSE = 3,
    SCORE = 4,
  };

  struct Player
  {
    std::string 	name;
    unsigned int	idx;
  };

  class ICore
  {
    public:
	     virtual ~ICore() {};
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
       virtual void		ShowSceneMenu() = 0;
       virtual void		ShowSceneGame() = 0;
       virtual void		ShowSceneScoreboard() = 0;
       virtual void		NotifyScene(CommandType) = 0;
       virtual void		NotifySceneMenu(CommandType) = 0;
       virtual void		NotifySceneGame(CommandType) = 0;
       virtual void		NotifySceneScoreboard(CommandType) = 0;
  };
};

#endif
