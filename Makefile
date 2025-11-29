CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
TEST_DIR = test
BUILD_DIR = build

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
               $(TEST_DIR)/test_deque.cpp

TEST_EXECUTABLES = $(BUILD_DIR)/test_vector \
                   $(BUILD_DIR)/test_linked_list \
                   $(BUILD_DIR)/test_double_linked_list \
                   $(BUILD_DIR)/test_stack \
                   $(BUILD_DIR)/test_queue \
                   $(BUILD_DIR)/test_deque

.PHONY: all clean test

all: $(BUILD_DIR) $(TEST_EXECUTABLES)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

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

test: all
	@echo -e "$(CYAN)================================$(RESET)"
	@echo -e "$(BOLD)$(BLUE)Running all tests...$(RESET)"
	@echo -e "$(CYAN)================================$(RESET)"
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
