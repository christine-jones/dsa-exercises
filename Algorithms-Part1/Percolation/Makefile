TARGET_EXE := percolate
TEST_EXE   := percolate-test

SRC_DIR   := ./src
INC_DIRS  := ./include
BUILD_DIR := ./build
TEST_DIR  := ./tests

SRCS      := $(wildcard $(SRC_DIR)/*.cpp)
SRCS_TEST := $(wildcard $(TEST_DIR)/*.cpp)

OBJS      := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
OBJS_TEST := $(filter-out $(BUILD_DIR)/main.o, $(OBJS)) \
             $(SRCS_TEST:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/%.o)

DEPS	  := $(OBJS:.o=.d)
DEPS_TEST := $(OBJS_TEST:.o=.d)

INC_FLAGS := $(addprefix -I, $(INC_DIRS))

CC := g++
CPPFLAGS := $(INC_FLAGS) -MMD -MP
CFLAGS   := -std=c++23 -Wall -g -O3
LDFLAGS  :=
LDLIBS   := -lm

# no additional flags/libs for tests at this time
CPPFLAGS_TEST := $(CPPFLAGS)
CFLAGS_TEST   := $(CFLAGS)
LDFLAGS_TEST  := $(LDFLAGS)
LDLIBS_TEST   := $(LDLIBS)

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
	rm -f $(OBJS) $(OBJS_TEST) $(DEPS) $(DEPS_TEST) $(TARGET_EXE) $(TEST_EXE)
	rm -rf $(BUILD_DIR)

-include $(DEPS)
-include $(DEPS_TEST)
