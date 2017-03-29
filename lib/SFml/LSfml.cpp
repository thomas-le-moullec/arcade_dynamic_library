#include "LSfml.hpp"

arcade::LSfml::LSfml()
{
  setFullScreen(false);
  setWindow(HEIGHT_WIN, WIDTH_WIN, PIXELS_WIN, isFullScreen());
  initMap();
  _player = new sf::RectangleShape(sf::Vector2f(25, 25));
  _player->setFillColor(sf::Color::Magenta);
  initGameInputs();
  initCoreInputs();
}

arcade::LSfml::~LSfml()
{
  _window->close();
}

void    arcade::LSfml::initGameInputs()
{
  _game_input[sf::Keyboard::Q] = CommandType::GO_LEFT;
  _game_input[sf::Keyboard::Z] = CommandType::GO_UP;
  _game_input[sf::Keyboard::D] = CommandType::GO_RIGHT;
  _game_input[sf::Keyboard::S] = CommandType::GO_DOWN;
  _game_input[sf::Keyboard::Return] = CommandType::SHOOT;
}

void    arcade::LSfml::initCoreInputs()
{
  _core_input[sf::Keyboard::Num2] = CoreCommand::PREV_GRAPHIC;
  _core_input[sf::Keyboard::Num3] = CoreCommand::NEXT_GRAPHIC;
  _core_input[sf::Keyboard::Num4] = CoreCommand::PREV_GAME;
  _core_input[sf::Keyboard::Num5] = CoreCommand::NEXT_GAME;
  _core_input[sf::Keyboard::Space] = CoreCommand::PAUSE;
  _core_input[sf::Keyboard::Num8] = CoreCommand::RESTART;
  _core_input[sf::Keyboard::Num9] = CoreCommand::PREV_GRAPHIC;
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
        if (_event.key.code == sf::Keyboard::Q || _event.key.code == sf::Keyboard::Z ||
           _event.key.code == sf::Keyboard::D || _event.key.code == sf::Keyboard::S ||
           _event.key.code == sf::Keyboard::Return)
           core->NotifyScene(_game_input[_event.key.code]);
        if (_event.key.code == sf::Keyboard::Num2 || _event.key.code == sf::Keyboard::Num3 ||
           _event.key.code == sf::Keyboard::Num4 || _event.key.code == sf::Keyboard::Num5 ||
           _event.key.code == sf::Keyboard::Space || _event.key.code == sf::Keyboard::Num8 ||
           _event.key.code == sf::Keyboard::Num9)
           core->NotifyCore(_core_input[_event.key.code]);
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

void										arcade::LSfml::ShowMenu(std::vector<std::string> graphicsLibs,
                                                std::vector<std::string> gamesLibs,
                                                int, int)
{
  (void)graphicsLibs;
  (void)gamesLibs;
}

void										arcade::LSfml::ShowScoreboard()
{

}

extern "C" arcade::IGraphic*		CreateDisplayModule()
{
  return new arcade::LSfml();
}

void										arcade::LSfml::PrintGameOver() const
{
}
