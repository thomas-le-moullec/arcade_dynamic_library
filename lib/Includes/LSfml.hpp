#ifndef LSFML_HPP_
#define LSFML_HPP_

#include "IGraphic.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define WIDTH_WIN 1200
#define HEIGHT_WIN 720
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
      virtual void					                             PrintGameOver(arcade::Status);
      virtual void																		   ShowMenu(std::vector<std::string>, int, std::vector<std::string>, int, Button, const arcade::playerName &);
			virtual void										 									 ShowScoreboard(const std::string &, std::vector<arcade::Score>);
      virtual void																			 ShowScore(const arcade::Score &, const std::vector<arcade::Score> &);

    private:
      bool													                     isOnMap(WhereAmI *, int, int) const;
      void                                               initMap(int, int, const Assets &);
      void                                               setFullScreen(bool);
      bool                                               isFullScreen();
      void                                               setWindow(unsigned int, unsigned int, unsigned int, bool);
      void                                               initGameInputs();
      void                                               initCoreInputs();
      void                                               setColor(const unsigned int &, arcade::TileType, sf::RectangleShape);
      void                                               print_commands() const;
      std::string										                     cutName(std::string &, int) const;
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
      sf::Texture                                         _textureBackgroundGame;
      sf::Font                                            _fontMasque;
      sf::Font                                            _fontArial;
  };
};


#endif
