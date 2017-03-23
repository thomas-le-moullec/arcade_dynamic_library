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
      IGraphic				*_graphic;
      void						*_handle_game;
      void						*_handle_graphic;
      void						loadLibraries(const std::string &lib);
      void				    unloadLibrairies();

      //template<typename T>
      //T *loadArcade(const std::string &, const std::string &);
  };
};

#endif
