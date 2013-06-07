#ifndef				ARCHIVE_HPP_
# define			ARCHIVE_HPP_

# include			<fstream>

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

  // PUBLIC METHODS
public:
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
  void				serialize(std::ofstream &file, std::string a)
  {
    this->serialize(file, (int)(a.size()));
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
  void				unserialize(std::ifstream &file, std::string *a)
  {
    int				strSize;
    this->unserialize(file, &strSize);

    char			buffer[strSize + 1];
    file.read(buffer, strSize);
    buffer[strSize] = '\0';
    a->assign(buffer);
  }
};

#endif				/* !ARCHIVE_HPP_ */
