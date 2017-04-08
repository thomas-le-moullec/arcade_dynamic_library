#include "OpenGL.hpp"
#include <stdio.h>

const std::string arcade::OpenGL::RESSOURCES_ASCII = "./ressources/ascii_files/";

arcade::OpenGL::OpenGL()
{
  const SDL_VideoInfo* info = NULL;
  int width = 0;
  int height = 0;
  int bpp = 0;
  int flags = 0;

  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    exit(-1);
  info = SDL_GetVideoInfo( );
  if(!info)
    exit(-1);
  width = 1600;
  height = 900;
  bpp = info->vfmt->BitsPerPixel;
  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
  flags = SDL_OPENGL;
  if( SDL_SetVideoMode( width, height, bpp, flags ) == 0 )
    exit(-1);
  this->setupOpengl( width, height );
  this->initMapInputGame();
  this->initMapInputCore();
  this->initMapColor();
  TTF_Init();
}

arcade::OpenGL::~OpenGL()
{
  SDL_Quit();
}

void									arcade::OpenGL::fillColor(float r, float g , float b)
{
  this->_rgb.clear();
  this->_rgb.insert(this->_rgb.end(), r);
  this->_rgb.insert(this->_rgb.end(), g);
  this->_rgb.insert(this->_rgb.end(), b);
}

void									arcade::OpenGL::initMapColor()
{
  this->fillColor(0, 0, 0);
  this->_colors[arcade::TileType::EMPTY] = this->_rgb;
  this->fillColor(1, 1, 1);
  this->_colors[arcade::TileType::BLOCK] = this->_rgb;
  this->fillColor(0, 0, 1);
  this->_colors[arcade::TileType::OTHER] = this->_rgb;
  this->fillColor(0, 0.5, 0.5);
  this->_colors[arcade::TileType::MY_SHOOT] = this->_rgb;
  this->fillColor(1, 0, 0);
  this->_colors[arcade::TileType::EVIL_DUDE] = this->_rgb;
  this->fillColor(0.5, 0, 0.5);
  this->_colors[arcade::TileType::EVIL_SHOOT] = this->_rgb;
  this->fillColor(0, 1, 0);
  this->_colors[arcade::TileType::POWERUP] = this->_rgb;
  this->fillColor(1, 1, 1);
  this->_colors[arcade::TileType::OBSTACLE] = this->_rgb;
}

void									arcade::OpenGL::initMapColor(Assets &assets)
{
  //printf("%d * (1/255) => %f\n", assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].val.r, assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].val.r * (1.0 / 255.0));
  this->fillColor(assets.c_map[static_cast<int>(arcade::TileType::EMPTY)].val.r * (1.0 / 255.0), assets.c_map[static_cast<int>(arcade::TileType::EMPTY)].val.v * (1.0 / 255.0), assets.c_map[static_cast<int>(arcade::TileType::EMPTY)].val.b * (1.0 / 255.0));
  this->_colors[arcade::TileType::EMPTY] = this->_rgb;
  this->fillColor(assets.c_map[static_cast<int>(arcade::TileType::BLOCK)].val.r * (1.0 / 255.0), assets.c_map[static_cast<int>(arcade::TileType::BLOCK)].val.v * (1.0 / 255.0), assets.c_map[static_cast<int>(arcade::TileType::BLOCK)].val.b * (1.0 / 255.0));
  this->_colors[arcade::TileType::BLOCK] = this->_rgb;
  this->fillColor(assets.c_player.val.r * (1.0 / 255.0), assets.c_player.val.v * (1.0 / 255.0), assets.c_player.val.b * (1.0 / 255.0));
  this->_colors[arcade::TileType::OTHER] = this->_rgb;
  this->fillColor(assets.c_map[static_cast<int>(arcade::TileType::MY_SHOOT)].val.r * (1.0 / 255.0), assets.c_map[static_cast<int>(arcade::TileType::MY_SHOOT)].val.v * (1.0 / 255.0), assets.c_map[static_cast<int>(arcade::TileType::MY_SHOOT)].val.b * (1.0 / 255.0));
  this->_colors[arcade::TileType::MY_SHOOT] = this->_rgb;
  this->fillColor(assets.c_map[static_cast<int>(arcade::TileType::EVIL_DUDE)].val.r * (1.0 / 255.0), assets.c_map[static_cast<int>(arcade::TileType::EVIL_DUDE)].val.v * (1.0 / 255.0), assets.c_map[static_cast<int>(arcade::TileType::EVIL_DUDE)].val.b * (1.0 / 255.0));
  this->_colors[arcade::TileType::EVIL_DUDE] = this->_rgb;
  this->fillColor(assets.c_map[static_cast<int>(arcade::TileType::EVIL_SHOOT)].val.r * (1.0 / 255.0), assets.c_map[static_cast<int>(arcade::TileType::EVIL_SHOOT)].val.v * (1.0 / 255.0), assets.c_map[static_cast<int>(arcade::TileType::EVIL_SHOOT)].val.b * (1.0 / 255.0));
  this->_colors[arcade::TileType::EVIL_SHOOT] = this->_rgb;
  this->fillColor(static_cast<float>(assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].val.r) * (1.0 / 255.0), assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].val.v * (1.0 / 255.0), assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].val.b * (1.0 / 255.0));
  this->_colors[arcade::TileType::POWERUP] = this->_rgb;
  this->fillColor(assets.c_map[static_cast<int>(arcade::TileType::OBSTACLE)].val.r * (1.0 / 255.0), assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].val.v * (1.0 / 255.0), assets.c_map[static_cast<int>(arcade::TileType::POWERUP)].val.b * (1.0 / 255.0));
  this->_colors[arcade::TileType::OBSTACLE] = this->_rgb;
}

void													arcade::OpenGL::initMapInputGame()
{
  this->input_game[(int)SDLK_z] = arcade::CommandType::GO_UP;
  this->input_game[(int)SDLK_q] = arcade::CommandType::GO_LEFT;
  this->input_game[(int)SDLK_s] = arcade::CommandType::GO_DOWN;
  this->input_game[(int)SDLK_d] = arcade::CommandType::GO_RIGHT;
  this->input_game[(int)SDLK_t] = arcade::CommandType::ILLEGAL;
  this->input_game[(int)SDLK_RETURN] = arcade::CommandType::SHOOT;
}

void													arcade::OpenGL::initMapInputCore()
{
  this->input_core[11] = arcade::CoreCommand::PREV_GRAPHIC;
  this->input_core[12] = arcade::CoreCommand::NEXT_GRAPHIC;
  this->input_core[13] = arcade::CoreCommand::PREV_GAME;
  this->input_core[14] = arcade::CoreCommand::NEXT_GAME;
  this->input_core[(int)SDLK_SPACE] = arcade::CoreCommand::PAUSE;
  this->input_core[18] = arcade::CoreCommand::RESTART;
  this->input_core[(int)SDLK_ESCAPE] = arcade::CoreCommand::ESCAPE;
}

void 			arcade::OpenGL::setupOpengl( int width, int height )
{
    float ratio = (float) width / (float) height;

    glShadeModel( GL_SMOOTH );
    glCullFace( GL_BACK );
    glFrontFace( GL_CCW );
    glEnable( GL_CULL_FACE );
    glClearColor( 0, 0, 0, 0 );
    glViewport( 0, 0, width, height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective( 60.0, ratio, 1.0, 1024.0 );
}

void									arcade::OpenGL::drawSquare(float x, float y, std::vector<float> rgb, float size)
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity( );
  glTranslatef( 0.0, 0.0, -5.0 );
  glBegin(GL_QUADS);
  glColor3f(rgb[0], rgb[1], rgb[2]);
  glVertex3f(x, y, 0);
  glVertex3f(x + size, y, 0);
  glVertex3f(x + size, y + size, 0);
  glVertex3f(x, y + size, 0);
}

bool									arcade::OpenGL::isOnMap(arcade::WhereAmI *player, int i, int width) const
{
  for (int pos = 0; pos < player->lenght; pos++)
    if (player->position[pos].x + player->position[pos].y * width == i)
      return true;
  return false;
}

void									arcade::OpenGL::ShowGame(WhereAmI *player, GetMap *map, Assets &assets)
{
//  static bool         initialisation = false;

  //if (initialisation == false) {
  this->initMapColor(assets);
//    initialisation = true;
//  }
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  for (float y = 0; y < map->height; y++)
  {
    for (float x = 0; x < map->width; x++)
    {
      if (this->isOnMap(player, (int)y * map->width + (int)x, map->width) == true)
        this->drawSquare(-2 + x / (map->width / 3), (-2 - y / (map->height / 3)) + 3, _colors[arcade::TileType::OTHER], 0.1);
      if (map->tile[(int)y * map->width + (int)x] != arcade::TileType::EMPTY)
        this->drawSquare(-2 + x / (map->width / 3), (-2 - y / (map->height / 3)) + 3, _colors[map->tile[(int)y * map->width + (int)x]], 0.1);
    }
  }
  //(void)assets;
}

void								  arcade::OpenGL::drawText(char c, float x, float y, std::vector<float> rgb)
{
    std::fstream			file;
    std::string				str;
    float							idx = 0;
    float							idxY = 7;

    file.open(RESSOURCES_ASCII + "alphabet.txt");
    if (file)
    {
      getline(file, str);
      while(!file.eof())
      {
        for (unsigned int i = 0; i < str.length(); i++)
          if (str[i] == '1' && ((idx >= (c - 65) * 7 * 2 && idx <= (c - 65) * 7 * 2 + 6) || (idx >= (c - 97) * 7 * 2 && idx <= (c - 97) * 7 * 2 + 6)))
            this->drawSquare(x + (float)i / 60, (y + idxY) / 40, rgb, 0.01);
        getline(file, str);
        if ((idx >= (c - 65) * 7 * 2 && idx <= (c - 65) * 7 * 2 + 6) || (idx >= (c - 97) * 7 * 2 && idx <= (c - 97) * 7 * 2 + 6))
          idxY--;
        idx++;
      }
    }
}

void								  arcade::OpenGL::drawNumber(int nb, float x, float y, std::vector<float> rgb)
{
    std::fstream			file;
    std::string				str;
    float							idx = 0;
    float							idxY = 7;

    file.open(RESSOURCES_ASCII + "./numbers.txt");
    if (file)
    {
      getline(file, str);
      while(!file.eof())
      {
        for (unsigned int i = 0; i < str.length(); i++)
        {
          if (str[i] == '1' && ((idx >= (nb) * 7 * 2 && idx <= nb * 7 * 2 + 6)))
            this->drawSquare(x + (float)i / 60, (y + idxY) / 40, rgb, 0.01);
        }
        getline(file, str);
        if (idx >= nb * 7 * 2 && idx <= nb * 7 * 2 + 6)
          idxY--;
        idx++;
      }
    }
}

void									arcade::OpenGL::putStrOpenGl(const char *str, float x, float y, std::vector<float> rgb)
{
  int	idx = 0;

  for (int i = 0; str[i] != '\0'; i++)
  {
    if (str[i] == '\n')
    {
      y -= 25;
      idx = 0;
    }
    if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
      drawText(str[i], x + (float)idx / 5, y, rgb);
    idx++;
  }
}

void									arcade::OpenGL::putNbrOpenGl(int nb, float x, float y, std::vector<float> rgb)
{
  int   a = 1;
  int		idx = 0;

  while (nb / a > 10)
    a *= 10;
  while (a)
  {
    drawNumber((nb / a), x + (float)idx / 5, y, rgb);
    nb %= a;
    a /= 10;
    idx++;
  }
}

void									arcade::OpenGL::ShowMenu(std::vector<std::string> gamesLibs, int idxGame,
                                               std::vector<std::string> graphicsLibs, int idxGraphic,
                                               arcade::Button button, const arcade::playerName &player)
{
  int									y = 0;

  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  this->putStrOpenGl("ARCADE", -0.5, 70, this->_colors[arcade::TileType::MY_SHOOT]);
  this->putStrOpenGl("APPUYER SUR ENTREE POUR COMMENCER L AVENTURE", -4.5, 50, this->_colors[arcade::TileType::MY_SHOOT]);

  for(unsigned int i = 0; i < graphicsLibs.size(); i++)
  {
    if ((int)i == idxGraphic)
      this->putStrOpenGl(graphicsLibs[i].c_str(), -3, 2 - y, this->_colors[arcade::TileType::EVIL_DUDE]);
    else
      this->putStrOpenGl(graphicsLibs[i].c_str(), -3, 2 - y, this->_colors[arcade::TileType::BLOCK]);
    y += 10;
  }
  y = 0;
  for(unsigned int i = 0; i < gamesLibs.size(); i++)
  {
    if ((int)i == idxGame)
      this->putStrOpenGl(gamesLibs[i].c_str(), 2, 2 - y, this->_colors[arcade::TileType::EVIL_DUDE]);
    else
      this->putStrOpenGl(gamesLibs[i].c_str(), 2, 2 - y, this->_colors[arcade::TileType::BLOCK]);
    y += 10;
  }
  (void)button;
  (void)player;
  glEnd( );
  SDL_GL_SwapBuffers( );
}

void 									arcade::OpenGL::handle_key_down( SDL_keysym* keysym, ICore *core)
{
  if (keysym->sym == SDLK_q || keysym->sym == SDLK_z || keysym->sym == SDLK_d || keysym->sym == SDLK_s ||
      keysym->sym == SDLK_RETURN || keysym->sym == SDLK_t)
      core->NotifyScene(this->input_game[(int)keysym->sym]);
  if (keysym->scancode == 11|| keysym->scancode == 12 || keysym->scancode == 13 ||keysym->scancode == 14 ||
      keysym->scancode == 18)
      core->NotifyCore(this->input_core[(int)keysym->scancode]);
  if (keysym->sym == SDLK_ESCAPE || keysym->sym == SDLK_SPACE)
    core->NotifyCore(this->input_core[(int)keysym->sym]);
}

void									arcade::OpenGL::GetInput(ICore *core)
{
  SDL_Event event;

  while( SDL_PollEvent( &event ) )
  {
    switch( event.type )
    {
      case SDL_KEYDOWN:
          handle_key_down( &event.key.keysym, core);
          break;
      case SDL_QUIT:
          exit(0);
          break;
    }
  }
}

void					        arcade::OpenGL::PrintGameOver(arcade::Status status)
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  if (status == arcade::Status::WIN)
    this->putStrOpenGl("WIN", -0.5, 40, this->_colors[arcade::TileType::MY_SHOOT]);
  else
    this->putStrOpenGl("GAME OVER", -0.5, 40, this->_colors[arcade::TileType::MY_SHOOT]);
  glEnd( );
  SDL_GL_SwapBuffers( );
}

void									arcade::OpenGL::ShowScoreboard(const std::string &game, std::vector<arcade::IScore *>bestScore)
{
  (void)game;
  (void)bestScore;
}

void                  arcade::OpenGL::initColors(const Assets &assets)
{
  (void)assets;
}

void	renderText(const char *text, TTF_Font *font, SDL_Color color, SDL_Rect *location);

void									arcade::OpenGL::ShowScore(const arcade::IScore *currentScore, const std::vector<arcade::IScore *> &bestScore)
{
  this->putStrOpenGl("Meilleurs Scores", 1.5, 40, this->_colors[arcade::TileType::EVIL_DUDE]);
  for (unsigned int i = 0; i < bestScore.size() && bestScore.size() > 0; i++)
  {
    this->putStrOpenGl(bestScore[i]->getName().c_str(), 1.5, 30 - i * 10, this->_colors[arcade::TileType::MY_SHOOT]);
    this->putNbrOpenGl((int)(bestScore[i]->getScore()), 3, 30 - i * 10, this->_colors[arcade::TileType::BLOCK]);
  }
  this->putStrOpenGl("Score actuel", 1.5, 0, this->_colors[arcade::TileType::EVIL_DUDE]);
  this->putNbrOpenGl((int)(currentScore->getScore()), 1.5, -10,  this->_colors[arcade::TileType::BLOCK]);
  (void)currentScore;
  (void)bestScore;
  glEnd( );
  SDL_GL_SwapBuffers( );
}

extern "C" arcade::IGraphic*		CreateDisplayModule()
{
  return new arcade::OpenGL();
}
