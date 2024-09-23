/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: exception.cpp

*/

#include <utility>

#include "../include/exception/exception.hpp"
#include "../include/globals.hpp"
#include "../include/color.hpp"



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

  Essa primeira classe é o construtor genérico, ou seja, apenas colocando o número
  do error ele já faz a configuração da class, isso se o erro existir

*/



fecux::exception::exception(const uint8_t _error_code) noexcept
  : _what(),
    _error_code(_error_code){
    switch(_error_code){
      case CONFIG_FILE_NOT_FOUND:
        _what.cat_str("Config file -> ", RED, CONFIG_FILE_LOCALE, NC, " not found!!! >:(");
        break;
      case REPO_DIR_IS_EMPTY:
       _what.cat_str("Repo directory is empty, use -> ", RED, "fecux -s ", NC, " to sync local repo"); 
        break;
      case PACKAGE_NOT_FOUND:
        _what.cat_str("Package not found in local repo");
        break;
  }
}



/*
 
  Esse aqui é o construtor personalizado, você pode documentar o error e colocar informações
  sobre ele, e possivelmente colocar um código de erro para esse problema

*/



fecux::exception::exception(const exception& _other_exception) noexcept
  : _what(_other_exception._what),
    _error_code(_other_exception._error_code){}



/*
 
  Esse aqui é um construtor de cópia, ele simplesmente pega uma instancia dessa 
  class e copia a mesma, util em casos de fazer uma cadeia de try catch, ou seja, 
  lançar a mesma exception dentro de um catch

*/



fecux::exception::exception(exception&& _other_exception) noexcept
  : _what(std::move(_other_exception._what)),
    _error_code(_other_exception._error_code){
    _other_exception._error_code = NO_EXCEPTION;
    _other_exception._what = "non-exception";
  }
