#ifndef				ARCHIVE_HPP_
# define			ARCHIVE_HPP_

# include			<fstream>

namespace			Archive
{
  /*
  ** Serialize T
  */
  template <typename T>
  inline void			serialize(std::ofstream &file, T const & a)
  {
    file.write(reinterpret_cast<const char *>(&a), sizeof(a));
  }

  /*
  ** Serialize std::string
  */
  inline void			serialize(std::ofstream &file, std::string const & a)
  {
    serialize(file, (int)(a.size()));
    file.write(a.c_str(), a.size());
  }

  /*
  ** Unserialize T
  */
  template <typename T>
  inline void			unserialize(std::ifstream &file, T & a)
  {
    file.read(reinterpret_cast<char *>(&a), sizeof(a));
  }

  /*
  ** Unserialize std::string
  */
  inline void			unserialize(std::ifstream &file, std::string & a)
  {
    int				strSize;

    unserialize(file, strSize);

    char			buffer[strSize + 1];
    file.read(buffer, strSize);
    buffer[strSize] = '\0';
    a.assign(buffer);
  }

  inline bool			open(std::ofstream &file, std::string const & path)
  {
    file.open(path.c_str(), std::ios::out | std::ios::binary);
    return (!file.fail());
  }

  inline bool			open(std::ifstream &file, std::string const & path)
  {
    unsigned int		s;
    unsigned int		rs;

    file.open(path.c_str(), std::ios::out | std::ios::binary);
    if (file.fail())
      return false;
    file.seekg(0, std::ios::end);
    s = file.tellg();
    file.seekg(s - sizeof(int));
    unserialize(file, rs);
    file.seekg(0, std::ios::beg);
    return (s - sizeof(int) == rs);
  }

  inline void			close(std::ofstream &file)
  {
    file.seekp(0, std::ios::end);
    serialize(file, (int)(file.tellp()));
    file.close();
  }

  inline void			close(std::ifstream &file)
  {
    file.close();
  }

}

#endif				/* !ARCHIVE_HPP_ */
