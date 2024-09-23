/*

  COPYRIGHT: (c) 2024 per Linuxperoxo.
  AUTHOR: Linuxperoxo
  FILE: string.cpp

*/

/*
 
  A ideia de fazer uma lib personalizada de string veio da curiosidade em entender
  como funciona alguns conceitos, como esse projeto é um projeto pessoal, não vejo
  motivos em não tentar implementar minhas próprias libs nele, ela não tem o intuito 
  de substituir o std::string, mas funciona muito bem no propósito deste projeto

*/



#include "../include/utils/string.hpp"




/*

  Construtor de inicialização simples, ou seja, declarando a "variável"
  sem passar um valor pra ela

  EX: fecux::utils::string _nome;

*/



fecux::utils::string::string() noexcept
  : _string(nullptr),
    _string_len(0){}



/*

  Construtor que recebe uma string c_str

  EX: fecux::utils::string _nome = "Linuxperoxo"; || fecux::utils::string _nome("Linuxperoxo");

  OBJ: Caso você defina explicit no construtor o operator '=' não é permitido no construtor, apenas
  será permitido usar o operator '=' após a instância do objeto, isso se sua classe tiver uma sobrecarga
  desse operator

*/



fecux::utils::string::string(const char* _src)
  : _string(nullptr),
    _string_len(0){
    cpy_str(_src, std::strlen(_src));
  }



/*
 
  Construtor de cópia, é muito importante para strings ter operações de cópia,
  aqui ele copia o conteúdo de outra classe do tipo fecux::utils::string

  EX: #include <iostream>

      fecux::utils::string _nome1 = "Linuxperoxo";
      fecux::utils::string _nome2 = _nome1;

      std::cout << _nome1 << '|' << _nome2 << '\n';

      OUT: Linuxperoxo|Linuxperoxo
 
*/



fecux::utils::string::string(const string& _src)
  : _string(nullptr),
    _string_len(0){
    cpy_str(_src._string, _src._string_len); 
  }



/*
 
  Parecido com o construtor acima, mas com pequenos detelhes. Esse é um construtor
  de movimentação, ou seja, se você usar a lib <utility> e ṕassar uma instância da classe
  fecux::utils::string por movimento(std::move()) ele vai mover os membros de uma classe 
  para outra

  EX: #include <utility> // Para std::move();
      #include <iostream> // Para std::cout;
      
      fecux::utils::string _nome1 = "Linuxperoxo";
      fecux::utils::string _nome2 = std::move(_nome1)

      std::cout << _nome1 << '|' << _nome2 << '\n';

  OUT: |Linuxperoxo

  Isso acontece exclusivamente pq a manipulação de string é baseada em ponteiros(char*), quando usamos
  o std::move(), falamos explicitamente que queremos mover o objeto e não copiar, diferente do construtor de cópia
  que copia o conteúdo do ponteiro, o construtor de movimento vai passar o endereço apontado para o inicio da string,
  e não o seu conteúdo

  EX: int* _n1 = new int(); // Digamos que _n1 aponta para o endereço 0xFFFFFFFF
      *_n1 = 10;

      int* _n2 = _n1; // Não estamos pegando o conteúdo de _n1 mas sim o local apontando por ele, ou seja, o endereço 0xFFFFFFFF
      
      *_n2 = 20; // Aqui tanto o conteúdo de _n1 
       2 = 20; // quando o de _n2 são modificados, 
               //pois ambos apontam para o mesmo lugar na memória  

  É isso que acontece quando passamos std::move(), o endereço apontado por _nome1 passa para _nome2 mantendo assim seu conteúdo original
  e não uma cópia dele, e como pode ser problemático ter 2 ponteiros apontando para o mesmo lugar na chamada do destrutor que usa o 
  std::free()(nesse caso que usamos malloc), deixamos o _nome1 em um estado seguro, simplesmente fazendo ele ser um nullptr, ou seja, apontando
  para lugar algum, o std::free() consegue lidar com situações que o ponteiro é nullptr

*/



fecux::utils::string::string(string&& _class_to_move) noexcept
  : _string(_class_to_move._string),
    _string_len(_class_to_move._string_len){
    _class_to_move._string = nullptr;
    _class_to_move._string_len = 0;
  }



/*

  Abaixo os operadores '=' fazem literalmente a mesma coisa que cada construtor faz acima, tirando o
  construtor de incialização simples, já que não podemos fazer:

  fecux::utils::string _nome1;
  _nome =;

  O certo é:

  fecux::utils::string _nome1;
  _nome = "Linuxperoxo" // Todos os operadores '=' são chamados nessa situação
  _nome = std::move(_nome2); // Movimentação
  _nome1 = _nome2; // Cópia


*/



fecux::utils::string& fecux::utils::string::operator=(const char* _src){
  cpy_str(_src, std::strlen(_src));
  return *this;
}

fecux::utils::string& fecux::utils::string::operator=(const string& _src){
  if(this != &_src){
    cpy_str(_src._string, _src._string_len);
  }
  return *this;
}

fecux::utils::string& fecux::utils::string::operator=(string&& _class_to_move) noexcept{
  if(this != &_class_to_move){
    _string = _class_to_move._string;
    _string_len = _class_to_move._string_len;

    _class_to_move._string = nullptr;
    _class_to_move._string_len = 0;
  }
  return *this;
}



/*
 
  Função main dessa lib. Ela aloca um buffer para a string passada,
  fazemos a cópia do conteúdo de _src_str para o _buffer,
  logo depois mandamos o local apontado por _buffer para _string(Membro da classe)
 
*/



void fecux::utils::string::cpy_str(const char* _src, const std::size_t _src_len){ 
  char* _buffer{
    static_cast<char*>(std::malloc( _src_len + 1))
  };

  if(_buffer == nullptr){
    throw std::bad_alloc();
  }
  std::memcpy(_buffer, _src, _src_len);
  _buffer[_src_len] = '\0';
  
  std::free(_string);

  _string = _buffer;
  _string_len = _src_len;
}

