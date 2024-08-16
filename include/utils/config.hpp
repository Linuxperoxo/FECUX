#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

#include "smartpointer.hpp"

struct configs{
  const std::string source_dir;
  const std::string fakeroot_dir;
  const std::string cflags;
  const std::string cxxflags;
  const std::string jobs;

  configs();
};

class config_file{
private:
  smt_ptr<configs> config_struct;  
public:
  config_file();

  const std::string getSourceDir() const noexcept;
  const std::string getFakerootDir() const noexcept;
  const std::string getCflags() const noexcept;
  const std::string getCxxflags() const noexcept;
  const std::string getJobs() const noexcept;
};

#endif
