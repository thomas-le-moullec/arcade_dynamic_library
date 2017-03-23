#include "Core.hpp"

int							main(int ac, char **av)
{
  arcade::ICore					*core = new arcade::Core();

  if (ac == 2)
    core->RunArcade(av[1]);
  return (0);
}
