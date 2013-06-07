#include			<iostream>
#include			<fstream>
#include			"Save.hh"

class				Archive
{
  // ATTRIBUTS
private:
  std::ofstream			inputFile_;
  std::ifstream			outputFile_;

  // CTOR - DTOR
public:
  Archive() {}
  ~Archive() {}
  Archive(Archive const &);

  // OPERATOR
public:
  Archive &			operator=(Archive const &);

  // METHODS
public:
  template <typename T>
  void				serialize(std::ofstream &file, T a)
  {
    file.write(reinterpret_cast<const char *>(&a), sizeof(a));
    std::cout << "Serialisation de \"" << a << "\" de taille " << sizeof(a) << std::endl;
  }

  void				serialize(std::ofstream &file, std::string a)
  {
    file.write(a.c_str(), a.size());
    std::cout << "Serialization de \"" << a.c_str() << "\" de taille " << a.size() << std::endl;
  }


  template <typename T>
  void				unserialize(std::ifstream &file, T *a, int size)
  {
    file.read(reinterpret_cast<char *>(a), size);
    std::cout << "Unserialisation de \"" << *a << "\" de taille " << size << std::endl;
  }

  void				unserialize(std::ifstream &file, std::string *a, int size)
  {
    char			buffer[size + 1];
    file.read(buffer, size);
    buffer[size] = '\0';

    a->assign(buffer);
    std::cout << "Unserialisation std::string " << buffer << " size " << size << std::endl;
  }
};

int				main(void)
{
  std::string			map = "0123";
  int				width = 5;
  Archive			archive;
  std::ofstream			f1("toto.dat", std::ios::out | std::ios::binary);

  archive.serialize(f1, width);
  archive.serialize(f1, (int)(map.size()));
  archive.serialize(f1, map);

  f1.close();

  std::ifstream			f2("toto.dat", std::ios::out | std::ios::binary);

  int				map1Size, width1;
  std::string			map1;

  archive.unserialize(f2, &width1, sizeof(width1));
  archive.unserialize(f2, &map1Size, sizeof(map1Size));
  archive.unserialize(f2, &map1, map1Size);

  f2.close();

  std::cout << "Width : " << width1 << std::endl;
  std::cout << "Map Size : " << map1Size << std::endl;
  std::cout << "Map Value : " << map1 << std::endl;

}
