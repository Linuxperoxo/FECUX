# Diretórios
SRC_DIR := src
INCLUDE_DIR := include
BIN_DIR := bin
MISC_DIR := misc

# Compilador e flags
CXX := g++
CXXFLAGS := -std=c++20 -v -I$(INCLUDE_DIR) -Wall -Wextra -Wpedantic -O2
LDFLAGS := -lconfig++

# Arquivos fonte e objetos
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
EXECUTABLE := $(BIN_DIR)/caro

# Padrão de regras
all: $(EXECUTABLE)

# Regra para criar o diretório bin se não existir
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Regra para compilar os arquivos .cpp em arquivos .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regra para linkar os arquivos .o em um executável
$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(BIN_DIR)/*.o $(EXECUTABLE)

# Regra para remover o diretório bin
distclean: clean
	rm -rf $(BIN_DIR)

# Inclui a regra padrão
.PHONY: all clean distclean
