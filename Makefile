CXX = g++ -std=c++17 -v -Wall -Wextra
LDFLAGS = -lconfig++
CXXFLAGS := -march=native -O3 -pipe

SRC_DIR = src
OBJ_DIR = build/obj
BIN_DIR = build/bin

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

BIN = $(BIN_DIR)/fecux

all: $(BIN)

$(BIN): $(OBJECTS)
	@mkdir -p $(BIN_DIR) $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: all clean

