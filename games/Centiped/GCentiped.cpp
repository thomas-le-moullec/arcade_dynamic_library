#include "GCentiped.hpp"

arcade::GCentiped::GCentiped()
{
  this->initMap();
  this->initAssets();
  this->initEnemies();
  this->initPlayer();
  this->initObstacles();
  this->_statusGame = arcade::Status::RUNNING;
  this->_score = 0;
  this->_playerShoot.lifes = 0;
}

void											arcade::GCentiped::initMap()
{
  for (int i = 0; i < HEIGHT_MAP * WIDTH_MAP; i++)
  {
    if (i < WIDTH_MAP || i >= HEIGHT_MAP * (WIDTH_MAP - 1) ||
        i % WIDTH_MAP == 0 || i % WIDTH_MAP == WIDTH_MAP - 1)
      this->_map[i] = TileType::BLOCK;
    else
      this->_map[i] = TileType::EMPTY;
  }
}

void											arcade::GCentiped::initAssets()
{
  _assets.c_player.color = 0x6699ccFF;
  _assets.c_map[static_cast<int>(arcade::TileType::EMPTY)].color = 0xf5f5dcFF;
  _assets.c_map[static_cast<int>(arcade::TileType::BLOCK)].color = 0x5e5d62FF;
  _assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].color = 0x99ffccFF;
  _assets.c_map[static_cast<int>(arcade::TileType::EVIL_DUDE)].color = 0xa40061FF;
  _assets.c_map[static_cast<int>(arcade::TileType::MY_SHOOT)].color = 0xd9f7f7FF;
  _assets.c_map[static_cast<int>(arcade::TileType::EVIL_SHOOT)].color = 0xffc5e4FF;
  _assets.c_map[static_cast<int>(arcade::TileType::OBSTACLE)].color = 0xf4977eFF;
  _assets.loadMap = true;
  _assets.t_map = "centiped_map.png";
  _assets.loadPlayer = true;
  _assets.t_player= "centiped_player.png";
  _assets.loadBg = true;
  _assets.t_bg = "CentipedBackgroundGame.jpg";
  _assets.dir = arcade::CommandType::GO_RIGHT;
}

void											arcade::GCentiped::initEnemies()
{
  std::vector<arcade::Actor>	enemy;

  for (int i = 1; i < 10; i++)
    this->addBodyEnemy(&enemy, i, 1, CommandType::GO_RIGHT, CommandType::GO_DOWN);
  this->addEnemy(enemy);
}

void											arcade::GCentiped::initPlayer()
{
  this->_player.pos.x = WIDTH_MAP / 2;
  this->_player.pos.y = HEIGHT_MAP - 3;
  this->_map[this->_player.pos.y * WIDTH_MAP + this->_player.pos.x] = arcade::TileType::OTHER;
}

void											arcade::GCentiped::initObstacles()
{
  int											x = 0;
  int											y = 0;
  int											dropByDefault = 0;

  srand(time(NULL));
  for (int i = 0; i < 10; i++)
  {
    dropByDefault = 0;
    while (dropByDefault == 0 || this->_map[dropByDefault] != TileType::EMPTY)
    {
      x = rand() % (WIDTH_MAP - 2) + 1;
      y = rand() % (HEIGHT_MAP - HEIGHT_MAP / 4) + 3;
      dropByDefault = y * WIDTH_MAP + x;
    }
    this->addObstacle(x, y);
  }
}

void													arcade::GCentiped::addEnemy(std::vector<arcade::Actor> enemy)
{
  this->_enemies.insert(this->_enemies.end(), enemy);
}

void											arcade::GCentiped::addBodyEnemy(std::vector<arcade::Actor> *enemy, int x, int y, CommandType dirX, CommandType dirY)
{
  arcade::Actor						bodyEnemy;

  bodyEnemy.pos.x = x;
  bodyEnemy.pos.y = y;
  bodyEnemy.dirX = dirX;
  bodyEnemy.dirY = dirY;
  enemy->insert(enemy->begin(), bodyEnemy);
  this->_map[y * WIDTH_MAP + x] = TileType::EVIL_DUDE;
}

void												arcade::GCentiped::addObstacle(int x, int y)
{
  arcade::Actor							obstacle;

  obstacle.pos.x = x;
  obstacle.pos.y = y;
  obstacle.lifes = 5;
  this->_obstacles.insert(this->_obstacles.end(), obstacle);
  this->_map[y * WIDTH_MAP + x] = TileType::OBSTACLE;
}

void												arcade::GCentiped::deleteObstacle(int i)
{
  this->_map[this->_obstacles[i].pos.y * WIDTH_MAP + this->_obstacles[i].pos.x] = TileType::EMPTY;
  this->_obstacles.erase(this->_obstacles.begin() + i);
}

void													arcade::GCentiped::cutCenti(int i, int j)
{
  std::vector<arcade::Actor>	enemy;
  unsigned int 								tmp;

  this->addObstacle(this->_enemies[i][j].pos.x, this->_enemies[i][j].pos.y);
//  this->_map[this->_enemies[i][j].pos.y * WIDTH_MAP + this->_enemies[i][j].pos.x] = arcade::TileType::OBSTACLE;
  if (this->_enemies[i][0].dirX == arcade::CommandType::GO_LEFT)
  {
    for (int y = 0; y < j && this->_enemies[i].size() > 0; y++)
      this->addBodyEnemy(&enemy, this->_enemies[i][y].pos.x, this->_enemies[i][y].pos.y, arcade::CommandType::GO_RIGHT, this->_enemies[i][y].dirY);
    for (int y = 0; y <= j; y++)
      this->_enemies[i].erase(this->_enemies[i].begin());
  }
  else
  {
    for (unsigned int y = j + 1; y < this->_enemies[i].size() && this->_enemies[i].size() > 0; y++)
      this->addBodyEnemy(&enemy, this->_enemies[i][y].pos.x, this->_enemies[i][y].pos.y, arcade::CommandType::GO_LEFT, this->_enemies[i][y].dirY);
    tmp = this->_enemies[i].size();
    for (unsigned int y = j; y < tmp; y++)
      this->_enemies[i].erase(this->_enemies[i].end() - 1);
  }
  if (this->_enemies[i].size() == 0)
    this->_enemies.erase(this->_enemies.begin() + i);
  if (enemy.size() > 0)
    this->addEnemy(enemy);
}

void											arcade::GCentiped::execMove(int i)
{
  int											j = (int)this->_enemies[i].size() - 1;

  this->_map[this->_enemies[i][0].pos.y * WIDTH_MAP + this->_enemies[i][0].pos.x] = arcade::TileType::EVIL_DUDE;
  this->_map[this->_enemies[i][j].pos.y * WIDTH_MAP + this->_enemies[i][j].pos.x] = arcade::TileType::EMPTY;
}

bool											arcade::GCentiped::isOnPlayer(int y, int x)
{
  if (this->_player.pos.x == x && this->_player.pos.y == y)
    return true;
  return false;
}

void											arcade::GCentiped::moveEnemies()
{

  for (unsigned int i = 0; i < _enemies.size(); i++)
  {
    if (_enemies[i][0].dirX == arcade::CommandType::GO_RIGHT && (_map[_enemies[i][0].pos.y * WIDTH_MAP + _enemies[i][0].pos.x + 1] == arcade::TileType::EMPTY || _map[_enemies[i][0].pos.y * WIDTH_MAP + _enemies[i][0].pos.x + 1] == arcade::TileType::OTHER))
    {
      addBodyEnemy(&_enemies[i], _enemies[i][0].pos.x + 1, _enemies[i][0].pos.y, arcade::CommandType::GO_RIGHT, _enemies[i][0].dirY);
      execMove(i);
      _enemies[i].erase(_enemies[i].end() - 1);
    }
    else if (_enemies[i][0].dirX == arcade::CommandType::GO_LEFT && (_map[_enemies[i][0].pos.y * WIDTH_MAP + _enemies[i][0].pos.x - 1] == arcade::TileType::EMPTY || _map[_enemies[i][0].pos.y * WIDTH_MAP + _enemies[i][0].pos.x - 1] == arcade::TileType::OTHER))
    {
      addBodyEnemy(&_enemies[i], _enemies[i][0].pos.x - 1, _enemies[i][0].pos.y, arcade::CommandType::GO_LEFT, _enemies[i][0].dirY);
      execMove(i);
      _enemies[i].erase(_enemies[i].end() - 1);
    }


    else if (_enemies[i][0].dirY == arcade::CommandType::GO_DOWN && _map[(_enemies[i][0].pos.y) * WIDTH_MAP + _enemies[i][0].pos.x + 1] != arcade::TileType::EMPTY &&
             _map[(_enemies[i][0].pos.y + 1) * WIDTH_MAP + _enemies[i][0].pos.x] != arcade::TileType::BLOCK && _enemies[i][0].pos.x + 1 != _enemies[i][1].pos.x && _enemies[i][0].pos.y + 1 != _enemies[i][1].pos.y)
    {
      addBodyEnemy(&_enemies[i], _enemies[i][0].pos.x, _enemies[i][0].pos.y + 1, arcade::CommandType::GO_LEFT, _enemies[i][0].dirY);
      execMove(i);
      _enemies[i].erase(_enemies[i].end() - 1);
    }
    else if (_enemies[i][0].dirY == arcade::CommandType::GO_DOWN && _map[(_enemies[i][0].pos.y) * WIDTH_MAP + _enemies[i][0].pos.x - 1] != arcade::TileType::EMPTY &&
             _map[(_enemies[i][0].pos.y + 1) * WIDTH_MAP + _enemies[i][0].pos.x] != arcade::TileType::BLOCK && _enemies[i][0].pos.x - 1 != _enemies[i][1].pos.x  && _enemies[i][0].pos.y - 1 != _enemies[i][1].pos.y)
    {
      addBodyEnemy(&_enemies[i], _enemies[i][0].pos.x, _enemies[i][0].pos.y + 1, arcade::CommandType::GO_RIGHT, _enemies[i][0].dirY);
      execMove(i);
      _enemies[i].erase(_enemies[i].end() - 1);
    }
    if (isOnPlayer(_enemies[i][0].pos.y, _enemies[i][0].pos.x))
      this->gameEnd(arcade::Status::LOSE);
  }
}

void											arcade::GCentiped::movePlayer(CommandType type)
{
  this->_map[this->_player.pos.y * WIDTH_MAP + this->_player.pos.x] = TileType::EMPTY;
  if (type == CommandType::GO_UP && this->_map[(this->_player.pos.y - 1) * WIDTH_MAP + this->_player.pos.x] == TileType::EMPTY &&
      this->_player.pos.y - 1 > WIDTH_MAP - WIDTH_MAP / 4)
    this->_player.pos.y--;
  else if (type == CommandType::GO_DOWN && this->_map[(this->_player.pos.y + 1) * WIDTH_MAP + this->_player.pos.x] == TileType::EMPTY)
    this->_player.pos.y++;
  else if (type == CommandType::GO_RIGHT && this->_map[this->_player.pos.y * WIDTH_MAP + this->_player.pos.x + 1] == TileType::EMPTY)
    this->_player.pos.x++;
  else if (type == CommandType::GO_LEFT && this->_map[this->_player.pos.y * WIDTH_MAP + this->_player.pos.x - 1] == TileType::EMPTY)
    this->_player.pos.x--;
  this->_map[this->_player.pos.y * WIDTH_MAP + this->_player.pos.x] = TileType::OTHER;
}

void											arcade::GCentiped::initMyShoot()
{
  this->_playerShoot.lifes = 1;
  this->_playerShoot.pos.x = this->_player.pos.x;
  this->_playerShoot.pos.y = this->_player.pos.y - 1;
  this->_map[this->_playerShoot.pos.y * WIDTH_MAP + this->_playerShoot.pos.x] = TileType::MY_SHOOT;
}

void											arcade::GCentiped::shootEvilDude()
{
  for (unsigned int i = 0; i < this->_enemies.size(); i++)
    for (unsigned int j = 0; j < this->_enemies[i].size(); j++)
      if (this->_playerShoot.pos.x == this->_enemies[i][j].pos.x && this->_playerShoot.pos.y == this->_enemies[i][j].pos.y)
        this->cutCenti(i, j);
  this->_playerShoot.lifes = 0;
  this->_score += 100;
}

void											arcade::GCentiped::shootObstacle()
{
  for (unsigned int i = 0; i < this->_obstacles.size(); i++)
    if (this->_playerShoot.pos.x == this->_obstacles[i].pos.x && this->_playerShoot.pos.y == this->_obstacles[i].pos.y)
    {
      if (this->_obstacles[i].lifes > 0)
        this->_obstacles[i].lifes--;
      else
        this->deleteObstacle(i);
    }
  this->_playerShoot.lifes = 0;
}

void											arcade::GCentiped::moveMyShoot()
{
  if (this->_map[this->_playerShoot.pos.y * WIDTH_MAP + this->_playerShoot.pos.x] == TileType::EVIL_DUDE)
    this->shootEvilDude();
  this->_map[this->_playerShoot.pos.y * WIDTH_MAP + this->_playerShoot.pos.x] = TileType::EMPTY;
  if (this->_playerShoot.lifes == 1)
    this->_playerShoot.pos.y--;
  if (this->_map[this->_playerShoot.pos.y * WIDTH_MAP + this->_playerShoot.pos.x] == TileType::EMPTY)
    this->_map[this->_playerShoot.pos.y * WIDTH_MAP + this->_playerShoot.pos.x] = TileType::MY_SHOOT;
  else if (this->_map[this->_playerShoot.pos.y * WIDTH_MAP + this->_playerShoot.pos.x] == TileType::EVIL_DUDE)
    this->shootEvilDude();
  else if (this->_map[this->_playerShoot.pos.y * WIDTH_MAP + this->_playerShoot.pos.x] == TileType::OBSTACLE)
    this->shootObstacle();
  else
    this->_playerShoot.lifes = 0;
}

void											arcade::GCentiped::gameEnd(arcade::Status status)
{
  this->_statusGame = status;
}

void	    							  arcade::GCentiped::Update(CommandType type, bool debug)
{
  if (type == CommandType::PLAY)
  {
    if (this->_playerShoot.lifes == 1)
      this->moveMyShoot();
    this->moveEnemies();
    if (this->_playerShoot.lifes == 1)
      this->moveMyShoot();
  }
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
  else if (type == CommandType::GET_MAP)
  {
    try {
      this->GetMap(debug);
    }
    catch (RunTimeErrorGame const &stdErr) {
      std::cerr << stdErr.what() << std::endl;
      exit(-1);
    }
  }
  else if (type == CommandType::GO_UP || type == CommandType::GO_DOWN || type == CommandType::GO_RIGHT || type == CommandType::GO_LEFT)
    this->movePlayer(type);
  else if (type == CommandType::SHOOT && this->_playerShoot.lifes == 0)
    this->initMyShoot();
  if (this->_enemies.size() == 0)
    this->gameEnd(arcade::Status::WIN);
}

struct arcade::GetMap	  					*arcade::GCentiped::GetMap(bool debug) const
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

struct arcade::WhereAmI	     			*arcade::GCentiped::GetPlayer(bool debug) const
{
  struct WhereAmI									*player;
  char														*s;
  int 														size;

  size = sizeof(*player) + (sizeof(Position));
  if ((player = new arcade::WhereAmI[size]) == NULL)
    throw RunTimeErrorGame("New Player Failed !");
  player->type = CommandType::WHERE_AM_I;
  player->lenght = 1;
  player->position[0] = this->_player.pos;
  if (debug == true)
  {
    s = (char *)player;
    for (int i = 0; i < size; i++)
      std::cout << s[i];
  }
  return player;
}

bool											arcade::GCentiped::IsGameOver() const
{
  if (this->_statusGame == arcade::Status::LOSE)
    return true;
  return false;
}

arcade::Status						arcade::GCentiped::GetStatus() const
{
  return this->_statusGame;
}

arcade::Assets             &arcade::GCentiped::GetAssets()
{
  _assets.dir = _player.dir;
  return _assets;
}

unsigned int							arcade::GCentiped::GetScore() const
{
  return this->_score;
}

extern "C"
void											         Play()
{
  static arcade::GCentiped 				 Centiped;
  arcade::CommandType              type;

  while(std::cin.read(reinterpret_cast<char *>(&type), sizeof(type)))
    Centiped.Update(type, true);
}

extern "C"
arcade::IGame*										CreateGame()
{
  return new arcade::GCentiped();
}
