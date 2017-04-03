#include "LSfml.hpp"

arcade::LSfml::LSfml()
{
  setFullScreen(false);
  setWindow(WIDTH_WIN, HEIGHT_WIN, PIXELS_WIN, isFullScreen());
  initGameInputs();
  initCoreInputs();
  if (!_fontArial.loadFromFile("arial.ttf")) {
    _window->close();
    exit(0);
  }
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
  _core_input[sf::Keyboard::Escape] = CoreCommand::ESCAPE;
}

/*void   arcade::LSfml::print_commands()
{

  mvprintw(y++, x, "z - Se déplacer vers le haut");
  mvprintw(y++, x, "s - Se déplacer vers le bas");
  mvprintw(y++, x, "q - Se déplacer vers la droite");
  mvprintw(y++, x, "d - Se déplacer vers la gauche");
  y++;
  mvprintw(y++, x, "espace - Mettre le jeu en pause");
  mvprintw(y++, x, "esc - Quitter le jeu");
  mvprintw(y++, x, "8 - Recommencer le jeu");
  mvprintw(y++, x, "9 - Quitter l'arcade");
}*/

void                  arcade::LSfml::setColor(const unsigned int &color, arcade::TileType tile, sf::RectangleShape rectangle)
{
  sf::Texture         texture;

  _mapTexture[tile] = texture;
  if (!_mapTexture[arcade::TileType::EMPTY].loadFromFile("Errorplancher.png")) //need a map of tiletype and .png
    rectangle.setFillColor(sf::Color(color));
  else
    rectangle.setTexture(&_mapTexture[tile]);
  _map[tile] = rectangle;
}

void                  arcade::LSfml::initMap(int height, int width, const Assets &assets)
{
  int                 idx(0);
  sf::RectangleShape  rectangle(sf::Vector2f((WIDTH_WIN * 0.60) / width, (HEIGHT_WIN * 0.60) / height));//add value to map->width et map->height

  while (idx < static_cast<int>(arcade::TileType::OTHER)) {
    setColor(assets.c_map[idx].color, static_cast<arcade::TileType>(idx), rectangle);
    idx++;
  }
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
           _event.key.code == sf::Keyboard::Num9 || _event.key.code == sf::Keyboard::Escape)
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



void		arcade::LSfml::ShowGame(arcade::WhereAmI *player, arcade::GetMap *map, const Assets &assets)
{
    unsigned int x;
    unsigned int y;
    int          i;
    //static bool  initialisation = true; //Réinitialiser la map dans le cas ou il y a eu des changements d'assets, de jeu etc.

    //if (initialisation) {
      _player = new sf::RectangleShape(sf::Vector2f((WIDTH_WIN * 0.60) / map->width, (HEIGHT_WIN * 0.60) / map->height)); //add value to map->width et map->height
      _player->setFillColor(sf::Color(assets.c_player.color));
      initMap(map->height, map->width, assets);
    //  initialisation = false;
    //}

    y = 0;
    i = 0;
    _window->clear();
    while (y < map->height) {
      x = 0;
      while (x < map->width && i < map->width * map->height) {
        if (this->isOnMap(player, i, map->width) == true) {
          _player->setPosition((WIDTH_WIN * 0.20) + (x * ((WIDTH_WIN * 0.60)/ map->width)), (HEIGHT_WIN * 0.20) + (y * ((HEIGHT_WIN * 0.60) / map->height)));
          _window->draw(*_player);
        }
        else {
          _map[map->tile[i]].setPosition((WIDTH_WIN * 0.20) + (x * ((WIDTH_WIN * 0.60) / map->width)), (HEIGHT_WIN * 0.20) + (y * ((HEIGHT_WIN * 0.60) / map->height)));
          _window->draw(_map[map->tile[i]]);
        }
        x++;
        i++;
      }
      y++;
    }
    //print_commands();
    _window->display();
}

void										arcade::LSfml::ShowMenu(std::vector<std::string> gamesLibs, int idxGame,
                                                std::vector<std::string> graphicsLibs, int idxGraphic,
                                                arcade::Player player)
{
  sf::Text              title;
  sf::Text              graphics;
  sf::Text              games;
  sf::Texture           texture;

  (void)player;
  _window->clear();
  if (!texture.loadFromFile("backgroundMenu.jpg")) {
  }
  sf::RectangleShape  background(sf::Vector2f(WIDTH_WIN, HEIGHT_WIN));
  background.setTexture(&texture);
  _window->draw(background);
  title.setFont(_fontArial);
  graphics.setFont(_fontArial);
  games.setFont(_fontArial);
  title.setString("Menu");
  title.setCharacterSize(42);
  title.setColor(sf::Color::Green);
  title.setStyle(sf::Text::Bold);
  sf::FloatRect textRect = title.getLocalBounds();
  title.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
  title.setPosition(sf::Vector2f(WIDTH_WIN/2.0f,HEIGHT_WIN * 0.20));
  for (unsigned int idx = 0; idx < graphicsLibs.size(); idx++){
    graphics.setString(graphicsLibs[idx].c_str());
    graphics.setCharacterSize(18);
    graphics.setColor(sf::Color::White);
    graphics.setStyle(sf::Text::Regular);
    sf::FloatRect textRectGraphics = graphics.getLocalBounds();
    graphics.setOrigin(textRectGraphics.left + textRectGraphics.width/2.0f, textRectGraphics.top  + textRectGraphics.height/2.0f);
    graphics.setPosition(sf::Vector2f(WIDTH_WIN * 0.30, (HEIGHT_WIN * 0.20) + 300 + (idx * 50)));
    if (static_cast<int>(idx) == idxGraphic) {
      graphics.setCharacterSize(24);
      graphics.setColor(sf::Color::Red);
      graphics.setStyle(sf::Text::Bold);
    }
    _window->draw(graphics);
  }
  //functions !
  for (unsigned int idx = 0; idx < gamesLibs.size(); idx++){
    games.setString(gamesLibs[idx].c_str());
    games.setCharacterSize(18);
    games.setColor(sf::Color::White);
    games.setStyle(sf::Text::Regular);
    sf::FloatRect textRectGraphics = games.getLocalBounds();
    games.setOrigin(textRectGraphics.left + textRectGraphics.width/2.0f, textRectGraphics.top  + textRectGraphics.height/2.0f);
    games.setPosition(sf::Vector2f((WIDTH_WIN * 0.7), (HEIGHT_WIN * 0.20) + 300 + (idx * 50)));
    if (static_cast<int>(idx) == idxGame) {
      games.setCharacterSize(24);
      games.setColor(sf::Color::Red);
      games.setStyle(sf::Text::Bold);
    }
    _window->draw(games);
  }
  _window->draw(title);
  _window->display();
}

void										arcade::LSfml::ShowScoreboard(std::string &nameGame, std::vector<arcade::Score> score)
{
  (void)nameGame;
  (void)score;
}

void										arcade::LSfml::ShowScore(const arcade::Score &currentScore, const std::vector<arcade::Score> &bestScore)
{
  (void)currentScore;
  (void)bestScore;
}

extern "C" arcade::IGraphic*		CreateDisplayModule()
{
  return new arcade::LSfml();
}

void										arcade::LSfml::PrintGameOver(arcade::Status status)
{
  sf::Texture           texture;

  _window->clear();
  if (status == arcade::Status::WIN && !texture.loadFromFile("win.png"))
  {
  }
  if (status == arcade::Status::LOSE && !texture.loadFromFile("lose.jpg"))
  {
  }
  sf::RectangleShape  background(sf::Vector2f(WIDTH_WIN, HEIGHT_WIN));
  background.setTexture(&texture);
  _window->draw(background);
  _window->display();
}
