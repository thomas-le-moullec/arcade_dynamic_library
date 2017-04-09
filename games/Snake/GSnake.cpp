#include "GSnake.hpp"

arcade::GSnake::GSnake()
{
  this->initMap();
  this->initPlayer();
  this->initAssets();
  this->_dir.insert(this->_dir.begin(), CommandType::GO_RIGHT);
  this->_statusGame = arcade::Status::RUNNING;
  this->_score = 0;
  //this->_lvl = 1;
}

bool											arcade::GSnake::isOnSnake(int pos)
{
  for (unsigned int i = 0; i < this->_player.size(); i++)
    if (pos == this->_player[i].y * WIDTH_MAP + this->_player[i].x)
      return true;
  return false;
}

void											arcade::GSnake::dropApple()
{
  int											x = 0;
  int											y = 0;
  int											dropByDefault = 0;

  srand(time(NULL));
  while (this->_map[dropByDefault] != TileType::EMPTY ||
         this->isOnSnake(dropByDefault) == true)
    {
      x = rand() % (WIDTH_MAP - 2) + 1;
      y = rand() % (HEIGHT_MAP - 2) + 1;
      dropByDefault = y * WIDTH_MAP + x;
    }
  this->_map[dropByDefault] = TileType::POWERUP;
}

void											arcade::GSnake::initMap()
{
  unsigned int obstacles;

  srand(time(NULL));
  obstacles = ((WIDTH_MAP * HEIGHT_MAP) / 64);
  for (int i = 0; i < HEIGHT_MAP * WIDTH_MAP; i++)
  {
    if (i < WIDTH_MAP || i >= HEIGHT_MAP * (WIDTH_MAP - 1) ||
        i % WIDTH_MAP == 0 || i % WIDTH_MAP == WIDTH_MAP - 1)
      this->_map[i] = TileType::BLOCK;
    else
      {
        if (obstacles > 0 && (rand() % (WIDTH_MAP * (HEIGHT_MAP / 8))) == 0 && (i != 0 && this->_map[i - 1] != TileType::OBSTACLE) && (i / HEIGHT_MAP) != (HEIGHT_MAP / 2))
        {
          this->_map[i] = TileType::OBSTACLE;
          obstacles--;
        }
        else
          this->_map[i] = TileType::EMPTY;
      }
  }
  this->dropApple();
}

void											arcade::GSnake::initAssets()
{
  _assets.c_player.color = 0x39ff14FF;
  _assets.c_map[static_cast<int>(arcade::TileType::EMPTY)].color = 0xf5f5dcFF;
  _assets.c_map[static_cast<int>(arcade::TileType::BLOCK)].color = 0x5e5d62FF;
  _assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].color = 0xa8353aFF;
  _assets.c_map[static_cast<int>(arcade::TileType::OBSTACLE)].color = 0x809DC4FF;
  _assets.loadMap = true;
  _assets.t_map = "snake_map.png";
  _assets.loadPlayer = true;
  _assets.t_player= "snake_player.png";
  _assets.loadBg = true;
  _assets.t_bg = "SnakeBackgroundGame.jpg";
  _assets.dir = arcade::CommandType::GO_RIGHT;
  _assets.sound = arcade::SoundType::SNAKE_START;
}

void                      arcade::GSnake::increaseSnake(int x, int y)
{
  arcade::Position        pos;

  pos.x = x;
  pos.y = y;
  this->_player.insert(this->_player.begin(), pos);
}

void											arcade::GSnake::initPlayer()
{
  this->increaseSnake(WIDTH_MAP / 2 - 2, HEIGHT_MAP / 2);
  this->increaseSnake(WIDTH_MAP / 2 - 1, HEIGHT_MAP / 2);
  this->increaseSnake(WIDTH_MAP / 2, HEIGHT_MAP / 2);
  this->increaseSnake(WIDTH_MAP / 2 + 1, HEIGHT_MAP / 2);
}

void                      arcade::GSnake::move()
{
  if (this->_dir[0] == CommandType::GO_UP)
    this->increaseSnake(this->_player[0].x, this->_player[0].y - 1);
  else if (this->_dir[0] == CommandType::GO_DOWN)
    this->increaseSnake(this->_player[0].x, this->_player[0].y + 1);
  else if (this->_dir[0] == CommandType::GO_RIGHT)
    this->increaseSnake(this->_player[0].x + 1, this->_player[0].y);
  else
    this->increaseSnake(this->_player[0].x - 1, this->_player[0].y);
  if (this->_map[this->_player[0].y * WIDTH_MAP + this->_player[0].x] != TileType::POWERUP)
    this->_player.pop_back();
  else
  {
    this->_map[this->_player[0].y * WIDTH_MAP + this->_player[0].x] = TileType::EMPTY;
    this->_score += 100;
    this->dropApple();
    _assets.sound = arcade::SoundType::EATAPPLE;
  }
  if ((this->_map[this->_player[0].y * WIDTH_MAP + this->_player[0].x] == TileType::BLOCK) ||
      this->snakeBitesItself() == true || (this->_map[this->_player[0].y * WIDTH_MAP + this->_player[0].x] == TileType::OBSTACLE)) {
        _assets.sound = arcade::SoundType::LOSE;
        this->gameEnd(arcade::Status::LOSE);
      }
}

bool											arcade::GSnake::checkDir(arcade::CommandType type)
{
  for (unsigned int i = 0; i < this->_dir.size(); i++)
    if (this->_dir[i] == type)
      return false;
  return true;
}

void	    							  arcade::GSnake::Update(CommandType type, bool debug)
{
  _assets.sound = arcade::SoundType::NOTHING;
  if (type == CommandType::WHERE_AM_I)
  {
    try {
      this->GetPlayer(debug);
    }
    catch (RunTimeErrorGame const &stdErr) {
      std::cerr << stdErr.what() << std::endl;
      exit(-1);
    }
  }
  if (type == CommandType::GET_MAP)
  {
    try {
      this->GetMap(debug);
    }
    catch (RunTimeErrorGame const &stdErr) {
      std::cerr << stdErr.what() << std::endl;
      exit(-1);
    }
  }
  if ((type == CommandType::GO_UP && this->checkDir(CommandType::GO_DOWN)) ||
      (type == CommandType::GO_DOWN && this->checkDir(CommandType::GO_UP)) ||
      (type == CommandType::GO_LEFT && this->checkDir(CommandType::GO_RIGHT)) ||
      (type == CommandType::GO_RIGHT && this->checkDir(CommandType::GO_LEFT)))
    this->_dir.insert(this->_dir.begin(), type);
  if (type == CommandType::PLAY && this->_statusGame == arcade::Status::RUNNING)
  {
    this->move();
    for (unsigned int i = 1; i < this->_dir.size(); i++)
      this->_dir.erase(this->_dir.begin() + i);
    //if (this->_score == this->_lvl * 50 + (this->_lvl - 1) * 50)
    //this->_lvl++;
    this->_score ++;
    return ;
  }
  if (type == CommandType::SHOOT && this->_statusGame == arcade::Status::RUNNING)
    this->_statusGame = arcade::Status::RUNNING;
}

struct arcade::GetMap	  					*arcade::GSnake::GetMap(bool debug) const
{
  struct GetMap										*map;
  char														*s;
  int 														size;

  size = sizeof(*map) + (WIDTH_MAP * HEIGHT_MAP * sizeof(TileType));
  if ((map = new arcade::GetMap[size]) == NULL)
    throw RunTimeErrorGame("New Map Failed !");
  map->type = CommandType::GET_MAP;
  map->width = WIDTH_MAP;
  map->height = HEIGHT_MAP;
  for (int i = 0; i < WIDTH_MAP * HEIGHT_MAP; i++)
    map->tile[i] = this->_map[i];
  if (debug == true)
  {
    s = (char *)map;
    for (int i = 0; i < size; i++)
      std::cout << s[i];
  }
  return map;
}

struct arcade::WhereAmI	     			*arcade::GSnake::GetPlayer(bool debug) const
{
  struct WhereAmI									*player;
  char														*s;
  int 														size;

  size = sizeof(*player) + (this->_player.size() * sizeof(Position));
  if ((player = new arcade::WhereAmI[size]) == NULL)
    throw RunTimeErrorGame("New Player Failed !");
  player->type = CommandType::WHERE_AM_I;
  player->lenght = this->_player.size();
  for (unsigned int i = 0; i < this->_player.size(); i++)
    player->position[i] = this->_player[i];
  if (debug == true)
  {
    s = (char *)player;
    for (int i = 0; i < size; i++)
      std::cout << s[i];
  }
  return player;
}

void												 			arcade::GSnake::gameEnd(arcade::Status status)
{
  this->_statusGame = status;
}

bool												 			arcade::GSnake::IsGameOver() const
{
  if (this->_statusGame == arcade::Status::LOSE)
    return true;
  else
    return false;
}

arcade::Status							 			arcade::GSnake::GetStatus() const
{
  return this->_statusGame;
}

unsigned int											arcade::GSnake::GetScore() const
{
  return this->_score;
}

bool															 arcade::GSnake::snakeBitesItself() const
{
  for (unsigned int i = 0; i < this->_player.size(); i++)
    for (unsigned int j = 0; j < this->_player.size(); j++)
      if (i != j && this->_player[j].x == this->_player[i].x &&
          this->_player[j].y == this->_player[i].y)
          return true;
  return false;
}

arcade::Assets    &arcade::GSnake::GetAssets()
{
  _assets.dir = _dir[0];
  return _assets;
}

extern "C"
void											         Play()
{
  static arcade::GSnake 					 Snake;
  arcade::CommandType              type;

  while(std::cin.read(reinterpret_cast<char *>(&type), sizeof(type)))
    Snake.Update(type, true);
}

extern "C"
arcade::IGame*										CreateGame()
{
  return new arcade::GSnake();
}
