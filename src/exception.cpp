/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: exception.cpp

*/

#include <utility>

#include "../include/fecux/exception.hpp"
#include "../include/color.hpp"
#include "../include/env.hpp"

/* 
 
  Esta classe de exceção personalizada foi criada por dois motivos principais

  Primeiro, busquei estabelecer uma gestão de erros exclusiva para este programa, 
  já que muitas implementações não tem um tratamento adequado. É frustrante ver 
  como alguns desenvolvedores não se preocupam em lidar com os erros potenciais, 
  o que pode comprometer a robustez do software. Portanto, meu objetivo aqui é 
  manipular e documentar adequadamente todos os possíveis erros que possam surgir
 
  O segundo motivo é a busca por controle total. Acredito que ter um controle 
  rigoroso sobre todos os aspectos do código é fundamental, e a gestão de erros 
  não deve ser uma exceção. Assim, pretendo garantir que cada erro seja tratado 
  de maneira clara e eficaz
 
*/


/*

  Essa primeira classe é o construtor genérico, ou seja, apenas colocando o código
  de error ele já faz a manipulação do erro se ele existir

*/


fecux::main::exception::exception(const uint16_t _error_code) noexcept
  : _what(),
    _error_code(_error_code){
    switch(_error_code){
      case CONFIG_FILE_NOT_FOUND:
          _what.cat_str("Config file not found in -> ", RED, CONFIG_FILE_LOCALE, NC);
        break;
        
      case REPO_DIR_IS_EMPTY:
        _what.cat_str("Repo directory is empty, use -> ", RED, "fecux -s ", NC, " to sync local repo");
        break;

      case PKG_NOT_FOUND:
        _what.cat_str("Package not found in local repo");
        break;
    }  
  }

/*
 
  Esse aqui é o construtor personalizado, você pode documentar o error e colocar informações
  sobre ele, e possivelmente colocar um código de erro para esse problema

*/

fecux::main::exception::exception(fecux::utils::string& _what, const uint16_t _error_code) noexcept
  : _what(_what),
    _error_code(_error_code){}

/*
 
  Esse aqui é um construtor de cópia, ele simplesmente pega uma instancia dessa 
  class e copia a mesma, util em casos de fazer uma cadeia de try catch, ou seja, 
  lançar outra exception dentro de um catch

*/

fecux::main::exception::exception(fecux::main::exception&& _exception_class) noexcept
  : _what(std::move(_exception_class._what)),
    _error_code(_exception_class._error_code){
    _exception_class._error_code = 0;
  }

/*
 
  Aqui são os get 

*/

const char* fecux::main::exception::what() noexcept { return *_what; }
uint16_t fecux::main::exception::error_code() const noexcept { return _error_code; }
