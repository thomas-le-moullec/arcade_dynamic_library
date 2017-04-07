#ifndef ICORE_HPP_
#define ICORE_HPP_

#include <unistd.h>
#include <dlfcn.h>
#include "ArcadeProtocol.hpp"
#include "Errors.hpp"

namespace arcade
{
  enum class			CoreCommand : uint16_t
  {
    PREV_GRAPHIC  = 0, 		// Load the previous graphic library
    NEXT_GRAPHIC  = 1,    // Load the next graphic library
    PREV_GAME	    = 2,		// Load the previous game
    NEXT_GAME	    = 3,		// Load the next game
    PAUSE	        = 4,		// Pause the game
    RESTART       = 5,		// Restart the game
    MENU          = 6,		// Back to the Menu
    ESCAPE        = 7,    // Quit the arcade
    NOTHING       = 8			// Do nothing
  };

  enum class                    SoundType : uint16_t
  {
    NOTHING = 0,                        // No sound
    EATAPPLE = 1,                       // Play a "Nam nam nam" sound
    SHOOT = 2,                          // Play a "Pew pew pew" sound
    WAKA = 3,                           // Play a "Waka Waka" sound
    INTRO_PACMAN = 4,                   // Play a "Toulitoutoulitoutou" sound
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
    RUNNING = 0,					// The game is running
    WIN = 1,							// The game is over, the player won
    LOSE = 2,							// The game is over, the player lost
    PAUSE = 3,						// The game is paused
  };

  enum class      Button : uint16_t
  {
    PLAY = 0,
    LEFT_PANE = 1,
    RIGHT_PANE = 2,
    SCOREBOARD = 3,
    QUIT = 4,
    NAME = 5
  };

  struct playerName
  {
    std::string 	name;			// Name of the player
    unsigned int	idx;			// Index of the selected letter
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
