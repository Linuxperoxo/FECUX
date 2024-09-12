//==========================================|
//   FILE: animation.hpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef __ANIMATION_HPP__
#define __ANIMATION_HPP__

#include <atomic>

#define _ANIMATION_FRAMES 11

namespace fecux {
namespace utils {
class animation {
private:
  static const char *_animation_frames[_ANIMATION_FRAMES];

  animation() = delete;
  animation(const animation &) = delete;
  animation(animation &&) = delete;
  animation &operator=(const animation &) = delete;
  animation &operator=(animation &&) = delete;

  ~animation() = delete;

public:
  static void run(std::atomic<bool> *_running,
                  const char *_loading_msg) noexcept;
};
} // namespace utils
} // namespace fecux

#endif // !__ANIMATION_HPP__
