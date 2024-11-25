TARGET_EXE := percolate
TEST_EXE   := ptest

SRC_DIR   := ./src
INC_DIRS  := ./include
BUILD_DIR := ./build
TEST_DIR  := ./tests

# find all the C++ source files
SRCS      := $(wildcard $(SRC_DIR)/*.cpp)
SRCS_TEST := $(wildcard $(TEST_DIR)/*.cpp)

# replace SRC_DIR with BUILD_DIR and .c with .o for every src file
OBJS      := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJS_TEST := $(filter-out $(BUILD_DIR)/main.o, $(OBJS)) \
             $(SRCS_TEST:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)

CC := g++
CPPFLAGS := $(addprefix -I,$(INC_DIRS))
CFLAGS   := -std=c++23 -Wall -g -O3
LDFLAGS  :=
LDLIBS   := -lm

CATCH2_INC_DIR := "C:/Program Files (x86)/Catch2/include"
CATCH2_LIB_DIR := "C:/Program Files (x86)/Catch2/lib"

CPPFLAGS_TEST := $(CPPFLAGS)
#CPPFLAGS_TEST := $(CPPFLAGS) -I$(CATCH2_INC_DIR)
CFLAGS_TEST   := $(CFLAGS)
LDFLAGS_TEST  := $(LDFLAGS)
LDLIBS_TEST   := $(LDLIBS)
#LDFLAGS_TEST  := $(LDFLAGS) -L$(CATCH2_LIB_DIR)
#LDLIBS_TEST   := $(LDLIBS) -lCatch2Main -lCatch2

.PHONY: all test clean

all: $(TARGET_EXE)

$(TARGET_EXE): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

test: $(TEST_EXE)

$(TEST_EXE): $(OBJS_TEST)
	$(CC) $(LDFLAGS_TEST) $^ $(LDLIBS_TEST) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CC) $(CPPFLAGS_TEST) $(CFLAGS_TEST) -c $< -o $@

$(BUILD_DIR):
	mkdir $@

clean:
	rm -f $(OBJS) $(OBJS_TEST) $(TARGET_EXE) $(TEST_EXE)
	rmdir $(BUILD_DIR)
