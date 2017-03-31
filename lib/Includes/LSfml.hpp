#ifndef LSFML_HPP_
#define LSFML_HPP_

#include "IGraphic.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define WIDTH_WIN 1200
#define HEIGHT_WIN 980
#define PIXELS_WIN 24

namespace arcade
{
  class LSfml : public IGraphic
  {
    public:
      LSfml();
      virtual ~LSfml();
      virtual void		                                   ShowGame(WhereAmI *, GetMap *, const Assets &);
      virtual void				                               GetInput(ICore *);
      virtual void					                             PrintGameOver(arcade::Status) const;
      virtual void																		   ShowMenu(std::vector<std::string>, std::vector<std::string>, int, int);
      virtual void																		   ShowScoreboard();
      virtual void																			 ShowScore(std::vector<Score>);

    private:
      bool													                     isOnMap(WhereAmI *, int, int) const;
      void                                               initMap(int, int, const Assets &);
      void                                               setFullScreen(bool);
      bool                                               isFullScreen();
      void                                               setWindow(unsigned int, unsigned int, unsigned int, bool);
      void                                               initGameInputs();
      void                                               initCoreInputs();
      void                                               setColor(const unsigned int &, arcade::TileType, sf::RectangleShape);
      sf::RenderWindow                                   *_window;
      sf::Event                                           _event;
      bool                                                _fullScreen;
      std::map<arcade::TileType, sf::RectangleShape>			_map;
      sf::RectangleShape                                  *_player;
      std::map<arcade::TileType, sf::Texture>			        _mapTexture;
      std::map<sf::Keyboard::Key, arcade::CommandType>    _game_input;
      std::map<sf::Keyboard::Key, arcade::CoreCommand>    _core_input;
      sf::Texture                                         _textureEmpty;
      sf::Texture                                         _textureBlock;
      sf::Texture                                         _texturePower;
  };
};


#endif
