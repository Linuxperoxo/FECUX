//==========================================|
//   FILE: random.hpp                       |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#ifndef RANDOM_H
#define RANDOM_H

#include <random>

template <typename T = int>
T randomNum(T min, T max){
  std::random_device rd;
  std::mt19937 gen(rd());

  std::uniform_int_distribution<> distrib(min, max);

  return distrib(gen);
}

#endif
