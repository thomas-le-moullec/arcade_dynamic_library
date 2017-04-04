#include "Core.hpp"

int							main(int ac, char **av)
{
  arcade::Core					*core = new arcade::Core();

  if (ac == 2)
  {
    try {
      core->LoadGraphic(av[1]);
    }
    catch (RunTimeErrorCore const &stdErr) {
      std::cerr << stdErr.what() << std::endl;
      exit(-1);
    }
    core->RunArcade();
    delete core;
  }
  return (0);
}
