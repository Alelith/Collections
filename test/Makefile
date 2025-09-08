# Makefile

# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -I../include
BIN = ../bin

# Lista de tests
TESTS = test_vector test_linked_list test_double_linked_list test_stack test_queue test_deque

# Targets
all: $(BIN) $(addprefix $(BIN)/, $(TESTS))

$(BIN):
	@mkdir -p $(BIN)

$(BIN)/test_vector: test_vector.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) test_vector.cpp -o $@

$(BIN)/test_linked_list: test_linked_list.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) test_linked_list.cpp -o $@

$(BIN)/test_double_linked_list: test_double_linked_list.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) test_double_linked_list.cpp -o $@

$(BIN)/test_stack: test_stack.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) test_stack.cpp -o $@

$(BIN)/test_queue: test_queue.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) test_queue.cpp -o $@

$(BIN)/test_deque: test_deque.cpp | $(BIN)
	$(CXX) $(CXXFLAGS) test_deque.cpp -o $@

clean:
	rm -rf $(BIN)

.PHONY: all clean