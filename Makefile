# based off
# https://github.com/wodeni/Animate-plus-plus/blob/master/Makefile
# and
# https://github.com/Contentmaudlin/kernel_generators/blob/master/test/Makefile

PACKAGE = simplegl 
VERSION = 0.1.0

TARGET_EXEC  ?= libSimplegl.a
BUILD_DIR    ?= ./build
SRC_DIRS     ?= ./src ./include
TEST_SRC_DIR ?= ./test/src
CXX 		 ?= g++

distr     := $(shell find $(SRC_DIRS) -name *.hpp) $(BUILD_DIR)/$(TARGET_EXEC)

SRCS      := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS      := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS      := $(OBJS:.o=.d)

INC_DIRS  := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) -I/usr/local/Cellar/glfw/3.2.1/include

CMPFLAGS  := -MP -MMD -std=c++17 -O2 -Wall -Werror 
LDFLAGS   := -L/usr/local/Cellar/glfw/3.2.1/lib -lglfw
CPPFLAGS  ?= $(INC_FLAGS) $(CMPFLAGS)

# For every <test>.cpp file in the test/src/ directory, add it to TESTS.
TESTS = test1 compare1 test2 compare2 test_invalid_param test_objs \
		spring_test tetrahedron composite_test hellosimplegl #compare_spring_test
TEST_EXECS = $(foreach t, $(TESTS), $(BUILD_DIR)/$(t))

TEST_INC_FLAGS  := $(INC_FLAGS) -I$(TEST_SRC_DIR)
TEST_LDFLAGS    := $(TEST_INC_FLAGS) $(LDFLAGS) -L$(BUILD_DIR) -lSimplegl
TEST_CPPFLAGS   ?= $(TEST_INC_FLAGS) $(CMPFLAGS)

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	ar crv $(BUILD_DIR)/$(TARGET_EXEC) $(OBJS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) -c $< -o $@

.PHONY: clean all $(TESTS) tests release 

release: $(BUILD_DIR)/$(TARGET_EXEC)
	$(MKDIR_P) $(PACKAGE)-$(VERSION)
	cp -p $(distr) $(PACKAGE)-$(VERSION)
	tar -czvf $(PACKAGE)-$(VERSION).tar.gz $(PACKAGE)-$(VERSION)
	rm -rf $(PACKAGE)-$(VERSION)

all: clean $(BUILD_DIR)/$(TARGET_EXEC)

clean:
	$(RM) -r $(BUILD_DIR) release
	rm -rf $(PACKAGE)-$(VERSION)
	rm -rf $(PACKAGE)-$(VERSION).tar.gz

-include $(DEPS)

tests: $(TEST_EXECS)

$(TESTS): %: $(BUILD_DIR)/%

$(TEST_EXECS): $(BUILD_DIR)/%: $(BUILD_DIR)/%.o
	$(CXX) $< -o $@ $(TEST_LDFLAGS)

$(BUILD_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp
	$(CXX) $(TEST_CPPFLAGS) -c $< -o $@

MKDIR_P ?= mkdir -p
