BUILD_DIR=$(abspath build)
SRC_DIR=$(abspath src)

CXX=g++
CXXFLAGS=-Wall -Wextra -std=c++20 -pedantic -g -I$(SRC_DIR) -O2 # -Werror
CXXLIBS=

SRC=$(wildcard $(SRC_DIR)/*.cpp)
OBJ=$(patsubst %.cpp, $(BUILD_DIR)/%.o, $(SRC))

NAME=main

.PHONY: all main clean always

all: main

always:
	@mkdir -p $(BUILD_DIR)

main: $(BUILD_DIR)/$(NAME).out

$(BUILD_DIR)/$(NAME).out: $(OBJ)
	@$(CXX) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp always
	@$(CXX) -c $< $(CXXFLAGS) $(CXXLIBS) -o $@

run: main
	@$(BUILD_DIR)/$(NAME).out

clean:
	@rm -f $(BUILD_DIR)/$(NAME).out $(OBJ)