#include "GSnake.hpp"
#include "LSfml.hpp"

int							main()
{
  //Play();
  arcade::IGraphic*	graphic = new arcade::LSfml;
  arcade::WhereAmI*	snake = (arcade::WhereAmI*)malloc(sizeof(*snake) + 4 * sizeof(arcade::Position));
  arcade::GetMap*	map = (arcade::GetMap*)malloc(sizeof(*map) + 64 * sizeof(arcade::TileType));
  snake->type = arcade::CommandType::WHERE_AM_I;
  snake->lenght = 4;
  snake->position[0].x = 2;
  snake->position[0].y = 4;
  snake->position[1].x = 3;
  snake->position[1].y = 4;
  snake->position[2].x = 4;
  snake->position[2].y = 4;
  snake->position[3].x = 5;
  snake->position[3].y = 4;
  map->type = arcade::CommandType::GET_MAP;
  map->width = 8;
  map->height = 8;
  for (int i = 0; i < 64; i++)
    map->tile[i] = arcade::TileType::EMPTY;
  graphic->ShowGame(snake, map);
  while (1);
  return (0);
}
