#ifndef				ARCHIVE_HPP_
# define			ARCHIVE_HPP_

# include			<fstream>

namespace			Archive
{
  bool				open(std::ofstream &file, std::string const & path)
  {
    file.open(path.c_str(), std::ios::out | std::ios::binary);
    return (!file.fail());
  }

  bool				open(std::ifstream &file, std::string const & path)
  {
    file.open(path.c_str(), std::ios::out | std::ios::binary);
    return (!file.fail());
  }

  /*
  ** Serialize T
  */
  template <typename T>
  void				serialize(std::ofstream &file, T a)
  {
    file.write(reinterpret_cast<const char *>(&a), sizeof(a));
  }

  /*
  ** Serialize std::string
  */
  void				serialize(std::ofstream &file, std::string const & a)
  {
    serialize(file, (int)(a.size()));
    file.write(a.c_str(), a.size());
  }

  /*
  ** Unserialize T
  */
  template <typename T>
  void				unserialize(std::ifstream &file, T *a)
  {
    file.read(reinterpret_cast<char *>(a), sizeof(*a));
  }

  /*
  ** Unserialize std::string
  */
  void				unserialize(std::ifstream &file, std::string & a)
  {
    int				strSize;

    unserialize(file, &strSize);

    char			buffer[strSize + 1];
    file.read(buffer, strSize);
    buffer[strSize] = '\0';
    a.assign(buffer);
  }
}

#endif				/* !ARCHIVE_HPP_ */
