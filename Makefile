SHELL := /bin/sh

SRC_DIR := src
OBJ_DIR := obj

EXE := hello
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

CXX				:= clang++
CPPFLAGS	:= -Iinclude -MMD -MP
CFLAGS		:= -std=c++17 -g -O0 -Wall
LDFLAGS		:=
LDLIBS		:= -larmadillo

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

${OBJ_DIR}:
	mkdir -p $@

clean:
	@$(RM) -rv $(OBJ_DIR)

-include $(OBJ:.o=.d)

