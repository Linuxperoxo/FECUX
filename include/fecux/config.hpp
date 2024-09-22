/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: config.hpp

*/

#ifndef __CONFIG_HPP__
#define __CONFIG_HPP__

#include <atomic>
#include <condition_variable>

#include "../utils/string.hpp"

#define OPTIONS_NUM 5

namespace fecux{
namespace main{

class config;

typedef struct options{
private:
  inline static const char* _opts_names[OPTIONS_NUM]{
    "source_dir",
    "fakeroot_dir",
    "cflags",
    "cxxflags",
    "jobs"
  };

  inline static fecux::utils::string _source_dir;
  inline static fecux::utils::string _fakeroot_dir;
  inline static fecux::utils::string _cflags;
  inline static fecux::utils::string _cxxflags;
  inline static fecux::utils::string _jobs;

  options() = delete;
  options(const options&) = delete;
  options(options&&) = delete;
  options& operator=(const options&) = delete;
  options& operator=(options&&) = delete;

  ~options() = delete;

  friend class fecux::main::config;
}opts;

class config{
  config() = delete;
  config(const config&) = delete;
  config(config&&) = delete;
  config& operator=(const config&) = delete;
  config& operator=(config&&) = delete;

  ~config() = delete;

public:
  static void load_config(const char** _opts_value, std::atomic<bool>& _loadded, std::condition_variable& _cond) noexcept;   
  
  inline static const char* source_dir() noexcept { return *fecux::main::options::_source_dir; };
  inline static const char* fakeroot_dir() noexcept { return *fecux::main::options::_fakeroot_dir; };
  inline static const char** opts_names() noexcept { return fecux::main::options::_opts_names; }
};

} // namespace main
} // namespace fecux

#endif
