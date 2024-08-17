#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

#include "../utils/smartpointer.hpp"

struct configs{
  std::string source_dir;
  std::string fakeroot_dir;
  std::string cflags;
  std::string cxxflags;
  std::string jobs;

  explicit configs();
};

class config_file{
private:
  const smt_ptr<configs> config_struct;  
public:
  explicit config_file() : config_struct(){};

  std::string getSourceDir() const noexcept;
  std::string getFakerootDir() const noexcept;
  std::string getCflags() const noexcept;
  std::string getCxxflags() const noexcept;
  std::string getJobs() const noexcept;
};

#endif
