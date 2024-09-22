/*

  AUTHOR: Linuxperoxo                    
  COPYRIGHT: (c) 2024 per Linuxperoxo.
  FILE: integrity.cpp

*/

#include <chrono>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <libconfig.h++>
#include <new>
#include <string>
#include <thread>

#include "../include/fecux/integrity.hpp"
#include "../include/memory/make_obj.hpp"
#include "../include/fecux/exception.hpp"
#include "../include/fecux/config.hpp"
#include "../include/utils/files.hpp"
#include "../include/color.hpp"
#include "../include/env.hpp"

#define DIR_TO_CHECK 4
#define DELAY 300

void fecux::main::integrity::config_file(const char** _opts_names, std::exception_ptr& _except_ptr){
  
  /*
  
    O arquivo  de configuração existe?

  */

  try{
  
    if(!fecux::utils::files::is_file(CONFIG_FILE_LOCALE)){
      throw fecux::main::exception(CONFIG_FILE_NOT_FOUND);
    }

  /*
  
    Sim, estou alocando memória com malloc em C++
  
  */


    libconfig::Config* _libconfig{
      static_cast<libconfig::Config*>(std::malloc(sizeof(libconfig::Config)))
    };

    char** _opts_value{
      static_cast<char**>(std::malloc(sizeof(char*) * OPTIONS_NUM))
    };
  
    if(_libconfig == nullptr || _opts_value == nullptr){
      std::free(_libconfig);
      std::free(_opts_value);
      throw std::bad_alloc();
    }

    /*
   
      Lambda que não deveria existir mas deixa a coitada

    */

    auto clean = [&_libconfig, &_opts_value](int _index_alloc, bool _clean_index, bool _clean_array = true) -> void{
      fecux::memory::expurg<libconfig::Config>(_libconfig);
      if(_clean_index){
        for(int i = 0; i < _index_alloc; i++){
          std::free(_opts_value[i]);
        }
      }
    
      if(_clean_array){
        std::free(_opts_value);
      }
      std::free(_libconfig);
    };

  
    /* 
    
      Multithread session
    
      Multithread aqui não faz tanta diferença no desempenho 
      mas decidi usar =^)

    */

    std::mutex _mtx;
    std::condition_variable _cond;
    std::atomic<bool> _loadded(false);

  
    /*
    
      Deixando a thread rodando em segundo plano, ela sabe se virar bem dentro da função 

    */
  
    std::thread _thread2(&fecux::main::integrity::check_dir, std::ref(_mtx), std::ref(_cond), std::ref(_loadded), std::ref(_except_ptr)); 

    /* 

      Chamando o construtor do objeto 
  
    */

    fecux::memory::make<libconfig::Config>(_libconfig);
  
    /*
  
      Nesse loop for simplesmente estamos carregando as informações do arquivo e passando 
      para um buffer do tipo std::string, infelizmente o libconfig so suporta com std::string :(

      Isso está longe do método mais recomendado de fazer isso, mas a ideia desse gerenciador é 
      usar técnicas mais antigas para manipular memória

    */


    /*

      Carregando arquivo 

    */

    _libconfig->readFile(CONFIG_FILE_LOCALE);
  
  

    /* 
  
      Buffer que seŕá usado 

    */

    std::string _buffer;

    for(int i{0}; i < OPTIONS_NUM; i++){

      /*
    
        Nesse if estamos pegando a variável armazenada no arquivo e jogando pro buffer.

        Caso algo falhe ele cai dentro do if e lança um exception que será capturado dentro da função
        check_health

      */


      if(!_libconfig->lookupValue(_opts_names[i], _buffer) || _buffer.empty()){
        clean(i, true, true);
        fecux::utils::string _what;
        _what.cat_str("Options ", RED, _opts_names[i], NC, " not loadded in config file -> ", RED, CONFIG_FILE_LOCALE, NC);
        throw fecux::main::exception(_what, OPTIONS_NOT_LOADDED);
      }
     
      /* 
     
        Alocando memória para a nova string 

      */

      _opts_value[i] = static_cast<char*>(std::malloc(_buffer.length() + 1));
    
      /* 

        Pequena verificação para vê se foi alocado 

      */

      if(_opts_value[i] == nullptr){
        clean(i, true, true);
        throw std::bad_alloc();
      }

      /* 
    
        Por fim, copiamos a string da class std::string para nosso array de char* 
        que vamos mandar lá pra outra função(fecux::main::config::load_config).

        Eu poderia tmb fazer um get e set na classe config pra poder manipular isso, mas 
        otimização prematura é a raiz de todo mal :)

      */

      std::memcpy(_opts_value[i], _buffer.c_str(), _buffer.length());
      _opts_value[i][_buffer.length()] = '\0';
    }
    clean(0, false, false);
  

    /*
  
      Outro thread para outra função, essa função vai fazer a manipulação de carregar as variáveis na struct
      e avisar a _thread2 que pode seguir em frente

    */

    std::thread _thread3(&fecux::main::config::load_config, const_cast<const char**>(_opts_value), std::ref(_loadded), std::ref(_cond));
    _thread3.detach();
    _thread2.join();
  }

  catch(...){
    _except_ptr = std::current_exception();
  }
}

void fecux::main::integrity::check_dir(std::mutex& _mtx, std::condition_variable& _cond, std::atomic<bool>& _loadded, std::exception_ptr& _except_ptr){
  try{
  
    /*
  
      A thread vai ficar aqui esperando até a função fecux::main::config::load_config liberar 

    */
  
    std::unique_lock<std::mutex> _locker(_mtx);
    _cond.wait(_locker, [&_loadded]{ return _loadded.load(); });

    /*

      Array que armazena cada dir para a verificação

    */

    const char* _dirs[DIR_TO_CHECK]{
      fecux::main::config::source_dir(),
      fecux::main::config::fakeroot_dir(),
      REPO_DIR,
      WORLD_DIR
    };

    for(int i = 0; i < DIR_TO_CHECK; i++){

      /*

        Aqui simplesmente vai criar o dir caso ele não exista

      */

      if(!fecux::utils::files::is_dir(_dirs[i])){
        std::cerr << YELLOW << "-*- " << NC << "Creating directory -> " << YELLOW << _dirs[i] << NC << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(DELAY));
        fecux::utils::files::create_dirs(_dirs[i]);
      }
    }

    /*

      Aqui é so pra vê se o dir do repo foi criado agora, caso sim, lança a exception

    */

    if(fecux::utils::files::is_empty(REPO_DIR)){
      throw fecux::main::exception(REPO_DIR_IS_EMPTY);
    }
  }

  catch(...){
    _except_ptr = std::current_exception();
  }
}

void fecux::main::integrity::check_health() noexcept{
  try{
    
    /*

      Ponteiro para a exception lançada por alguma das threads, precisamos disso quando uma função 
      que é executada por uma thread secundária pode lançar uma exception, e como cada thread tem sua
      statck, temos que compartilhar esse recurso com a thread principal jogando na heap

    */

    std::exception_ptr _except_ptr = nullptr;

    /*
    
      Tudo começa nessa _thread1. Se alguma exception for lançada ela vai ser capturada aqui
    
    */

    std::thread _thread1(&fecux::main::integrity::config_file, fecux::main::config::opts_names(), std::ref(_except_ptr));
    _thread1.join();
    
    if(_except_ptr != nullptr){
      std::rethrow_exception(_except_ptr);
    }  
  }

  catch(fecux::main::exception& _runtime_error){
    std::cerr << RED << "-*- ERROR: " << NC << _runtime_error.what() << '\n';
    std::cerr << RED << "-*- ERROR_CODE " << NC << _runtime_error.error_code() << '\n';
    exit(_runtime_error.error_code());
  }

  catch(libconfig::ParseException& _paex){
    std::cerr << RED << "-*- PARSE_ERROR: " << NC << _paex.what() << " file -> " << RED << _paex.getFile() << NC << " line -> " << _paex.getLine() << '\n';
    exit(EXIT_FAILURE);
  }

  catch(std::bad_alloc& _bad_alloc){
    std::cerr << RED << "-*- INTERNAL_CRITICAL_ERROR: " << NC << _bad_alloc.what() << '\n';
    exit(EXIT_FAILURE);
  }
}

