#include "LSfml.hpp"
#include <sstream>

arcade::LSfml::LSfml()
{
  setFullScreen(false);
  setWindow(WIDTH_WIN, HEIGHT_WIN, PIXELS_WIN, isFullScreen());
  initGameInputs();
  initCoreInputs();
  if (!_fontMasque.loadFromFile("MASQUE__.ttf") || !_fontArial.loadFromFile("arial.ttf")) {
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

void   arcade::LSfml::print_commands() const
{
  sf::Text                    commands;
  std::string                 restart = std::to_string(8) + " - Recommencer";
  static sf::RectangleShape   background(sf::Vector2f(WIDTH_WIN, HEIGHT_WIN * 0.07));

  background.setPosition(0, HEIGHT_WIN * 0.93);
  background.setFillColor(sf::Color::Black);
  _window->draw(background);
  background.setPosition(0, 0);
  _window->draw(background);
  commands.setFont(_fontArial); //Not fun but visible
  commands.setCharacterSize(18);
  commands.setColor(sf::Color(0xe2fefeFF));
  commands.setStyle(sf::Text::Bold);
  sf::FloatRect commandsArea = commands.getLocalBounds();
  commands.setOrigin(commandsArea.left + commandsArea.width/2.0f, commandsArea.top  + commandsArea.height/2.0f);

  commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.05, HEIGHT_WIN * 0.025));
  commands.setString("z - Deplacement Haut");
  _window->draw(commands);
  commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.30, HEIGHT_WIN * 0.025));
  commands.setString("s - Deplacement Bas");
  _window->draw(commands);
  commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.55, HEIGHT_WIN * 0.025));
  commands.setString("q - Deplacement Droite");
  _window->draw(commands);
  commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.8, HEIGHT_WIN * 0.025));
  commands.setString("d - Deplacement Gauche");
  _window->draw(commands);
  commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.15, (HEIGHT_WIN * 0.95)));
  commands.setString("espace - Pause");
  _window->draw(commands);
  commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.35, (HEIGHT_WIN * 0.95)));
  commands.setString("esc - Quitter le jeu");
  _window->draw(commands);
  commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.55, (HEIGHT_WIN * 0.95)));
  commands.setString("8 - Recommencer");
  _window->draw(commands);
  commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.75, (HEIGHT_WIN * 0.95)));
  commands.setString("9 - Quitter l'arcade");
  _window->draw(commands);
}

std::string	arcade::LSfml::cutName(std::string &libName, int size_path) const
{
  return libName.substr(size_path, libName.length() - 3 - size_path);
}

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
    _window = new sf::RenderWindow(sf::VideoMode(width, height, pixels), "Play Fullscreen !", sf::Style::Fullscreen);
  else
    _window = new sf::RenderWindow(sf::VideoMode(width, height, pixels), "Play !");
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
    static bool  initialisation = true; //Réinitialiser la map dans le cas ou il y a eu des changements d'assets, de jeu etc.
    static sf::RectangleShape  background(sf::Vector2f(WIDTH_WIN, HEIGHT_WIN));

    _window->clear();
    if (initialisation) {
      if (!_textureBackgroundGame.loadFromFile("backgroundGame.jpg")) {
      }
      initialisation = false;
      background.setTexture(&_textureBackgroundGame);
    }
    _window->draw(background);
    _player = new sf::RectangleShape(sf::Vector2f((WIDTH_WIN * 0.60) / map->width, (HEIGHT_WIN * 0.60) / map->height)); //add value to map->width et map->height
    _player->setFillColor(sf::Color(assets.c_player.color));
    initMap(map->height, map->width, assets);

    y = 0;
    i = 0;
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
    print_commands();
    //_window->display();
}

void										arcade::LSfml::ShowMenu(std::vector<std::string> gamesLibs, int idxGame,
                                                std::vector<std::string> graphicsLibs, int idxGraphic,
                                                const arcade::playerName &player)
{
  sf::Text              graphics;
  sf::Text              games;
  sf::Texture           texture;

  (void)player;
  _window->clear();
  if (!texture.loadFromFile("backgroundMenu.gif")) {
  }
  sf::RectangleShape  background(sf::Vector2f(WIDTH_WIN, HEIGHT_WIN));
  background.setTexture(&texture);
  _window->draw(background);
  graphics.setFont(_fontMasque);
  games.setFont(_fontMasque);
  for (unsigned int idx = 0; idx < graphicsLibs.size(); idx++){
    graphics.setString(cutName(graphicsLibs[idx], 15));
    graphics.setCharacterSize(12);
    graphics.setColor(sf::Color(0x157FEFFF));
    graphics.setStyle(sf::Text::Regular);
    sf::FloatRect textRectGraphics = graphics.getLocalBounds();
    graphics.setOrigin(textRectGraphics.left + textRectGraphics.width/2.0f, textRectGraphics.top  + textRectGraphics.height/2.0f);
    graphics.setPosition(sf::Vector2f(WIDTH_WIN * 0.2, (HEIGHT_WIN * 0.20) + 200 + (idx * 50)));
    if (static_cast<int>(idx) == idxGraphic) {
      graphics.setCharacterSize(28);
      graphics.setColor(sf::Color(0xD011D0FF));
      graphics.setStyle(sf::Text::Bold);
    }
    _window->draw(graphics);
  }
  //functions !
  for (unsigned int idx = 0; idx < gamesLibs.size(); idx++){
    games.setString(cutName(gamesLibs[idx], 17));
    games.setCharacterSize(12);
    games.setColor(sf::Color(0x157FEFFF));
    games.setStyle(sf::Text::Regular);
    sf::FloatRect textRectGraphics = games.getLocalBounds();
    games.setOrigin(textRectGraphics.left + textRectGraphics.width/2.0f, textRectGraphics.top  + textRectGraphics.height/2.0f);
    games.setPosition(sf::Vector2f((WIDTH_WIN * 0.7), (HEIGHT_WIN * 0.20) + 200 + (idx * 50)));
    if (static_cast<int>(idx) == idxGame) {
      games.setCharacterSize(28);
      games.setColor(sf::Color(0xD011D0FF));
      games.setStyle(sf::Text::Bold);
    }
    _window->draw(games);
  }
  //_window->draw(title);
  _window->display();
}

void										arcade::LSfml::ShowScoreboard(const std::string &nameGame, std::vector<arcade::Score> score)
{
  (void)nameGame;
  (void)score;
}

void										arcade::LSfml::ShowScore(const arcade::Score &currentScore, const std::vector<arcade::Score> &bestScore)
{
  sf::Text              commands;

  commands.setFont(_fontMasque);
  commands.setCharacterSize(17);
  commands.setColor(sf::Color(0xe2fefeFF));
  sf::FloatRect commandsArea = commands.getLocalBounds();
  commands.setOrigin(commandsArea.left + commandsArea.width/2.0f, commandsArea.top  + commandsArea.height/2.0f);

  commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.815, (HEIGHT_WIN * 0.20) + 100));
  commands.setStyle(sf::Text::Bold);
  commands.setString("Meilleurs Scores");
  _window->draw(commands);
  commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.815, (HEIGHT_WIN * 0.20) + 300));
  commands.setString("Score actuel");
  _window->draw(commands);
  commands.setFont(_fontArial);
  commands.setCharacterSize(19);

  for (unsigned int i = 0; i < bestScore.size() && bestScore.size() > 0; i++) {
    commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.815, (HEIGHT_WIN * 0.20) + ((i + 1) * 50) + 100));
    commands.setString(bestScore[i].namePlayer.c_str());
    _window->draw(commands);
    commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.85, (HEIGHT_WIN * 0.20) + ((i + 1) * 50) + 100));
    commands.setString(std::to_string(bestScore[i].valueScore));
    _window->draw(commands);
  }
  commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.85, (HEIGHT_WIN * 0.20) + 350));
  commands.setString(std::to_string(currentScore.valueScore));
  _window->draw(commands);
  _window->display();
}

extern "C" arcade::IGraphic*		CreateDisplayModule()
{
  return new arcade::LSfml();
}

void										arcade::LSfml::PrintGameOver(arcade::Status status)
{
  sf::Texture           texture;

  _window->clear();
  if (status == arcade::Status::WIN && !texture.loadFromFile("win.jpg"))
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
