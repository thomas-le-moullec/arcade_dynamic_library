#ifndef CORE_HPP_
#define CORE_HPP_

#include <chrono>
#include <thread>
#include <vector>
#include <map>
#include "ICore.hpp"
#include "IGraphic.hpp"
#include "IGame.hpp"

namespace arcade
{
  class Core : public ICore
  {
    public:
      Core();
	    virtual ~Core();
      virtual void		NotifyGame(arcade::CommandType);
      virtual void		NotifyCore(arcade::CoreCommand);
      virtual void		RunArcade();
      virtual void    LoadGame(const std::string&);
      virtual void    LoadGraphic(const std::string&);
      void						LoadPrevGraphic();
      void						LoadNextGraphic();
      void						LoadPrevGame();
      void						LoadNextGame();
      void						Restart();
      void	  				Menu();
      void						Quit();
      void						Pause();
    private:
      IGame												*_game;
      IGraphic										*_graphic;
      void												*_handle_game;
      void												*_handle_graphic;
      arcade::CoreCommand					_coreCmd;
      std::vector<std::string> 		_libs;
  };
};

#endif
