#include "GSolarFox.hpp"

const unsigned int         arcade::GSolarFox::RANGE = 4;

arcade::GSolarFox::GSolarFox()
{
  this->initMap();
  this->initPlayer();
  this->initEnemies();
  this->initAssets();
  this->initPowerUp();
  this->_statusGame = arcade::Status::RUNNING;
  this->_countMovesWidth = 0;
  this->_countMovesHeight = 0;
  this->_playerShoot.lifes = 0;
  this->_score = 0;
  this->_cmpt = 0;
}

void											arcade::GSolarFox::initMap()
{
  for (int i = 0; i < HEIGHT_MAP * WIDTH_MAP; i++)
  {
    if ((i > WIDTH_MAP && i < (WIDTH_MAP * 2) - 1) ||
        (i > (HEIGHT_MAP - 2) * WIDTH_MAP && i < (HEIGHT_MAP - 1) * WIDTH_MAP - 1) ||
        ((i % WIDTH_MAP == 1  || i % WIDTH_MAP == WIDTH_MAP - 2) && i > WIDTH_MAP && i < (HEIGHT_MAP - 1) * WIDTH_MAP))
      this->_map[i] = TileType::BLOCK;
    else
      this->_map[i] = TileType::EMPTY;
  }
}

void											arcade::GSolarFox::initPlayer()
{
  this->_player.dir = CommandType::GO_RIGHT;
  this->_player.pos.x = WIDTH_MAP / 2;
  this->_player.pos.y = HEIGHT_MAP / 2;
}

void											arcade::GSolarFox::initEnemies()
{
  this->addEnemy(2, 1, CommandType::GO_RIGHT);
  this->addEnemy(1, HEIGHT_MAP - 3, CommandType::GO_UP);
  this->addEnemy(WIDTH_MAP - 3, HEIGHT_MAP - 2, CommandType::GO_LEFT);
  this->addEnemy(WIDTH_MAP - 2, 2, CommandType::GO_DOWN);
}

void											arcade::GSolarFox::initAssets()
{
  _assets.c_player.color = 0x6699ccFF;
  _assets.c_map[static_cast<int>(arcade::TileType::EMPTY)].color = 0xf5f5dcFF;
  _assets.c_map[static_cast<int>(arcade::TileType::BLOCK)].color = 0x5e5d62FF;
  _assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].color = 0x99ffccFF;
  _assets.c_map[static_cast<int>(arcade::TileType::EVIL_DUDE)].color = 0xa40061FF;
  _assets.c_map[static_cast<int>(arcade::TileType::MY_SHOOT)].color = 0xd9f7f7FF;
  _assets.c_map[static_cast<int>(arcade::TileType::EVIL_SHOOT)].color = 0xffc5e4FF;
  _assets.loadMap = true;
  _assets.t_map = "solarfox_map.png";
  _assets.loadPlayer = true;
  _assets.t_player= "solarfox_player.png";
  _assets.loadBg = true;
  _assets.t_bg = "SolarFoxBackgroundGame.jpg";
  _assets.dir = arcade::CommandType::GO_RIGHT;
  _assets.sound = arcade::SoundType::SOLARFOX_START;
}

void											arcade::GSolarFox::initPowerUp()
{
  int											x = 0;
  int											y = 0;
  int											dropByDefault = 0;

  srand(time(NULL));
  for (int i = 0; i < 5; i++)
  {
    dropByDefault = 0;
    while (dropByDefault == 0 || this->_map[dropByDefault] != TileType::EMPTY)
    {
      x = rand() % (WIDTH_MAP - 10) + 3;
      y = rand() % (HEIGHT_MAP - 10) + 3;
      dropByDefault = y * WIDTH_MAP + x;
    }
    this->addPowerup(x, y);
    this->_map[dropByDefault] = TileType::POWERUP;
  }
}

void											arcade::GSolarFox::addPowerup(int x, int y)
{
  Position								pos;

  pos.x = x;
  pos.y = y;
  this->_powerUp.insert(this->_powerUp.begin(), pos);
}

void											arcade::GSolarFox::modifyMapActors(std::vector<struct Actor> actors, TileType type)
{
  for (unsigned int i = 0; i < actors.size(); i++)
    this->_map[actors[i].pos.y * WIDTH_MAP + actors[i].pos.x] = type;
}

void											arcade::GSolarFox::addMyShoot(int x, int y, CommandType dir)
{
  this->_playerShoot.pos.x = x;
  this->_playerShoot.pos.y = y;
  this->_playerShoot.dir = dir;
  this->_map[y * WIDTH_MAP + x] = TileType::MY_SHOOT;
}

bool											arcade::GSolarFox::shootPowerup()
{
  for (unsigned int i = 0; i < this->_powerUp.size(); i++)
  {
    if (this->_playerShoot.pos.x == this->_powerUp[i].x &&
        this->_playerShoot.pos.y == this->_powerUp[i].y)
      return true;
  }
  return false;
}

void											arcade::GSolarFox::deletePowerup()
{
  unsigned int						i = 0;

  while (i < this->_powerUp.size() &&
         this->_powerUp[i].x != this->_playerShoot.pos.x &&
         this->_powerUp[i].y != this->_playerShoot.pos.y)
    i++;
  this->_map[this->_powerUp[i].y * WIDTH_MAP + this->_powerUp[i].x] = TileType::EMPTY;
  this->_powerUp.erase(this->_powerUp.begin() + i);
  this->_playerShoot.lifes = 0;
  this->_score += 10;
}

bool											arcade::GSolarFox::shootEvilShoot()
{
  for (unsigned int i = 0; i < this->_shoots.size(); i++)
    if (this->_playerShoot.pos.x == this->_shoots[i].pos.x &&
        this->_playerShoot.pos.y == this->_shoots[i].pos.y)
      return true;
  return false;
}

void											arcade::GSolarFox::deleteEvilShoot()
{
  unsigned int						i = 0;

  while (i < this->_shoots.size() &&
         this->_shoots[i].pos.x != this->_playerShoot.pos.x &&
         this->_shoots[i].pos.y != this->_playerShoot.pos.y)
    i++;
  this->_map[this->_shoots[i].pos.y * WIDTH_MAP + this->_shoots[i].pos.x] = TileType::EMPTY;
  this->_shoots.erase(this->_shoots.begin() + i);
  this->_playerShoot.lifes = 0;
}

void											arcade::GSolarFox::moveMyShoot()
{
  if (this->shootPowerup())
    this->deletePowerup();
  if (this->_playerShoot.lifes == 0)
    return ;
  this->_map[this->_playerShoot.pos.y * WIDTH_MAP + this->_playerShoot.pos.x] = TileType::EMPTY;
  if (this->_playerShoot.dir == CommandType::GO_DOWN)
    this->_playerShoot.pos.y++;
  else if (this->_playerShoot.dir == CommandType::GO_UP)
    this->_playerShoot.pos.y--;
  else if (this->_playerShoot.dir == CommandType::GO_LEFT)
    this->_playerShoot.pos.x--;
  else
    this->_playerShoot.pos.x++;
  this->_playerShoot.lifes--;
  if (this->shootPowerup())
    this->deletePowerup();
  if (this->shootEvilShoot())
    this->deleteEvilShoot();
  if (this->_map[this->_playerShoot.pos.y * WIDTH_MAP + this->_playerShoot.pos.x] != TileType::EMPTY)
    this->_playerShoot.lifes = 0;
  if (this->_playerShoot.lifes != 0)
    this->_map[this->_playerShoot.pos.y * WIDTH_MAP + this->_playerShoot.pos.x] = TileType::MY_SHOOT;
}

void											arcade::GSolarFox::initMyShoot()
{
  this->_playerShoot.lifes = RANGE;
  _assets.sound = arcade::SoundType::SHOOT;
  if (this->_player.dir == CommandType::GO_DOWN)
    this->addMyShoot(this->_player.pos.x, this->_player.pos.y + 1, CommandType::GO_DOWN);
  else if (this->_player.dir == CommandType::GO_UP)
    this->addMyShoot(this->_player.pos.x, this->_player.pos.y - 1, CommandType::GO_UP);
  else if (this->_player.dir == CommandType::GO_RIGHT)
    this->addMyShoot(this->_player.pos.x + 1, this->_player.pos.y, CommandType::GO_RIGHT);
  else
    this->addMyShoot(this->_player.pos.x - 1, this->_player.pos.y, CommandType::GO_LEFT);
  if (this->_map[this->_playerShoot.pos.y * WIDTH_MAP + this->_playerShoot.pos.x] != TileType::EMPTY &&
      this->_map[this->_playerShoot.pos.y * WIDTH_MAP + this->_playerShoot.pos.x] != TileType::MY_SHOOT)
    this->_playerShoot.lifes = 0;
}

void                      arcade::GSolarFox::addShoot(int x, int y, CommandType dir)
{
  arcade::Actor						shoot;

  shoot.pos.x = x;
  shoot.pos.y = y;
  shoot.dir = dir;
  this->_shoots.insert(this->_shoots.begin(), shoot);
  this->_map[y * WIDTH_MAP + x] = TileType::EVIL_SHOOT;
}

void											arcade::GSolarFox::shoot(int i)
{
  if (i == 0)
    addShoot(this->_enemies[i].pos.x - 2, this->_enemies[i].pos.y, CommandType::GO_LEFT);
  else if (i == 1)
    addShoot(this->_enemies[i].pos.x, this->_enemies[i].pos.y - 2, CommandType::GO_UP);
  else if (i == 2)
    addShoot(this->_enemies[i].pos.x + 2, this->_enemies[i].pos.y, CommandType::GO_RIGHT);
  else
    addShoot(this->_enemies[i].pos.x, this->_enemies[i].pos.y + 2, CommandType::GO_DOWN);
}

void											arcade::GSolarFox::moveShoot()
{
  this->modifyMapActors(this->_shoots, TileType::EMPTY);
  for (unsigned int i = 0; i < this->_shoots.size(); i++)
  {
    if (this->_shoots[i].pos.x == this->_player.pos.x &&
        this->_shoots[i].pos.y == this->_player.pos.y)
      this->gameEnd(arcade::Status::LOSE);
    if (this->_shoots[i].dir == CommandType::GO_DOWN)
      this->_shoots[i].pos.y++;
    else if (this->_shoots[i].dir == CommandType::GO_UP)
      this->_shoots[i].pos.y--;
    else if (this->_shoots[i].dir == CommandType::GO_LEFT)
      this->_shoots[i].pos.x--;
    else
      this->_shoots[i].pos.x++;
    if (this->_map[this->_shoots[i].pos.y * WIDTH_MAP + this->_shoots[i].pos.x] != TileType::EMPTY)
      this->_shoots.erase(this->_shoots.begin() + i);
    else if (this->_shoots[i].pos.x == this->_player.pos.x &&
             this->_shoots[i].pos.y == this->_player.pos.y)
      this->gameEnd(arcade::Status::LOSE);
  }
  this->modifyMapActors(this->_shoots, TileType::EVIL_SHOOT);
}

void                      arcade::GSolarFox::addEnemy(int x, int y, CommandType dir)
{
  arcade::Actor						enemy;

  enemy.pos.x = x;
  enemy.pos.y = y;
  enemy.dir = dir;
  this->_enemies.insert(this->_enemies.begin(), enemy);
  this->_map[y * WIDTH_MAP + x] = TileType::EVIL_DUDE;
}

void											arcade::GSolarFox::inverseDir(int i, CommandType typeOne, CommandType typeTwo)
{
  if (this->_enemies[i].dir == typeOne)
    this->_enemies[i].dir = typeTwo;
  else
    this->_enemies[i].dir = typeOne;
}

void											arcade::GSolarFox::manageCycleEnemies()
{
  this->_countMovesWidth++;
  this->_countMovesHeight++;
  if (this->_countMovesWidth == WIDTH_MAP - 5)
  {
    this->_countMovesWidth = 0;
    this->inverseDir(1, CommandType::GO_LEFT, CommandType::GO_RIGHT);
    this->inverseDir(3, CommandType::GO_RIGHT, CommandType::GO_LEFT);
  }
  if (this->_countMovesHeight == HEIGHT_MAP - 5)
  {
    this->_countMovesHeight = 0;
    this->inverseDir(0, CommandType::GO_DOWN, CommandType::GO_UP);
    this->inverseDir(2, CommandType::GO_UP, CommandType::GO_DOWN);
  }
}

void											arcade::GSolarFox::moveEnemies()
{
  this->modifyMapActors(this->_enemies, TileType::EMPTY);
  for (int i = 0; i < 4; i++)
  {
    this->_map[this->_enemies[i].pos.y * WIDTH_MAP + this->_enemies[i].pos.x] = arcade::TileType::BLOCK;
    if (this->_enemies[i].dir == CommandType::GO_DOWN)
      this->_enemies[i].pos.y++;
    else if (this->_enemies[i].dir == CommandType::GO_UP)
      this->_enemies[i].pos.y--;
    else if (this->_enemies[i].dir == CommandType::GO_LEFT)
      this->_enemies[i].pos.x--;
    else
      this->_enemies[i].pos.x++;
    if (this->_enemies[i].pos.y == this->_player.pos.y ||
        this->_enemies[i].pos.x == this->_player.pos.x)
      this->shoot(i);
  }
  this->manageCycleEnemies();
  this->modifyMapActors(this->_enemies, TileType::EVIL_DUDE);
}

void                      arcade::GSolarFox::move()
{
  if (this->_player.dir == CommandType::GO_UP)
    this->_player.pos.y--;
  else if (this->_player.dir == CommandType::GO_DOWN)
    this->_player.pos.y++;
  else if (this->_player.dir == CommandType::GO_RIGHT)
    this->_player.pos.x++;
  else
    this->_player.pos.x--;
  if (this->_map[this->_player.pos.y * WIDTH_MAP + this->_player.pos.x] == TileType::BLOCK)
    this->gameEnd(arcade::Status::LOSE);
}

void	    							  arcade::GSolarFox::Update(CommandType type, bool debug)
{
  (void)type;
  (void)debug;
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
  if ((debug == true && (type == CommandType::GO_UP || type == CommandType::GO_DOWN || type == CommandType::GO_RIGHT || type == CommandType::GO_LEFT))
      || ((type == CommandType::GO_UP && this->_player.dir != CommandType::GO_DOWN) ||
      (type == CommandType::GO_DOWN && this->_player.dir != CommandType::GO_UP) ||
      (type == CommandType::GO_LEFT && this->_player.dir != CommandType::GO_RIGHT) ||
      (type == CommandType::GO_RIGHT && this->_player.dir != CommandType::GO_LEFT)))
    this->_player.dir = type;
  if (type == CommandType::SHOOT && this->_playerShoot.lifes == 0)
    this->initMyShoot();
  if (type == CommandType::PLAY && this->_statusGame == arcade::Status::RUNNING)
  {
    if (this->_playerShoot.lifes > 0)
      this->moveMyShoot();
    this->move();
    this->moveEnemies();
    this->moveShoot();
    if (this->_playerShoot.lifes > 0)
      this->moveMyShoot();
/*    if (this->_cmpt % 3 < 2 || debug == true)
    {
    }*/
    if (this->_powerUp.size() == 0)
      this->gameEnd(arcade::Status::WIN);
    this->_cmpt++;
    return;
  }
  if (type == CommandType::SHOOT && this->_statusGame != arcade::Status::RUNNING)
    this->_statusGame = arcade::Status::RUNNING;
}

struct arcade::GetMap	  					*arcade::GSolarFox::GetMap(bool debug) const
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

struct arcade::WhereAmI	     			*arcade::GSolarFox::GetPlayer(bool debug) const
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

void												 			arcade::GSolarFox::gameEnd(arcade::Status status)
{
  if (status == arcade::Status::LOSE) {
    _assets.sound = arcade::SoundType::LOSE;
  }
  else {
    _assets.sound = arcade::SoundType::WIN;
  }
  this->_statusGame = status;
}

arcade::Status							 			arcade::GSolarFox::GetStatus() const
{
  return this->_statusGame;
}

unsigned int											arcade::GSolarFox::GetScore() const
{
  return this->_score;
}

bool															arcade::GSolarFox::IsGameOver() const
{
  if (this->_statusGame == arcade::Status::LOSE)
    return true;
  return false;
}

arcade::Assets                  &arcade::GSolarFox::GetAssets()
{
  _assets.dir = _player.dir;
  return _assets;
}

extern "C"
void											         Play()
{
  static arcade::GSolarFox 				 SolarFox;
  arcade::CommandType              type;

  while(std::cin.read(reinterpret_cast<char *>(&type), sizeof(type)))
    SolarFox.Update(type, true);
}

extern "C"
arcade::IGame*										CreateGame()
{
  return new arcade::GSolarFox();
}
