/*

  AUTHOR: Linuxperoxo                    
  COPYRIGHT: (c) 2024 per Linuxperoxo.
  FILE: config.cpp

*/

#include <cstdint>

#include "../include/fecux/config.hpp"

void fecux::config::load_config(char** _opts_value, std::atomic<bool>& _dir_is_loadded, std::condition_variable& _cond_to_thread) noexcept{
  


  /*
  
    Array para alterar os membros da struct

  */



  fecux::utils::string* _opts_ref[OPTIONS_NUM]{
    &opts::_source_dir,
    &opts::_fakeroot_dir,
    &opts::_cflags,
    &opts::_cxxflags,
    &opts::_jobs
  };



  /*
  
    Esse for está interando pelo array e mandando as informações
    do arquivo de configurações para cada membro da struct

  */



  for(uint8_t i{0}; i < OPTIONS_NUM; i++){
    *_opts_ref[i] = _opts_value[i];
    if(i == 2){
      _dir_is_loadded.store(true);
      _cond_to_thread.notify_one();
    }



    /* 
    
      Liberando memória que não vai ser mais ultilizada 
    
    */



    std::free(_opts_value[i]);
  }



  /* 
    
    Liberando o resto da memória 
  
  */



  std::free(_opts_value);
}
