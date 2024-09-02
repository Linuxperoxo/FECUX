#ifndef __FILES_HPP__
#define __FILES_HPP__

#include <filesystem>

namespace fecux{
  namespace tools{
    class files{
    public:
      inline static bool is_file(const char* _file) noexcept{
        return std::filesystem::exists(_file) && std::filesystem::is_regular_file(_file);
      }
      
      inline static bool is_dir(const char* _dir) noexcept{
        return std::filesystem::exists(_dir) && std::filesystem::is_directory(_dir);
      }
    };
  }
}

#endif
