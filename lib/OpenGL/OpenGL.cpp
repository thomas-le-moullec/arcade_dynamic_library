#include "OpenGL.hpp"

SDL_Surface *text();
void			renderText(std::string, SDL_Color, int, int, TTF_Font *);

arcade::OpenGL::OpenGL()
{
  const SDL_VideoInfo* info = NULL;
  int width = 0;
  int height = 0;
  int bpp = 0;
  int flags = 0;

  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
  {
      fprintf( stderr, "Video initialization failed: %s\n", SDL_GetError());
      exit(-1);
  }
  info = SDL_GetVideoInfo( );
  if(!info)
   {
      fprintf( stderr, "Video query failed: %s\n",
      SDL_GetError( ) );
      exit(-1);
  }
  width = 1600;
  height = 900;
  bpp = info->vfmt->BitsPerPixel;
  SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 5 );
  SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
  SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
  flags = SDL_OPENGL;// | SDL_FULLSCREEN;
  if( SDL_SetVideoMode( width, height, bpp, flags ) == 0 )
  {
      fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
      exit(-1);
  }
  this->setupOpengl( width, height );
  this->initMapColor();
  this->initMapInputGame();
  this->initMapInputCore();
  //this->_angle = 0;
  TTF_Init();
  //this->_font = TTF_OpenFont("./ressources/Fonts/MASQUE__.ttf", 65);
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
}

void													arcade::OpenGL::initMapInputGame()
{
  this->input_game[(int)SDLK_s] = arcade::CommandType::GO_UP;
  this->input_game[(int)SDLK_q] = arcade::CommandType::GO_LEFT;
  this->input_game[(int)SDLK_z] = arcade::CommandType::GO_DOWN;
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

void									arcade::OpenGL::drawSquare(float x, float y, std::vector<float> rgb)
{
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity( );
  glTranslatef( 0.0, 0.0, -5.0 );
  glBegin(GL_QUADS);
  glColor3f(rgb[0], rgb[1], rgb[2]);
  glVertex3f(x, y, 0);
  glVertex3f(x + 0.1, y, 0);
  glVertex3f(x + 0.1, y + 0.1, 0);
  glVertex3f(x, y + 0.1, 0);
}

bool									arcade::OpenGL::isOnMap(arcade::WhereAmI *player, int i, int width) const
{
  for (int pos = 0; pos < player->lenght; pos++)
    if (player->position[pos].x + player->position[pos].y * width == i)
      return true;
  return false;
}

void									arcade::OpenGL::ShowGame(WhereAmI *player, GetMap *map, const Assets &assets)
{
/*
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  for (float y = 0; y < map->height; y++)
  {
    for (float x = 0; x < map->width; x++)
    {
      if (this->isOnMap(player, (int)y * map->width + (int)x, map->width) == true)
        this->drawSquare(-2 + x / (map->width / 3), -2 + y / (map->height / 3), _colors[arcade::TileType::OTHER]);
      if (map->tile[(int)y * map->width + (int)x] != arcade::TileType::EMPTY)
        this->drawSquare(-2 + x / (map->width / 3), -2 + y / (map->height / 3), _colors[map->tile[(int)y * map->width + (int)x]]);
    }
  }
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 10, 10, 0, GL_RGB, GL_UNSIGNED_BYTE, text());
  glEnd( );
  SDL_GL_SwapBuffers( );*/

(void)player;
(void)map;
  (void)assets;
}

void									arcade::OpenGL::ShowMenu(std::vector<std::string> gamesLibs, int idxGame,
                                               std::vector<std::string> graphicsLibs, int idxGraphic,
                                               arcade::Button button, const arcade::playerName &player)
{
  (void)gamesLibs;
  (void)idxGame;
  (void)graphicsLibs;
  (void)idxGraphic;
  (void)button;
  (void)player;
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
  (void)status;
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
  //SDL_BindTexture(solidTexture);
  //InitEverything();
  //std::cout << "Attention ! ca va segfault" << std::endl;
  //std::cout << "PUTA" << std::endl;
  TTF_Font* font = TTF_OpenFont("./ressources/Fonts/arial.ttf", 50);
  SDL_Color col;
  SDL_Rect rect;

  rect.x = 0;
  rect.y = 0;
  col.r = 255;
  col.g = 255;
  col.b = 255;
  renderText("TOTO", font, col, &rect);

  (void)currentScore;
  (void)bestScore;
}

extern "C" arcade::IGraphic*		CreateDisplayModule()
{
  return new arcade::OpenGL();
}

void			ArenderText(std::string message, SDL_Color color, int x, int y, TTF_Font* font)
{
  std::cout << "coucou" << std::endl;
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

//  gluOrtho2D(0, gWindow->getWidth(),0,gWindow->getHeight());
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  SDL_Surface * sFont = TTF_RenderText_Blended(font, message.c_str(), color);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sFont->w, sFont->h, 0, GL_BGRA,
                GL_UNSIGNED_BYTE, sFont->pixels);

  glBegin(GL_QUADS);
  {
    glTexCoord2f(0,1); glVertex2f(x, y);
    glTexCoord2f(1,1); glVertex2f(x + sFont->w, y);
    glTexCoord2f(1,0); glVertex2f(x + sFont->w, y + sFont->h);
    glTexCoord2f(0,0); glVertex2f(x, y + sFont->h);
  }
  glEnd();
  SDL_GL_SwapBuffers( );

}


SDL_Surface *text()
{
  TTF_Font* font = TTF_OpenFont("./ressources/Fonts/arial.ttf", 50);

  if (!font)
    exit(0);

  SDL_Color col1;
  SDL_Color col2;

  col1.r = 255;
  col1.g = 255;
  col1.b = 255;

  col2.r = 0;
  col2.g = 0;
  col2.b = 255;
  SDL_Surface* textSurface = TTF_RenderText_Shaded(font, "This is my text.", col1, col2);
  if (!textSurface)
    std::cout << "NULL" << std::endl;


    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

  //  gluOrtho2D(0, gWindow->getWidth(),0,gWindow->getHeight());
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Pass zero for width and height to draw the whole surface
  SDL_Rect textLocation = { 100, 100, 0, 0 };

return textSurface;
}

void renderText(const char *text, TTF_Font *font, SDL_Color color, SDL_Rect *location)
{
SDL_Surface *initial;
SDL_Surface *initialOutline;
SDL_Surface *intermediary;
SDL_Rect rect;
int w,h;
GLuint textureTwo;
SDL_Color outline;

w = 0;
h = 0;

outline.r = 255;
outline.g = 0;
outline.b = 0;

// Use SDL_TTF to render our text
initial = TTF_RenderText_Solid(font, text, color);
initialOutline = TTF_RenderText_Solid(font, text, outline);

// Convert the rendered text to a known format
//w = nextpoweroftwo(5+initial->w);
//h = nextpoweroftwo(5+initial->h);

/* SDL interprets each pixel as a 32-bit number, so our masks must
depend
on the endianness (byte order) of the machine */
Uint32 rmask, gmask, bmask, amask;
bool colorIsRGBA = true;
rmask = 0xff000000;
gmask = 0x00ff0000;
bmask = 0x0000ff00;
amask = 0x000000ff;
colorIsRGBA = false;
rmask = 0x000000ff;
gmask = 0x0000ff00;
bmask = 0x00ff0000;
amask = 0xff000000;
colorIsRGBA = true;
intermediary = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);

for (int outlineY = 0; outlineY < 5; outlineY++)
for (int outlineX = 0; outlineX < 5; outlineX++)
{
rect.x = outlineX;
rect.y = outlineY;
SDL_BlitSurface(initialOutline, 0, intermediary, &rect);
}

rect.x = 2;
rect.y = 2;
SDL_BlitSurface(initial, 0, intermediary, &rect);

// Tell GL about our new texture
glGenTextures(1, &textureTwo);
glBindTexture(GL_TEXTURE_2D, textureTwo);
if (colorIsRGBA == true)
  glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, intermediary->pixels );
else
  glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, intermediary->pixels );


// GL_NEAREST looks horrible, if scaled...
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// prepare to render our texture
glEnable(GL_TEXTURE_2D);
glBindTexture(GL_TEXTURE_2D, textureTwo);
glColor3f(1.0f, 1.0f, 1.0f);

// Draw a quad at location
glBegin(GL_QUADS);
// Recall that the origin is in the lower-left corner
// That is why the TexCoords specify different corners
// than the Vertex coors seem to.
glTexCoord2f(0.0f, 1.0f);
glVertex2f(location->x , location->y + h);

glTexCoord2f(1.0f, 1.0f);
glVertex2f(location->x + w, location->y + h);

glTexCoord2f(1.0f, 0.0f);
glVertex2f(location->x + w, location->y );

glTexCoord2f(0.0f, 0.0f);
glVertex2f(location->x , location->y );
glEnd();

// Bad things happen if we delete the texture before it finishes
glFinish();

// return the deltas in the unused w,h part of the rect
location->w = initial->w;
location->h = initial->h;

}
