#include "GSnake.hpp"

arcade::GSnake::GSnake()
{
  this->initMap();
  this->initPlayer();
  this->initAssets();
  this->_dir.insert(this->_dir.begin(), CommandType::GO_RIGHT);
  this->_statusGame = arcade::Status::RUNNING;
  this->_score = 0;
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
  for (int i = 0; i < HEIGHT_MAP * WIDTH_MAP; i++)
  {
    if (i < WIDTH_MAP || i >= HEIGHT_MAP * (WIDTH_MAP - 1) ||
        i % WIDTH_MAP == 0 || i % WIDTH_MAP == WIDTH_MAP - 1)
      this->_map[i] = TileType::BLOCK;
    else
      this->_map[i] = TileType::EMPTY;
  }
  this->dropApple();
}

void											arcade::GSnake::initAssets()
{
  _assets.c_player.color = 0x39ff14FF;
  _assets.c_map[static_cast<int>(arcade::TileType::EMPTY)].color = 0xf5f5dcFF;
  _assets.c_map[static_cast<int>(arcade::TileType::BLOCK)].color = 0x5e5d62FF;
  _assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].color = 0xa8353aFF;
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
    this->_score += 10;
    this->dropApple();
  }
  if (this->_map[this->_player[0].y * WIDTH_MAP + this->_player[0].x] == TileType::BLOCK ||
      this->snakeBitesItself() == true)
    this->gameEnd(arcade::Status::LOSE);
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
  if (type == CommandType::WHERE_AM_I)
    this->GetPlayer(debug);
  if (type == CommandType::GET_MAP)
    this->GetMap(debug);
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
    return;
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
  //map = new [size] GetMap; -- AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
  if ((map = reinterpret_cast<arcade::GetMap *>(malloc(size))) == NULL)
    exit(0);
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
  //player = new [size] GetPlayer; -- OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
  if ((player = reinterpret_cast<arcade::WhereAmI *>(malloc(size))) == NULL)
    exit(0);
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

const arcade::Assets    &arcade::GSnake::GetAssets() const
{
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
