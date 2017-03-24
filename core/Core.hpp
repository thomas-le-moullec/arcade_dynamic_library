#ifndef CORE_HPP_
#define CORE_HPP_

#include <chrono>
#include <thread>
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
      virtual void		Notify(arcade::CommandType);
      virtual void		RunArcade();
      virtual void   	LoadGame(const std::string&);
      virtual void   	LoadGraphic(const std::string&);
    private:
      IGame						*_game;
      IGraphic				*_graphic;
      void						*_handle_game;
      void						*_handle_graphic;

      void						loadLibraries(const std::string &lib);
      void				    unloadLibrairies();
  };
};

#endif
