# Directly adopted from Chnossos's answer at:
# https://stackoverflow.com/questions/30573481/how-to-write-a-makefile-with-separate-source-and-header-directories

SRC_DIR := src
OBJ_DIR := build
BIN_DIR := bin

EXE := ${BIN_DIR}/tests
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# CXX				:= g++-11
# CPPFLAGS	:= -Iinclude -I/usr/local/include -MMD -MP
# LDLIBS		:= -L/usr/local/lib -larmadillo

CXX				:= clang++
CPPFLAGS	:= -Iinclude -MMD -MP
CFLAGS		:= -std=c++17 -g -Wall -O3
LDFLAGS		:=
LDLIBS		:= -larmadillo

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)

