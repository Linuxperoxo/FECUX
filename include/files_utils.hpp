//==========================================|
//   FILE: files_utils.hpp                  |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef __FILES_UTILS_HPP__
#define __FILES_UTILS_HPP__

#include <filesystem>

namespace fecux{
  namespace tools{
    namespace runtime{
      class filesUtils{
      private:
        filesUtils() = delete;
        filesUtils(const filesUtils&) = delete;
        filesUtils(const filesUtils&&) = delete;
        filesUtils& operator=(const filesUtils&) = delete;
        filesUtils& operator=(const filesUtils&&) = delete;
        ~filesUtils() = delete;
      public:
        static inline bool is_file(const char* _file) noexcept{
          return std::filesystem::exists(_file) && std::filesystem::is_regular_file(_file);
        }
        
        static inline bool is_dir(const char* _dir) noexcept{
          return std::filesystem::exists(_dir) && std::filesystem::is_directory(_dir);
        }
      };
    }
  }
}

#endif
