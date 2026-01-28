CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
TEST_DIR = test
BUILD_DIR = build
SRC_DIR = src
LIB_DIR = $(BUILD_DIR)/lib
LIB_NAME = libcollections.a

# Colors
GREEN = \033[0;32m
BLUE = \033[0;34m
CYAN = \033[0;36m
YELLOW = \033[1;33m
RED = \033[0;31m
BOLD = \033[1m
RESET = \033[0m

# Test files explicitly listed
TEST_SOURCES = $(TEST_DIR)/test_vector.cpp \
			   $(TEST_DIR)/test_linked_list.cpp \
			   $(TEST_DIR)/test_double_linked_list.cpp \
			   $(TEST_DIR)/test_stack.cpp \
			   $(TEST_DIR)/test_queue.cpp \
			   $(TEST_DIR)/test_deque.cpp \
			   $(TEST_DIR)/test_check.cpp \
			   $(TEST_DIR)/test_conversion.cpp

# Source files for standard functions
SRC_SOURCES = $(SRC_DIR)/check.cpp $(SRC_DIR)/conversion.cpp
SRC_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/obj/%.o,$(SRC_SOURCES))
LIBRARY = $(LIB_DIR)/$(LIB_NAME)

TEST_EXECUTABLES = $(BUILD_DIR)/test_vector \
				   $(BUILD_DIR)/test_linked_list \
				   $(BUILD_DIR)/test_double_linked_list \
				   $(BUILD_DIR)/test_stack \
				   $(BUILD_DIR)/test_queue \
				   $(BUILD_DIR)/test_deque \
				   $(BUILD_DIR)/test_check \
				   $(BUILD_DIR)/test_conversion

.PHONY: all clean test library

all: $(BUILD_DIR) $(LIBRARY) $(TEST_EXECUTABLES)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/obj
	@mkdir -p $(LIB_DIR)

# Compile object files
$(BUILD_DIR)/obj/%.o: $(SRC_DIR)/%.cpp
	@echo -e "$(CYAN)Compiling $<...$(RESET)"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Create static library
$(LIBRARY): $(SRC_OBJECTS)
	@echo -e "$(YELLOW)Creating static library $(LIB_NAME)...$(RESET)"
	@ar rcs $@ $^
	@echo -e "$(GREEN)✓ Library created successfully$(RESET)"

library: $(BUILD_DIR) $(LIBRARY)

$(BUILD_DIR)/test_vector: $(TEST_DIR)/test_vector.cpp
	@$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/test_linked_list: $(TEST_DIR)/test_linked_list.cpp
	@$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/test_double_linked_list: $(TEST_DIR)/test_double_linked_list.cpp
	@$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/test_stack: $(TEST_DIR)/test_stack.cpp
	@$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/test_queue: $(TEST_DIR)/test_queue.cpp
	@$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/test_deque: $(TEST_DIR)/test_deque.cpp
	@$(CXX) $(CXXFLAGS) $< -o $@

$(BUILD_DIR)/test_check: $(TEST_DIR)/test_check.cpp $(LIBRARY)
	@$(CXX) $(CXXFLAGS) $< -L$(LIB_DIR) -lcollections -o $@

$(BUILD_DIR)/test_conversion: $(TEST_DIR)/test_conversion.cpp $(LIBRARY)
	@$(CXX) $(CXXFLAGS) $< -L$(LIB_DIR) -lcollections -o $@

test: all
	@echo -e "$(CYAN)================================$(RESET)"
	@echo -e "$(BOLD)$(BLUE)Running all tests...$(RESET)"
	@echo -e "$(CYAN)================================$(RESET)"
	@echo ""
	@./$(BUILD_DIR)/test_check || exit 1
	@echo ""
	@./$(BUILD_DIR)/test_conversion || exit 1
	@echo ""
	@./$(BUILD_DIR)/test_deque || exit 1
	@echo ""
	@./$(BUILD_DIR)/test_double_linked_list || exit 1
	@echo ""
	@./$(BUILD_DIR)/test_linked_list || exit 1
	@echo ""
	@./$(BUILD_DIR)/test_queue || exit 1
	@echo ""
	@./$(BUILD_DIR)/test_stack || exit 1
	@echo ""
	@./$(BUILD_DIR)/test_vector || exit 1
	@echo ""
	@echo -e "$(GREEN)================================$(RESET)"
	@echo -e "$(BOLD)$(GREEN)✓✓✓ ALL TESTS PASSED ✓✓✓$(RESET)"
	@echo -e "$(GREEN)================================$(RESET)"

clean:
	@rm -rf $(BUILD_DIR)
