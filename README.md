# 🚀 Collections Library

![Status](https://img.shields.io/badge/status-In%20development-blue)
![Language](https://img.shields.io/badge/language-C%2B%2B17-orange)
![Build System](https://img.shields.io/badge/build-Make-yellow)
![License](https://img.shields.io/badge/license-MIT-green)
![Last update](https://img.shields.io/github/last-commit/Alelith/Collections)

---

## 🧠 Description

A comprehensive C++ template library providing efficient implementations of fundamental data structures and utility functions. This library offers STL-compatible containers including vectors, linked lists, stacks, queues, and deques, along with character validation and type conversion utilities designed for modern C++ applications.

---

## 🧩 Table of Contents

- [Description](#-description)
- [Features](#-features)
- [Technologies Used](#-technologies-used)
- [Architecture](#-architecture)
- [Project Structure](#-project-structure)
- [Installation](#-installation)
- [Execution](#-execution)
- [Usage Examples](#-usage-examples)
- [Tests](#-tests)
- [Documentation](#-documentation)
- [Learnings & Future Improvements](#-learnings--future-improvements)
- [Contributing](#-contributing)
- [Credits](#-credits)
- [License](#-license)
- [Author](#-author)

---

## 🌟 Features

-   [x] Dynamic vector with automatic memory management
-   [x] Single and double linked list implementations
-   [x] Stack (LIFO) and Queue (FIFO) containers
-   [x] Deque with efficient front and back operations
-   [x] Character validation utilities (alphabetic, numeric, whitespace detection)
-   [x] Type conversion functions (numeric to string, string to numeric)
-   [x] STL-compatible iterators for all containers
-   [x] Exception-safe operations with RAII principles
-   [x] Move semantics support for optimal performance
-   [x] Comprehensive unit test suite
-   [x] Complete API documentation with Doxygen
-   [ ] Binary tree implementation (in progress)

---

## ⚙️ Technologies Used

**Languages:** C++17  
**Build System:** GNU Make  
**Compiler:** GCC 15.2.1 (supports C++17 standard)  
**Documentation:** Doxygen 1.9.1  
**Testing:** Custom assertion-based test framework  
**Tools:** Git, Linux, Doxygen

---

## 🏗️ Architecture

This library follows a modular architecture organized into three main modules:

-   **Architecture Pattern:** Template-based generic programming with header-only implementations
-   **Memory Management:** RAII principles with proper copy/move semantics
-   **Module Organization:** Linear containers, tree structures, and utility functions

``` mermaid
flowchart TD
    A[Collections Library] --> B[Linear Containers]
    A --> C[Tree Structures]
    A --> D[Utility Functions]
    B --> E[Vector]
    B --> F[LinkedList]
    B --> G[DoubleLinkedList]
    B --> H[Stack]
    B --> I[Queue]
    B --> J[Deque]
    C --> K[BinaryTree]
    D --> L[Character Validation]
    D --> M[Type Conversion]
```

---

## 📂 Project Structure

```
/Collections
 ├── include/
 │   ├── linear/
 │   │   ├── vector.hpp
 │   │   ├── linked_list.hpp
 │   │   ├── double_linked_list.hpp
 │   │   ├── stack.hpp
 │   │   ├── queue.hpp
 │   │   ├── deque.hpp
 │   │   └── src/ (template implementations .tpp)
 │   ├── tree/
 │   │   ├── binary_tree.hpp
 │   │   └── binary_tree.tpp
 │   ├── standard_functions/
 │   │   ├── check.hpp (character validation)
 │   │   └── conversion.hpp (type conversion)
 │   └── super_lib.hpp (main include file)
 ├── src/
 │   ├── check.cpp
 │   └── conversion.cpp
 ├── test/
 │   ├── test_vector.cpp
 │   ├── test_linked_list.cpp
 │   ├── test_double_linked_list.cpp
 │   ├── test_stack.cpp
 │   ├── test_queue.cpp
 │   ├── test_deque.cpp
 │   ├── test_check.cpp
 │   ├── test_conversion.cpp
 │   └── test_colors.hpp
 ├── html/ (generated Doxygen documentation)
 ├── Doxyfile
 ├── Makefile
 └── README.md
```

---

## 📦 Installation

### Prerequisites

Before you begin, ensure you have the following installed:

-   **GCC** version 7.0 or higher (with C++17 support)
-   **GNU Make** version 3.81 or higher
-   **Doxygen** version 1.9.1 or higher (optional, for documentation generation)
-   **Git**

### Steps

#### 1. Clone the repository

``` bash
git clone https://github.com/Alelith/Collections.git
cd Collections
```

#### 2. Build the static library

``` bash
make library
```

This will compile the utility functions from `src/` and create the static library `libcollections.a` in `build/lib/`.

#### 3. Using the library in your project

To use this library in your own C++ project:

**A. Copy the necessary files:**

``` bash
# Copy the entire include directory to your project
cp -r /path/to/Collections/include /path/to/your/project/

# Copy the compiled static library
cp /path/to/Collections/build/lib/libcollections.a /path/to/your/project/lib/
```

**B. Compile your project with the library:**

``` bash
# Basic compilation command
g++ -std=c++17 -I./include your_code.cpp -L./lib -lcollections -o your_program
```

**Example project structure:**
```
your_project/
├── include/           # Copied from Collections
│   ├── super_lib.hpp
│   ├── linear/
│   ├── tree/
│   └── standard_functions/
├── lib/
│   └── libcollections.a  # Copied from build/lib/
├── your_code.cpp
└── Makefile (optional)
```

**Example Makefile for your project:**

``` makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
LDFLAGS = -L./lib -lcollections

TARGET = your_program
SOURCES = your_code.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

clean:
	rm -f $(TARGET)
```

**Note:** Most of the library is header-only (template implementations). The static library `libcollections.a` contains only the compiled utility functions (`check.cpp` and `conversion.cpp`). For template-based containers (Vector, LinkedList, etc.), no linking is required—simply include the headers.

---

## ▶️ Execution

### Build All Tests

``` bash
make all
```

This compiles all test executables and places them in the `build/` directory.

### Run All Tests

``` bash
make test
```

This builds and runs all unit tests with colored output showing test results.

### Run Individual Tests

``` bash
./build/test_vector
./build/test_linked_list
./build/test_stack
# ... etc
```

### Generate Documentation

``` bash
doxygen Doxyfile
```

Generated HTML documentation will be available in the `html/` directory. Open `html/index.html` in a browser to view.

### Clean Build Artifacts

``` bash
make clean
```

---

## 🧪 Usage Examples

### Vector Example

``` cpp
#include "super_lib.hpp"

int main() {
    // Create a vector of integers
    Vector<int> numbers;
    
    // Add elements
    numbers.push_back(10);
    numbers.push_back(20);
    numbers.push_back(30);
    
    // Access elements
    std::cout << "First element: " << numbers[0] << std::endl;
    
    // Iterate using range-based for
    for (const auto& num : numbers) {
        std::cout << num << " ";
    }
    
    // Check size and capacity
    std::cout << "Size: " << numbers.size() << std::endl;
    std::cout << "Capacity: " << numbers.capacity() << std::endl;
    
    return 0;
}
```

**Expected output:**
```
First element: 10
10 20 30 Size: 3
Capacity: 4
```

### LinkedList Example

``` cpp
#include "super_lib.hpp"

int main() {
    LinkedList<std::string> names;
    
    // Add elements
    names.push_back("Alice");
    names.push_back("Bob");
    names.push_front("Charlie");
    
    // Iterate with iterator
    for (auto it = names.begin(); it != names.end(); ++it) {
        std::cout << *it << " ";
    }
    
    return 0;
}
```

**Expected output:**
```
Charlie Alice Bob 
```

### Stack Example

``` cpp
#include "super_lib.hpp"

int main() {
    Stack<int> stack;
    
    // Push elements
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    // Pop and display
    while (!stack.empty()) {
        std::cout << stack.top() << " ";
        stack.pop();
    }
    
    return 0;
}
```

**Expected output:**
```
3 2 1 
```

### Character Validation Example

``` cpp
#include "super_lib.hpp"

int main() {
    char ch = 'A';
    
    if (is_alpha(ch)) {
        std::cout << ch << " is alphabetic" << std::endl;
    }
    
    if (is_upper(ch)) {
        std::cout << ch << " is uppercase" << std::endl;
    }
    
    return 0;
}
```

**Expected output:**
```
A is alphabetic
A is uppercase
```

### Type Conversion Example

``` cpp
#include "super_lib.hpp"

int main() {
    // Integer to string with different bases
    std::string binary = to_string(42, 2);
    std::string hex = to_string(42, 16);
    
    std::cout << "42 in binary: " << binary << std::endl;
    std::cout << "42 in hex: " << hex << std::endl;
    
    // String to integer
    int num = to_int("123");
    std::cout << "String to int: " << num << std::endl;
    
    return 0;
}
```

**Expected output:**
```
42 in binary: 101010
42 in hex: 2A
String to int: 123
```

---

## 🧾 Tests

The library includes comprehensive unit tests for all components.

### Run all tests:

``` bash
make test
```

### Run individual test suites:

``` bash
make all
./build/test_vector
./build/test_linked_list
./build/test_double_linked_list
./build/test_stack
./build/test_queue
./build/test_deque
./build/test_check
./build/test_conversion
```

### Test output:

Each test file produces colored output indicating:
- 🔵 Test group being executed
- ✅ Passed tests (green)
- ❌ Failed tests (red, with assertion details)

When all tests pass, you'll see:
```
================================
✓✓✓ ALL TESTS PASSED ✓✓✓
================================
```

### Test coverage includes:

- Constructors (default, fill, copy, move)
- Assignment operators
- Element access and modification
- Insertion and deletion operations
- Iterator functionality
- Capacity management
- Edge cases and error handling
- Memory leak prevention

---

## 📖 Documentation

The complete code documentation is generated with Doxygen.

🔗 **Documentation:** Open `html/index.html` after generating documentation

To generate documentation locally:
```bash
doxygen Doxyfile
```

The documentation includes:
- Detailed API reference for all classes and functions
- Module organization and relationships
- Usage examples and code snippets
- Implementation details and complexity notes
- Template parameter descriptions
- Exception specifications

Documentation is organized into modules:
- **Linear Container Module:** Vector, LinkedList, DoubleLinkedList, Stack, Queue, Deque
- **Tree Module:** BinaryTree (in progress)
- **Character Validation Module:** Character type checking functions
- **Type Conversion Module:** Numeric and string conversion utilities

---

## 🧭 Learnings & Future Improvements

### Key Learnings:
- Implementing template-based generic data structures in modern C++
- Memory management with RAII principles and smart pointer patterns
- STL-compatible iterator design and implementation
- Exception-safe programming techniques
- Comprehensive unit testing strategies
- API documentation best practices with Doxygen

### Future Improvements:
- Complete binary tree implementation with traversal algorithms
- Add support for C++20 features (concepts, ranges)
- Implement additional containers (hash map, set, priority queue)
- Performance benchmarking against STL containers
- Thread-safe container variants
- Custom allocator support
- Enhanced error reporting with custom exception types
- Integration with CMake build system

---

## 🤝 Contributing

Contributions are welcome! If you'd like to contribute to this project, please follow these steps:

1. **Fork** the repository
2. **Create** a new branch (`git checkout -b feature/YourFeature`)
3. **Commit** your changes (`git commit -m 'Add some feature'`)
4. **Push** to the branch (`git push origin feature/YourFeature`)
5. **Open** a Pull Request

Please make sure to:
- Follow the existing code style (C++17 standard)
- Write clear commit messages
- Add tests for new features
- Update documentation as needed
- Ensure all tests pass before submitting

---

## 🤝 Credits

-   C++ Standard Template Library (STL) design patterns
-   Doxygen documentation system
-   Educational resources on data structures and algorithms

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

The MIT License allows you to freely use, modify, and distribute this software, provided that the original copyright notice and license terms are included in all copies or substantial portions of the software.

---

## 👩‍💻 Author

**Lilith Estévez Boeta**  
💻 Backend & Multiplatform Developer  
📍 Málaga, Spain

🔗 [GitHub](https://github.com/Alelith) | [LinkedIn](https://www.linkedin.com/in/alelith/)

---

<p align="center">
  <b>⭐ If you like this project, don't forget to leave a star on GitHub ⭐</b>
</p>
