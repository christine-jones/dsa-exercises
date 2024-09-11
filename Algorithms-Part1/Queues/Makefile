TARGET_EXE := queues

SRC_DIR   := ./src
INC_DIRS  := ./include
BUILD_DIR := ./build

# find all the C++ source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# replaces SRC_DIR with BUILD_DIR and .c with .o for every src file
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)


CC := g++

# preprocessor flags
CPPFLAGS := $(addprefix -I,$(INC_DIRS))

# compiler flags
CFLAGS   := -std=c++23 -Wall -g -O3

# linker flags
LDFLAGS  :=

# libraries to link against
LDLIBS   := -lm


.PHONY: all clean

all: $(TARGET_EXE)

$(TARGET_EXE): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir $@

clean:
	rm -f $(OBJS) $(TARGET_EXE)
	rmdir $(BUILD_DIR)
