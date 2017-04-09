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
  else
  {
    std::cout << "Usage: ./arcade graphic_library" << std::endl;
    std::cout << "Ex:    ./arcade lib/lib_arcade_ncurses.so" << std::endl;
  }
  return (0);
}
