#ifndef LSFML_HPP_
#define LSFML_HPP_

#include "IGraphic.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace arcade
{
  class LSfml : public IGraphic
  {
    public:
      LSfml();
      virtual ~LSfml();
      virtual void		                                   ShowGame(WhereAmI *, GetMap *);
      virtual void				                               GetInput(ICore *);
      virtual void					                             PrintGameOver() const;
    private:
      bool													                     isOnMap(WhereAmI *, int, int) const;
      void                                               initMap();
      void                                               setFullScreen(bool);
      bool                                               isFullScreen();
      void                                               setWindow(unsigned int, unsigned int, unsigned int, bool);
      sf::RenderWindow                                   *_window;
      sf::Event                                           _event;
      bool                                                _fullScreen;
      std::map<arcade::TileType, sf::RectangleShape>			_map;
      sf::RectangleShape                                  *_player;
      sf::Texture                                         _texture;
  };
};


#endif
