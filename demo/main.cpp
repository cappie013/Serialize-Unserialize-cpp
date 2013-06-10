#include			<iostream>

#include			"Archive.hpp"

int				main(void)
{
  std::string			map = "0123";
  int				width = 5, test = 2;
  std::ofstream			f1;

  if (!Archive::open(f1, "toto.dat"))
    return -1;

  Archive::serialize(f1, width);
  Archive::serialize(f1, map);
  Archive::serialize(f1, test);

  Archive::close(f1);

  std::ifstream			f2;
  int				width1, test1;
  std::string			map1;

  if (!Archive::open(f2, "toto.dat"))
    return -1;

  Archive::unserialize(f2, width1);
  Archive::unserialize(f2, map1);
  Archive::unserialize(f2, test1);

  f2.close();

  std::cout << "Width : " << width1 << std::endl;
  std::cout << "Map Value : " << map1 << std::endl;
  std::cout << test1 << std::endl;

  Archive::close(f2);

  return 0;
}
