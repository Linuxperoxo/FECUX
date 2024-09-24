/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: globals.hpp

*/

#ifndef __GLOBALS_HPP__
#define __GLOBALS_HPP__

/*

  Esse arquivo guarda variáveis gerais para o funcionamento
  do fecux. Você pode alterar se quiser, mas o funcionamento não
  é garantido, teste e veja o resultado você mesmo =)

  OBS: Caso o projeto seja compilado e depois haja uma modificação
  nesse arquivo, vocẽ terá que recompilar o projeto

*/

/*

CONFIG_FILE_LOCALE:

  * Variável para o arquivo de configuração do fecux

  * Ela pode ser modificada sem preocupações

*/



constexpr const char* CONFIG_FILE_LOCALE{"/etc/fecux.conf"};



/*

  REPO_DIR:
    
    * Variável para o diretório do repositório do gerenciador
    
    * Não recomendo a modificação, pode ser problemático 
    já que não houve nenhum teste

*/



constexpr const char* REPO_DIR{"/var/db/fecux/repo/"};



/*

  WORLD_DIR:
    
    * Variável para o diretório dos pacotes instalados
    
    * Não existe uma necessidade real em mudar esse local, 
    esse diretório vai armazenar apenas simples arquivos de texto

    OBS: DELETAR ESSE DIRETÓRIO USANDO RM -RF FARÁ COM QUE TODOS OS PACOTES
    INSTALADOS FIQUEM OBSOLETOS NO SISTEMA

*/



constexpr const char* WORLD_DIR{"/var/db/fecux/world/"};

#endif
