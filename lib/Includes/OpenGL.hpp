#ifndef OPENGL_HPP_
#define OPENGL_HPP_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "IGraphic.hpp"

namespace arcade
{
  class OpenGL : public IGraphic
  {
    public:
      OpenGL();
      virtual ~OpenGL();
      virtual void									ShowGame(WhereAmI *, GetMap *, Assets &);
      virtual void									ShowMenu(std::vector<std::string>, int, std::vector<std::string>, int, arcade::Button, const arcade::playerName &);
      virtual void									GetInput(ICore *);
      virtual void					        PrintGameOver(arcade::Status);
      virtual void									ShowScoreboard(const std::string &, std::vector<arcade::IScore *>);
      void                          initColors(const Assets &);
      virtual void									ShowScore(const arcade::IScore *, const std::vector<arcade::IScore *> &);

    private:
      void 													setupOpengl(int, int);
      void 													handle_key_down(SDL_keysym *, ICore *);
      void													drawSquare(float, float, std::vector<float>, float);
      void								  				drawNumber(int, float, float, std::vector<float>);
      void								  				drawText(char, float, float, std::vector<float>);
      bool													isOnMap(arcade::WhereAmI *, int, int) const;
      void													initMapColor(Assets &assets);
      void									        initMapColor();
      void													initMapInputGame();
      void													initMapInputCore();
      void													fillColor(float, float, float);
      void													putStrOpenGl(const char *, float, float, std::vector<float>);
      void													putNbrOpenGl(int, float, float, std::vector<float>);

      std::vector<float>																					_rgb;
      std::map<arcade::TileType, std::vector<float>>							_colors;
      std::map<int, arcade::CommandType>													input_game;
      std::map<int, arcade::CoreCommand>													input_core;
      float																												_angle;

      static const std::string                            RESSOURCES_ASCII;
    };
};

#endif
