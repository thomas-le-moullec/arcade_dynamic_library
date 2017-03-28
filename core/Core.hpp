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
      typedef void	(arcade::Core::*coreFct)();
      typedef void	(arcade::Core::*showScene)();

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
      arcade::Status													_status;
      IGame																		*_game;
      IGraphic																*_graphic;
      void																		*_handle_game;
      void																		*_handle_graphic;
      arcade::CoreCommand											_coreCmd;
      std::map<arcade::CoreCommand, coreFct>	_mapCore;
      std::map<arcade::Status, showScene>			_mapScene;
      std::vector<std::string> 								_graphicLibs;
      std::vector<std::string> 								_gamesLibs;
      unsigned int														_idxGraphicLib;
      unsigned int														_idxGamesLib;

      void						initMapCore();
      void						initMapScene();
      void						getIndexLib(bool, const std::string &);
      void						ShowGame();
      void						ShowMenu();
      void						ShowScoreBoard();
  };
};

#endif
