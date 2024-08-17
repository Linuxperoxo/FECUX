#include <cstdlib>
#include <vector>
#include <thread>
#include <chrono>
#include <filesystem>
#include <iostream>

#include "../include/caroline/const_var.hpp"
#include "../include/utils/check.hpp"
#include "../include/utils/color.hpp"
#include "../include/utils/caroexception.hpp"
#include "../include/caroline/caroline.hpp"

caroline::caroline() 
  : config(){
  check_dirs();
}

int caroline::check_dirs(){
  const std::vector<std::string> dirs = {config->getSourceDir(), config->getFakerootDir(), WORLD_DIR, REPO_DIR};
  
  try{
    for(const auto& dir : dirs){
      if(!check::is_dir(dir.c_str())){
        if(dir == REPO_DIR){
          throw caroexception(REPO_DIR_NOT_FOUND);
        }
        std::cerr << YELLOW "WARNING: " NC "Creating directory " GREEN << dir << NC << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
        if(std::filesystem::create_directories(dir)){
          std::cerr << GREEN ">>> " NC "Successfully created\n"; 
        } else {
          throw caroexception(FAILED_TO_CREATE_DIR);
        }
      }
    }
    return 1;
  }
  catch(caroexception& _runtime_error){
    _runtime_error.getAll();
    exit(_runtime_error.getErrorCode());
  }
}
