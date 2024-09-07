//==========================================|
//   FILE: integrity.cpp                    |
//   AUTHOR: Linuxperoxo                    |
//   COPYRIGHT: (c) 2024 per Linuxperoxo.   |
//==========================================/

#include <cstddef>
#include <chrono>
#include <thread>
#include <iostream>

#include "../include/integrity.hpp"
#include "../include/color.hpp"
#include "../include/fecux_vars.hpp"
#include "../include/files_utils.hpp"

#define NUM_CHECK_DIRS 4
#define DELAY 500


/*
 
===========================================================|
CLASS MEMBER FUNCTIONS
 
 */

void fecux::tools::runtime::integrity::verify_dirs(const fecux::main::config *_config) noexcept{
  const char* _dirs[NUM_CHECK_DIRS] = {_config->source_dir(), _config->fakeroot_dir(), MAIN_REPO_DIR, WORLD_DIR};

  for(size_t i = 0; i < sizeof(_dirs) / sizeof(_dirs[0]); i++){
    if(!fecux::tools::runtime::filesUtils::is_dir(_dirs[i])){
      fecux::tools::runtime::filesUtils::create_dirs(_dirs[i]);
      std::cerr << YELLOW << "::: " << NC << GREEN << _dirs[i] << NC << " Created! :)\n";
      std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
    }
  }
}
