//==========================================|
//   FILE: animation.cpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <chrono>
#include <iostream>
#include <thread>

#include "../include/color.hpp"
#include "animation.hpp"

#define FPS 5

/*

============================================================|
STATIC MEMBER

*/

const char *fecux::utils::animation::_animation_frames[_ANIMATION_FRAMES]{
    "---------------------", "C-------------------H", " C-----------------H ",
    "  C---------------H  ", "   C-------------H   ", "    C-----------H    ",
    "     C---------H     ", "      C-------H      ", "       C-----H       ",
    "        C---H        ", "        C + H <3     "};

/*

============================================================|
CLASS MEMBER FUNCTIONS

*/

void fecux::utils::animation::run(std::atomic<bool> *_running,
                                  const char *_loading_msg) noexcept {
  while (_running->load()) {
    for (int i = 0; i < _ANIMATION_FRAMES; i++) {
      std::cout << '\r' << _loading_msg << ' ' << BLUE << '[' << NC
                << _animation_frames[i] << BLUE << ']' << NC;
      std::cout.flush();
      std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
    }
  }
  std::cout << '\n';
}
