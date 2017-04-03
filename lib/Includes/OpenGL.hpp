#ifndef OPENGL_HPP_
#define OPENGL_HPP_

#include "IGraphic.hpp"

namespace arcade
{
  class OpenGL : public IGraphic
  {
    public:
      OpenGL();
      virtual ~OpenGL();
      virtual void									ShowGame(WhereAmI *, GetMap *, const Assets &);
      virtual void									ShowMenu(std::vector<std::string>, int, std::vector<std::string>, int, const arcade::playerName &);
      virtual void									GetInput(ICore *);
      virtual void					        PrintGameOver(arcade::Status);
      virtual void									ShowScoreboard(const std::string &, std::vector<arcade::Score>);
      void                          initColors(const Assets &);
      virtual void									ShowScore(const arcade::Score &, const std::vector<arcade::Score> &);
    };
};

#endif
