#include			<iostream>

#include			"Archive.hpp"

int				main(void)
{
  std::string			map = "0123";
  int				width = 5, test = 2;
  Archive			archive;
  std::ofstream			f1("toto.dat", std::ios::out | std::ios::binary);

  archive.serialize(f1, width);
  archive.serialize(f1, map);
  archive.serialize(f1, test);

  f1.close();

  std::ifstream			f2("toto.dat", std::ios::out | std::ios::binary);

  int				width1, test1;
  std::string			map1;

  archive.unserialize(f2, &width1);
  archive.unserialize(f2, &map1);
  archive.unserialize(f2, &test1);

  f2.close();

  std::cout << "Width : " << width1 << std::endl;
  std::cout << "Map Value : " << map1 << std::endl;
  std::cout << test1 << std::endl;
}
