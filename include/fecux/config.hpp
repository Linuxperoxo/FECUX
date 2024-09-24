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

class config{
private:
  config() = delete;
  config(const config&) = delete;
  config(config&&) = delete;
  config& operator=(const config&) = delete;
  config& operator=(config&&) = delete;

  ~config() = delete;

  typedef struct options{
    options() = delete;
    options(const options&) = delete;
    options(options&&) = delete;
    options& operator=(const options&) = delete;
    options& operator=(options&&) = delete;
  
    ~options() = delete;

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
  }opts;
public:
  static void load_config(char** _opts_value, std::atomic<bool>& _dir_is_loadded, std::condition_variable& _cond_to_thread) noexcept;

  inline static const char* source_dir() noexcept { return *opts::_source_dir; }
  inline static const char* fakeroot_dir() noexcept { return *opts::_fakeroot_dir; }
  inline static const char** options_names() noexcept { return opts::_opts_names; }
};

} // namespace fecux

#endif
