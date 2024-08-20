# Dirs
SRC_DIR := src
INCLUDE_DIR := include
BIN_DIR := bin
MISC_DIR := misc

# Flags
CXX := g++
CXXFLAGS := -std=c++20 -v -I$(INCLUDE_DIR) -Wall -Wextra -Wpedantic -O2
LDFLAGS := -lconfig++

# Arquivos fonte e objetos
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
EXECUTABLE := $(BIN_DIR)/caro

all: $(EXECUTABLE)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# gen .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

clean:
	rm -f $(BIN_DIR)/*.o $(EXECUTABLE)

distclean: clean
	rm -rf $(BIN_DIR)

.PHONY: all clean distclean
