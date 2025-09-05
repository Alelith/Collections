CXX = g++
CXXFLAGS = -g -Wall -Wextra -pedantic -I ../include

all: test_vector test_linked_list test_double_linked_list

test_vector: test_vector.cpp $(SRC)
	$(CXX) $(CXXFLAGS) test_vector.cpp -o test_vector

test_linked_list: test_linked_list.cpp $(SRC)
	$(CXX) $(CXXFLAGS) test_linked_list.cpp -o test_linked_list

test_double_linked_list: test_double_linked_list.cpp
	$(CXX) $(CXXFLAGS) test_double_linked_list.cpp -o test_double_linked_list

clean:
	rm -f test_vector test_linked_list test_double_linked_list