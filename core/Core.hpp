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
      typedef void	(arcade::Core::*notifyScene)(arcade::CommandType);

      Core();
	    virtual ~Core();
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
      void						ShowSceneMenu();
      void						ShowSceneGame();
      void						ShowSceneScoreboard();
      void						NotifyScene(CommandType);
      void						NotifySceneMenu(CommandType);
      void						NotifySceneGame(CommandType);
      void						NotifySceneScoreboard(CommandType);

    private:
      arcade::Scene														_scene;
      arcade::Status													_status;
      IGame																		*_game;
      IGraphic																*_graphic;
      void																		*_handle_game;
      void																		*_handle_graphic;
      arcade::CoreCommand											_coreCmd;
      std::map<arcade::CoreCommand, coreFct>	_mapCore;
      std::map<arcade::Scene, showScene>			_mapShowScene;
      std::map<arcade::Scene, notifyScene>		_notifyScene;
      std::vector<std::string> 								_graphicLibs;
      std::vector<std::string> 								_gamesLibs;
      int																			_idxGraphicLib;
      int																			_idxGamesLib;

      void						initMapCore();
      void						initMapShowScene();
      void					  initMapNotifyScene();
      void						getIndexLib(bool, const std::string &);
  };
};

#endif
