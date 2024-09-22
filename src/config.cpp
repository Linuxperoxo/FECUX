/*

  AUTHOR: Linuxperoxo                    
  COPYRIGHT: (c) 2024 per Linuxperoxo.
  FILE: config.cpp

*/

#include <libconfig.h++>

#include "../include/fecux/config.hpp"

void fecux::main::config::load_config(const char** _opts_value, std::atomic<bool>& _loadded, std::condition_variable& _cond) noexcept{
  
  /*
  
    Array para alterar os membros da struct

  */

  fecux::utils::string* _opts_ref[OPTIONS_NUM]{
    &fecux::main::options::_source_dir,
    &fecux::main::options::_fakeroot_dir,
    &fecux::main::options::_cflags,
    &fecux::main::options::_cxxflags,
    &fecux::main::options::_jobs
  };


  /*
  
    Esse for está interando pelo array e mandando as informações
    do arquivo de configurações para cada membro da struct

  */

  for(int i{0}; i < OPTIONS_NUM; i++){
    *_opts_ref[i] = _opts_value[i];
    if(i == 1){
      _loadded.store(true);
      _cond.notify_one();
    }

    /* Liberando memória que não vai ser mais ultilizada */

    std::free(const_cast<char*>(_opts_value[i]));
  }
  
  /* Liberando o resto da memória */
  
  std::free(_opts_value);
}
