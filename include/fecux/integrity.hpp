/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: integrity.hpp

*/

#ifndef __INTEGRITY_HPP__
#define __INTEGRITY_HPP__

#include <exception>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace fecux{
namespace main{

class integrity{
private:
  integrity() = delete;
  integrity(integrity&&) = delete;
  integrity(const integrity&) = delete;
  integrity& operator=(integrity&&) = delete;
  integrity& operator=(const integrity&) = delete;
  
  ~integrity() = delete;

  static void config_file(const char** _opts_names, std::exception_ptr& _except_ptr);
  static void check_dir(std::mutex& _mtx, std::condition_variable& _cond, std::atomic<bool> & _loadded, std::exception_ptr& _except_ptr); 

public:
  static void check_health() noexcept;
};

} // namespace main
} // namespace fecux

#endif 
