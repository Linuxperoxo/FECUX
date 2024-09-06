//==========================================|
//   FILE: files_utils.hpp                  |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef __FILES_UTILS_HPP__
#define __FILES_UTILS_HPP__

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
        static bool is_file(const char* _file) noexcept;
        static bool is_dir(const char* _dir) noexcept;
        static bool is_empty(const char* _dir) noexcept;
        static void create_dirs(const char* _dir) noexcept;
      };
    }
  }
}

#endif
