#include "LSfml.hpp"

arcade::LSfml::LSfml()
{
  setFullScreen(false);
  setWindow(1200, 920, 24, isFullScreen());
  initMap();
  _player = new sf::RectangleShape(sf::Vector2f(25, 25));
  _player->setFillColor(sf::Color::Magenta);
}

arcade::LSfml::~LSfml()
{
  _window->close();
}

void    arcade::LSfml::initMap()
{
  sf::RectangleShape empty(sf::Vector2f(25, 25));
  sf::RectangleShape block(sf::Vector2f(25, 25));
  sf::RectangleShape powerup(sf::Vector2f(25, 25));
  if (!_texture.loadFromFile("wall.jpg")) {
    std::cerr << "Error on Wall.jpg" << std::endl;
  }

  empty.setFillColor(sf::Color::White);
  block.setTexture(&_texture);
  powerup.setFillColor(sf::Color::Green);
  _map[arcade::TileType::EMPTY] = empty;
  _map[arcade::TileType::BLOCK] = block;
  _map[arcade::TileType::POWERUP] = powerup;
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
      case sf::Event::KeyPressed:
        switch (_event.key.code) {
              case sf::Keyboard::Q: core->Notify(CommandType::GO_LEFT); break;
              case sf::Keyboard::Z: core->Notify(CommandType::GO_UP); break;
              case sf::Keyboard::D: core->Notify(CommandType::GO_RIGHT); break;
              case sf::Keyboard::S: core->Notify(CommandType::GO_DOWN); break;
              case sf::Keyboard::Return: core->Notify(CommandType::SHOOT); break;
            }
        break;
      case sf::Event::LostFocus:
        std::cout << "Lost Focus !" << std::endl;
        break;
      case sf::Event::GainedFocus:
        std::cout << "Gained Focus !" << std::endl;
        break;
      default:
          break;
  }
}

bool		arcade::LSfml::isOnMap(arcade::WhereAmI *player, int i, int width) const
{
  for (int pos = 0; pos < player->lenght; pos++)
    if (player->position[pos].x + player->position[pos].y * width == i)
      return true;
  return false;
}

void		arcade::LSfml::ShowGame(arcade::WhereAmI *player, arcade::GetMap *map)
{
    unsigned int x;
    unsigned int y;
    int          i;

    y = 0;
    i = 0;
    _window->clear();
    while (y < map->height) {
      x = 0;
      while (x < map->width && i < map->width * map->height) {
        if (this->isOnMap(player, i, map->width) == true) {
          _player->setPosition(x * 25, y * 25);
          _window->draw(*_player);
        }
        else {
          _map[map->tile[i]].setPosition(x * 25, y * 25);
          _window->draw(_map[map->tile[i]]);
        }
        x++;
        i++;
      }
      y++;
    }
    _window->display();
}

arcade::IGraphic*		CreateDisplayModule()
{
  return new arcade::LSfml();
}

void										arcade::LSfml::PrintGameOver() const
{
}
