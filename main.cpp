#include "Core.hpp"

int							main(int ac, char **av)
{
  arcade::Core					*core = new arcade::Core();

  if (ac == 2)
  {
    core->LoadGraphic(av[1]);
    core->RunArcade();
  }
  return (0);
}
