#include "LSfml.hpp"

const std::string arcade::LSfml::RESSOURCES = "./ressources/";
const std::string arcade::LSfml::RESSOURCES_SOUNDS = "./ressources/sounds/";
const std::string arcade::LSfml::RESSOURCES_FONTS = "./ressources/fonts/";
const std::string arcade::LSfml::RESSOURCES_TEXTURES = "./ressources/textures/";
const unsigned int arcade::LSfml::WIDTH_WIN = 1200;
const unsigned int arcade::LSfml::HEIGHT_WIN = 720;
const unsigned int arcade::LSfml::PIXELS_WIN = 24;

arcade::LSfml::LSfml()
{
  setFullScreen(false);
  setWindow(WIDTH_WIN, HEIGHT_WIN, PIXELS_WIN, isFullScreen());
  initGameInputs();
  initCoreInputs();
  if (!_fontMasque.loadFromFile(RESSOURCES_FONTS + "Masque.ttf")) {
    if (!_fontMasque.loadFromFile(RESSOURCES_FONTS + "arial.ttf")) {
      std::cerr << "Error on loading Fonts." << std::endl;
      _window->close();
      exit(0);
    }
  }
  if (!_fontArial.loadFromFile(RESSOURCES_FONTS + "arial.ttf")) {
    std::cerr << "Error on loading Fonts." << std::endl;
    _window->close();
    exit(0);
  }
  loadSounds();
  _backgroundTexture = NULL;
  _playerTexture = NULL;
  _mapTexture = NULL;
  if ((_WinTexture = new sf::Texture) && !_WinTexture->loadFromFile(RESSOURCES+"win.jpg"))
    _WinTexture = NULL;
  if ((_LoseTexture = new sf::Texture) && !_LoseTexture->loadFromFile(RESSOURCES+"lose.jpg"))
    _LoseTexture = NULL;
}

arcade::LSfml::~LSfml()
{
  _window->close();
}

void    arcade::LSfml::loadSounds()
{
  if (!_music.openFromFile(RESSOURCES_SOUNDS + "Push_It_To_The_Limit_scarface_.ogg")) {
    //maybe do smth
  }
  _music.setVolume(15);
  _music.play();
  _music.setLoop(true);

  _sounds[arcade::SoundType::EATAPPLE].loadFromFile(RESSOURCES_SOUNDS + "eatApple.wav");
  _sounds[arcade::SoundType::SHOOT].loadFromFile(RESSOURCES_SOUNDS + "shoot.wav");
}

void    arcade::LSfml::loadTextures(Assets &assets)
{
  if (assets.loadMap) {
    if ((_mapTexture = new sf::Texture) && !_mapTexture->loadFromFile(RESSOURCES_TEXTURES+assets.t_map))
      _mapTexture = NULL;
    assets.loadMap = false;
  }
  if (assets.loadPlayer) {
    if ((_playerTexture= new sf::Texture) && !_playerTexture->loadFromFile(RESSOURCES_TEXTURES+assets.t_player))
      _playerTexture = NULL;
    assets.loadPlayer = false;
  }
  if (assets.loadBg) {
    if ((_backgroundTexture = new sf::Texture) && !_backgroundTexture->loadFromFile(RESSOURCES_TEXTURES+assets.t_bg))
    {
      if (!_backgroundTexture->loadFromFile(RESSOURCES+"defaultGameBackground.jpg"))
      {
        _backgroundTexture = NULL;
      }
      assets.loadBg = false;
    }
    assets.loadBg = false;
  }
}

void    arcade::LSfml::initGameInputs()
{
  _game_input[sf::Keyboard::Q] = CommandType::GO_LEFT;
  _game_input[sf::Keyboard::Z] = CommandType::GO_UP;
  _game_input[sf::Keyboard::D] = CommandType::GO_RIGHT;
  _game_input[sf::Keyboard::S] = CommandType::GO_DOWN;
  _game_input[sf::Keyboard::Return] = CommandType::SHOOT;
  _game_input[sf::Keyboard::T] = CommandType::ILLEGAL;
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

void                  arcade::LSfml::setColor(const unsigned int &color, arcade::TileType tile, sf::RectangleShape rectangle)
{
  rectangle.setFillColor(sf::Color(color));
  _map[tile] = rectangle;
  if (_mapTexture != NULL) {
    _textureMapSize = _mapTexture->getSize().y;
    _map[tile].setFillColor(sf::Color::White);
    _map[tile].setTexture(_mapTexture);
    _map[tile].setTextureRect(sf::IntRect(_textureMapSize * static_cast<int>(tile), 0, _textureMapSize, _textureMapSize));
  }
}

void                  arcade::LSfml::initMap(int height, int width, Assets &assets)
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
           _event.key.code == sf::Keyboard::Return || _event.key.code == sf::Keyboard::T)
           core->NotifyScene(_game_input[_event.key.code]);
        if (_event.key.code == sf::Keyboard::Num2 || _event.key.code == sf::Keyboard::Num3 ||
           _event.key.code == sf::Keyboard::Num4 || _event.key.code == sf::Keyboard::Num5 ||
           _event.key.code == sf::Keyboard::Space || _event.key.code == sf::Keyboard::Num8 ||
           _event.key.code == sf::Keyboard::Num9 || _event.key.code == sf::Keyboard::Escape)
           core->NotifyCore(_core_input[_event.key.code]);
      case sf::Event::LostFocus:
        //std::cout << "Lost Focus !" << std::endl;
        break;
      case sf::Event::GainedFocus:
        //std::cout << "Gained Focus !" << std::endl;
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

bool		arcade::LSfml::isHeadPlayer(arcade::WhereAmI *player, int i, int width) const
{
  for (int pos = 0; pos < player->lenght; pos++)
    if (player->position[pos].x + player->position[pos].y * width == i && pos == 0)
      return true;
  return false;
}

void arcade::LSfml::playSound(arcade::SoundType type)
{
  _sound.setBuffer(_sounds[type]);
  _sound.setVolume(100);
  _sound.play();
}

void		arcade::LSfml::ShowGame(arcade::WhereAmI *player, arcade::GetMap *map, Assets &assets)
{
    unsigned int          x;
    unsigned int          y;
    int                   i;
    static                sf::RectangleShape  background(sf::Vector2f(WIDTH_WIN, HEIGHT_WIN));
    unsigned int          texturePlayerSize;

    _window->clear();
    if (assets.sound != arcade::SoundType::NOTHING && \
        _sound.getStatus() != sf::SoundSource::Playing)
      playSound(assets.sound);
    loadTextures(assets);
    initMap(map->height, map->width, assets);
    if (_playerTexture != NULL) {
      texturePlayerSize = _playerTexture->getSize().y;
    }
    if (_backgroundTexture != NULL)
      background.setTexture(_backgroundTexture);
    _window->draw(background);
    y = 0;
    i = 0;
    while (y < map->height) {
      x = 0;
      while (x < map->width && i < map->width * map->height) {
        _player = new sf::RectangleShape(sf::Vector2f((WIDTH_WIN * 0.60) / map->width, (HEIGHT_WIN * 0.60) / map->height)); //add value to map->width et map->height
        _player->setFillColor(sf::Color(assets.c_player.color));
        if (this->isOnMap(player, i, map->width) == true) {
          _player->setPosition((WIDTH_WIN * 0.20) + (x * ((WIDTH_WIN * 0.60)/ map->width)), (HEIGHT_WIN * 0.20) + (y * ((HEIGHT_WIN * 0.60) / map->height)));
          if (isHeadPlayer(player, i, map->width) == true) {
            _player->setFillColor(sf::Color::White);
            _player->setTexture(_playerTexture);
            _player->setTextureRect(sf::IntRect(texturePlayerSize * (static_cast<int>(assets.dir) - 2), 0, texturePlayerSize, texturePlayerSize));
          }
          else
          {
            _player->setFillColor(sf::Color::White);
            _player->setTexture(_mapTexture);
            _player->setTextureRect(sf::IntRect(_textureMapSize * static_cast<int>(arcade::TileType::MY_SHOOT), 0, _textureMapSize, _textureMapSize));
          }
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
}

void										arcade::LSfml::ShowMenu(const std::vector<std::string> gamesLibs, int idxGame,
                                                const std::vector<std::string> graphicsLibs, int idxGraphic,
                                                arcade::Button button, const arcade::playerName &player)
{
  sf::Text              graphics;
  sf::Text              games;
  sf::Texture           texture;
  sf::Text              name;

  (void)button;
  _window->clear();
  if (!texture.loadFromFile(RESSOURCES+"menu.png")) {
  }
  sf::RectangleShape  background(sf::Vector2f(WIDTH_WIN, HEIGHT_WIN));
  background.setTexture(&texture);
  _window->draw(background);
  name.setCharacterSize(30);
  name.setFont(_fontMasque);
  for (unsigned int i = 0; i < 3; i++)
  {
    name.setStyle(sf::Text::Regular);
    name.setString(player.name[i]);
    name.setColor(sf::Color::Black);
    sf::FloatRect textName = name.getLocalBounds();
    name.setOrigin(textName.left + textName.width/2.0f, textName.top  + textName.height/2.0f);
    name.setPosition(sf::Vector2f((WIDTH_WIN * 0.45) + ((i  + 1)* 30), HEIGHT_WIN * 0.57));
    if (i == player.idx) {
      name.setStyle(sf::Text::Bold);
      name.setColor(sf::Color(0x157FEFFF));
    }
    _window->draw(name);
  }
  graphics.setFont(_fontMasque);
  games.setFont(_fontMasque);
  for (unsigned int idx = 0; idx < graphicsLibs.size(); idx++) {
    graphics.setString(graphicsLibs[idx]);
    graphics.setCharacterSize(16);
    graphics.setColor(sf::Color(0x157FEFFF));
    graphics.setStyle(sf::Text::Regular);
    sf::FloatRect textRectGraphics = graphics.getLocalBounds();
    graphics.setOrigin(textRectGraphics.left + textRectGraphics.width/2.0f, textRectGraphics.top  + textRectGraphics.height/2.0f);
    graphics.setPosition(sf::Vector2f(WIDTH_WIN * 0.18, (HEIGHT_WIN * 0.20) + 200 + (idx * 50)));
    if (static_cast<int>(idx) == idxGraphic) {
      graphics.setCharacterSize(30);
      graphics.setColor(sf::Color(0xD011D0FF));
      graphics.setStyle(sf::Text::Bold);
    }
    _window->draw(graphics);
  }
  for (unsigned int idx = 0; idx < gamesLibs.size(); idx++){
    games.setString(gamesLibs[idx]);
    games.setCharacterSize(16);
    games.setColor(sf::Color(0x157FEFFF));
    games.setStyle(sf::Text::Regular);
    sf::FloatRect textRectGraphics = games.getLocalBounds();
    games.setOrigin(textRectGraphics.left + textRectGraphics.width/2.0f, textRectGraphics.top  + textRectGraphics.height/2.0f);
    games.setPosition(sf::Vector2f((WIDTH_WIN * 0.8), (HEIGHT_WIN * 0.20) + 200 + (idx * 50)));
    if (static_cast<int>(idx) == idxGame) {
      games.setCharacterSize(30);
      games.setColor(sf::Color(0xD011D0FF));
      games.setStyle(sf::Text::Bold);
    }
    _window->draw(games);
  }
  _window->display();
}

void										arcade::LSfml::ShowScoreBoard(const std::string &nameGame, const std::vector<arcade::IScore *> &score)
{
  int									  y = 0;
  sf::Texture           texture;
  sf::Text              Scores;

  _window->clear();
  if (!texture.loadFromFile(RESSOURCES+"Scoreboard.gif")) {
  }
  else {
    sf::RectangleShape  background(sf::Vector2f(WIDTH_WIN, HEIGHT_WIN));
    background.setTexture(&texture);
    _window->draw(background);
  }
  Scores.setFont(_fontMasque);
  Scores.setCharacterSize(25);
  Scores.setColor(sf::Color(0xe2fefeFF));
  sf::FloatRect ScoresArea = Scores.getLocalBounds();
  Scores.setOrigin(ScoresArea.left + ScoresArea.width/2.0f, ScoresArea.top  + ScoresArea.height/2.0f);
  Scores.setStyle(sf::Text::Bold);

  Scores.setPosition(sf::Vector2f(WIDTH_WIN * 0.47, HEIGHT_WIN * 0.1));
  Scores.setString(nameGame);
  _window->draw(Scores);
  Scores.setCharacterSize(20);
  Scores.setPosition(sf::Vector2f(WIDTH_WIN * 0.42, (HEIGHT_WIN * 0.15) + 50));
  Scores.setFont(_fontArial);
  Scores.setString("Top 20 des meilleurs scores");
  _window->draw(Scores);
  Scores.setCharacterSize(17);
  for (int i = 0; i < 20 && i < (int)score.size(); i++)
  {
    Scores.setPosition(sf::Vector2f(WIDTH_WIN * 0.30, (HEIGHT_WIN * 0.3) + ((i + 1) * 30)));
    Scores.setString(score[i]->getName());
    Scores.setFont(_fontArial);
    _window->draw(Scores);
    Scores.setPosition(sf::Vector2f(WIDTH_WIN * 0.75, (HEIGHT_WIN * 0.3) + ((i + 1) * 30)));
    Scores.setString(std::to_string(score[i]->getScore()));
    Scores.setFont(_fontArial);
    _window->draw(Scores);
  }
  _window->display();
}

void										arcade::LSfml::ShowScore(arcade::IScore *currentScore, const std::vector<arcade::IScore *> &bestScore)
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
    commands.setString(bestScore[i]->getName().c_str());
    _window->draw(commands);
    commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.9, (HEIGHT_WIN * 0.20) + ((i + 1) * 50) + 100));
    commands.setString(std::to_string(bestScore[i]->getScore()));
    _window->draw(commands);
  }
  commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.85, (HEIGHT_WIN * 0.20) + 350));
  commands.setString(std::to_string(currentScore->getScore()));
  _window->draw(commands);
  _window->display();
}

extern "C" arcade::IGraphic*		CreateDisplayModule()
{
  return new arcade::LSfml();
}

void										arcade::LSfml::PrintGameOver(arcade::Status status)
{
  sf::RectangleShape    background(sf::Vector2f(WIDTH_WIN, HEIGHT_WIN));
  sf::Text              commands;

  commands.setFont(_fontMasque);
  commands.setCharacterSize(35);
  commands.setColor(sf::Color(0xe2fefeFF));
  sf::FloatRect commandsArea = commands.getLocalBounds();
  commands.setOrigin(commandsArea.left + commandsArea.width/2.0f, commandsArea.top  + commandsArea.height/2.0f);

  commands.setPosition(sf::Vector2f(WIDTH_WIN * 0.4, HEIGHT_WIN * 0.40));
  commands.setStyle(sf::Text::Bold);

  _window->clear();
  if (status == arcade::Status::WIN) {
    if (_WinTexture == NULL) {
      commands.setString("YOU WIN!");
      _window->draw(commands);
    }
    else {
      background.setTexture(_WinTexture);
      _window->draw(background);
    }
  }

  if (status == arcade::Status::LOSE) {
    if (_LoseTexture == NULL) {
      commands.setString("GAME OVER");
      _window->draw(commands);
    }
    else {
      background.setTexture(_LoseTexture);
      _window->draw(background);
    }
  }
  _window->display();
}
