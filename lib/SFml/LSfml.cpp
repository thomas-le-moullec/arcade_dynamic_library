#include "LSfml.hpp"

arcade::LSfml::LSfml()
{
  setFullScreen(false);
  setWindow(1920, 1080, 24, isFullScreen());
}

arcade::LSfml::~LSfml()
{
  _window->close();
}

void    arcade::LSfml::setFullScreen(bool isFullScreen)
{
  _fullScreen = isFullScreen;
}

bool    arcade::LSfml::isFullScreen()
{
  return _fullScreen;
}

void    arcade::LSfml::setWindow(unsigned int width, unsigned int height, unsigned int pixels, bool fullscreen)
{
  if (fullscreen == true)
    _window = new sf::RenderWindow(sf::VideoMode(width, height, pixels), "Snake Fullscreen !", sf::Style::Fullscreen);
  else
    _window = new sf::RenderWindow(sf::VideoMode(width, height, pixels), "Snake !");
}

void    arcade::LSfml::GetInput(ICore *core)
{
  _window->pollEvent(_event);
  switch (_event.type)
  {
      // touche pressée
      case sf::Event::KeyPressed:
        switch (_event.key.code) {
              case sf::Keyboard::Q: core->Notify(); break;
              case sf::Keyboard::Z: core->Notify(); break;
              case sf::Keyboard::D: core->Notify(); break;
              case sf::Keyboard::S: core->Notify(); break;
              case sf::Keyboard::BackSpace: core->Notify('\r'); break;
            }
        break;
      case sf::Event::LostFocus:
        //myGame.pause();
        break;
      case sf::Event::GainedFocus:
        //myGame.resume();
        break;
      // on ne traite pas les autres types d'évènements
      default:
          break;
  }
}

void		arcade::LSfml::ShowGame(arcade::WhereAmI *player, arcade::GetMap *map)
{
    _window->clear();
    _window->display();
}

arcade::IGraphic*		CreateDisplayModule()
{
  return new arcade::LSfml();
}
