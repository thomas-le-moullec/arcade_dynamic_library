#include "GCentiped.hpp"

arcade::GCentiped::GCentiped()
{
  this->initMap();
  this->initAssets();
  this->initEnemies();
  this->_statusGame = arcade::Status::RUNNING;
  this->_score = 0;
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
  _assets.loadMap = true;
  _assets.t_map = "CentipedMap.png";
  _assets.loadPlayer = true;
  _assets.t_player= "CentipedPlayer.png";
  _assets.loadBg = true;
  _assets.t_bg = "CentipedBackgroundGame.jpg";
  _assets.dir = arcade::CommandType::GO_RIGHT;
}

void											arcade::GCentiped::initEnemies()
{
  std::vector<arcade::Actor>	enemy;

  for (int i = 15; i > 0; i--)
    this->addBodyEnemy(&enemy, i, 1, CommandType::GO_RIGHT, CommandType::GO_DOWN);
  this->addEnemy(enemy);
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
  enemy->insert(enemy->end(), bodyEnemy);
  this->_map[y * WIDTH_MAP + x] = TileType::EVIL_DUDE;
}

void													arcade::GCentiped::cutCenti(int i, int j)
{
/*  std::vector<arcade::Actor>	enemy;

  std::cout << j << std::endl;
  if (this->_enemies[i][0].dirX == arcade::CommandType::GO_LEFT)
    for (unsigned int y = j; y < this->_enemies[i].size(); y++)
      this->addBodyEnemy(&enemy, this->_enemies[i][0].pos.x, this->_enemies[i][0].pos.y, arcade::CommandType::GO_RIGHT, this->_enemies[i][0].dirY);
  else
    for (unsigned int y = 0; y < (unsigned int)j; y++)
      this->addBodyEnemy(&enemy, this->_enemies[i][0].pos.x, this->_enemies[i][0].pos.y, arcade::CommandType::GO_LEFT, this->_enemies[i][0].dirY);
  for (int y = 0; y <= j; y++)
  {
    this->_map[this->_enemies[i][0].pos.y * WIDTH_MAP + this->_enemies[i][0].pos.x + 1] = arcade::TileType::EMPTY;
    if (this->_enemies[i][0].dirX == arcade::CommandType::GO_RIGHT)
      this->_enemies[i].erase(this->_enemies[i].begin());
    else
      this->_enemies[i].erase(this->_enemies[i].end() - 1);

  }
  this->addEnemy(enemy);*/
  (void)i;
  (void)j;
}

void											arcade::GCentiped::execMove(int i)
{
  int											j = (int)this->_enemies[i].size() - 1;

  this->_map[this->_enemies[i][0].pos.y * WIDTH_MAP + this->_enemies[i][0].pos.x] = arcade::TileType::EVIL_DUDE;
  this->_map[this->_enemies[i][j].pos.y * WIDTH_MAP + this->_enemies[i][j].pos.x] = arcade::TileType::EMPTY;
}

void											arcade::GCentiped::moveEnemies()
{
  for (unsigned int i = 0; i < this->_enemies.size(); i++)
  {
    std::cout << " i vaut " << i <<  std::endl;
    //for (unsigned int j = 0; j < this->_enemies[i].size(); j++)
    //{
      if (this->_enemies[i][0].dirX == arcade::CommandType::GO_RIGHT && this->_map[this->_enemies[i][0].pos.y * WIDTH_MAP + this->_enemies[i][0].pos.x + 1] == arcade::TileType::EMPTY)
      {
        std::cout << " RIGHT " << i <<  std::endl;

        this->addBodyEnemy(&this->_enemies[i], this->_enemies[i][0].pos.x + 1, this->_enemies[i][0].pos.y, arcade::CommandType::GO_RIGHT, this->_enemies[i][0].dirY);
        this->execMove(i);
        this->_enemies[i].erase(this->_enemies[i].end() - 1);
      }
      else if (this->_enemies[i][0].dirX == arcade::CommandType::GO_LEFT && this->_map[this->_enemies[i][0].pos.y * WIDTH_MAP + this->_enemies[i][0].pos.x - 1] == arcade::TileType::EMPTY)
      {
        std::cout << " LEFT " << i <<  std::endl;

        this->addBodyEnemy(&this->_enemies[i], this->_enemies[i][0].pos.x - 1, this->_enemies[i][0].pos.y, arcade::CommandType::GO_LEFT, this->_enemies[i][0].dirY);
        this->_enemies[i].erase(this->_enemies[i].end() - 1);
        this->execMove(i);
      }


      else if (this->_enemies[i][0].dirY == arcade::CommandType::GO_DOWN && this->_map[this->_enemies[i][0].pos.y * WIDTH_MAP + this->_enemies[i][0].pos.x + 1] != arcade::TileType::EMPTY)
      {
        this->addBodyEnemy(&this->_enemies[i], this->_enemies[i][0].pos.x - 1, this->_enemies[i][0].pos.y + 1, arcade::CommandType::GO_LEFT, this->_enemies[i][0].dirY);
        this->_enemies[i].erase(this->_enemies[i].end() - 1);
        this->execMove(i);
      }
      else if (this->_enemies[i][0].dirY == arcade::CommandType::GO_DOWN && this->_map[this->_enemies[i][0].pos.y * WIDTH_MAP + this->_enemies[i][0].pos.x - 1] != arcade::TileType::EMPTY)
      {
        this->addBodyEnemy(&this->_enemies[i], this->_enemies[i][0].pos.x, this->_enemies[i][0].pos.y - 1, arcade::CommandType::GO_RIGHT, this->_enemies[i][0].dirY);
        this->_enemies[i].erase(this->_enemies[i].end() - 1);
        this->execMove(i);
      }


      /*if (this->_enemies[i][0].pos.y == 3 && toto && this->_enemies[i][0].pos.x == 5)
      {
        this->cutCenti(i, 5);
        toto = false;
      }*/
  }
}

void	    							  arcade::GCentiped::Update(CommandType type, bool debug)
{
  this->moveEnemies();
  /*if (type == CommandType::WHERE_AM_I)
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
  }*/
	(void)type;
	(void)debug;
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
