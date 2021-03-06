#ifndef LSFML_HPP_
#define LSFML_HPP_

#include "IGraphic.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <SFML/Audio.hpp>

namespace arcade
{
  class LSfml : public IGraphic
  {
    public:
      LSfml();
      virtual ~LSfml();
      virtual void		                                   ShowGame(WhereAmI *, GetMap *, Assets &);
      virtual void				                               GetInput(ICore *);
      virtual void					                             PrintGameOver(arcade::Status);
      virtual void																		   ShowMenu(const std::vector<std::string>, int, const std::vector<std::string>, int, Button, const arcade::playerName &);
			virtual void										 									 ShowScoreBoard(const std::string &, const std::vector<arcade::IScore *> &);
      virtual void																			 ShowScore(arcade::IScore *, const std::vector<arcade::IScore *> &);

    private:
      bool													                     isOnMap(WhereAmI *, int, int) const;
      bool													                     isHeadPlayer(WhereAmI *, int, int) const;
      void                                               initMap(int, int, Assets &);
      void                                               setFullScreen(bool);
      bool                                               isFullScreen();
      void                                               setWindow(unsigned int, unsigned int, unsigned int, bool);
      void                                               initGameInputs();
      void                                               initCoreInputs();
      void                                               setColor(const unsigned int &, arcade::TileType, sf::RectangleShape);
      void                                               print_commands() const;
      void                                               loadSounds();
      void                                               loadTextures(Assets &);
      void                                               playSound(arcade::SoundType type, unsigned int, float pitch = 1);
      sf::Texture                                        *_LoseTexture;
      sf::Texture                                        *_WinTexture;
      unsigned int                                       _textureMapSize;
      std::map<arcade::SoundType, sf::SoundBuffer>       _sounds;
      sf::Sound                                          _sound;
      sf::RenderWindow                                   *_window;
      sf::Event                                           _event;
      sf::Texture                                         *_playerTexture;
      sf::Texture                                         *_mapTexture;
      sf::Texture                                         *_backgroundTexture;
      bool                                                _fullScreen;
      sf::Music                                           _music;
      std::map<arcade::TileType, sf::RectangleShape>			_map;
      sf::RectangleShape                                  *_player;
      std::map<sf::Keyboard::Key, arcade::CommandType>    _game_input;
      std::map<sf::Keyboard::Key, arcade::CoreCommand>    _core_input;
      sf::Font                                            _fontMasque;
      sf::Font                                            _fontArial;
      static const unsigned int                           WIDTH_WIN;
      static const unsigned int                           HEIGHT_WIN;
      static const unsigned int                           PIXELS_WIN;
      static const std::string                            RESSOURCES;
      static const std::string                            RESSOURCES_SOUNDS;
      static const std::string                            RESSOURCES_FONTS;
      static const std::string                            RESSOURCES_TEXTURES;
  };
};

#endif
