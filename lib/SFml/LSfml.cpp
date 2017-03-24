#include "LSfml.hpp"

arcade::LSfml::LSfml()
{
  setFullScreen(false);
  setWindow(800, 600, 24, isFullScreen());
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
              case sf::Keyboard::Q: core->Notify(CommandType::GO_LEFT); break;
              case sf::Keyboard::Z: core->Notify(CommandType::GO_UP); break;
              case sf::Keyboard::D: core->Notify(CommandType::GO_RIGHT); break;
              case sf::Keyboard::S: core->Notify(CommandType::GO_DOWN); break;
              case sf::Keyboard::Return: core->Notify(CommandType::PLAY); break;
            }
        break;
      case sf::Event::LostFocus:
        std::cout << "Lost Focus !" << std::endl;
        break;
      case sf::Event::GainedFocus:
        std::cout << "Gained Focus !" << std::endl;
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

void										arcade::LSfml::PrintGameOver() const
{
}
