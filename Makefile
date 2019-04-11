# based off: https://github.com/wodeni/Animate-plus-plus/blob/master/Makefile

PACKAGE = simplegl 
VERSION = 0.1.0

TARGET_EXEC  ?= libSimplegl.a
BUILD_DIR    ?= ./build
TEST_EXEC    ?= $(BUILD_DIR)/test
SRC_DIRS     ?= ./src ./include
TEST_SRC_DIR ?= test/src
CXX ?= g++

dist_files := $(shell find $(SRC_DIRS) -name *.hpp) $(BUILD_DIR)/$(TARGET_EXEC)

SRCS      := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS      := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS      := $(OBJS:.o=.d)

#INC_DIRS  := $(shell find $(SRC_DIRS) -type d) /usr/local/Cellar/boost/1.66.0
#INC_FLAGS := $(addprefix -I,$(INC_DIRS)) -I/usr/local/Cellar/boost/1.66.0/include

INC_DIRS  := $(shell find $(SRC_DIRS) -type d) /usr/local/Cellar/glfw/3.2.1
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) -I/usr/local/Cellar/glfw/3.2.1/include

#LDFLAGS   := $(INC_FLAGS) -L/usr/local/Cellar/boost/1.66.0/lib -lboost_regex-mt
#CPPFLAGS  ?= $(INC_FLAGS) -MMD -MP -std=c++1z

LDFLAGS   := $(INC_FLAGS) -L/usr/local/Cellar/glfw/3.2.1/lib -lglfw
CPPFLAGS  ?= $(INC_FLAGS) -MP -MMD -std=c++17 -O2 -Wall -Werror

TEST_INC_FLAGS  := -I./src -I$(TEST_SRC_DIR)
TEST_LD_FLAGS   := $(TEST_INC_FLAGS) $(LDFLAGS) -L./build -lSimplegl
TEST_CPPFLAGS   ?= $(TEST_INC_FLAGS) -MP -MMD -std=c++17 -O2 -Wall -Werror

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	ar crv $(BUILD_DIR)/$(TARGET_EXEC) $(OBJS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean all test release

release: $(BUILD_DIR)/$(TARGET_EXEC)
	$(MKDIR_P) $(PACKAGE)-$(VERSION)
	cp -p $(dist_files) $(PACKAGE)-$(VERSION)
	tar -czvf $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE)-$(VERSION)
	rm -rf $(PACKAGE)-$(VERSION)

all: clean $(BUILD_DIR)/$(TARGET_EXEC)
clean:
	$(RM) -r $(BUILD_DIR) release
	rm -rf $(PACKAGE)-$(VERSION)
	rm -rf $(PACKAGE)-$(VERSION).tar.gz

-include $(DEPS)

test: $(TEST_EXEC)

$(TEST_EXEC): $(BUILD_DIR)/test.o
	$(CXX) $< -o $@ $(TEST_LD_FLAGS)

$(BUILD_DIR)/test.o: $(TEST_SRC_DIR)/test.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $(BUILD_DIR)/test.o

MKDIR_P ?= mkdir -p
